// 杰森 墓地看守者的通用对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 按城市调用对话 <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("镇上处于戒备状态。 看来我也该拿起武器了...", "你是不是被全镇的卫兵追着跑? 对我来说, 士兵们! ! ", "你在这里找不到庇护所。 但会在肋骨下找到几英寸的冷钢! "), 
					LinkRandPhrase("你想要什么, 无赖? ! 市政卫兵已经追踪到你了, 你逃不远的, " + GetSexPhrase("肮脏的海盗! ", "无赖") + "! ", "站住! " + GetSexPhrase("肮脏的杀手! 卫兵! ! ", "我不怕你! 很快你就会被吊在我们的堡垒里, 没地方可躲...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("看来你不想活了...", "你为什么不想平静地生活, 市民们..." + XI_ConvertString("Colony" + npchar.city + "Gen") + "! "), 
					RandPhraseSimple("去死吧! ", "你在这个世界上只剩下几秒钟了..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "啊-啊-啊! 啊, 是你... 你是谁? 你到墓地来干什么? ";
				link.l1 = "我叫" + GetFullName(pchar) + "。 你是谁, 在这里做什么? 你为什么这么害怕? ";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "那么, 怎么样? 你检查了吗? 现在相信我了? ";
				link.l1 = "没有, 我还没下到地窖去。 再等一会儿, 我会检查一切的。 ";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "那么? 你看了吗? 你看到了吗? ";
				link.l1 = "是的, 当然看到了! 你是对的! ";
				link.l1.go = "Lantern_10";
				link.l2 = "和你想的不太一样。 ";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("你好, 水手! 我叫" + GetFullName(npchar) + ", 我是这里唯一的活物。 实际上, 我们最终都会死, 哈哈哈! 你为什么来这里? ", "你好! 我很久没见过活人了... 请允许我自我介绍一下—— " + GetFullName(npchar) + ", 这个墓地是我最后的避难所。 显然, 我会被埋葬在这里。 我能为你做什么? ");
				link.l1 = "你好, " + npchar.name + "! 我叫" + GetFullName(pchar) + ", 是一名船长。 我穿过丛林来到这里。 想看看这个舒适的房子里面, 看看谁不害怕住在这里...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, 我的老朋友, " + GetFullName(pchar) + "船长! 进来, 进来! ";
				link.l1 = "欢迎, 朋友! 很高兴见到你。 你晚上没看到跳舞的骷髅, 梦里没看到眼睛上放着铜币的死人吗? ";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "我为什么要害怕呢, 船长? 需要害怕的是活人, 死人不咬人。 嗯! 我曾经有过完全不同的生活, 现在我是这个墓地的看守人。 我照看坟墓。 有时也交易一些零碎东西...";
			link.l1 = "请告诉我, 你交易什么物品? ";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "这次是什么风把你吹到我这里来的? ";
			link.l1 = "让我看看你今天有什么卖的。 ";
			link.l1.go = "trade";
			link.l2 = "我想问你一个问题...";
			link.l2.go = "quests";
			link.l3 = "没什么大事。 只是来问候你。 ";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "我有很多空闲时间, 因此我喜欢在丛林里散步, 收集有用的植物和奇特的石头。 然后我在镇上卖掉它们。 它们不贵, 但—— 总比什么都没有好。 我从朋友们那里得到各种各样的东西...";
			link.l1 = "朋友? 你的意思是, 你转卖别人带给你的东西? ";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "哦-呵-呵... 不, 他们免费给我一切。 如果不是死人, 谁会成为墓地看守人的朋友呢? ";
			link.l1 = "什... 你抢劫尸体吗? ";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "我不抢劫;我只是从那些不再需要东西的人身上拿走东西。 这里埋葬着许多不同的人—— 有些是不知名的, 不是我们这片土地上的人。 指挥官从镇上带来一具尸体, 说: ‘这是给你的, " + npchar.name + ", 送他走完最后一程。 ’无家可归的人。 被绞死的海盗。 被守护者杀死的强盗—— 都埋葬在这里。 而老" + npchar.name + "按照基督教的习俗埋葬他们的尸体。 ";
			link.l1 = "我明白了。 好吧, 钱就是钱, 让我看看你有什么。 ";
			link.l1.go = "trade";
			link.l2 = "知道了。 我得走了。 很高兴认识你。 ";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://对试图打开箱子的反应
			dialog.text = LinkRandPhrase("而你, " + GetFullName(pchar) + ", 是个小偷! 卫兵! ! ", "搞什么鬼! 我一转头, 你就已经想偷属于我的东西了! 抓住那个小偷! ! ", "卫兵! 抢劫! ! 抓住那个小偷! ! ");
			link.l1 = "哦, 该死! ! ";
			link.l1.go = "fight";
		break;
		//belamour 获得灯笼的任务 -->
		case "Lantern_01":
			dialog.text = "呼, 原来你只是个旅行者... 我叫" + GetFullName(npchar) + ", 是这个被上帝遗弃的地方的看守人。 ";
			link.l1 = "你为什么对墓地有这种感觉? 恰恰相反, 正是从这里, 我们的主在埋葬后带走义人。 ";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "但不义之人, 显然在埋葬后留在这里! 过去几个晚上, 地窖里一直有动静。 呻吟声如此令人毛骨悚然, 让我不寒而栗... 似乎有一个失落的灵魂无法安息! 现在我只在白天睡觉—— 晚上, 我不能离开岗位, 也睡不着觉...";
			link.l1 = "动静? 呻吟声? 但那里除了死者没有别人。 ";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "我就是这么说的, 你知道吗? 你最好在鬼魂感觉到你之前离开这里... 否则, 你就会像我一样睡不着觉。 ";
			link.l1 = "嗯, 是的, 我想我最好离开这个地方。 ";
			link.l1.go = "Lantern_04";
			link.l2 = "也许我能帮你? 今晚让我调查那些奇怪的声音。 ";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "你疯了吗? ! 我看你有武器, 但你打算用它怎么对付亡灵? 如果你在那里翘辫子了, 然后呢? 鬼魂会四处游荡, 甚至可能把你变成它的仆人! ";
			link.l1 = "嗯, 那只是迷信...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "什么迷信? 这不是虔诚的欧洲土地, 该死的... 当地人, 那些红脸的家伙, 他们什么妖术都能耍出来—— 现在我们不得不住在这里! ";
			link.l1 = "尽管如此, 让我试试。 我会等到夜幕降临, 然后下到地窖去。 ";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "好吧, 随你便。 但如果你在日出前不回来, 我就把一切都锁起来, 用障碍物堵住, 自己离开这里! 无论是作为水手擦洗甲板, 还是作为码头工人搬运箱子—— 反正我不会再回来了! ";
			link.l1 = "冷静点... 一切都会好的。 ";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "等等... 拿上这个灯笼。 我有一个备用的。 你在那里会需要它。 那里漆黑一片! ";
			link.l1 = "谢谢, 在那种地方灯笼确实会派上用场。 ";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern'received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "对吧? 那里有什么? 告诉我! ";
			link.l1 = "有一个不安的女人的灵魂! 幸运的是, 我让当地牧师为我的刀刃祝福, 以打击邪恶, 所以一切都解决了。 那个灵魂不会再打扰你了。 ";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "哦, 主啊, 拯救我们有罪的灵魂! 我警告过你! 你却不相信我! ";
			link.l1 = "是的, 我为此深感遗憾。 但现在一切都好了—— 我用圣水洒了这个地方, 没有灵魂敢从坟墓里起来。 你可以安心睡觉了。 ";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "非常感谢你! 你不知道这对我意味着什么! 来, 请收下这个。 这不多, 但我不能让你毫无回报地离开。 ";
			link.l1 = "谢谢你, 我不能拒绝。 祝你好运! ";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "没有? 那么到底是... 我的意思是, 上帝啊, 那里发生了什么? ";
			link.l1 = "根本没有鬼魂。 一对年轻夫妇选择这个地窖作为他们约会的地方。 他们的父母反对这门亲事, 所以他们在寻找一个独处的地方。 ";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "独处? ... 为什么是那些年轻人! 让他们再敢来这里试试! 我要么用鞭子把他们俩都赶走, 要么把他们锁在地窖里, 让他们待在那里! ! ";
			link.l1 = "他们不会再回到这里了。 我告诉他们, 他们的小插曲真的吓到了当地卫兵。 他们打算那样做。 顺便说一下, 门上的锁反正也坏了。 ";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "没问题, 我会换掉它。 但如果我抓到他们...";
			link.l1 = "别这么生气。 我们都曾是那个年龄。 他们来这里不是因为这是最好的约会地点。 ";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "说得对... 哦, 好吧, 愿主与他们同在。 谢谢你没有让一个老人陷入困境。 来, 请收下这个。 这不多, 但我不能让你毫无回报地离开。 ";
			link.l1 = "谢谢你, 我不能拒绝。 祝你好运! ";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- 获得灯笼的任务 
	}
}