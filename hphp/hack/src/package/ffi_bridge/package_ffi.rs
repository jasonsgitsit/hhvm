/**
 * Copyright (c) Meta, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the "hack" directory of this source tree. An additional
 * directory.
 *
 */
use cxx::CxxString;

#[cxx::bridge(namespace = "HPHP::package")]
mod ffi {
    #[derive(Default)]
    struct PackageInfo {
        packages: Vec<PackageMapEntry>,
        deployments: Vec<DeploymentMapEntry>,
        errors: Vec<String>,
    }
    struct PackageMapEntry {
        name: String,
        package: Package,
    }
    struct Package {
        uses: Vec<String>,
        includes: Vec<String>,
        soft_includes: Vec<String>,
        include_paths: Vec<String>,
    }
    struct DeploymentMapEntry {
        name: String,
        deployment: Deployment,
    }
    struct Deployment {
        packages: Vec<String>,
        soft_packages: Vec<String>,
        domains: Vec<String>,
    }
    extern "Rust" {
        pub fn package_info(package_v2: bool, packages_toml: &CxxString) -> PackageInfo;
    }
}

pub fn package_info(package_v2: bool, packages_toml: &CxxString) -> ffi::PackageInfo {
    // HHVM should not perform validation of include_paths, so invoking from_text_non_strict
    let s = package::PackageInfo::from_text_non_strict(package_v2, &packages_toml.to_string());
    match s {
        Ok(info) => {
            let convert = |v: Option<&package::NameSet>| {
                v.map(|v| v.iter().map(|v| v.get_ref().clone()).collect())
                    .unwrap_or_default()
            };
            let packages = info
                .packages()
                .iter()
                .map(|(name, package)| {
                    let package_ffi = ffi::Package {
                        uses: convert(package.uses.as_ref()),
                        includes: convert(package.includes.as_ref()),
                        soft_includes: convert(package.soft_includes.as_ref()),
                        include_paths: convert(package.include_paths.as_ref()),
                    };
                    ffi::PackageMapEntry {
                        name: name.get_ref().to_string(),
                        package: package_ffi,
                    }
                })
                .collect();
            let deployments = info
                .deployments()
                .map(|deployments_unwrapped| {
                    deployments_unwrapped
                        .iter()
                        .map(|(name, deployment)| {
                            let deployment_ffi = ffi::Deployment {
                                packages: convert(deployment.packages.as_ref()),
                                soft_packages: convert(deployment.soft_packages.as_ref()),
                                domains: convert(deployment.domains.as_ref()),
                            };
                            ffi::DeploymentMapEntry {
                                name: name.get_ref().into(),
                                deployment: deployment_ffi,
                            }
                        })
                        .collect()
                })
                .unwrap_or_default();
            let errors = info.errors().iter().map(|e| e.msg()).collect();
            ffi::PackageInfo {
                packages,
                deployments,
                errors,
            }
        }
        Err(_e) => ffi::PackageInfo::default(),
    }
}
