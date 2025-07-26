// Addon-2016 Jason, 马提尼克法国迷你任务 (FMK) 
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明显的程序错误, 请告知开发者。 ";
			link.l1 = "我会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// 任务发布者
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting() + ", 船长。 请允许我自我介绍 --" + GetFullName(npchar) + "。 尽管我们不久前见过面, 但我怀疑您已经不记得我了。 ";
			link.l1 = "您好, 先生。 我之前在哪里见过您? ";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "双桅小帆船'阿德琳'号";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "单桅纵帆船'黑狗'号";
			dialog.text = "在我们的造船厂。 您曾购买过" + sTemp + "。 现在想起来了吗? 我是那里的木匠。 ";
			link.l1 = "是的, 我确实买过那艘船。 那么您想做什么, " + GetFullName(npchar) + "先生? ";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "我们的造船师" + GetFullName(sld) + "想和您谈谈。 我相信他有一些商业提议。 他在港口看到了您的船, 派我来寻找您。 您愿意接受邀请吗? ";
			link.l1 = "好的。 等我在镇上处理完事情就去拜访您的老板。 ";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "啧啧... 又有走私犯落网了! ";
			link.l1 = "呃... ";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "少废话! 这个造船厂里有几桶树脂。 船长, 您把它们运给了您的同伙。 你们俩都被捕了, 我以法律的名义没收这批货物! ";
			link.l1 = "... ";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "别装傻了, 老板! 什么桶? 您知道我在说您刚从这个水手船上卸下的那些桶! 你们俩都要在地牢里腐烂! 走, 混蛋... ";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "亲爱的造船大师, 这种树脂是战略物资, 由我们的总督直接管控! 既然您声称这是您的 --那就如您所愿。 您被捕了, 今晚将在我们舒适的地牢里度过, 明天您需要详细报告您是如何得到它们的以及用途。 别担心, 我们最终会查明一切。 你, 船长, 可以走了。 今天算你走运。 ";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "我就知道这艘船有问题... 看来我低估你了, 船长。 ";
			link.l1 = "没错, 中尉。 我没那么蠢。 你和造船师的愉快合作现在暴露了。 ";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "明白了。 恭喜你, 你很有天赋, 居然能追踪到我并出其不意地抓住我。 现在告诉我你想要什么。 ";
			link.l1 = "这还不清楚吗? 我需要拿回我的树脂。 你和你的同伙从我这里偷走的树脂。 ";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "好吧。 你可以拿走, 但只能拿你那批货的一半。 我这里就藏了这么多。 希望你觉得足够, 因为这是我能提供的全部了。 ";
			link.l1 = "你还想骗我吗? 用金子或你身后藏的货物补偿我另一半。 ";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "没门。 另一半去找我们的共同朋友要。 ";
			link.l1 = "你在开玩笑吗? 你真以为" + GetFullName(characterFromId("FortFrance_shipyarder")) + "会把桶还给我? 太荒谬了。 ";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "船长, 把我所有的树脂都拿走, 保住你的命, 然后滚出这里。 我可以保证在圣皮埃尔不给你制造任何麻烦。 这是我的最终报价。 ";
			link.l1 = "什么时候我的命也成了交易的一部分? 哈! ";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "看来你在战斗后仍然觉得自己不可战胜, 船长。 让我解释一下: 那些是新手, 未经训练且缺乏动力, 你没有机会对抗我的小队。 我本可以不谈判就杀了你, 但我珍惜手下的生命。 在杀你的过程中, 他们可能会受伤甚至死亡。 所以你要么接受我慷慨的提议, 要么永远留在这里。 该选择了。 ";
			link.l1 = "去你的, 中尉, 但我被迫接受你的条件。 我在这里寡不敌众。 ";
			link.l1.go = "officer_13";
			link.l2 = "太自信了, 中尉? 我想我应该给你和你的雇佣兵一个教训。 你这个树脂狗! ";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "你是个通情达理的人, 船长。 带上你的桶离开吧。 我必须警告你, 在总督面前指责我不会有帮助。 我今天就会转移藏匿点。 省省你的时间吧。 ";
			link.l1 = "没打算那么做。 我知道向当局申诉是徒劳的。 ";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "快点, 我没太多时间浪费。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "哦! 真是巧会! 晚上好, 先生! 今晚过得愉快吗? ";
			link.l1 = "晚安... 啊, 是你! 我记得你, 我到达加勒比的第一天就见过你。 格雷瓜尔.瓦林尼先生。 ";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "很高兴您还记得。 我看到您现在已经是船长了。 " +GetFullName(pchar)+ "船长。 恭喜。 ";
			link.l1 = "谢谢... ";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "您看起来很烦恼, 船长。 这里发生了什么? 有什么不对劲吗? ";
			link.l1 = "是有些不对劲... ";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "先生, 与其站在街中央, 不如我们去酒馆吧。 您可以喝上几杯。 我们可以在那里谈谈。 来吧! ";
			link.l1 = "... ";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "倒上, 船长... ";
			link.l1 = "倒吧..";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "呜... 现在请告诉我怎么了? 您看起来像上周被绞死的那个人。 他站在绞刑架上时就是这副表情。 ";
			link.l1 = "是这样的, 格雷瓜尔先生... 这么说吧, 我工作上遇到了麻烦。 ";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "船长, 您可以把一切都告诉我。 我不会把您出卖给总督或司令官, 这一点您可以相信我。 您不信任我吗? ";
			link.l1 = "我信任您, 先生。 ";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "那就坦白吧, 让您的灵魂轻松些。 我也许有能力帮助您。 ";
			link.l1 = "当地一位造船师雇我去抢劫一艘从特立尼达起航的西班牙商队。 他急需树脂, 那是我的目标, 他答应每桶支付15达布隆。 我追踪到商队, 抢劫了它, 并把货物带到了这里。 他们正在修理我的船, 并把桶卸到了造船厂。 我们正要完成交易时, 那个军官出现了... 我想知道他是怎么发现的? ";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "就是这样, 他们抓住了我们。 我觉得应该赞扬一下造船师 --他把所有责任都揽在自己身上, 告诉他们树脂是他的财产, 我与此事无关。 最后, 他被捕了, 我的钱也没了。 虽然很幸运没进监狱, 但与西班牙商队的麻烦只是浪费时间和金钱。 再倒一杯吧, 格雷瓜尔先生。 ";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "那么, 造船师被捕了? ";
			link.l1 = "嗯, 是的。 他被我提到的那个军官带去监狱了。 您真该看看他们。 ";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "是的, 我看到他们俩了, 不过我不知道费利西安.格罗尼耶中尉竟然会逮捕他的老朋友。 ";
			link.l1 = "你... 你刚才说什么? ";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "您没听错。 费利西安.格罗尼耶中尉和造船师" + GetFullName(characterFromId("FortFrance_shipyarder")) + "是老朋友。 他们以前在欧洲军队一起服役。 格罗尼耶留在了军队, 而" + GetFullName(characterFromId("FortFrance_shipyarder")) + "成功开始了自己的事业。 ";
			link.l1 = "所以他们彼此认识... 现在我明白了... ";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "我亲爱的" +pchar.name+ ", 看来您被欺骗了。 您在这里还是个新人, 他们利用了这一点。 我敢打赌100达布隆, " + GetFullName(characterFromId("FortFrance_shipyarder")) + "先生三天内就会再次在他的造船厂附近走动。 ";
			link.l1 = "看来您是对的, 先生。 他们骗了我。 那个军官不可能知道树脂的事。 时机也太完美了。 ";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "这就是加勒比, " +pchar.name+ "先生。 习惯吧。 别看外表, 这里最坏的混蛋总是看起来像个受尊敬的贵族。 ";
			link.l1 = "我以前听过这句话... 我该怎么对付他们? 应该去找总督吗? ";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "恐怕在这种情况下, " + GetFullName(characterFromId("FortFrance_shipyarder")) + "会给他们讲另一个故事, 而您最终会进监狱。 ";
			link.l1 = "可想而知。 那好吧! 既然法律不站在我这边, 我就用我的方式解决! 我不会就这样放弃的。 ";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "请冷静, " +pchar.name+ "。 这是愤怒和朗姆酒在说话, 不是您。 睡一觉, 然后再考虑。 也许最好还是放手。 费利西安.格罗尼耶中尉和" + GetFullName(characterFromId("FortFrance_shipyarder")) + "在这里都是有权有势的人, 他们远在您之上。 别做傻事。 ";
			link.l1 = "走着瞧。 感谢您的指点。 很高兴遇见您。 ";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "小心点。 记住我告诉您的话。 ";
			link.l1 = "我会的。 现在让我们再喝最后一杯! ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = GetFullName(pchar) + "船长! ";
			link.l1 = "哦, 格雷瓜尔先生! 又是您! ";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "是的。 我们在酒馆谈话后, 我打听了费利西安.格罗尼耶中尉的情况。 原来他不久前申请了十天假期。 他的请求被批准了。 我今天看到他, 他乘长艇上了一艘小帆船, 那艘船很快就驶往瓜德罗普了。 她叫'黄玉'号\n我把一切都告诉您了, 现在该您决定了。 我相信您能看出格罗尼耶突然请假并乘坐新造的小帆船离开岛屿的规律。 ";
			link.l1 = "该死, 现在我完全明白了! 那艘小帆船的货舱里肯定装着我的树脂! 格雷瓜尔先生, 谢谢您, 您真是帮了大忙! 我能为您做些什么作为回报吗? ";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "哦, 得了吧, 我的朋友。 我们是贵族, 应该互相帮助。 我们就是这样生活的。 我相信如果我处于您的境地, 您也会这么做。 别浪费时间了, 向北航行, 找到那个军官。 不要交战, 只要跟踪他, 看看他在做什么。 快点, 船长! ";
			link.l1 = "再次感谢您! ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "你在看什么? 你在这里想干什么? ";
			link.l1 = "嘿, 伙计, 我在找我的东西。 看到那边的那些桶了吗? 那是我的树脂, 他们一分钱都没付我。 ";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "你是个白痴还是怎么的? 趁你还能走, 赶紧滚! ";
			link.l1 = "我费了这么大劲才弄到这些树脂, 不会让几个肮脏的混蛋阻止我。 ";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "我们会把你这身漂亮的衣服埋在这里! ";
			link.l1 = "哦, 你们真好, 还建议埋葬, 但恐怕我们只会把你们留在海滩上, 让海鸥吃掉你们的内脏! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}