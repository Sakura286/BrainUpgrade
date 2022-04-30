
# mySQL5 尝试修复

## 错误内容

第一次log结尾（2022.4.23）

```log
[27542s] The servers were restarted 897 times
[27542s] Spent 42433.133 of 11006 seconds executing testcases
[27542s] 
[27542s] Check of testcase failed for: rpl.rpl_multi_source_channel_map_stress
[27542s] 
[27542s] Completed: Failed 5/3516 tests, 99.86% were successful.
[27542s] 
[27542s] Failing test(s): sys_vars.innodb_numa_interleave_basic auth_sec.keyring_file_data_qa
[27542s] 
[27542s] Unstable test(s)(failures/attempts): rpl.rpl_row_until(1/2) perfschema.func_file_io(1/2) main.xa_prepared_binlog_off(1/2)
[27542s] 
[27542s] The log files in var/log may give you some hint of what went wrong.
[27542s] 
[27542s] If you want to report this error, please read first the documentation
[27542s] at http://dev.mysql.com/doc/mysql/en/mysql-test-suite.html
[27542s] 
[27542s] 1708 tests were skipped, 339 by the test itself.
```

第二次log结尾（2022.4.27）

```log
[27128s] The servers were restarted 902 times
[27128s] Spent 67653.679 of 15185 seconds executing testcases
[27128s] 
[27128s] Check of testcase failed for: innodb.update_time rpl.rpl_change_master_crash_safe
[27128s] 
[27128s] Completed: Failed 5/3516 tests, 99.86% were successful.
[27128s] 
[27128s] Failing test(s): auth_sec.keyring_file_data_qa sys_vars.innodb_numa_interleave_basic
[27128s] 
[27128s] Unstable test(s)(failures/attempts): gis.gis_bugs_crashes(1/2) main.server_uuid(1/2) perfschema.func_file_io(1/2)
[27128s] 
[27128s] The log files in var/log may give you some hint of what went wrong.
[27128s] 
[27128s] If you want to report this error, please read first the documentation
[27128s] at http://dev.mysql.com/doc/mysql/en/mysql-test-suite.html
[27128s] 
[27128s] 1708 tests were skipped, 339 by the test itself.
```

## 初步分析

测试的过程包括 testcase 与 test ，test 又分为 failing test 与 unstable test

两次测试共同的错误有
failing test: `sys_vars.innodb_numa_interleave_basic`与`auth_sec.keyring_file_data_qa`，
unstable test `perfschema.func_file_io`
应先着重解决这些错误

不同的错误有

- testcase
  - rpl.rpl_multi_source_channel_map_stress (第1次)
  - innodb.update_time (第2次)
  - rpl.rpl_change_master_crash_safe (第2次)
- unstable test
  - rpl.rpl_row_until (第1次)
  - main.xa_prepared_binlog_off (第1次)
  - gis.gis_bugs_crashes (第2次)
  - perfschema.func_file_io (第2次)

## 详细文本查看

查看对应文本：sys_vars.innodb_numa_interleave_basic

```log
[23765s] [ 55%] perfschema.start_server_innodb           w5 [ pass ]   2416
[23769s] [ 55%] sys_vars.innodb_numa_interleave_basic    w2 [ fail ]  Found warnings/errors in server log file!
[23769s]         Test ended at 2022-04-23 00:37:19
[23769s] line
[23769s] 2022-04-23T00:37:11.351718Z 0 [Warning] InnoDB: Failed to set NUMA memory policy to MPOL_INTERLEAVE: Function not implemented
[23769s] 2022-04-23T00:37:11.353680Z 0 [Warning] InnoDB: Failed to set NUMA memory policy of buffer pool page frames to MPOL_INTERLEAVE (error: Function not implemented).
[23769s] 2022-04-23T00:37:11.414028Z 0 [Warning] InnoDB: Failed to set NUMA memory policy to MPOL_DEFAULT: Function not implemented
[23769s] ^ Found warnings in /home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/2/log/mysqld.1.err
[23769s] ok
[23769s] 
[23769s]  - the logfile can be found in '/home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/log/sys_vars.innodb_numa_interleave_basic/innodb_numa_interleave_basic.log'
[23769s] 
[23769s] Retrying test sys_vars.innodb_numa_interleave_basic, attempt(2/2)...
[23769s] 
[23770s] [ 55%] sys_vars.require_secure_transport_windows_basic w4 [ skipped ]  Need windows
[23773s] [ 55%] perfschema.start_server_on               w5 [ pass ]   2423
[23774s] [ 55%] rpl.rpl_row_merge_engine 'row'           w8 [ pass ]   8785
[23774s] [ 55%] sys_vars.optimizer_trace_offset_max      w1 [ pass ]    132
[23779s] [ 55%] main.innodb_mrr                          w3 [ pass ]  18057
[23779s] [ 55%] sys_vars.innodb_numa_interleave_basic    w2 [ retry-fail ]  Found warnings/errors in server log file!
[23779s]         Test ended at 2022-04-23 00:37:29
[23779s] line
[23779s] 2022-04-23T00:37:22.517588Z 0 [Warning] InnoDB: Failed to set NUMA memory policy to MPOL_INTERLEAVE: Function not implemented
[23779s] 2022-04-23T00:37:22.519276Z 0 [Warning] InnoDB: Failed to set NUMA memory policy of buffer pool page frames to MPOL_INTERLEAVE (error: Function not implemented).
[23779s] 2022-04-23T00:37:22.577429Z 0 [Warning] InnoDB: Failed to set NUMA memory policy to MPOL_DEFAULT: Function not implemented
[23779s] ^ Found warnings in /home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/2/log/mysqld.1.err
[23779s] ok
[23779s] 
[23779s]  - the logfile can be found in '/home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/log/sys_vars.innodb_numa_interleave_basic/innodb_numa_interleave_basic.log'
[23785s] [ 55%] perfschema.setup_consumers_defaults      w4 [ pass ]     62

```

查看对应文本：auth_sec.keyring_file_data_qa

```log
[21408s] [ 35%] rpl.rpl_misc_functions 'row'             w8 [ pass ]  10311
[21415s] [ 35%] auth_sec.keyring_file_data_qa            w5 [ fail ]  Found warnings/errors in server log file!
[21415s]         Test ended at 2022-04-22 23:58:05
[21415s] line
[21415s] 2022-04-22T23:58:02.210725Z 7 [ERROR] Plugin keyring_file reported: 'Could not remove file / OS retuned this error: Device or resource busy'
[21415s] ^ Found warnings in /home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/5/log/mysqld.1.err
[21415s] ok
[21415s] 
[21415s]  - the logfile can be found in '/home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/log/auth_sec.keyring_file_data_qa/keyring_file_data_qa.log'
[21416s] 
[21416s] Retrying test auth_sec.keyring_file_data_qa, attempt(2/2)...
[21416s] 
[21431s] [ 35%] rpl.rpl_mixed_bit_pk 'row'               w8 [ pass ]  10678
[21431s] [ 35%] innodb_fts.mecab_sjis                    w3 [ skipped ]  Test fail to load mecab parser, please set correct 'loose_mecab_rc_file'.
[21434s] [ 35%] auth_sec.keyring_file_data_qa            w5 [ retry-fail ]  Found warnings/errors in server log file!
[21434s]         Test ended at 2022-04-22 23:58:24
[21434s] line
[21434s] 2022-04-22T23:58:20.026591Z 3 [ERROR] Plugin keyring_file reported: 'Could not remove file / OS retuned this error: Device or resource busy'
[21434s] ^ Found warnings in /home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/5/log/mysqld.1.err
[21434s] ok
[21434s] 
[21434s]  - the logfile can be found in '/home/abuild/rpmbuild/BUILD/mysql-5.7.34/build/mysql-test/var/log/auth_sec.keyring_file_data_qa/keyring_file_data_qa.log'
[21437s] [ 35%] main.locking_service                     w1 [ pass ]   8326
[21446s] [ 35%] rpl.rpl_ps 'mix'                         w2 [ pass ]  13973
```

## 依赖

```bash
error: Failed build dependencies:
libaio-devel is needed by mysql5-5.7.37-1.riscv64
libedit-devel is needed by mysql5-5.7.37-1.riscv64
libevent-devel is needed by mysql5-5.7.37-1.riscv64
libtirpc-devel is needed by mysql5-5.7.37-1.riscv64
lz4-devel is needed by mysql5-5.7.37-1.riscv64
mecab-devel is needed by mysql5-5.7.37-1.riscv64
multilib-rpm-config is needed by mysql5-5.7.37-1.riscv64
numactl-devel is needed by mysql5-5.7.37-1.riscv64
perl(JSON) is needed by mysql5-5.7.37-1.riscv64
perl-generators is needed by mysql5-5.7.37-1.riscv64
rpcgen is needed by mysql5-5.7.37-1.riscv64
time is needed by mysql5-5.7.37-1.riscv64
```

其中，mecab需要手动编译
