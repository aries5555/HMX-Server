--�㷨��ʹ��lua�﷨�Լ�����.
----------------------------------------------------------

--level  ��ɫ�ȼ�
--lastonlinetime  ��������ʱ��(��λ����)
function cangetsalary(level,lastonlinetime)
	if level >= 100 and lastonlinetime >=60*60  then
		return 30000;
	end
	if level >= 80 and lastonlinetime >=60*60  then
		return 20000;
	end
	if level >= 60 and lastonlinetime >=60*60  then
		return 10000;
	end
end

--level  ��ɫ�ȼ�
--needexp  ����һ����Ҫ�ľ���
--exploit  ��Ҫ�һ���ѫֵ
function exploit2exp(level,needexp,exploit)
	return  (level * 5) * exploit;
end

--level  ��ɫ�ȼ�
--needexp  ����һ����Ҫ�ľ���
--grace   ��Ҫ�һ����Ĳ�ֵ
function grace2exp(level,needexp,grace)
	return  (level * 5) * grace;
end