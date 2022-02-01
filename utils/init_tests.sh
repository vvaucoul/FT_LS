mkdir -p ../tests

mkdir ../tests/dir-with-
mkdir ../tests/dir_without_permission && chmod 000 ../tests/dir_without_permission
mkdir ../tests/empty_dir

ln -s ../srcs ../tests/LinkDirectory
ln -s ../ft_ls ../tests/link_ls
# ln -vs ../srcs/*.c ../tests/multipleLinks

touch ../tests/no_permission && chmod 000 ../tests/no_permission

ln -s ../ft_ls ../tests/hardLink_ls
ln -s ../ft_ls ../tests/hardLink_lsModed && chmod 744 ../tests/hardLink_lsModed

mkfifo ../tests/mkfifo

# mknod ../tests/mknod c 7 9
# mknod ../tests/mknod_minor c 0 256
# mknod ../tests/mknod_major c 254 0
# mknod ../tests/mknod_block b 12 7

mkdir -p ../tests/uids

### UID ###
touch ../tests/uids/setuid_foo
chmod u+s ../tests/uids/setuid_foo

touch ../tests/uids/setuid_foo2
chmod u+s ../tests/uids/setuid_foo2
chmod u+x ../tests/uids/setuid_foo2

### GID ###
touch ../tests/uids/setgid_foo
chmod g+s ../tests/uids/setgid_foo

touch ../tests/uids/setgid_foo
chmod g+s ../tests/uids/setgid_foo

touch ../tests/uids/setgid_foo2
chmod g+s ../tests/uids/setgid_foo2
chmod g+x ../tests/uids/setgid_foo2

mkdir ../tests/uids/setgid_dir
chmod g+s ../tests/uids/setgid_dir

### STICKY DIR ###
mkdir ../tests/uids/sticky_dir
chmod +t ../tests/uids/sticky_dir

mkdir ../tests/uids/sticky_dir_owner
chmod +t ../tests/uids/sticky_dir_owner
# chown root ../tests/uids/sticky_dir_owner
# chgrp docker ../tests/uids/sticky_dir_owner