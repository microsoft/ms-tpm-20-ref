# Guidelines for reporting bugs:
Non-security-critical bugs can be filed on the Issues tracker:

https://github.com/Microsoft/ms-tpm-20-ref/issues

Security sensitive bugs should be reported to secure@microsoft.com

# Guideline for submitting changes:


This repository tracks official TPM Library Specification releases and errata from
the Trusted Computing Group:

https://trustedcomputinggroup.org/tpm-library-specification/

All changes to core TPM logic, particularly changes to files in
TPMCmd/tpm and its subdirectories, must be approved by TCG voting
members.  Github pull requests may be used to propose changes, but changes
will not be incorporated without TCG member approval.

Other changes (e.g. new files or changes to TPMCmd/Platform or TPMCmd/Simulator),
particularly to support new platforms, scenarios, build environments or
crypto-libraries, will be considered if they are expected to be widely useful.

Contributors that wish to be involved in
the future evolution of the TPM specification and reference implementation
should consider joining the Trusted Computing Group.  Information about
membership and liaison programs is available at https://trustedcomputinggroup.org/membership/

