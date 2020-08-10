2020-08-08

# udev rules

`udev` is a Linux subsystem that supplies your computer with **device events**. This is useful because we can write scripts to perform tasks in response to device events. For example, we can load a driver when a certain USB thumb drive is plugged in. These scripts (known as **udev rules**) are stored in `/etc/udev/rules.d` and look like `<number>-<name>.rules`. An example would be `/etc/udev/rules.d/99-jlink.rules`

## Brief History

- `/dev` is populated with file-like device **nodes** which refer to certain devices in the system (e.g. the X server listens to `/dev/input/mice`)

- The way to manage `/dev` has changed over the years, but the most modern solution is `udev`.
- `udev` relies on matching information provided by `sysfs` with **rules** provided by the user.
- The kernel uses `sysfs` to export information about the devices currently plugged into the system. `sysfs` is mounted at `/sys`, and these two terms are used interchangeably.

## Use Cases

- Rename a device node from the default name to something else
- Provide a persistent name for a device node by creating a symbolic link to the device node.
  - For example, when a Nintendo Pro Controller is plugged in, it may show up as `/dev/hidraw0` or `/dev/hidraw1`. However, we can map the controller's unique serial number to a symbolic link with a persistent name (e.g. Plugging in controller with serial number `0x1234` will always create `/dev/myController -> /dev/hidrawX`, where `X` could theoretically be any number).
- Change permission and ownership of a device node
- Launch a script when a device node is added (plugged in) or removed (unplugged)

## Writing Rules

### Rules Parsing

- `udev` reads the `.rules` files in `/etc/udev/rules.d` in lexical order
- A device **can** be matched by more than one rule. For example, if there are two rules attempting to create its own alternate name for a device, both names will be created.

### Rule Syntax

- Matches are AND combined, meaning: `a==b,c==d,do action`
- Available matches can be queried by using `udevadm info`, including
  - `KERNEL` - kernel name
  - `SUBSYSTEM` - subsystem
  - `DRIVER` - driver
  - `ATTR`- sysfs attribute
- To match something from a parent device, `S` must be appended to the key. For example, if a parent's kernel name is `"DEADBEEF"`, the match `KERNELS=="DEADBEEF"`must be used.
- `action` includes, but is not limited to,
  - `NAME` - name to use for the device node
  - `SYMLINK`- symbolic links to the device node
  - `RUN` - execute a script

### String Substitution

`udev` provides special tokens that expand to useful values. Suppose we are dealing with a device with a kernel name called `sda3`:

- `%k` evaluates to the kernel name, or `sda3`

- `%n` evaluates to the kernel number, or `3`

## Sysfs Tree

- `sysfs` is a tree-like structure where each "node" is a directory with one or more attributes and  possibly, a symbolic link to its parent node.
- Only directories with a file called `dev` have a corresponding device node

## References

- http://www.reactivated.net/writing_udev_rules.html
