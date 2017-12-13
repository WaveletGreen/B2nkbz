prompt PL/SQL Developer import file
prompt Created on 2017年10月11日 by Administrator
set feedback off
set define off
prompt Dropping B2NKBZ_HEADTABLE...
drop table B2NKBZ_HEADTABLE cascade constraints;
prompt Dropping B2NKBZPZZ...
drop table B2NKBZPZZ cascade constraints;
prompt Dropping B2NKBZZZZ...
drop table B2NKBZZZZ cascade constraints;
prompt Creating B2NKBZ_HEADTABLE...
create table B2NKBZ_HEADTABLE
(
  b2nkbz_headtable_id NUMBER(10) not null,
  b21                 NVARCHAR2(255),
  b22                 NVARCHAR2(255),
  b23                 NVARCHAR2(255),
  b24                 NVARCHAR2(255),
  b25                 NVARCHAR2(255),
  b26                 NVARCHAR2(255),
  b27                 NVARCHAR2(50),
  b28                 NVARCHAR2(255),
  b29                 NVARCHAR2(255),
  b210                NVARCHAR2(255),
  b211                NVARCHAR2(255)
)
tablespace SYSTEM
  pctfree 10
  pctused 40
  initrans 1
  maxtrans 255
  storage
  (
    next 16K
  );
comment on table B2NKBZ_HEADTABLE
  is '内控标准-头表';
alter table B2NKBZ_HEADTABLE
  add constraint PK_B2NKBZ_HEADTABLE_ID primary key (B2NKBZ_HEADTABLE_ID)
  using index 
  tablespace SYSTEM
  pctfree 10
  initrans 2
  maxtrans 255;

prompt Creating B2NKBZPZZ...
create table B2NKBZPZZ
(
  b2nkbzpzz_id        NUMBER(10) not null,
  b2nkbz_headtable_id NUMBER(10) not null,
  b212                NVARCHAR2(255),
  b213                NVARCHAR2(255),
  b214                NVARCHAR2(255),
  b215                NVARCHAR2(255),
  b216                NVARCHAR2(255),
  b217                NVARCHAR2(255),
  b218                NVARCHAR2(255),
  b219                NVARCHAR2(255),
  b220                NVARCHAR2(255),
  b221                NVARCHAR2(255),
  b222                NVARCHAR2(255),
  b223                NVARCHAR2(255),
  b224                NVARCHAR2(1024)
)
tablespace SYSTEM
  pctfree 10
  pctused 40
  initrans 1
  maxtrans 255
  storage
  (
    next 16K
  );
comment on table B2NKBZPZZ
  is '内控标准-品质字表';
comment on column B2NKBZPZZ.b2nkbzpzz_id
  is '内控标准-品质ID，主键';
alter table B2NKBZPZZ
  add constraint PK_B2NKBZPZZ primary key (B2NKBZPZZ_ID)
  using index 
  tablespace SYSTEM
  pctfree 10
  initrans 2
  maxtrans 255;
alter table B2NKBZPZZ
  add constraint FK_B2NKBZZZZ_HEADTABLE_ID foreign key (B2NKBZ_HEADTABLE_ID)
  references B2NKBZ_HEADTABLE (B2NKBZ_HEADTABLE_ID) on delete cascade;

prompt Creating B2NKBZZZZ...
create table B2NKBZZZZ
(
  b2nkbzzzz_id        NUMBER(10) not null,
  b2nkbz_headtable_id NUMBER(10) not null,
  b212                NVARCHAR2(255),
  b213                NVARCHAR2(255),
  b214                NVARCHAR2(255),
  b215                NVARCHAR2(255),
  b216                NVARCHAR2(255),
  b217                NVARCHAR2(255),
  b218                NVARCHAR2(255),
  b219                NVARCHAR2(255),
  b220                NVARCHAR2(255),
  b221                NVARCHAR2(255),
  b222                NVARCHAR2(255),
  b223                NVARCHAR2(255),
  b224                NVARCHAR2(255),
  b225                NVARCHAR2(1024)

)
tablespace SYSTEM
  pctfree 10
  pctused 40
  initrans 1
  maxtrans 255
  storage
  (
    next 16K
  );
comment on table B2NKBZZZZ
  is '内控标准-制造字表';
alter table B2NKBZZZZ
  add constraint PK_B2NKBZZZZ_ID primary key (B2NKBZZZZ_ID)
  using index 
  tablespace SYSTEM
  pctfree 10
  initrans 2
  maxtrans 255;
alter table B2NKBZZZZ
  add constraint FK_B2NKBZPZZ_HEADTABLE_ID foreign key (B2NKBZ_HEADTABLE_ID)
  references B2NKBZ_HEADTABLE (B2NKBZ_HEADTABLE_ID) on delete cascade;

-- Create sequence 
create sequence SEQ_B2NKBZ_HEADTABLE_ID
minvalue 1
maxvalue 9999999999
start with 1
increment by 1
cache 30
order;

-- Create sequence 
create sequence SEQ_B2NKBZPZZ_ID
minvalue 1
maxvalue 9999999999
start with 1
increment by 1
cache 30
order;

-- Create sequence 
create sequence SEQ_B2NKBZZZZ_ID
minvalue 1
maxvalue 9999999999
start with 1
increment by 1
cache 30
order;


prompt Disabling triggers for B2NKBZ_HEADTABLE...
alter table B2NKBZ_HEADTABLE disable all triggers;
prompt Disabling triggers for B2NKBZPZZ...
alter table B2NKBZPZZ disable all triggers;
prompt Disabling triggers for B2NKBZZZZ...
alter table B2NKBZZZZ disable all triggers;
prompt Loading B2NKBZ_HEADTABLE...
prompt Table is empty
prompt Loading B2NKBZPZZ...
prompt Table is empty
prompt Loading B2NKBZZZZ...
prompt Table is empty
prompt Enabling triggers for B2NKBZ_HEADTABLE...
alter table B2NKBZ_HEADTABLE enable all triggers;
prompt Enabling triggers for B2NKBZPZZ...
alter table B2NKBZPZZ enable all triggers;
prompt Enabling triggers for B2NKBZZZZ...
alter table B2NKBZZZZ enable all triggers;
set feedback on
set define on
prompt Done.
