.. _changelog:


#########
Changelog
#########


******************
0.0.4 (unreleased)
******************


******************
0.0.3 (2021-05-06)
******************

New Features
============
- Add full tensor construction from Abaqus stress and strain type ``NTENS`` vectors (:jira:`610`, :pull:`12`). By `Kyle
  Brindley`_.
- Add full tensor deconstruction to Abaqus stress and strain type ``NTENS`` vectors (:jira:`614`, :pull:`13`). By `Kyle
  Brindley`_.
- Add full Voigt matrix (9x9) contraction to Abaqus Voigt (6x6) matrix and (``NTENS`` x ``NTENS``) matrix (:jira:`615`,
  :pull:`14`). By `Kyle Brindley`_. 

Internal Changes
================
- Updates to documentation source for ReST style guide (:jira:`610`, :pull:`12`). By `Kyle Brindley`_.
- Add support for multi-host, multi-environment CI/CD (:jira:`646`, :pull:`15`). By `Kyle Brindley`_.


******************
0.0.2 (2021-04-30)
******************

Breaking changes
================
- Change Abaqus stress-type vector expansion function name to match the general purpose nature for both Standard and
  Explicit (:jira:`591`, :pull:`7`). By `Kyle Brindley`_.
- Change Abaqus stress-type vector contraction function name to match the general purpose nature for both Standard and
  Explicit (:jira:`592`, :pull:`8`). By `Kyle Brindley`_.
- Change Abaqus NTENS matrix contraction function name to match the general purpose nature for both Standard and
  Explicit (:jira:`593`, :pull:`9`). By `Kyle Brindley`_.


******************
0.0.1 (2021-04-13)
******************

Breaking changes
================

New Features
============

Bug fixes
=========

Documentation
=============
- First production release (:jira:`543`, :pull:`5`). By `Kyle Brindley`_.

Internal Changes
================
- Setup Jenkins PR builder:
  https://toolbox-jenkins.lanl.gov/view/VIPor%20and%20C++/job/abaqus_tools_Pull_Request_Builder/ (:jira:`540`,
  :pull:`4`). By `Kyle Brindley`_.
- Update change log for abaqus\_tools release versions and update repository tags (:jira:`539`, :pull:`3`). By `Kyle
  Brindley`_.
- Remove everything except the abaqus\_tools (:jira:`538`, :pull:`2`). By `Kyle Brindley`_.
- Update project name (:jira:`537`, :pull:`1`). By `Kyle Brindley`_.
- Creation from cpp_stub (:jira:`534`). By `Kyle Brindley`_.

Enhancements
============

