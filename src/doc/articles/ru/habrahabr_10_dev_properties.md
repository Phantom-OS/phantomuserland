� �������� ������ ��� �� ������, ������� ������ �� ����� ������� ������, ���, ��� �� �����, ���������� ������� � �� Unix-compatible ����������. �� ��, ����� ����� POSIX, �� ���-�� ���������� �������. ������� �� �����������, ������� ��� ��������, ������� ��� ��� ���� migration path. (�� � ������ ���� ���������, ��������� ������ �������� ����������� ����� "�� ������".) � �������� ���� ����� 1 ���� ���������� ������ ��������� quake 1 for Unix, ������� � ���� ����������.

� ��������, �����������, ��������� open/close/r/w/ioctl, � ��������� ��������, ��� ��������� ����������, �������� �������. � �������� ���������� ��� �������� ����� � ���������� (� ���������� � �������� ioctl) ��������� �������������� API, ������� �� �������� ��������� ���������� ��������� ����� ������ � ������� � ����� ������ ������������ ��������. ���� API, �������, ����� ���� �������� ������, �, � �����, ��� ������ - RFC, aka request For Comments.

����, API �� ������ ������������:

<source lang="cpp">
// returns name of property with sequential number nProperty, or error
errno_t listproperties( int fd, int nProperty, char *buf, int buflen );

errno_t getproperty( int fd, const char *pName, char *buf, int buflen );
errno_t setproperty( int fd, const char *pName, const char *pValue );
</source>

�������:

<ol>
	<li>������� �������� � ��������, ������ �����.</li>
	<li>������� �������� ������, ������ ������</li>
</ol>

��� �� ����� ����������, �� ������� ������������, ��� ���������/������ ������� - ������� ������, � ������ ��������� � ��� �������� ������ �������, �� � ���� ������������ ��������� ��� ������ ����� ������.

����� ��������� �������������� ���������, ��������, ���:

<source lang="cpp">
// returns name of property with sequential number nProperty, or error
errno_t listproperties( int fd, int nProperty, char *buf, int buflen );

// returns property id by name
errno_t property_by_name( int fd, int *nProperty, const char *name );


errno_t getproperty( int fd, int nProperty, char *buf, int buflen );
errno_t setproperty( int fd, int nProperty, const char *pValue );

// fast lane

errno_t getproperty_i32( int fd, int nProperty, int32_t *data );
errno_t setproperty_i32( int fd, int nProperty, int32_t data );
</source>

��� ����� ��� ���������� �������� �� ���������, ��� ioctl. 

��� ��� ������: ����� ������� ����� ������� (���� mode), ������� ��������� ����������� ������ ��������, �� ���� � �� ������ - mode /dev/myCrazyDriver ������ ������ �������, � mode /dev/myCrazyDriver name val ��������� �������� name � �������� val.

���������� ������ �������� (��� �������, �������, � ���� ���� ��������������� �������������� ��������������) ���� ��������:

<source lang="cpp">
static property_t proplist[] =
{
    { pt_int32, "leds", 0, &leds, 0, (void *)set_leds, 0, 0 },
};
</source>

��� ������ ��������� ��������, ������� ����� ��� int32, ����� � ���������� leds, � ���� ��� ����������, �� ������� ������� ������� set_leds.

� ���������� ����� pt_int32 �������� ������ pt_mstring - malloc'ed strings, ��� ���� �������� ������.

������, ���� �������, ����� �������� API ������������� ������ ���� ��������� �������� - ���� ��������, ��� ����� �� ������� �� ����������, ����, �������, ����������� �������������� ��� ���� �� ��������.

� ���� ���� ��� ��������� ���������� � ������������� POSIX-�, ������� ���, ��������� � 30-������ ������, ������� ������ ����������. ����� ����� - ���������.

������ �� ���������� (���� � �����, �� �� ��):

<ul>
	<li><a href="https://github.com/dzavalishin/phantomuserland/blob/master/include/kernel/properties.h">��������� ������ ����</a></li>
	<li><a href="https://github.com/dzavalishin/phantomuserland/blob/master/phantom/apps/mode/mode.c">������� mode</a></li>
	<li><a href="https://github.com/dzavalishin/phantomuserland/blob/c5ab56286ef098429a2bcef28da191118e0c6cbf/oldtree/kernel/phantom/keyboard.c#L425">������ �������� � ������� �������</a></li>
	<li><a href="https://github.com/dzavalishin/phantomuserland/blob/master/oldtree/kernel/phantom/properties.c">������� ����������</a></li>
</ul>

������� ���������, �� �������, ��� ��������, � ��������, ����� ��������� ��� ����� ���������, ����� �� ������ ��� ���������.
