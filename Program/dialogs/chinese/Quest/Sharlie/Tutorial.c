void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "你想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> 夏尔在船头, 阿隆索走近对话
		case "StartSailor":
			dialog.text = "风景不错, 嗯? ";
			link.l1 = "这该死的大海已经折腾了我两个月。 还没成功呢。 ";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "确实如此。 有时大海会提醒你我们有多渺小。 ";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "我发现海上只有两种状态: 无聊或恐惧。 这... 不一样。 ";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "哈! 第一次出海吗, 先生? 像这样风平浪静时, 谁都能当船长。 最好趁现在享受。 ";
			link.l1 = ""+GetFullName(pchar)+"。 记住, 我是贵族。 别叫我‘先生’。 ";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "哈! 第一次出海吗, 先生? 像这样风平浪静时, 谁都能当船长。 最好趁现在享受。 ";
			link.l1 = ""+GetFullName(pchar)+"。 记住, 我是贵族。 别叫我‘先生’。 ";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "哈! 第一次出海吗, 先生? 像这样风平浪静时, 谁都能当船长。 最好趁现在享受。 ";
			link.l1 = ""+GetFullName(pchar)+"。 记住, 我是贵族。 别叫我‘先生’。 ";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "如您所愿, 大人。 那么, 这是您的第一次航行吗, "+pchar.lastname+"大人? ";
			link.l1 = "很明显吗? 是的, 第一次。 我可不是为了狭窄的船舱和发霉的船上食物而生的。 ";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "一眼就能看出您是个陆地佬, 大人。 ";
			link.l1 = "注意你的言辞! 对一个有荣誉的人, 我会扔下手套要求决斗。 但对像你这样的农民 —我会直接割下你的耳朵。 ";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "在巴黎或许可以。 但在这里, 那样的话会被喂鱼。 我劝您别挥舞那把剑, 大人 —别让船长后悔让您带剑上甲板。 上一个惹麻烦的人被关进了货舱, 只给发霉的硬饼干和连老鼠都不愿碰的舱底水。 知道吗? 那可怜的混蛋到港后还得额外付钱。 ";
			link.l1 = "你能指望什么... 好吧, 忘了这场误会。 我得不断提醒自己这破船离卢浮宫远着呢。 ";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "嗯? 卢浮宫? 那是什么? ";
			link.l1 = "哈! 卢浮宫是少数人的宫殿。 舞会。 招待会。 阴谋诡计... ";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "啊... 那是妓院吧。 我们这儿多的是。 不能说专为少数人 —付了钱就是你的。 ";
			link.l1 = "哈! 你说得不算太错, 水手。 ";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "顺便说下, 我叫阿隆索。 您为什么来这天涯海角, 大人? 我猜您穿越大西洋不只是为了和一个水手吵架吧。 ";
			link.l1 = "我父亲病了, 不能离开我们在加斯科尼的庄园。 我被派来找我... 哥哥。 他来这儿办事, 之后就杳无音信。 ";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "为什么不派个可靠的人, 非要自己忍受海上的艰辛? ";
			link.l1 = "家庭优先。 我不能把家族的命运托付给随便一个人。 ";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "我本来想 —但父亲坚持必须是我。 不知道为什么。 ";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "你哥哥叫什么名字? ";
			link.l1 = "米歇尔.德.蒙佩尔。 ";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "你哥哥叫什么名字? ";
			link.l1 = "米歇尔.德.蒙佩尔。 ";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "德.蒙佩尔? 你却姓"+pchar.lastname+"? 怎么回事? ";
			link.l1 = "别那样看我。 我是合法儿子。 只是随了母亲的姓。 ";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "没什么可羞愧的。 您会适应的 —在新世界, 每个人都有故事。 比如我... ";
			link.l1 = "我没什么可羞愧的! 告诉我马提尼克的情况。 是大城市吗? 像图卢兹那样? ";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "城市? 哈! 马提尼克是个岛。 法国在加勒比最大的岛屿之一。 种着辛辣的咖啡, 开采地狱般的硫磺, 还孕育着世界上最美的女人。 要我说, 这组合不错。 ";
			link.l1 = "我对咖啡和硫磺没兴趣。 不过等等... 一个岛? 我怎么在整个岛上找我哥哥? ";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "别担心。 圣皮埃尔是个小镇 —当然不像卢浮宫, 但也不是丛林。 至于勒弗朗索瓦, 上帝保佑 —正派人不该去那里。 ";
			link.l1 = "如果必须去, 我就去找强盗。 米歇尔总是帮我摆脱麻烦。 现在该我了。 ";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "不错... 对一个陆地佬来说。 ";
			link.l1 = "你又来这套。 我们还要多久到这该死的马提尼克? ";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "五天。 ";
			link.l1 = "五天? ! ";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "至少五天。 如果遇到海盗 —可能根本到不了。 小安的列斯群岛水域很危险, 即使没有贵重货物。 ";
			link.l1 = "除了乘客之外! ";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "哈哈哈! 别担心。 最坏的情况, 我会亲自把您藏到货舱里 —没有海盗会想到在朗姆酒桶里找加斯科尼贵族! 毕竟我们不傻 —把活的加斯科尼人和朗姆酒放在一起。 那比火药爆炸还厉害, 哈哈哈! ";
			link.l1 = "哈! 幸好一个月前朗姆酒就喝完了! ";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "呃... 最好别大声说这种话。 人们可能会认为是您把朗姆酒喝光的。 ";
			link.l1 = "好吧, 阿隆索, 我不会的。 反正我也不喝那玩意儿。 至于你那在战斗前把我藏到货舱的‘好’计划 —不可能。 ";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "为什么不? ";
			link.l1 = "我是贵族, 剑术不错, 不会藏到货舱里。 ";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "如果有必要 —我会和其他人一起保卫船只。 还能怎样? ";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "我会自己决定何时战斗何时逃跑。 走着瞧。 ";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "哈。 也许你还有点本事。 但小心 —加勒比喜欢打脸那些趾高气扬的人。 您连海盗先头部队的第一次遭遇都活不下来。 该死, 圣皮埃尔城外某个衣衫褴褛的暴徒会在您反应过来前捅死您。 ";
			link.l1 = "你根本不了解我。 ";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "哈。 也许你还有点本事。 但小心 —加勒比喜欢打脸那些趾高气扬的人。 您连海盗先头部队的第一次遭遇都活不下来。 该死, 圣皮埃尔城外某个衣衫褴褛的暴徒会在您反应过来前捅死您。 ";
			link.l1 = "你根本不了解我。 ";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "哈。 也许你还有点本事。 但小心 —加勒比喜欢打脸那些趾高气扬的人。 您连海盗先头部队的第一次遭遇都活不下来。 该死, 圣皮埃尔城外某个衣衫褴褛的暴徒会在您反应过来前捅死您。 ";
			link.l1 = "你根本不了解我。 ";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "但我了解新世界和这里的人。 如果您不打算在账本后面枯萎或在总督府任职 —您需要从头学起。 ";
			link.l1 = "幸好我不打算久留。 ";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "您这么认为。 我们不常带乘客回欧洲。 有些人死了 —死于热病。 绞刑或子弹。 另一些人留下了 —永远。 我见过虚弱的贵族成为船长, 残忍的强盗成为受尊敬的种植园主。 还有杰出的军官 —变成身无分文的流浪汉。 ";
			link.l1 = "听起来很诱人, 但我会回法国。 有人在等我。 ";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "啊对, 没错。 生病的父亲? ";
			link.l1 = "这么说吧... 有位女士的丈夫真的不想让我在巴黎出现。 但几个月后 —激情会冷却。 ";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "哈哈哈! 那您来对地方了。 加勒比是躲避嫉妒丈夫的天堂。 时间过得很快。 过段时间 —您可能会成为水手! ";
			link.l1 = "更可能成为船长。 我恐怕不适合当普通水手, 体力劳动不是我的强项。 ";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "在法国, 人们靠出身统治。 但在船上 —船长是国王。 法官和上帝。 没人知道他经历了什么才戴上那顶帽子。 在这里, 每个人得到应得的。 就像我们在甲板上说的 —各得其所。 ";
			link.l1 = "胡说八道。 说到船长 —我需要和他谈谈, 特别是他一直在找我。 再见, 阿隆索。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// < —夏尔在船头, 阿隆索走近对话
		
		// --> 随时可以和阿隆索对话
		case "AlonsoWait":
			dialog.text = "您想问什么吗? ";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "我是平雄先生派来的。 ";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "没什么。 ";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "哈! 那个四眼也把您卷进来了? ";
			link.l1 = "四眼? ";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "见过他的眼镜吗? 没错! 但别误会 —船员们尊重平雄先生。 船上总是需要好医生。 他也是个体面的事务长。 ";
			link.l1 = "你和他有什么业务? ";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "呃... 抱歉, 但那是我们自己的事。 不过别担心 —我们没违反任何船上的规定。 ";
			link.l1 = "那普通法律呢? ";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "普通法律与我们无关。 那么, 他们给我算了多少? ";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40枚达布隆。 ";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50枚达布隆。 ";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60枚达布隆。 ";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "我需要再核对一下。 稍后再来。 ";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "钱在这里。 圣皮埃尔, 我来了! 哈哈哈! ";
			link.l1 = "... ";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "钱在这里。 圣皮埃尔, 我来了! 哈哈哈! ";
			link.l1 = "... ";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "钱在这里。 圣皮埃尔, 我来了! 哈哈哈! ";
			link.l1 = "... ";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// < —随时可以和阿隆索对话
		
		// --> 从欧洲来的船上的船长
		case "Captain":
			dialog.text = "啊, 夏尔。 不着急, 是吧? 当船长想说话时, 你应该立刻报到。 服从命令有困难? ";
			link.l1 = "我不习惯服从命令, 船长。 ";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "抱歉, 船长, 我被耽搁了。 ";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "已经很清楚了, 你的船 —你的规则。 ";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "Beta测试 (跳过教程并在马提尼克开始游戏) ";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "我不允许质疑我的权威。 你不知道海上乘客遭遇不幸有多常见。 你很幸运, 我有兴趣看到你安全抵达圣皮埃尔。 ";
			link.l1 = "你在说什么? ";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "接受道歉。 享受这一刻吧。 你不会经常看到这样的日落。 ";
			link.l1 = "你在说什么? ";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "很高兴看到你在这次航行中学到了东西。 船长的话就是法律 —有时甚至在岸上, 远离船只时也是如此。 ";
			link.l1 = "你在说什么? ";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "船长。 请按照航海礼仪称呼我。 ";
			link.l1 = "你在说什么, 船长? ";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "我想通知你, 我们已经降帆漂流。 不幸的是, 你抵达马提尼克的时间将推迟几天。 ";
			link.l1 = "但为什么, 船长? ";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "因为我决定如此。 ";
			link.l1 = "这和昨天遇到的前往那个... 叫什么来着... ";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "卡普斯特维尔。 听着, "+pchar.name+": 我们需要认真谈谈。 我邀请你到我的舱室用餐。 钟声很快会敲响 —那时我们将有时间像文明人一样交谈, 喝完船上最后一瓶酒。 ";
			link.l1 = "感谢您的邀请。 我很荣幸, 船长。 ";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "准备好后告诉我。 我们还有时间, 所以你可以在船上走走 —只是不要打扰我的船员工作。 ";
				npchar.SharlieTutorial_question_0 = true;
				// 现在可以从炮门射击
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "还有其他问题吗? ";
			link.l1 = "(结束谈话) 我准备好了, 船长。 和您一起 —我甚至会喝勃艮第! ";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "你通过望远镜在专注观察什么... 船长? ";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "船长, 我有幸和一个叫阿隆索的人交谈。 他在船上是什么职位? ";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "船长, 告诉我关于你的船。 是一艘小快船, 对吗? ";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "下次见, 船长。 ";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "没什么特别的, 只是扫视地平线。 漂流的船只很容易成为猎物。 ";
			link.l1 = "在找海盗? ";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "或者西班牙人。 我们悬挂法国国旗却没有护航, 小安的列斯群岛是真正的十字路口 —也是雅克.巴尔巴宗的地盘。 ";
			link.l1 = "那是谁? 总督? ";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "更糟 —海盗男爵之一。 这些绞刑犯组成了类似组织, 自称海岸兄弟会。 他们把加勒比分成六部分, 每部分派一个男爵, 这样就不会自相残杀。 ";
			link.l1 = "当局为什么不采取行动? ";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "你太天真了, "+pchar.name+"。 海盗存在只是因为地方当局允许他们在选定的港口维修和补给, 以换取一部分赃物。 我不想承认, 但实际上唯一在对付这黑死病的是西班牙人。 如果不是他们, 我们就得给船装备昂贵的大炮 —还要雇佣护航队。 ";
			link.l1 = "... ";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "高级水手。 我对他了解不多, 但可以告诉你: 如果每个人都有不可告人的秘密, 阿隆索的秘密能装满整个墓地。 ";
			link.l1 = "听起来你不信任他。 ";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "一点也不。 你认为为船员找到这样有经验的人容易吗? 至少需要 一 年和 一 个优秀的水手长才能把 一 群酒馆醉汉训练得像个船员。 此外, 阿隆索也是船员的代言人。 船长不必费心和下层船员交谈, 但忘记普通水手也有利益是愚蠢的 —甚至致命的。 必要时阿隆索代表他们。 ";
			link.l1 = "如果船员不满意会怎样? ";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "他们会绞死我, 而你只会被刺伤。 别这么苍白。 只要船员得到报酬。 食物。 酒和治疗 —船长和船员之间的合同就履行了。 我不拿他们的生命冒险, 不随意惩罚, 分享战利品, 有时用免费的酒和岸上假期宠他们。 这就是我们维持脆弱平衡的方式 —也是船总能到达目的地的原因。 ";
			link.l1 = "... ";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "你触动了我的神经, "+pchar.name+"! 我可以永远谈论我的宝贝。 三流, 二十门炮, 速度极快 —别被‘商船’这个词骗了! ";
			link.l1 = "我明白炮和速度的部分。 但‘等级’? ‘商船’? ";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "等级是按加农炮数量进行的松散分类。 七等几乎是条船, 而一等几乎是座堡垒。 但别在欧洲重复这个 —尤其是在海军军官面前。 ";
			link.l1 = "为什么不? 这是水手的笑话吗? ";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "他们会认为你是个彻头彻尾的傻瓜并嘲笑你。 事实是, 在任何严肃的海军中, 分级系统都不同, 只适用于战舰。 但在加勒比这里, 我们按自己的方式做事, 一如既往。 ";
			link.l1 = "你称你的船为‘商船’是什么意思? ";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "另一个松散的术语。 战舰 —更坚固, 射击更好。 袭击船 —抢劫就跑。 商船 —可以运载大量货物。 人员或加农炮, 但必须妥协, 否则速度会变得可笑。 还有多用途船, 但除了它们适应船主的需求外, 没什么好说的。 ";
			link.l1 = "你兴奋了, 船长。 ";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "我爱我的船, "+pchar.name+"。 ";
			link.l1 = "... ";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "嗯, 你运气好 —我只剩勃艮第了... 等等, "+pchar.name+"。 你从哪弄到我旧帽子的? ! \n等等。 嘿, 在桅杆顶! 上面怎么了? ";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "嗯, 你运气好 —我只剩勃艮第了\n等等。 嘿, 在桅杆顶! 上面怎么了? ";
			link.l1 = "... ";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// 提前上岸
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// < —从欧洲来的船上的船长
		
		// --> 船舱守卫对话
		case "OhrannikCabin":
			dialog.text = "原谅我, 德.莫尔先生, 但您不能进去。 ";
			link.l1 = "我以前去过船长的舱室。 你现在应该记住了。 ";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "唉, 我狡猾的计划失败了。 再见, 水手。 ";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "原谅我, 先生, 但情况变了。 ";
			link.l1 = "到底发生了什么? ";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "航程所剩无几, 船长不想让任何人拿走他的贵重物品, 消失在勒弗朗索瓦的强盗窝点。 ";
			link.l1 = "我怀疑船长下这样的命令时没考虑到我。 ";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "嗯... 您有道理。 而且您已经在船长的舱室吃过不止一次饭了。 请进, 德.莫尔先生。 ";
					link.l1 = "这才像话! ";
					link.l1.go = "OhrannikCabin_4";
					Notification_Skill(true, 12, SKILL_LEADERSHIP);
				}
				else
				{
					dialog.text = "含... 含沙射影? 我没有那个意思, 德.莫尔先生! ";
					link.l1 = "那你必须让我通过。 ";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "先生, 您肯定明白船长的舱室不是公共通道。 命令就是命令。 ";
					link.l1 = "该死, 我等不及回到陆地了。 这太屈辱了! ";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "先生, 我们已经讨论过了。 我不能让您通过。 ";
					link.l1 = "还是这么固执, 水手。 再见。 ";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				Notification_Skill(false, 12, SKILL_LEADERSHIP);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "呃... 好吧。 我想这也不会有什么大碍。 ";
			link.l1 = "这才像话! ";
			link.l1.go = "OhrannikCabin_4";
			Notification_Skill(true, 12, SKILL_LEADERSHIP);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "还有事吗, 先生? 我不能让您进去 —船长担心他的贵重物品。 ";
			link.l1 = "你是在暗示盗窃吗, 水手? 说话小心。 这纯粹是含沙射影! ";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "没什么, 水手。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// < —船舱守卫对话
		
		// --> 水手斥责激活绞盘的主角
		case "SailorWithWindlass_1":
			dialog.text = "嘿, 你这个贵族蠢货! 你在干什么, 想把魔鬼塞进绞盘里吗? ! \n你用高贵的脚踢了止动器! 打算把我们都送进海底吗? ! \n行行好 —除非是法国鼻涕, 否则别碰任何东西! ";
			link.l1 = "这到底是什么? ";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "这是绞盘, 你这个笨蛋。 用来起锚的。 如果不锁好 —它会把船撕成碎片, 或者把人卷得像桶里的鲱鱼! ";
			link.l1 = "哈... 如果向另一边转 —就是放下锚, 对吗? ";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "不, 天才, 它能让时间倒流。 可惜你已经出生了! ";
			link.l1 = "好吧, 没人受伤, 对吧? 船确实很复杂。 我会更小心的。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// < —水手斥责激活绞盘的主角
		
		// --> 水手斥责激活加农炮的主角
		case "SailorWithCannon_1":
			dialog.text = "你盯着那门大炮的长管, 就像之前盯着日落一样敬畏。 ";
			link.l1 = "我看你喜欢观察我, 阿隆索。 最好告诉我这军事工程的奇迹。 ";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "那是十六磅炮。 不是每艘战舰都有。 ";
			link.l1 = "用它容易命中吗? ";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "近距离 —我们能炸掉任何东西。 一百码内我们有把握。 再远  —mostly 是噪音和火焰, 但总比没有好。 ";
			link.l1 = "一百码 —敌人也能这么做。 ";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "没错。 但这取决于船员的配合和炮手的技术。 可惜我们的炮手睡着了 —他会给你上一整节课, 然后把你自己塞进炮里, 哈! ";
			link.l1 = "炮手是军官, 对吗? ";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "通常是。 没有至少一个半 competent 的炮手, 最好避免战斗 —不如把大炮扔海里跑掉。 \n商船船长很少携带比六磅炮更大的 —他们指望护航或运气。 \n这很公平: 没有重炮和弹药, 船航行更好, 有更多空间装货卖钱。 \n如果我们船长没在这些宝贝上挥霍, 我们可能还有些朗姆酒。 唉。 ";
			link.l1 = "船长不亲自指挥炮击吗? ";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "有好的炮手和船员, 他不需要。 但告诉你: 当船长亲自瞄准而不是在后甲板喊‘开火! ’时 —敌船会有更多洞。 ";
			link.l1 = "我能开一炮吗? ";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "谢谢你的精彩讲座, 阿隆索。 你真是海军智慧的宝库。 ";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "当然! 但还是别碰大炮, 别让船员紧张。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "开炮? 不太可能。 要开炮 —你需要船长的允许。 我现在就问他! ";
			link.l1 = "不必了! ";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "船-长! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "这里怎么了, 阿隆索? ";
			link.l1 = "... ";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "查尔斯先生建议开炮 —严格用于训练目的。 ";
			link.l1 = "... ";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "我以为你关心船员的利益, 阿隆索。 可你却提议我们叫醒下一班岗, 用最野蛮的方式把大家都吵醒? ";
			link.l1 = "... ";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "在我看来, 激起他们的斗志并做好准备是明智的。 我不喜欢我们在光天化日之下漂流。 可能会出事。 ";
			link.l1 = "... ";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "别咒我们! ... 好吧。 一炮。 空包弹。 ";
			link.l1 = "... ";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "玩得开心, "+pchar.name+"。 我们会叫醒船员... 由你买单, 哈哈哈! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// < —水手斥责激活加农炮的主角
		
		// --> 想喝朗姆酒的水手对话
		case "SailorWantRum":
			dialog.text = "耽误您一分钟, 先生? ";
			link.l1 = "说吧, 水手。 ";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "很高兴认识您, 先生。 我叫亨利。 有兴趣赚点小钱吗? ";
			link.l1 = "多少算‘小’钱? ";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "五百比索。 ";
			link.l1 = "多少? ! 你想让我为这么多钱做什么? 发动叛变? ";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "天哪, 先生! 没必要喊! ";
			link.l1 = "那是很多钱, 水手。 在巴黎能用那钱过上好日子。 ";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "啊, 我不会利用您的无知。 在加勒比这里, 500比索不算什么。 船长和商人带来这么多货物, 任何稍微有用的东西价格都飙升。 有时一把稀有刀剑的价格和一艘小船一样。 ";
			link.l1 = "太疯狂了。 ";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "我能说什么? 我们都在等情况稳定, 价格回归正常。 那么, 您有兴趣赚500比索吗? ";
			link.l1 = "首先, 我想知道是什么工作。 ";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "您肯定知道船上朗姆酒的不幸情况。 但我相信某处还有几瓶。 瓶装朗姆酒和桶装劣酒不同。 味道好, 防止中毒, 增强臂力和健康 —真正的宝藏。 尤其是在航行结束时, 当地平线开始让你发疯时。 ";
			link.l1 = "你会用它做什么? 为什么不自己找? ";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "我什么时候有时间? 我们人手不足, 我一人干三人的活。 至于朗姆酒, 我会转卖 —我会找到买家。 ";
			link.l1 = "好吧, 我尊重诚实的人。 ";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "那么, 您接这个活吗? 我需要三瓶。 ";
			link.l1 = "我试试, 但不保证。 ";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "我还是拒绝。 这种工作有失我的身份。 ";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "可惜, 但我不记恨。 晚上好, 先生。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // 等待朗姆酒
			dialog.text = "是的, "+pchar.lastname+"先生";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "这是你的三瓶朗姆酒。 ";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "亨利, 我有平雄先生给你的东西。 ";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "没什么。 ";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "总是很高兴为他效劳! 这次我该得多少? ";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28枚达布隆。 ";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35枚达布隆。 ";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42枚达布隆。 ";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "我需要再核对一下。 我会回来的。 ";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "谢谢您, "+pchar.lastname+"先生。 请代我向财务官问好。 ";
			link.l1 = "... ";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "谢谢您, "+pchar.lastname+"先生。 请代我向财务官问好。 ";
			link.l1 = "... ";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "谢谢您, "+pchar.lastname+"先生。 请代我向财务官问好。 ";
			link.l1 = "... ";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "谢谢您, "+pchar.lastname+"先生。 请代我向财务官问好。 ";
			link.l1 = "... ";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "谢谢您, "+pchar.lastname+"先生。 干得漂亮! ";
			link.l1 = "希望我也能顺利拿到报酬。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "您考虑过非货币报酬吗? ";
			link.l1 = "看来你不像自己声称的那么诚实。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "不, 不! 如果您要钱, 肯定会给您! 但我也可以分享一些知识。 ";
			link.l1 = "什么样的知识? ";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "我可以告诉您很多在学术书籍里学不到的航海知识。 ";
			link.l1 = "好吧, 给我上这辈子里最昂贵的一课。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "五百个建议换不来五百枚硬币。 我要拿钱。 ";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "给您, "+pchar.lastname+"先生。 再次感谢! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
			AddMoneyToCharacter(pchar, 500);
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "我真心希望, "+pchar.name+"先生, 我的课能派上用场。 您知道什么是航海吗? ";
			link.l1 = "说出来您可能不信, 我知道。 我甚至会认字。 航海就是确定空间位置并规划航线, 比如船只的航线。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "啊, 您说的是星星和海图。 不, 我不懂那些。 那是领航员或船长的事。 在这附近, 航海意味着驾驶和指挥船只的能力。 ";
			link.l1 = "‘这附近’指的是哪里? ";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "在加勒比海。 就是这样, 别问我为什么。 所以, 您的航海技术越好, 能驾驭的船只就越大! 如果驾驶超出您技术水平的船只, 您会失去专注力。 精力, 甚至健康! ";
			link.l1 = "听起来很危险。 奇怪的是, 我之前不知道这些也活下来了。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "您的航海技术越好, 能指挥的船只就越大! 如果驾驶过于先进的船只, 您会失去专注力。 精力, 甚至健康! ";
			link.l1 = "听起来很危险。 奇怪我居然不知道这些还活了这么久。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "幸运的是, 您不必精通所有事情。 您总可以雇佣一位优秀的领航员来弥补您的不足。 只要确保他们得到报酬并忠于您。 在超出您技术水平的船上失去领航员 —可不好玩。 ";
			link.l1 = "谢谢你的讲座, 亨利。 不确定是否用得上, 但我想知识总是多多益善。 ";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "不客气, "+pchar.lastname+"先生。 再次感谢您! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// < —与想喝朗姆酒的水手的对话
		
		// --> 与货舱老水手的对话
		case "OldSailor":
			dialog.text = "(唱) 米歇尔妈妈丢了她的猫... 谁在窗口呼喊, 谁来还她猫... ";
			link.l1 = "你在这里做什么, 水手? ? ";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "现在我就像米歇尔夫人 —在找猫。 只是我不喊 —她不喜欢大喊大叫。 ";
			link.l1 = "我今早看到她了 —又在抓我的靴子。 ";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "那算什么。 船长的靴子更惨。 您喜欢猫吗? ";
			link.l1 = "当然喜欢。 ";
			link.l1.go = "OldSailor_3";
			link.l2 = "不太喜欢。 ";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "说得通。 否则我们怎么对付那些该死的老鼠? ";
			link.l1 = "但你不能永远依赖猫, 对吧? 它们可是很任性的生物。 ";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "可惜了。 猫在船上很受喜爱和重视。 否则我们怎么对付那些该死的老鼠? ";
			link.l1 = "但你不能永远依赖猫, 对吧? 它们可是很任性的生物。 ";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "没错。 所以我们依赖砒霜。 只是在加勒比很难找到。 所以我们损失货物 —老鼠污染朗姆酒, 毁坏硬饼干, 啃食其他所有东西\n而我们的财务官说: ‘放宽心, 就像交易税’\n但我们知道真相: 他只是懒惰。 如果不是我们亲爱的尚塔尔, 船长早就让他住在货舱里自己抓老鼠了, 哈哈哈! ";
			link.l1 = "祝你找到猫好运。 我得走了。 ";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "等等, 先生。 普通水手通常只在甲板上看到贵族乘客, 但您却来到了这里 —一直下到货舱! ";
			link.l1 = "好奇心害死猫, 哈哈哈! ";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "对航海感兴趣, 是吗? ";
			link.l1 = "似乎每个船员都决心在靠岸前把我变成真正的水手。 ";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "不足为奇。 虽然大海给我们许多人带来的只有悲伤, 但我们热爱自己的工作。 当新人表现出真正的兴趣时, 水手总是很高兴。 ";
			link.l1 = "... ";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "现在告诉我: 船长最重要的技能是什么? ";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "航海技术。 它决定了他能指挥的船只大小。 ";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "我不想撒谎 —我不知道。 ";
				link.l1.go = "OldSailor_9_1";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "别沮丧, 先生。 和船员谈谈, 探索一下船。 如果您找到答案 —我会和您分享一些真正有趣的事情。 就像对待自己人一样。 ";
			link.l1 = "我会记住的。 再见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "正确! 现在有个更难的问题: 横帆还是纵帆 —哪个更好? ";
			link.l1 = "很难说, 但我感觉有陷阱。 我会说各有优点。 ";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "又对了! 顺风时横帆很棒。 但纵帆装置可以抢风航行, 甚至捕捉侧风。 很高兴看到您没有浪费时间, 先生。 ";
			link.l1 = "不确定这些知识是否有用... 除非我想假装成真正的水手来打动上流社会的女士们, 哈哈哈! ";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "哦, 我不知道, "+pchar.name+"先生。 您或许是贵族 —但您对我们很体面。 我们很看重这一点。 船长在搞什么鬼。 一只黑猫从您面前穿过了。 ";
			link.l1 = "胡说八道。 你在说什么, 水手? ";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "有消息说, 他几天前刚随一艘过路船给卡普斯特维尔寄了封信\n然后就开始漂流 —就在航行即将结束时, 当每个人都在渴望靠岸的时候。 ";
			link.l1 = "我不在乎谣言。 何必呢? 我可以直接问他。 他不会拒绝一个贵族的直接提问。 ";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "您不了解他, "+pchar.name+"先生。 他会拒绝 —而且会巧妙地拒绝。 现在他很生气 —丢了钥匙。 ";
			link.l1 = "钥匙? ";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "他舱里箱子的钥匙。 我估计钥匙就在某个地方躺着。 ";
			link.l1 = "找钥匙? 我? ";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "这取决于您\n顺便说一句, "+pchar.name+"先生, 还有朗姆酒吗? 您肯定没把所有朗姆酒都给亨利吧, 哈哈哈! ";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "还有。 给你。 ";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "恐怕没有了。 能找到那三瓶已经是奇迹了。 ";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "说得对。 祝您好运, "+pchar.name+"先生。 我会继续找那只条纹无赖。 ";
			link.l1 = "也祝你好运, 水手。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "您为船员做了件好事, "+pchar.name+"先生。 这是给您的幸运小护身符! ";
			link.l1 = "一块有孔的石头? 真贴心。 ";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "尽管笑吧。 在海上, 护身符没坏处。 ";
			link.l1 = "你们水手真是一群迷信的人。 祝你好运。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "已经找到答案了? 船长最重要的技能是什么? ";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "航海技术。 它决定了他能指挥的船只大小。 ";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "还没有。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;
		
		// < —与货舱老水手的对话
		
		// --> 与需要炮弹箱的水手的对话 (保罗) 
		case "SailorNeedBox":
			dialog.text = "嘿, 小伙子! ";
			link.l1 = "你看起来不像我父亲。 谢天谢地。 ";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "哈! 我会为有这么高大高贵的儿子感到骄傲。 但我只能生出像我一样的凡夫俗子。 ";
			link.l1 = "好吧, 我接受这个赞美。 有什么麻烦? ";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "需要帮忙, 小伙子。 接到命令要在加农炮旁堆放炮弹 —以防在这危险水域遇到麻烦。 花了半个值班时间把这些铁疙瘩从货舱拖上来, 最后一箱把我的背累垮了。 ";
			link.l1 = "为什么不直接找你的伙伴? 我以为你们水手会互相帮助。 ";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "我们兄弟会最讨厌的就是无故搬运重物。 今天抽中了下下签 —从货舱拖炮弹箱。 糟糕的工作, 有失我这种水平水手的身份。 但能怎么办? ";
			link.l1 = "别抱怨了。 我来帮你。 至少我能看看这个大家一直威胁我的货舱。 ";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(运动员) 看到我腰上这把阔剑了吗? 它比你还重。 我去拿你的炮弹 —一点都不麻烦。 ";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "我不做体力劳动, 水手。 自己拖你的箱子。 ";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "谢谢, 小伙子。 只是别把背累坏了! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// 等待拿炮弹
			dialog.text = "怎么样了, 小伙子? ";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "这是你的炮弹。 还以为会更大些。 ";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "你叫保罗, 对吧? ";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "再见。 ";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "呃... 是-是的。 ";
			link.l1 = "平雄先生给我的名单上有你的名字。 ";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "呼, 刚才我还以为... 是的, 保罗 —是我。 你给我带了多少钱? ";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20枚达布隆。 ";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25枚达布隆。 ";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30枚达布隆。 ";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "我需要再核对一下。 稍后再来。 ";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "谢谢, 小伙子。 ";
			link.l1 = "... ";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "谢谢, 小伙子。 ";
			link.l1 = "... ";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "谢谢, 小伙子。 ";
			link.l1 = "... ";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "再大的话就成送给敌人的礼物了! 如果击中船体 —嗯, 也许只能溅起些木屑。 但如果击中船尾, 它会像球一样在甲板上弹得到处都是! ";
			link.l1 = "以前见过这种情况吗? ";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "亲眼见过, 小伙子。 人类真是擅长发明杀人机器。 比如葡萄弹 —射程短, 打不穿船体, 但能把十几个人直接送上下一个世界。 还有链弹 —击中帆, 把它们撕成碎片! 至于炸弹 —我什么都不说, 从没见过, 感谢上帝! 魔鬼的工具, 而且还很贵。 ";
			link.l1 = "我已经见识过炮弹的杀伤力了 —问问你可怜的背就知道。 ";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "好吧, 你帮了我一个大忙。 我会回报你的。 给 —几乎满瓶的上等朗姆酒, 哈哈哈! ";
			link.l1 = "你从哪弄来的? 我一直听说朗姆酒早就喝完了。 有这种好东西, 你本可以让任何人不仅拖一箱, 而是把货舱里所有箱子都拖上来。 ";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "就是这么碰巧, 小伙子。 谢谢, 再见。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// < —与需要炮弹箱的水手的对话
		
		// --> 与从事各类交易的军官对话
		case "OfficerTorgovets":
			dialog.text = "啊, "+pchar.lastname+"先生。 如果您打算睡觉 —那您运气不好。 我们的炮手已经占了您的床。 如您所知, 叫醒他相当棘手。 ";
			link.l1 = "我得说, 当他需要的时候 —听得可清楚了! ";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "不。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "那算什么。 听说Sharp的船员里曾经有个盲人炮手。 说他靠枪声瞄准。 ";
			link.l1 = "你今天异常健谈, 水手长先生。 ";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "这是有原因的! 我们很快就要上岸了 —是时候把剩下的货物换成叮当作响的比索了。 圣皮埃尔的妓院总是很高兴见到这些, 哈哈哈! ";
			link.l1 = "奇怪的是, 在船上做小生意的是你, 而不是财务官。 ";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "财务官不会和人打交道! 这就是水手长的作用 —能说会道又能干, 哈哈哈! 财务官当然有自己的计划 —但我不打算趟那浑水。 ";
			link.l1 = "今天有什么货? ";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "船上最后一瓶朗姆酒, 几个幸运符... 还有瞧! 一张完整的藏宝图。 ";
				link.l1 = "你应该当商人, 而不是水手长! 让我看看你有什么。 ";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "还有其他吗? ";
				link.l1 = "让我看看你有什么。 ";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "护身符? 就像你胸前挂的那个? ";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "抱歉... 您是说藏宝图? ";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "也许下次吧。 ";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "啊, 眼光锐利, 先生。 是的, ‘珊瑚头’ —好东西。 对我尤其有用。 如果我必须带领登船队 —它能帮我团结众人。 ";
			link.l1 = "你真的相信这个? ";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "我不必相信。 加勒比就是这样, 水手的命运也是如此。 护身符是有用的东西。 所以如果您要和我们一起干, 我建议您带几个 —应对不同场合。 ";
			link.l1 = "... ";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "哦是的。 在加勒比并不罕见。 有些人很幸运 —大赚一笔。 然后他们要么交税, 安静长寿地生活... 要么把金子藏在山洞里。 剩下的就是坟墓。 宝藏... 和一张纸片。 ";
			link.l1 = "就这样? ";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "不完全是。 地图很贵, 而且会吸引像您这样的其他寻宝者。 有时战利品几乎不够弥补麻烦。 就连伟大的阿尔伯特.布莱克伍德一开始也很艰难。 把寻宝作为您的职业 —找到的越多, 回报就越大。 如果您有幸运符 —那就更好了! ";
			link.l1 = "... ";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// < —与从事各类交易的军官对话
		
		// --> 与财务官军官的对话
		case "OfficerKaznachey":
			dialog.text = ""+pchar.lastname+"先生! 稍等一下。 ";
			link.l1 = "又来上课了, 平雄先生? 我没碰您珍贵的墨水! ";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "那您用什么在小本子上写字? 圣水? 乘客清单里没有墨水。 总之, 您现在有更大的麻烦。 ";
			link.l1 = "... ";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "还有二百比索 —赔偿损坏的绞盘。 锚缆断了。 ";
			dialog.text = "您还欠船国库三十比索 —赔偿您弄坏的雨水桶。 如果没有再次下雨, 您那洗衬衫的搞笑尝试会让您赔得更多。 "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "这正是我需要的 —下船就欠债。 给你。 ";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "这正是我需要的 —下船就欠债。 给你。 ";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "就这样? 这又不是赌债。 我有点忙 —您得等到我们靠港。 ";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "可惜。 那么 —谈正事。 我有个任务给您。 ";
			link.l1 = "您不太擅长与人打交道, 是吗? ";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "等一下, 让我数数。 ";
			link.l1 = "别忘了数我晚饭后留在桌上的面包屑。 ";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "恭喜。 船国库暂时没有您的问题了。 言归正传 —我有个任务给您。 ";
			link.l1 = "您不太擅长与人打交道, 是吗? ";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "与人打交道? 不太擅长。 但我擅长数字。 \n您呢, "+pchar.lastname+"先生 —您会数数吗? ";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(会计) 我对账本或汇票并不陌生。 我甚至知道零是什么意思。 ";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "足够把我父亲微薄的津贴撑过一个季度。 ";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "哦哦! 真遗憾您没早点告诉我 —这次航行本可以更有趣。 ";
			link.l1 = "您提到了任务? ";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "为了您自己好, 我希望您永远不要成为船主。 您会让自己破产 —还有船上的所有人。 ";
			link.l1 = "您提到了任务? ";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "是的。 不确定您是否知道, 财务官和医生 —地位仅次于船长。 \n" +
			"没有他们就起航是在拿您的钱冒险。 没有钱, 船只是一块非常昂贵的木头。 \n" +
			"即使是小帆船, 没有财务官也会让船长破产。 没有医生的第一场战斗可能会消灭整个船员 —触发雇佣和训练替代人员的漫长而昂贵的过程。 \n" +
			"对我们俩来说幸运的是, 我身兼二职。 这使我能够进行个人贸易, 并向船员请求轻微服务。 \n" +
			"当然, 我会慷慨支付 —现在正是时候。 \n" +
			"我希望您拿着这份名单, 这个达布隆箱子 —给船员发工资。 \n" +
			"严格按名单来! 这就是我问您是否会数数的原因。 ";
			link.l1 = "为什么您自己不做? 如果他们期待发工资 —让他们来找您。 ";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "现在要做的事太多了。 航行只剩下几天 —很快就会有一百个水手排队要求发工资。 ";
			link.l1 = "您提到了达布隆... ";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "西班牙金币。 硬通货。 真正的财富衡量标准。 只有最稀有。 最有价值的服务才用这些支付。 \n为了方便, 它们像这样存放在箱子里。 ";
			link.l1 = "我能从中得到什么? ";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(会计) 150比索, 再加5枚额外达布隆 —因为您几乎是我的同事。 而且您会得到比索和达布隆之间的公平汇率。 ";
			}
			else
			{
				dialog.text = "150比索, 还有将比索兑换成达布隆的能力。 不多, 但工作很简单。 ";
			}
			link.l1 = "好吧。 把名单和箱子给我。 ";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "我恐怕这种工作不适合我。 再见, 平雄先生。 ";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "您的选择。 请别挡我的路, "+pchar.lastname+"先生。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "给您。 看在上帝的份上 —别忘了从箱子里拿达布隆, 严格按名单来, 别私藏任何额外的。 我也希望您把空箱子还给我。 \n别把自己累坏了, 先生。 为什么带这么多垃圾? 我建议把一些东西藏在箱子里。 ";
			}
			else
			{
				dialog.text = "给您。 看在上帝的份上 —别忘了从箱子里拿达布隆, 严格按名单来, 别私藏任何额外的。 我也希望您把空箱子还给我。 ";
			}
			link.l1 = "如您所愿。 很快见, 平雄先生。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "进展如何? 都给他们发工资了吗? 拿到剩余的达布隆和空箱子了吗? ";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && PCharDublonsTotal() >= 18)
			{
				link.l1 = "都完成了。 ";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "还没有, 平雄先生。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "让我看看... ";
			link.l1 = "... ";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = PCharDublonsTotal();
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "您还说会数数。 您返回的达布隆比预期少。 这意味着我要做更多工作, 而不是更少 —这意味着您没有报酬。 ";
				link.l1 = "但您仍然会兑换达布隆吗? ";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "您还说会数数。 您带回的比应该的多。 这意味着我要做更多工作, 而不是更少 —这意味着您没有报酬。 ";
				link.l1 = "兑换呢? ";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "全部正确。 很高兴看到年轻一代仍然会数数。 谢谢您, "+pchar.lastname+"先生。 这是您的报酬 —还有一点奖金, 从一个专业人士到另一个。 ";
					link.l1 = "兑换呢? ";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "全部正确。 很高兴看到年轻人认真对待金钱。 谢谢您, "+pchar.lastname+"先生。 这是您的报酬。 ";
					link.l1 = "还在兑换吗? ";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "为什么不呢。 115比索换1达布隆。 如果您感兴趣, 来找我。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "当然。 105比索换1达布隆。 如果您感兴趣, 来找我。 \n让我给您一些建议: 如果命运让您负责一艘船, 首先雇佣财务官。 即使是一个糟糕的财务官也会为您节省一大笔钱。 ";
			link.l1 = "谢谢您, 平雄先生。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "当然! 100比索换1达布隆 —公平汇率。 加勒比的银行会收您更多。 \n让我给您一些建议: 如果命运让您负责一艘船, 首先雇佣财务官。 即使是一个糟糕的财务官也会为您节省一大笔钱。 ";
			link.l1 = "谢谢您, 平雄先生。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // 如果未完成任务, 则没收达布隆
			dialog.text = "闲逛呢, "+pchar.lastname+"先生? ";
			link.l1 = "您也被派到货舱了? ";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "我是船医, "+pchar.lastname+"先生! 很快病房里就会挤满伤员, 我见到的血会比任何战士都多。 而且即使我只是财务官, 也会在火线上占据自己的位置。 不, 唯一被送到舒适货舱休息的人是您。 ";
			link.l1 = "那您在这下面做什么? ";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "战斗还有几个小时才开始, 所以现在是结每日账目的最佳时间。 您拿着我的达布隆箱子, 德.莫尔。 请还给我。 ";
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "拿去吧。 别再到这下面来露面。 ";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "我把您的破烂忘在别处了。 ";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = PCharDublonsTotal();
			dialog.text = "我可没这个打算。 我不是旱鸭子 —货舱不是我的地方。 再见。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "别的地方... 我们战后在船长面前讨论这个。 到时候见。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "对达布隆感兴趣吗, "+pchar.lastname+"先生? ";
			link.l1 = "我们做笔交易吧。 ";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "现在不了。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// < —与财务官军官的对话
		
		// --> 水手报告逼近的船只
		case "Sailor_Trevoga":
			dialog.text = "船长, 警报! 地平线上有海盗! ";
			link.l1 = "... ";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "阿隆索, 请护送"+pchar.lastname+"先生到货舱。 并确保德鲁萨克先生醒着且炮手已准备好。 ";
			link.l1 = "船长, 我准备战斗! 贵族不能... ";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "如果我能帮上忙... ";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "等等, 这意味着没有勃艮第酒了? ..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "阿隆索, 把他弄出去。 动起来, 你们这些懒鬼! 升起船帆! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "阿隆索, 把他弄出去。 动起来, 你们这些懒鬼! 升起船帆! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "阿隆索, 把他弄出去。 动起来, 你们这些懒鬼! 升起船帆! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// < —水手报告逼近的船只
				
				// --> 与货舱海盗的对话
		case "EnemyPirate_1":
			dialog.text = "该死! 顽固的混蛋! ";
			link.l1 = "... ";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //用于西班牙语版本
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "你在这里做什么? ! 抛弃了你的船员, 躲起来逃避战斗, 你这个舱底老鼠? ! 我现在就把你开膛破肚! ";
			link.l1 = "爬进我货舱是糟糕的举动。 我会亲自把你开膛破肚。 ";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "你几乎站不稳了, 你身上的大部分血甚至都不是你的。 ";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(决斗者) 两个月。 我不得不把剑鞘收起来两个月。 我们来跳舞吧! ";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "呵呵。 那就来吧, 花花公子。 ";
			link.l1 = "... ";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "呵呵。 那我就没什么可失去的了。 ";
			link.l1 = "... ";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "你在胡言乱语什么? ! ";
			link.l1 = "两个月。 我不得不把剑鞘收起来两个月。 我们来跳舞吧! ";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// < —与货舱海盗的对话
		
		// --> 与幸存水手的对话
		case "SailorAlive_1":
			dialog.text = "至少你还活着... 我完了。 舵柄重重地撞了我一下... ";
			link.l1 = "发生了什么? ! ";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "我们被登船了。 啊-啊-啊! 顽固的混蛋! \n仔细听着: 我们守住了加农炮甲板, 但楼上的好戏才刚刚开始。 我发誓, 他们马上就会下来。 拿上散弹枪! 见鬼, 小心! 它装着弹药呢! ";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(神枪手) 别担心我。 任何尝试的人我都会在他们身上打洞。 ";
			}
			else link.l1 = "... ";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "里面有葡萄弹。 做得好, 你可以一次击倒两三个。 \n我相信你, "+pchar.name+"。 一旦你击退他们, 检查尸体。 也许你会找到给我的饮料... 否则我帮不上忙。 ";
			link.l1 = "坚持住, 阿隆索。 客人来了! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "好吧... 干得好, "+pchar.name+"。 你给我找到什么了吗? ";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "觉得就是这个。 不过看起来有点可疑。 ";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "还在找! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "相当不错, 哈哈哈! 谢谢, "+pchar.name+"。 那三个 —你解决得很好。 既然你是真正的贵族, 就来指挥吧。 我们一起可以守住这个甲板。 如果楼上的兄弟们也能做到 —这一天就是我们的了! ";
			link.l1 = "... ";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "好多了。 你装散弹枪了吗? ";
				link.l1 = "正在装... 为什么突然这么安静? ";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "既然你是真正的贵族, 就来指挥吧。 ";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "好多了。 你装散弹枪了吗? ";
			link.l1 = "正在装... 为什么突然这么安静? ";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "只是为了增加戏剧性。 即将开始。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// < —与幸存水手的对话
		
		// --> 战斗后与阿隆索的对话
		case "AfterBattle_Alonso_1":
			dialog.text = "我们在开始的地方结束了。 谢谢你救了我, "+pchar.name+"。 ";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "我想我们扯平了。 我甚至不记得你是怎么把我从那里拖出来的。 ";
			}
			else
			{
				link.l1 = "我想我们扯平了。 如果不是你和兄弟们, 我还会在那里。 ";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "你本可以按吩咐待在货舱里。 可惜船长没能活着给你一个恰当的责骂。 ";
			link.l1 = "我们不得不把他从一堆尸体下挖出来。 他放倒了多少恶棍? ";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "有人看到他放倒了三个。 其他人说有一打。 我想只有魔鬼才数得清。 ";
			link.l1 = "你还没告诉我这一切是怎么变成这样的。 ";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "有什么好说的? 我们的十六磅炮没能把我们从一艘海盗双桅船上救出来。 \n" +
			"它一下子就冲到我们面前, 在我们转向时用葡萄弹击中了我们, 并立即登船。 你应该看看甲板 —医生都没什么可做的了。 \n" +
			"与海盗战斗最糟糕的部分 —没有利润。 只有穷光蛋。 我们甚至无法夺取他们的双桅船。 ";
			link.l1 = "那么接下来会发生什么? ";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "船还在漂浮, 我们剩下的船员足以按计划把你送到圣皮埃尔, 在那里我会寻找新船长, 你会找到你哥哥并告诉他你所有的冒险经历。 接下来会发生什么 —只有上帝知道。 \n" +
			"但有一件事是肯定的 —你会和我们相处得很好。 对于一个陆地老鼠来说, 不错了, "+pchar.name+"。 ";
			link.l1 = "... ";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "哈! 你即将开始翻江倒海。 别害羞。 那只是恐惧离开你的身体。 欢迎来到加勒比! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// < —战斗后与阿隆索的对话
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}