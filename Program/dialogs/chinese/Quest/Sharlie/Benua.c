int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "很高兴见到你, 我的孩子。 你是来还债的吗? ";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "是的, 父亲。 我在这儿。 ";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "很抱歉耽搁了, 但我不是为那事来的。 不过很快就会轮到我, 别担心。 ";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "孩子, 你有什么需要的吗? ";
				link.l1 = "是的, 父亲。 我想见我的哥哥, Michel de Monper。 他说……";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "孩子, 你有什么需要的吗? ";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "是的, 神父。 我需要您的帮助。 我的名字是"+GetFullName(pchar)+"。 Michel de Monper建议我来找您谈谈。 ";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "“是的, 父亲。 我需要您的帮助。 我的名字是"+GetFullName(pchar)+"。 是我哥哥Michel de Monper建议我来找您的。 ";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "是的, 神父。 我需要一艘船去帮Michel, 可我刚到加勒比, 口袋里一分钱都没有。 我哥哥说您也许能借我点钱……";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "您好, 神父。  我们需要您的帮助——是个相当棘手的问题。 ";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "神父, 我凑够了钱。  八百金币。 ";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "您好, 孩子。  我猜你是来询问……咳, 你们的事情进展如何?";
				link.l1 = "您果然一如既往地睿智, 神父。  别卖关子了, 您的人查到了什么? ";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "是的, 父亲。 我需要您的帮助。 ";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "是的, 神父。 我在这儿。 ";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "没什么, 父亲。 ";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "孩子, 是什么风把你带到我这里来的? ";
			link.l1 = "您好, 神父。 有人建议我来找您谈谈。 我叫Charles de Maure。 我正在寻找Michel de Monper。 据我所知, 他应该在Martinique的某个地方。 我……是他的弟弟。 ";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper的弟弟? De Maure? 真奇怪……";
			link.l1 = "父亲, 我明白您的疑虑。 我们只是姓氏不同而已。 我的父亲是Henri de Monper。 ";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "啊—啊, 我明白了。 我以前可是亲自认识Henri de Monper的。 小伙子, 把脸转向光亮处。 对! 你和他长得一模一样。 相貌、气质都如出一辙! 很高兴在我们教区见到Henri de Monper的儿子。 \n至于你的问题, 我可以告诉你, Michel是马耳他骑士团的高级军官, 但他现在……遇到麻烦了。 幸运的是, 骑士团里有一位骑士正好在拜访我。 我想他也许愿意陪你一起去见你那倒霉的兄长, 愿主怜悯他的命运……";
			link.l1 = "这人是谁, 神父? ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "孩子, 明天早上再来吧。 现在我已经没什么可对你说的了。 ";
			link.l1 = "好吧。 ";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "你好, 孩子。 正如我昨天承诺的, 那位我提到的人已经在这里等你了。 他已经准备好带你去见你哥哥了, 据我所知, 你哥哥现在很可怜。 愿主怜悯他的灵魂……";
			link.l1 = "这人是谁, 神父? ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "是的, Charles, 这点我知道。 但我要让你失望了。 Michel不在这里。 ";
			link.l1 = "你说他不在这儿是什么意思? 他明明说会在你们教堂等我! 神父, 发生了什么事? 我哥哥在哪儿? ! ";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "孩子, 你哥哥昨晚很晚才离开我这简陋的小教堂。 至于他去了哪里, 我也不清楚。 不过, 他留下一封信给你。 ";
			link.l1 = "真不敢相信……我为他做了那么多! 把那封信给我! ";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "别这么激动, Charles。 信在这儿。 你先看看, 然后……然后我想和你谈谈。 但首先, 先读读你哥哥的信息。 ";
			link.l1 = "我都快等不及了! ";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "看来你已经读过那封信了。 现在, 我想跟你说点什么, Charles……";
				link.l1 = "可是……怎么可能? 这都是什么胡说八道? 我知道我哥哥有点怪, 但他可不是疯子! ";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "孩子, 先把信读了。 我们待会儿再谈。 ";
				link.l1 = "是的, 父亲……";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Charles, 你兄长的所作所为也让我大为震惊。 至今我仍感到困惑不解。 身为圣殿骑士与三位一体的忠诚仆人, 如今却像个逃兵一般行事。 ";
			link.l1 = "你知道导致这种奇怪行为的原因可能是什么吗? ";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "唉, 我并不知道。 但我想他一定有自己的理由, 极其深刻的理由。 要彻底否定自己的一切过往, 必然有着非同寻常的原因。 我甚至无法想象那会是什么。 但我觉得, 这里面一定牵扯到极其糟糕……甚至可怕的事情。 ";
			link.l1 = "父亲, 会是什么事呢? ";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "孩子, 神父并非用眼睛看世界, 而是用心去感受。 我无法用言语向你解释, 但……你哥哥踏上了一条不洁、肮脏的道路。 我从未想过自己会说出这样的话。 然而……";
			link.l1 = "嗯, 我可不怀疑我那哥哥又在盘算什么见不得人的勾当。 我甚至能猜到他到底想干啥。 这个“什么东西”嘛, 八成是黄灿灿、叮当作响的玩意儿。 ";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "我觉得你哥哥并不是被对黄金的渴望驱使的。 我倒觉得他追求的是更重要的东西。 ";
			link.l1 = "我从Michel那里学到了很多, 也领悟了他的处世之道, 所以我自认为能分辨他在乎什么、不在乎什么。 不过, 父亲, 您的教诲我会铭记在心。 ";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "愿上帝保佑你, 孩子。 去吧, 快去吧。 愿主时刻护佑你! ";
			link.l1 = "谢谢您, 父亲。 再见! ";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monper的弟弟? De Maure? 真奇怪……";
			link.l1 = "父亲, 我明白您的疑虑。 我们只是姓氏不同而已。 我的父亲是Henri de Monper。 ";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "啊—啊, 我明白了。 我曾经与Henri de Monper先生有过私交。 年轻人, 把脸转向光亮处……对! 你果然像他。 长相一样, 侧脸也有那股贵族气派! 很高兴在我们的教区见到Henri de Monper的儿子。 \n我已经听说Michel最近有位从欧洲来的男子拜访过, 但我怎么也没想到那竟然是他的亲弟弟。 希望你能帮到Michel, 他现在正经历一段艰难的时光。 那么, 我能为你做些什么? ";
			link.l1 = "Michel跟我说过, 如果我哪天跟当局闹了麻烦, 你一定能帮上忙。 ";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "这是Michel告诉你的吗? 明白了。 那么, 这种事情我或许能帮上忙。 我在神圣罗马教会和荷兰殖民地中有些影响力, 因此也许可以在你与西班牙及荷兰当局之间斡旋。 当然, 如果你的不当行为太过分, 我也无能为力—那种情况下只能帮你稍微减轻一些惩罚。 \n要想彻底和解, 需要多次斡旋。 此外, 无论如何, 你都得为慈善和航海开销向我提供一些金币。 此外, 我一次只能帮你解决一个国家的问题。 如果你能接受这些条件, 随时可以来找我, 我们再看看能做些什么。 ";
			link.l1 = "谢谢! 我会记住的。 ";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "孩子, 有什么我能帮你的? 尽管说吧, 我在听。 ";
			link.l1 = "Michel跟我说过, 要是我哪天跟当局闹出麻烦, 你一定能帮我一把。 ";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "孩子, 我能为你做些什么? ";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "我惹上了西班牙当局的麻烦。 ";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "俺惹上了荷兰当局的麻烦。 ";
				link.l2.go = "relation_hol";
			}
			link.l9 = "抱歉, 这次我想自己来处理。 ";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "所以, 那些高贵的先生们巴不得把你关进哈瓦那的地牢……";
			link.l1 = "正是如此, 父亲……";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "所以, 那些精明的商人都巴不得把你关进威廉斯塔德的地牢……";
			link.l1 = "正是如此, 父亲……";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "是的, 这些传闻我们教会也听说了。 我可以帮你解决这个难题, 这事并非无解。 你需要给我" + sTemp + ", 才能摆平你的困境。 ";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "太好了! 金子在这儿。 ";
					link.l1.go = "agree";
				}
				link.l2 = "那正好是俺去找金币的时候。 ";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "是的, 你那些“丰功伟绩”的传闻连我们教会都听说了。 孩子, 你已经玷污了自己的名声, 应该更加谨慎才是。 不过, 我可以帮你。 你需要拿出" + sTemp + ", 老夫才能帮你摆平这场麻烦。 ";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "太好了! 金币在这儿。 ";
						link.l1.go = "agree";
					}
					link.l2 = "那现在正是俺去找那些金币的时候。 ";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "是的, 孩子。 你和你哥哥一样绝望……看来这是你们家族的通病。 我无法彻底扭转局势, 但我相信至少能缓解你眼下的困境。 如果你愿意, 之后我们还可以再做更多祈祷。 现在我需要" + sTemp + ", 我会立刻着手帮你解决难题。 ";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "太好了! 金子在这儿。 ";
						link.l1.go = "agree";
					}
					link.l2 = "那正好是俺去找达布隆金币的时候。 ";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "现在你至少得等上两个星期。 我想在这段时间里, 我应该能见到合适的人并和他们谈谈。 ";
			link.l1 = "谢谢您, 父亲! 我会等着……";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? 你是Michel de Monper的弟弟? 真奇怪……";
			link.l1 = "我明白您的疑虑, 神父。 家父是Henri de Monper。 ";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "啊—我明白了。 我和Henri de Monper是旧识。 小伙子, 转过身来, 让我看看光线下的你。 没错! 一模一样的眼睛, 同样高贵的面容! 很高兴在我的教堂见到Henri de Monper的儿子。 希望你能帮帮你的兄弟, 他最近可真是时运不济啊。 ";
			link.l1 = "是的, 神父。 我需要一艘船去帮Michel, 可我刚到加勒比, 口袋里一分钱都没有。 我哥哥说您或许能借我点钱……";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "是Michel告诉你的? ";
			link.l1 = "神父, 或许我听起来不太可靠, 但这是真的。 老子越快弄到船, 就能越快把我哥哥从牢里救出来。 ";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "我明白了, 孩子。 我听得出来你说的是实话。 好吧, 看在Michel和你父亲的份上, 我会帮你一把。 我这里有些积蓄, 拿去吧。 我想五万比索和一百金币应该够了。 ";
			link.l1 = "谢谢您, 神父。 条件是什么? ";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "别紧张, 半年还清就够了。 ";
			link.l1 = "非常好, 神父大人。 再次感谢您! ";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "带着我的祝福去吧, 孩子。 ";
			link.l1 = "……";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "太好了, 孩子。 希望那笔钱对你有用。 ";
			link.l1 = "确实如此! 多谢! ";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, 真不敢相信是你! 你怎么会到这儿来? ! ";
			link.l1 = "仁慈的天父, 请赐我祝福, 因为我带来了好消息—我要结婚了, 我希望您能作为我的婚礼神父。 ";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "孩子, 这真是太好了! 所以你收到了你父亲的信, 然后像往常一样, 还是按照你自己的想法行事? 我真心为你高兴! 不过, 除非你决定就在这座教堂里结婚, 否则恐怕我也帮不上你。 ";
			link.l1 = "我听说您的任务陷入了僵局, 圣父? 有什么我能帮忙的吗? 既然婚礼将在西班牙教堂举行, 这样的冒险我当然乐意参与, 但我决心要在馬提尼克举办庆典。 要适度隆重, 还要有体面的见证人和尊贵的宾客在场。 ";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "很抱歉, 孩子, 但你所有的权威在天主教会最高阶层的固执面前毫无用处, 尤其是在西班牙殖民地。 我们国家之间关于如何分配天主教传教团影响力的问题上没有达成一致, 所以我现在才会以“尊贵的客人”和“尊贵的人质”的身份待在这里。 西班牙人正在等我们提出更好的条件。 我已经向欧洲发了消息, 希望两个月内能收到回复, 到时候我们就能重新开始谈判。 如果两个月还没消息, 半年内肯定会有。 \n还有, 虽然最近几周教皇和Mazarin已经达成了某种妥协, 但现在还远谈不上什么真正温馨的关系。 说实话, 我甚至不确定我们是否能达成任何协议。 在我看来, Palotti只是把我当作他政治博弈中的一个筹码。 不过, 我得承认, 那位宗教裁判官的咖啡确实一流! ";
			link.l1 = "我哪有六个月, 连两个月都没有! 我必须完成父亲的心愿, 否则他会强迫我结婚, 根本不管我同不同意。 而且他的身体也大不如前了, 我还想有时间把我心仪的姑娘介绍给他, 让他见见未来的Monper夫人。 ";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "恐怕你得另请一位神父来主持你的婚礼了, 孩子。 唉, 我还得在这里待很久。 ";
			link.l1 = "要是老子把你和宗教法庭官的咖啡分开, 你会怎么说? ";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "我非常乐意接受你的帮助。 我怀疑自己被选中执行这个任务并非偶然。 最坏的情况也不过是他们把Benoit神父忘了。 虽然主让我学会忍耐, 可我的结论依然让我感到沉重, 哪怕其中有些……恩赐。 但我还是要重复一遍—Palotti神父大概率不会听你的请求。 ";
			link.l1 = "那我就省点力气, 不再劝他了。 等弥撒一结束, 我们就直接离开教堂, 上我的船。 别犹豫了, 神父—他们已经看见我们见面了, 也认得我。 如果等我去总督府救你, 那可就难多了。 ";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "很危险啊, 孩子, 非常危险。 外面有一队卫兵等着护送我去官邸, 城里到处都是士兵。 ";
			link.l1 = "我们要打他们个措手不及, Benoit神父。 你只需要相信我, 一切都会顺利。 我在这方面……多少有点经验。 ";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "如你所愿。 但请务必避免无谓的流血! 我也曾有过类似的经历……带路吧, 孩子, 我会紧随其后。 不过我不会拿起武器, 所以别指望我出手。 ";
			link.l1 = "根本没想那么多, 父亲。 我能搞定。 跟着我走, 不过小心点, 他们可能会朝咱们开枪。 ";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "孩子, 我还没来得及感谢你救我出狱。 显然, 西班牙主教和宗教裁判官Palotti想破坏我们红衣主教与教廷刚刚建立的微妙关系, 所以你的所作所为完全符合我们国家的利益。 又一次。 不过, 除了我, 没人会对你说声“谢谢”。 ";
			link.l1 = "很平常的事, 神父大人。 能帮上忙我也很高兴。 不过, 我也有件事要问您, 还记得吧? ";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "当然! 那咱们说点开心的事吧—Charles, 你人生最重要的日子准备得怎么样了? ";
			link.l1 = "慢慢有点雏形了。 我见过筹备得更快更轻松的军事行动, 但这值得! ";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "当然可以, 我的孩子! 这次我还想问清楚一件事—你对你的婚礼仪式有什么想法? ";
			link.l1 = "你是说, 有多自大? ";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "当然! 因为我得去准备教堂, 而且, 也许你还想邀请一些重要的人。 ";
			link.l1 = "没什么特别的, 神父大人。 我认为的朋友们会在别处等我们。 这里只有几个官员、我的手下, 还有一些普通的看热闹的人。 ";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "那么, 我想我们用一笔小小的捐赠就能解决了。 ";
			link.l1 = "听起来也没多吓人。 那这种“捐赠”要多少金币? ";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "唱诗班、庄严仪式和其他开销—一百五十, 不多不少。 再加上新人的惯例捐赠, 总共—两百达布隆。 ";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "给您, 神父大人。 ";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "关于那些军事行动……我得去趟银行, 回来再说。 ";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "孩子, 你的捐赠呢? ";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "给您, 神父大人。 ";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "是是是, 我马上就拿来……";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "还有一个问题需要解决—谁会代表新娘, 将她交给新郎, 并为她作证婚人? ";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, 来自布鲁维尔德。 他是个英国人, 但很受人尊敬, 对Helen就像亲生女儿一样, 而Helen的养母是Gladys McArthur。 ";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "男爵 Noel Forget, 我相信他一定会赏脸。 ";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "菲利普·德·Poincy骑士, 我相信他一定会赏脸接见我。 ";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "那么, 谁来为新郎作证? 记住, 必须是出身高贵、声誉卓著的人。 ";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "男爵 Noel Forget, 我相信他一定会赏脸。 ";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "菲利普·德·Poincy骑士阁下, 我相信他一定会赏脸接见我。 ";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey—瓜德罗普的体面商人。 我只需要备好他最喜欢的酒就行。 ";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey—瓜德罗普的体面商人。 俺只需要给他备上他最爱的酒就行。 ";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "太好了, 我会立刻派人送出请柬, 不过宾客们还需要些时间才能赶到。 我想一个月内一切都会准备妥当, 指定的人选也都会抵达城里。 ";
			link.l1 = "太好了! 那我正好有时间去办点事。 很快再见, 神父, 祝我好运吧! ";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "太好了, 我这就去发请柬, 不过宾客们还需要些时间才能赶到。 我想一个月内一切都会准备妥当, 指定的人也都会到城里了。 ";
			link.l1 = "太好了! 那我还有时间去办点事。 很快再见, 神父, 祝我好运吧! ";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "太好了, 我会立刻发出请柬, 不过宾客们需要些时间才能赶到。 我想一个月内一切都会准备妥当, 指定的人也都会到达城里。 ";
			link.l1 = "太好了! 那我还有时间去办点事。 很快再见, 圣父, 祝我好运吧! ";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "所以, 这一天终于来了, 我的儿子! 一切都准备妥当—再过几个小时我们就能开始了。 你看起来脸色苍白! ";
			link.l1 = "我有点紧张, 神父。 ";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "这很常见。 今天是你人生中最重要的一天, 我真心为你高兴, 就像在场的每一个人一样。 希望你至少还记得基本的祷词—你可从来没怎么关心过教会, 对吧? 不过, 无论如何, 我都会帮你的。 \n还有一件事—据我所知, 新娘还是不会改变她的原则, 我们也见不到她穿裙子? 唉, 上流社会又要被你们俩惊到一次了—你总是能带来惊喜。 好了, 孩子, 去整理一下自己, 我们就要开始了。 ";
			link.l1 = "是的, 神父。 我们开始吧。 ";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "吾主在天之上, 愿人都尊你的名为圣, 愿……";
			link.l1 = "……愿你的国降临";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "“…主, 赐予他们永恒的安息”";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "……愿你的旨意行在地上, 如同行在天上。 求你今日赐给我们日用的饮食, 免我们的债, 如同……";
			link.l1 = "……正如我们宽恕了亏欠我们的人";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "……正如太初一样, 如今、直到永远, 世世无穷。 阿门";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "呃、呃……嗯……";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "“呃、呃……嗯……”";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "不叫我们遇见试探: 救我们脱离凶恶。  阿们。 ";
			link.l1 = "阿门。 ";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "亲爱的各位, 我们今日齐聚于上帝面前, 在众人见证下, 将这位男士与女士结合为神圣的夫妻。 亲爱的"+sld.name+"还有Charles, 你聆听了上帝的话语, 上帝提醒你人间之爱与婚姻的意义。 现在, 我代表圣教会, 要考验你们的心意。 \n"+sld.name+"“还有你, Charles, 你是否怀着自愿且真挚的心意, 在主的见证下, 与对方结为连理? ”";
			link.l1 = "是的。 ";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "你们是否愿意无论健康还是疾病、幸福还是不幸, 都彼此忠诚, 直到生命的终结? ";
			link.l1 = "是的。 ";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "你是否愿意去爱护并接纳主赐予你们的孩子, 并将他们抚养成人, 使其信仰基督教? ";
			link.l1 = "是的。 ";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "好吧, 彼此转身, 立下誓言。 ";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "在座的各位, 若有人知道这对新人不应在主的见证下结为夫妻, 请现在说出来, 否则就永远保持沉默。 \n既然如此, 在主的面前, 在众人见证下, 我宣布你们成为合法的夫妻! 奉圣父、圣子、圣灵之名。 阿门。 ";
			link.l1 = "阿门。 ";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(低声说) 查尔斯, 我的孩子, 动动嘴唇就好, 求你了 - 别出声...";
			else sTemp = "";
			dialog.text = "新婚夫妇, 请跪下共同祈祷。 信众祷词。 "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("过了一段时间...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "恭喜你, 孩子。 你父亲会为你感到自豪, 我也一样。 在这艰难时刻, 愿你们彼此珍惜, 幸福安康。 ";
			link.l1 = "多谢您, 神父大人。 弥撒非常庄严美好, 我很高兴是由您主持的。 ";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "那么你们是来向我寻求建议的, 孩子们? 好吧, 我洗耳恭听。 ";
			link.l1 = "更确切地说, 是寻求协助, 神父。 来自一位有门路、认识各类人物的人的协助……";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "原谅打断你, 孩子, 但我要提醒你, 我只是个普通的修士, 不是什么密探。 ";
			link.l1 = "可普通修士也可能认识密探, 对吧? 或者至少能指条路? ";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "我们来找您, 是为了探寻一些被遗忘已久的秘密…… 我们只是想把它们重新带回世间。 ";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "小伙子, 我开始不太喜欢你们绕圈子了。  快说正题吧, 我再看看我能不能帮你……或者说要不要帮。 ";
			link.l1 = "是, 神父。 我尽量简明扼要地说……";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "别拐弯抹角了, "+pchar.name+", 这让我头疼。 ";
			link.l1 = "是, 神父。 我尽量简明扼要地说……";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "继续说吧, 孩子。 ";
			link.l1 = "我旅伴玛丽·卡斯珀正在寻找她父亲, 或至少有关他的线索。 我们查到他曾是英国海军军官, 服役于 '兰格勒' 号双桅船, 该船于1638年在卡托奇角触礁沉没。 ";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "你们还指望他活着? 都过了这么多年。 ";
			link.l1 = "即便他没能幸存, 玛丽也想知道父亲的出身、为人, 以及他曾过怎样的生活……官方文件寥寥数语——可也可能藏着重要线索, 对吧, 神父? ";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "你的想法很正确, 孩子。 这是件正义又合乎天意的事。  但我还没弄明白, 你们到底想让我做什么? ";
			link.l1 = "您在群岛生活多年, 神父。 也许您认识某位能接触到英国海军档案的熟人? ";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "我们需要一位能接触到殖民地档案、掌握英国海军军官资料的人。 神父, 您肯定认识这样的角色。 ";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "你知道你在请求什么吗, 孩子? 问题不只是这可能是军事机密……";
			link.l1 = "那还有什么问题, 神父? 我这就说清楚……";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "你知道你在请求什么吗, 孩子? 问题不只是这可能是军事机密……";
			link.l1 = "那还有什么问题, 神父? 我这就说清楚……";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "问题出在那些殖民地档案上。  二十年前牙买加还是西班牙人掌控, 而圣约翰和布里奇敦一直受到袭扰。  皇家舰队的船只不太可能被派驻那里……";
			link.l1 = "您是说伦敦海军部的档案吗, 神父? ";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "或许吧。 文件应当已交给海军部。  但获取这些资料……并不容易。 ";
			link.l1 = "但也不是不可能, 对吧, 神父? ";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "没有什么是不可能的, 孩子。 但这需要努力……还有报酬。 ";
			link.l1 = "当然, 神父。 钱是给您, 还是要见另一个人? ";
			link.l1.go = "WildRose_Abb_12";
		break;
		
		case "WildRose_Abb_12":
			dialog.text = "另一个人我自己会去见, 孩子。 我需要你……八百个达布隆。 ";
			link.l1 = "好的, 神父。 这件事大概需要多久? ";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "我估计需要两个月。 还有, 你还没告诉我你在找的那个人的名字。 ";
			link.l1 = "那人叫约书亚·卡斯珀。 ";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "我记下了。 如果你现在就能把钱交给我——我明天就能派人联络。 ";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "当然可以, 神父。 请收下。 八百金达布隆。 ";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			else
			{
				link.l1 = "对不起, 神父, 我现在身上没有这么多钱。 但我很快会回来带来它们。 ";
				link.l1.go = "WildRose_Abb_14_nopay";
			}
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "很好, "+pchar.name+"。 两个月后来找我——到时我应该能给你一个答复。 ";
			link.l1 = "谢谢您, 神父。 回头见! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "随你吧, 孩子。 ";
			link.l1 = "我很快就会回来。 ";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;

		case "WildRose_Abb_16":
			dialog.text = "他调查了约书亚·卡斯珀和他的船, 但那艘船却不是 '兰格勒' 号。 皇家舰队里从未有过此名的双桅船。 ";
			link.l1 = "嗯……我敢肯定约书亚·卡斯珀当年所服役的船就叫这个名……那他本人呢? ";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "那人是一位优秀军官, 立下许多功勋, 也获得不少荣誉——一切都在他的档案里。 虽然他并非我教信徒, 但他是位值得尊敬的船长。 小姐可以为她的血统自豪。 ";
			link.l1 = "这是好消息, 神父。 但请允许我再问关于那艘船的事。 如果它不是 '兰格勒' 号, 那它叫什么? ";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = " '康沃尔' 号。 1638年一月从普利茅斯出发, 奉命将军饷送至安提瓜与普罗维登斯的驻军。 ";
			link.l1 = "难以置信……";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "那艘船是否抵达终点我不清楚。 但它确实曾停靠圣约翰。 港口管理局保存了一份卡斯珀船长于当年六月二日提交的报告。 ";
			link.l1 = "我就知道您不像表面看起来那么简单, 神父! 那份文件里是不是有什么重要的线索? ";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "我们欠您一大人情, 神父。 既然您提到这份文件, 那里面肯定有重要信息吧? ";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "报告中记载了在亚速尔群岛附近与西班牙 '托罗' 号大帆船的战斗, 三分之一的船员阵亡——你可以从中找到一切信息。 ";
			link.l1 = "还有一个问题: 既然您查阅了安提瓜港口的记录, 那有没有在别处见过约书亚·卡斯珀这个名字? ";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "报告中记载了在亚速尔群岛附近与西班牙 '托罗' 号大帆船的战斗, 三分之一的船员阵亡——你可以从中找到一切信息。 ";
			link.l1 = "还有一个问题: 既然您查阅了安提瓜港口的记录, 那有没有在别处见过约书亚·卡斯珀这个名字? ";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "你这是强人所难啊, 孩子。 如果你在暗示他在那次海难中幸存, 并重返舰队——我很难相信这一点。 ";
			link.l1 = "上帝的安排不可捉摸, 神父。 ";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "确实如此, 孩子。 不过你看, 他的档案里记载着约书亚·卡斯珀出生于1586年……";
			link.l1 = "也许您是对的, 神父。 ";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "您知道吗, 神父, 在加勒比这些年我见识了太多事, 连最荒诞的我都信。 ";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "毫无疑问, 这样的军官应该战死沙场。 但若从哲学角度讲, 那种场景也算是一场战斗……";
			link.l1 = "我对哲学没什么研究, 神父。 但无论如何, 感谢您的一切……";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "毫无疑问, 这样的军官应该战死沙场。 但若从哲学角度讲, 那种场景也算是一场战斗……";
			link.l1 = "我对哲学没什么研究, 神父。 但无论如何, 感谢您的一切……";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "主在引导你们, 孩子们, 帮助你们便是我卑微的职责。 但恐怕这件事上我已帮不上更多……";
			link.l1 = "我明白, 神父。 那么, 请允许我们告辞。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
