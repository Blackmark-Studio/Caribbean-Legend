// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
       case "First time":
			dialog.text = "你想要什么?";
			link.l1 = "我该走了... ";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "查尔斯.德.莫尔船长!终于找到您了!雅克.迪勒.德.帕奎特大人要求见您!非常紧急!";
			link.l1 = "我并不惊讶。 好吧, 请转告大人我很快就到。 ";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "如果眼前真是查尔斯.德.莫尔本人, 那我的眼睛一定是骗了我!我不常举办这样的招待会, 很高兴您能抽出时间光临我这简陋的住所。 我太幸运了!这值得举杯庆祝!";
			link.l1 = "向您致敬, 夫人。 请原谅我可能让您失望的举止 —我已经很久没有参加过这样的... 活动了。 船上的礼仪仅限于上下级关系。 干净的围巾和每天早上一杯提神的咖啡。 ";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "太迷人了, 船长, 您身上还保留着巴黎的优雅。 在您饱经风霜的面具下, 我能看到它羞涩的一瞥。 别担心, 我很高兴终于见到您, 现在可以原谅您很多事情。 以后我们再看看相处得如何。 喝点酒吗?红葡萄酒还是白葡萄酒?";
			link.l1 = "这是开朗姆酒玩笑的最佳时机, 但可惜我没心情, 抱歉。 您美丽的手倒的任何酒我都乐意喝。 ";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "说得好。 但我坚持。 对葡萄酒的品味能反映一个人的很多方面, 而我打算今晚了解您的一切。 所以我再问一遍:红葡萄酒还是白葡萄酒?";
			link.l1 = "如您所愿。 我看您在喝红葡萄酒。 我也一样 —我也想了解您一些事情。 ";
			link.l1.go = "Julianna_3";
			link.l2 = "那样的话, 我喝白葡萄酒, 但由您选择。 这应该对双方都有效, 您同意吗?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "太好了, 现在轮到我了?这是勃艮第黑皮诺, 酿酒师称它为'调皮的女孩'。 这不是一个容易驾驭的品种, 它的余味也可能相当具有欺骗性。 满意吗?";
			link.l1 = "黑皮诺, 嗯?对我来说还行。 不可靠又神秘, 初尝味道平淡, 但让它醒一会儿, 你会惊讶的。 层次和味道的轻盈舞动, 是经验丰富鉴赏家的选择。 第一印象不可靠, 对吧?我为您的眼睛干杯, 夫人!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "太好了, 现在轮到我了?我有很棒的长相思, 直接来自卢瓦尔河谷。 相当野性, 你几乎能感觉到它在舌头上跳跃。 最妙的是 —还有一丝火药味。 我想您和它有共同之处。 ";
			link.l1 = "我期望更好的, 也许是雷司令之类的。 好吧, 让我们尝尝这种闻起来像夏天和火药的简单烈酒。 有没有听说有人把它误认为猫尿?我要为您的微笑干杯, 它像这些蓝宝石一样明亮!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "了不起, 查尔斯!我可以这样叫您吗?我对您的看法没错, 如果换一天, 您会成为我夜晚的明星。 但可惜, 我的船长, 今天您有强劲的竞争对手。 看来我们那边即将发生丑闻, 您看到了吗?";
			link.l1 = "我听到了愤怒的声音。 那个令人不快的先生是谁?他做了什么让我们最亲爱的总督不高兴?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "那个'令人不快'的先生是安杰伦.德.谢沃, 德.列维.旺塔杜尔伯爵不被承认的私生子。 您正在谈论他们的争论话题。 谢沃多年来一直试图赢得我的好感, 他跟着我到这里, 以为可以取代他父亲在我心中的位置。 尽管他不是合法的儿子, 但他富有且有权势。 固执是他的另一个特点, 对某些人来说, 固执可以取代智慧。 就在您到来之前, 他和雅克开始就这个明显的话题争吵。 大人总是以一种非常感人的方式保护我, 您应该看看!来吧, 我们观察一下这次会如何结束。 ";
			link.l1 = "我闻到了麻烦的气息... 为什么即使在如此美好的夜晚, 总是有陷阱... ";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "请原谅, 查尔斯?";
			link.l1 = "忘了吧。 请把我介绍给您那位纠缠不休的朋友, 然后我们再看... ";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "先生, 请允许我向您介绍我亲爱的客人 —查尔斯.德.莫尔船长, 真人到场!这样的名人很少来这里做客。 ";
			link.l1 = "... ";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "查尔斯, 我不喜欢事情的发展方向!雅克对我的论点充耳不闻, 而安杰伦肯定在搞什么鬼。 这场争吵是有目的的, 我需要您的帮助!";
			link.l1 = "恐怕我没跟上您的思路... 我在这里能做什么?他已经拒绝和我决斗了... ";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "船长, 请不要让我失望。 刚才您还是对话的大师, 现在您的世界却分裂成可以用剑戳的东西和不能戳的东西。 跳出思维定式!让我们破坏安杰伦的计划。 他想自己挑战可怜的雅克, 但那太无聊了!我们举办一场锦标赛吧!这里有几位先生可以下重注, 而您的运气已经闻名遐迩!也许今晚牌运会眷顾您?";
			link.l1 = "我不太明白这如何能阻止德.谢沃和我们可爱的总督决斗, 但我加入, 女士。 任何能抹去他那点微笑的事都行。 ";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "太好了, 现在去桌边吃点东西吧, 这将是一个漫长的夜晚。 等您准备好了, 到大厅见我, 我们需要更多空间来办这个。 同时, 我会表演一番, 说服其他人给我看点精彩的比赛和高赌注的游戏。 我甚至可能对他们大喊大叫, 让这些自负的家伙注意到一位女士正沉浸在无聊中。 请不要干涉, 不能让任何人知道我们今晚是一伙的。 稍后见, 我的船长!";
			link.l1 = "悉听尊便, 夫人, 悉听尊便... ";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "好了, 祝贺我吧, 成功了!一点点骄傲, 一些偏见, 瞧!做出无聊的表情, 他们在看着我们。 让他们以为您对喝酒感兴趣, 而不是对我\n锦标赛即将开始, 赌注很高, 没有第二次机会和重赛。 不知何故, 我知道您已经习惯了这个。 您会处理好的。 记住, 安杰伦肯定在搞什么鬼, 他会对我们的朋友雅克采取行动, 但他没有考虑到您的到来。 做我手中的王牌, 因为看到他自信的 smug 脸从来都不是好兆头。 我们有八名玩家, 但我确保您在决赛前不会遇到他\n哦!您的第一个对手!上校和我们堡垒的指挥官。 海上对陆地 —对于有军事经验的客人来说是一个有价值的挑战!掌声!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "您做得很好, 查尔斯, 太棒了。 安杰伦和雅克马上就要对决了。 可惜他们不听劝, 把比赛推迟一周。 我本可以召集一个真正一流的派对, 流言蜚语会传到巴黎!好吧, 也许下次吧。 看来您的下一个对手是与您运气相当的值得尊敬的竞争对手, 真正的海狼, 莫雷诺船长!船长们, 请!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "唉, 您的运气辜负了您, 船长。 我很抱歉, 但您的游戏结束了。 安杰伦已经在和雅克对战, 所以我该走了。 再见。 ";
				link.l1 = "很荣幸... 夫人。 ";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "祝贺您当之无愧的胜利, 船长!还不清楚谁将在决赛中与您对决... 我们稍微让开一点。 压低声音, 观察那张桌子。 看, 他走了!我开始明白安杰伦的意图了!他已经把可爱的雅克的钱赢光了, 但他不让他离开桌子。 我经过时, 那个可怜的家伙用一整艘船和货物赌了一些文件。 可悲的是, 今晚运气不在他那边。 或者有人让她不要在。 ";
				link.l1 = "认为德.谢沃在作弊?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "唉, 您的运气辜负了您, 船长。 我很抱歉, 但您的游戏结束了。 安杰伦已经在和雅克对战, 所以我该走了。 再见。 ";
				link.l1 = "很荣幸... 夫人。 ";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "如果他想的话, 他肯定可以, 但我没有证据。 我们亲爱的总督很会打牌, 但他的对手也是如此。 安杰伦在赌他的护卫舰时甚至没有眨眼, 想象一下。 如果我们在巴黎或里昂进行这场决斗, 它会成为一个传奇, 查尔斯!尽管如此, 他今晚可能只是运气好。 让我们接近他们, 亲自看看。 ";
			link.l1 = "... ";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "查尔斯, 扶我一下, 不然我会摔倒... 或者我不会 —这些白痴甚至不会注意到我假装晕倒。 你看到了吗?雅克, 该死的愚蠢!像个孩子, 天啊!一个愚蠢的孩子!";
			link.l1 = "侯爵夫人, 我想我没跟上您。 那张桌子现在发生了什么?他们在赌什么?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "赌我, 查尔斯。 我们可爱。 愚蠢的雅克赌了我。 安杰伦找到了他唯一的软肋, 并在正确的时机击中了它。 ";
			link.l1 = "该死的!但我是锦标赛的下一个, 我可以把他那该死的船赢回来!为什么?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "因为安杰伦深思熟虑, 计划周全。 听我说, 我们时间不多了。 您必须对他做同样的事。 剥夺他的一切, 拿走他所有的钱, 所有的船, 激怒他!让他在名誉。 荣誉。 激情上失去理智, 在任何事情上!您今晚已经看到了如何做到这一点。 把他逼到角落, 迫使他下注\n我求您了, 查尔斯!我什么都愿意做, 但我不会跟他走。 不能这样!即使旺塔杜尔伯爵也不会反对诚实的牌局胜利, 他甚至不会动一根手指来帮助我。 看, 牌局对贵族来说是神圣的, 该死的!您是我最后的唯一希望, 查尔斯!";
			link.l1 = "别这么快为我们的总督默哀, 夫人。 也许他会赢回他的船?幸运女神是善变的... 女人。 ";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "您还是不明白, 对吗?那张桌子上没有运气可言!安杰伦.德.谢沃说了算。 他发现了一种既能拥有我又能让他父亲远离此事的方法。 我不知道他计划了多久, 但他现在几乎赢了。 他掌控着游戏, 我们只有一次机会打破它。 给, 拿着这个!我要假装晕倒, 给您一两分钟。 明智地利用它。 ";
			link.l1 = "侯爵夫人... 来人啊, 帮帮我!夫人不舒服!快!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("你获得了护身符'海龟'");
			Log_Info("你获得了护身符'小丑'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "不, 不, 我没事... 这里有点闷... 很抱歉, 先生们。 我出去透透气, 你们可以继续, 不用管我。 ";
			link.l1 = "... ";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "现在不行, 在圣皮埃尔也不行, 但我认识一个人。 我向您保证, 安杰伦, 这将是一幅值得的画... ";
			link.l1 = "... ";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "安杰伦, 你真让人受不了!学会输吧!这只是个游戏, 你不能预测一切。 喝完你的酒, 穿上衣服 —规则不变 —输家离开我们舒适的派对。 ";
			link.l1 = "侯爵夫人, 等等... ";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "这太过分了, 先生们!立刻停止!经过这疲惫的一夜, 我们都很累, 恐怕我不得不请我的客人道别了。 你们可以明天再继续你们的争论, 这符合有荣誉的人的做法, 除非你们改变主意。 但这里没有人会动武, 清楚吗?";
			link.l1 = "... ";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "查尔斯, 恐怕我得请您也离开了。 上楼去给自己选个房间。 我会安排好一切。 我对您所做的一切感激不尽, 但我需要一些时间独处, 您一定也累坏了。 ";
			link.l1 = "还不算太糟, 夫人, 但我不会拒绝一张床。 这场随意的派对比大规模的敌舰中队更让我疲惫。 我明白这对您来说也不容易, 侯爵夫人。 休息一下, 别担心, 您不欠我什么。 我现在只需要睡一觉。 ";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "我会确保他们中午叫醒您。 已经天亮了, 所以我不能再祝您晚安了。 睡个好觉。 ";
			link.l1 = "您也是, 侯爵夫人。 ";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "你来了, 查尔斯。 说实话, 我根本没睡, 但你看起来休息得很好。 睡得怎么样?早餐马上就到。 ";
			link.l1 = "您的款待名不虚传, 夫人, 但恐怕我没有时间享受了。 大人。 德.谢沃的助手。 我赢的船 —所有这些都在等我。 ";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "您不仅赢了船。 这是我想问您的另一件事, 查尔斯... ";
			link.l1 = "我既不是雅克也不是安杰伦, 侯爵夫人。 我不会为了赢得女人的青睐而拿她们打赌。 您不欠我什么。 ";
			link.l1.go = "Julianna_41";
			link.l2 = "您在我的保护之下, 侯爵夫人。 雅克和安杰伦都不会再打扰您, 我可以向您保证。 ";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "您要么极其高尚, 要么陷入了爱情, 查尔斯。 而且不是对我。 但我再次从心底里永远感激您。 如果我能为您做任何事 —尽管告诉我。 ";
			link.l1 = "朱莉安娜, 时间紧迫, 我面临着最艰巨的任务。 德.谢沃是个人渣, 即使是一场诚实的决斗也可能很快像我们昨晚观察到的那样结束。 等这一切彻底结束后我们再谈。 感谢您提供安静的睡眠, 我期待再次见到您。 ";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "我从心底里感激您, 查尔斯... 相信我, 成为您的奖品对我来说也是一种胜利。 说您和我应该在更... 私密的环境中继续这次谈话?";
			link.l1 = "朱莉安娜, 时间紧迫, 我面临着最艰巨的任务。 德.谢沃是个人渣, 即使是一场诚实的决斗也可能很快像我们昨晚观察到的那样结束。 等这一切彻底结束后我们再谈。 感谢您提供安静的睡眠, 我期待再次见到您。 ";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "那我就不再耽误您了, 我的船长。 不过请记住, 安杰伦很危险。 我无法判断他的战斗能力, 但他参加过几场战争, 在罗克鲁瓦打过仗。 我还听说他赢过几次决斗, 大多是用手枪。 最重要的是, 正如您自己注意到的, 他是个 deceitful 类型。 我恳求您小心, 事后一定来见我!";
			link.l1 = "关心别人的样子很适合您, 侯爵夫人。 相信我, 德.谢沃不是第一个挡我路的混蛋。 我会处理的。 现在我真的该去见大人, 讨论决斗的事情了。 ";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "一路顺风, 我的船长!告诉雅克让他离我家的门越远越好。 ";
			link.l1 = "我向您保证。 再见, 侯爵夫人!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "船长, 您来了, 真让人放心!怎么样?您流血了吗?!";
			link.l1 = "不是我的血... 至少不全是。 侯爵夫人, 德.谢沃在哪里?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "我正要问您同样的问题 —您没把他打倒?发生了什么?为什么我看到半个城镇的卫兵在外面?";
			link.l1 = "我告诉总督您可能有危险。 德.谢沃受伤逃跑了, 派他的暴徒攻击我们。 那是一场屠杀。 不过, 这样的故事不适合您美丽的耳朵。 结束了。 您摆脱了他, 也摆脱了我们'可爱的'雅克。 ";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "这太糟糕了, 查尔斯。 像安杰伦.德.谢沃这样的敌人, 有机会就应该彻底除掉。 我认识这个人很多年了 —他不是宽容的类型。 迟早, 他会找到报复的方法。 但我不喜欢您现在的样子, 您的伤口处理了吗?";
			link.l1 = "只是擦伤, 比这严重得多的我都经历过。 有点疼, 就这样。 感谢您关心我, 夫人, 但我该走了... ";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "船长, 您为我赌博, 冒着您的船和财富的风险, 您为我在交易中战斗, 冒着生命和事业的风险。 我能为您做的最起码的事就是照顾您的伤口, 给您一个安全休息的地方。 不!我不想再听到这些。 牵着我的手, 跟我上楼。 您的房间在等您。 ";
			link.l1 = "我接受您的提议, 夫人, 谢谢。 但我不想让您承受重量。 我自己上楼。 ";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "侯爵夫人, 您是我的守护天使。 恐怕现在是我欠您的了。 ";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "查尔斯, 您是骑士精神的典范!我向上帝发誓, 如果您继续这样, 我会失去理智的!好吧, 我的骑士, 我会派丹尼斯去您那里, 她会像任何合适的医生一样照顾您的伤口。 ";
			link.l1 = "谢谢您, 侯爵夫人。 如果我的心没有被占据, 我会很乐意配合。 但可惜!晚安!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "在这种情况下, 我要求您立即迁就我。 牵着我的手, 照我说的做。 丹尼斯!把绷带。 热酒和吃的拿到楼上!走吧, 我的船长。 记住 —这次不要争论!";
			link.l1 = "如您所愿, 侯爵夫人, 我全听您的。 ";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "早上好, 查尔斯。 您那些'擦伤'怎么样了?";
				link.l1 = "多亏了您的努力, 我感觉重生了。 请接受我诚挚的感谢, 朱莉安娜。 ";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "早上好, 我的英雄。 您那些'擦伤'怎么样了?";
				link.l1 = "感谢您的关心, 夫人, 我完全好了。 我愿意花一大笔钱让您的丹尼斯担任我船上的医生。 她是个奇迹!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "恐怕安排起来不容易。 但如果没有严重的理由, 我从不敢叫醒您。 相信我, 我无畏地守护着您的睡眠, 但楼下这个人非常执着。 他说他是您的船员, 事情很紧急。 ";
			link.l1 = "我的船员?您叫醒我是对的, 侯爵夫人!我马上就去。 ";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "在不同的情况下我会的, 我的船长, 但我们不得不推迟。 楼下有一位非常没教养的先生在等您。 他说他是您的船员, 事情很紧急。 ";
			link.l1 = "我们会回来谈的, 夫人, 等我回来。 我希望这不是关于西班牙人再次围攻的事。 ";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "查尔斯, 您回来了!您的人带来了什么消息?您甚至没说再见!";
			link.l1 = "我道歉, 侯爵夫人。 德.谢沃又耍了卑鄙手段。 他偷了我的船, 今晚起航了。 我的一位信任的军官在那艘船上, 我不能把她留在那个混蛋手里。 ";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "她?您的船上有一位女军官?这与我所知的所有航海术相悖。 您凭什么认为她还活着?";
			link.l1 = "我希望。 朱莉安娜, 希望是我目前唯一拥有的。 我必须了解更多关于安杰伦.德.谢沃的信息。 我绝对必须找出他去了哪里!我必须把她带回来!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "现在我明白了!您确实恋爱了, 我的骑士!我愿意毫不犹豫地付出半生来换取这样的忠诚和依恋!";
			link.l1 = "我没有发誓, 但这个女人对我意义重大, 侯爵夫人。 ";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "这嫉妒得令人感动。 听着, 查尔斯, 我准备好为您吃醋了!但哪个妓女能对真爱之声充耳不闻呢?此外, 您救了我, 我的骑士, 我当然会帮助您。 请问吧。 ";
			link.l1 = "谢谢您。 您认识德.谢沃很久了。 在所有这些麻烦之后, 他可能去哪里躲避他父亲的愤怒?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "如果我用早午餐诱惑您呢?您已经两天没有想过这个... 女孩了, 也许她可以再等一天?";
			link.l1 = "侯爵夫人, 我知道在您眼中我可能是什么样子, 但木已成舟。 尽管我没有发誓, 但我的心属于她。 我恳求您理解我并帮助我。 ";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "得了吧, 查尔斯!在妓女面前用爱情来为自己辩护?我很久没有这样笑过了!您太不可思议了!放松, 在这所房子里发生的事, 就留在这所房子里。 我记得我欠您什么。 请问吧。 ";
			link.l1 = "谢谢您。 您认识德.谢沃很久了。 在所有这些麻烦之后, 他可能去哪里躲避他父亲的愤怒?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "说实话, 尽管邀请安杰伦.德.谢沃可能不是最令人愉快的事情, 但在政治上仍然非常有用。 他在任何地方都是受欢迎的客人, 包括与法国结盟的国家。 但我只知道附近有一个人会永远帮助他并提供庇护。 弗朗索瓦.德.里昂, 我们瓜德罗普殖民地的总督。 他是德.列维.旺塔杜尔伯爵的老同事, 总是对这个混蛋有好感。 ";
			link.l1 = "瓜德罗普就是了!这是我所能希望的最好线索了!如果我们今晚起航, 我们只落后他们一天。 ";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "等等, 查尔斯, 还有别的事。 我最近收到一封给您的信。 我以为这与决斗有关, 但我现在不确定了。 给您。 ";
			link.l1 = "没有封印, 但纸张很贵。 我不喜欢这个... ";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "来吧, 查尔斯!别让我悬着心, 是他写的吗?";
			link.l1 = "是的, 是他写的。 她还活着!他偷我船的时候抓住了她。 现在他建议我们见面, 在文明的环境中谈谈。 正如您所说, 瓜德罗普, 巴斯特尔。 ";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "里昂先生肯定会选择列维.旺塔杜尔的儿子而不是您。 德.谢沃可能会再次为您设下陷阱!您通过保护我树立了一个非常强大的敌人, 查尔斯。 我希望我能帮助您, 但恐怕我所能做的只是请您小心。 ";
			link.l1 = "朱莉安娜, 如果我总是选择直接的方式, 我在新世界就无法立足。 阴暗的事情不是我的强项, 但我知道如何配合。 ";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "有什么消息吗, 船长?";
			link.l1 = "唉, 没什么... ";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "欢迎回来, 查尔斯!很高兴您还活着。 有什么消息?";
			link.l1 = "我们对德.谢沃能力的了解都严重低估了。 那个混蛋扣押了我的... 军官, 我只有两周时间筹集赎金。 恐怕没有您的帮助不行。 ";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "查尔斯, 您的爱是相当的风信子, 但我欠您很多, 会尽力帮助您。 我能为您做什么?";
			}
			else
			{
				dialog.text = "查尔斯, 我已经说过我永远不会忘记您为我所做的一切。 我会做我能做的来回报您。 我准备好了, 但我不太明白我在这方面能有什么用?";
			}
			link.l1 = "请坐, 朱莉安娜。 看, 安杰伦的赎金... 是您。 我不是指官方的赞助, 我的意思是像他货舱里的绑匪。 ";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "我无语... 但您的表情告诉我这不是玩笑。 他疯了吗?";
			link.l1 = "更像是, 他认为我疯了。 他绝望到不惜跨越一切可能的界限。 ";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "那您在要求我什么?在被绑架时不要尖叫?船长, 您不觉得这要求有点过分吗?我欠您很多, 但通过把自己的生命交给一个不光彩的混蛋来拯救别人的爱情... 您是这里的骑士, 而我是一个极其现实和物质主义的女人。 ";
			link.l1 = "恐怕, 夫人, 这正是我要求您的。 收拾东西, 我们走。 我对此深感抱歉, 但时间紧迫。 ";
			link.l1.go = "Julianna_76";
			link.l2 = "侯爵夫人, 我不会绑架信任我的女人。 这可能是我们的机会。 ";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "您总是充满惊喜, 查尔斯。 听到了吗?那是我对您所有的好感, 现在刚刚破碎。 不管爱不爱, 我不会让您绑架我。 卫兵!救命!!!来人啊!!!!";
			link.l1 = "我还以为我们是朋友。 ";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "这是一种侮辱!您把我的休息室变成了什么样子?!这是什么恶魔般的恐怖?查尔斯, 恢复理智吧!您是个贵族, 不是该死的海盗!!";
			link.l1 = "我已经向您道歉了。 我请您不要让事情进一步复杂化 —您不听。 相信我, 我不喜欢我正在做的事情, 但我别无选择。 为了那个女人, 我会不惜一切。 ";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "什么样的女人会选择您这样的骑士?我向上帝发誓, 如果您继续这样, 我会失去理智的!好吧, 我的骑士, 我自己走, 别碰我!您不是在偷牛, 所以表现出一些尊严!";
			link.l1 = "好吧。 跟我来, 夫人。 待在我身后, 低下头 —也许他们会开始射击。 ";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "有那么一刻, 我以为我根本不了解您, 查尔斯。 那个眼神... 但您打算怎么做?您提到的机会是什么?";
			link.l1 = "为什么那个混蛋利用我来接近您?为什么他精心安排那场纸牌游戏而不是直接拿走他想要的?他害怕什么?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "什么都不怕。 唉, 但这一切背后的原因都很无聊和原始。 亨利伯爵仍然对我有好感。 如果安杰伦违背我的意愿对我做任何事, 他会冒很大的风险。 抱歉查尔斯, 但这是死胡同。 他会否认一切并逃脱惩罚。 没有人会相信您这个绑架者的话, 而他的父亲会毁了您。 ";
			link.l1 = "该死的!我希望事情不是这样... 准备好, 侯爵夫人, 我们必须走。 是的, 我请您保持安静。 ";
			link.l1.go = "Julianna_76";
			link.l2 = "但那个混蛋除了他父亲之外肯定还有其他弱点, 对吧?他不完美, 恰恰相反, 他是完美的反面!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "我不知道这对... 我们是否有用。 安杰伦和当地的海盗男爵有一些交易。 雅克.巴拉班?";
			link.l1 = "是巴巴松, 夫人。 好一对, 他们俩!但'善良的'雅克对我没有好感, 没有确凿的把握, 我不能对勒弗朗索瓦发动攻击。 ";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "您又太直截了当了, 我的骑士。 还记得莫雷诺船长吗?您的第二个赌博对手?我打赌他来这里是因为安杰伦。 他一定知道对我们有价值的事情。 ";
				link.l1 = "莫雷诺船长, 哈!是的, 当然。 他还在城里吗?我在哪里可以找到他?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "您又太直截了当了, 我的骑士。 总有人知道些什么, 在某些情况下不是每个人都能守口如瓶。 我的... 学生们在这所房子里听到了一些事情。 给我一天时间, 我会了解更多, 或者给您找个能告诉您的人。 ";
				link.l1 = "侯爵夫人, 我以为关心您适合您, 但您生气的样子更适合您。 谢谢您, 您给了我希望!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "是的, 他还在, 我会省去您到处找他的麻烦。 明天晚上来这里 —莫雷诺船长会在这个房间等您。 我希望我能做更多, 但我不能, 查尔斯。 ";
			link.l1 = "这已经足够了, 侯爵夫人。 有他在我身边, 事情会容易得多。 谢谢您。 明晚见。 ";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "我希望在不同的情况下听到您这样说, 查尔斯。 明晚来看我。 我希望我能得到您需要的东西。 ";
			link.l1 = "再次感谢您, 朱莉安娜!那就明晚见。 ";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "您来了, 我的朋友!莫雷诺船长已经在等您了。 ";
				link.l1 = "... ";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "查尔斯, 我想我找到了一些东西。 还记得莫雷诺船长吗?那个在那个不幸的夜晚和您对战的人?";
				link.l1 = "记得, 真是个无赖。 他怎么了?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "我一直都知道, 巴托洛梅奥.德.拉.库埃瓦。 这就是您参加我的派对的原因。 就像在晚餐中加入墨西哥辣椒。 我知道您和您的人已经在这个岛上打探了几个星期了。 我知道这一定与勒弗朗索瓦的海盗男爵和安杰伦.德.谢沃有关。 把一切都告诉我的朋友, 作为回报, 我们会保密您的传奇名字。 否则我会叫守卫 , 他们已经站在门后了。 我在您到达时就叫了他们。 ";
			link.l1 = "... ";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "不仅仅是他们!安杰伦送给我一条项链, 一条漂亮的项链!包括这颗像南方夜晚一样黑暗的大而干净的珍珠, 在中间。 但他是从当地珠宝商那里订购的!";
			link.l1 = "... ";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "我打赌他这样做不仅仅是为了用奢侈品取悦我。 尽管, 那份礼物是他在体面范围内赢得我好感的最后手段。 安杰伦没有头衔和土地, 甚至他的护卫舰在他父亲决定之前仍然是他唯一的。 他利用权力和影响力, 但他自己没有收入来源。 也许他厌倦了等待父亲的捐款, 决定解决自己的财务状况?";
			link.l1 = "等等, 夫人!纸牌游戏!如果我们是对的, 而德.谢沃提前计划了整个事情, 他一定需要很多钱来下注, 以便足够狠地逼我们的总督。 向父母要这么多钱可能会让他父亲注意到这件事。 从私掠者那里偷已经被偷的宝藏似乎是获得所需硬币的安静而安全的方式。 没人会知道!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "为我们干杯, 查尔斯!安杰伦这次不能逃脱惩罚。 他对我的控制已经太过分了, 我想帮助您确保这一点。 ";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "一个失败的海盗和一个几乎被迷住的交际花。 查尔斯, 您为自己找到了一个梦幻团队!";
			link.l1 = "尽管如此, 谢谢你们, 两位。 真诚地!现在我需要稍微思考一下, 制定一个计划。 ";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "这所房子里有客人想要的一切。 我会安排的。 准备好了就加入我们, 查尔斯。 ";
			link.l1 = "很好, 夫人。 ";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "没什么, 但镇上有人在找他。 他们正在积极询问您和那晚的其他客人。 我还不知道发生了什么, 但我肯定您卷入了比您想象的更大的事情。 ";
			link.l1 = "更大的事情?您是什么意思, 朱莉安娜?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "安杰伦... 我是说德.谢沃先生送给我一条奇妙的珍珠项链作为礼物。 其中一颗珍珠黑如夜晚。 我以为这只是一个有美好故事的假货。 我从未戴过它, 不想给人虚假的希望, 但它美得令人着迷。 ";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "您会怎么做, 查尔斯?您知道发生了什么吗?";
			link.l1 = "还不知道, 但我会知道的。 德.谢沃深陷某件严重的事情, 这是我的机会。 他的祖国不敢碰他, 但英国当局可能会。 我宁愿不绑架您, 朱莉安娜。 ";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "您真贴心, 查尔斯, 但不好笑。 ";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "查尔斯, 您学到了什么吗?您看起来很紧张... 怎么了?";
			link.l1 = "该死的!我希望事情不同... 收拾东西, 我们该走了, 侯爵夫人。 请不要制造麻烦。 ";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "查尔斯, 进来。 男爵已经到了, 我们聊得很愉快。 我刚刚告诉他您对正在发生的事件的兴趣。 ";
			link.l1 = "朱莉安娜, 我不确定这是否明智... ";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "男爵, 看来您的人刚在门后掉了什么东西!请告诉他们注意举止好吗?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "太可怕了!我们现在该怎么办?!";
			link.l1 = "该死的!我希望事情不同... 收拾东西, 我们该走了, 侯爵夫人。 请不要制造麻烦。 ";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "全能的上帝!先生们, 你们把我的客厅怎么了?!这看起来像中世纪的噩梦!这些人是谁?卫兵在哪里?";
			link.l1 = "你没事吧, 朱莉安娜?很好。 我敢打赌守卫们正在酒馆里花他们应得的贿赂。 男爵, 恭喜您 —您成功地把'好人杰克'惹毛了。 如此混乱和准备不足的暗杀企图根本不是他的风格。 ";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "很抱歉打断你们精彩的讨论, 但除非你们有人受伤了, 否则我们还是去内室吧。 这种景象对女士来说不太舒服... 只有天花板没沾血! ";
			link.l1 = "那您上楼吧, 侯爵夫人。 您真的应该躺一会儿, 远离这些血迹。 科特尼男爵和我会谈清楚的。 我们继续好吗? ";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "查尔斯, 你准备好和我们分享你的计划了吗? ";
			link.l1 = "差不多了。 告诉我, 德.谢沃是个拘泥细节的人吗? 他的账簿和日志都整理得井井有条吗? ";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "安杰伦在财务方面简直是拖沓的化身! 他签的文件比我认识的任何银行家都多。 我猜他从小就这样, 那时他不知道自己的父亲是谁, 在街上过着贫困的生活。 ";
			link.l1 = "太好了! 现在我们需要他的日志和账簿! 这些可以作为给英国人的有效证据。 我们必须想办法拿到它们! 真希望我在拥有他的船时就知道这个... 唉。 ";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "等等, 查尔斯, 你真的认为在发生了这一切之后, 我会允许自己像农场的山羊一样被卖给德.谢沃吗? ";
			link.l1 = "别担心, 朱莉安娜, 这只会持续几天。 我保证他们会把你当作中国的无价花瓶一样对待。 如果我错了请纠正我, 但德.谢沃绝不会亲自出现在交换现场, 对吗? ";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "我确定。 安杰伦会躲在弗朗索瓦.德.里昂的庇护下, 绝不敢在公海上与你见面。 但关于我的这次被俘... ";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "查尔斯, 抱歉打断一下, 但你是不是忘了问我对这一切的看法? 在那些吱呀作响的棺材里待上几周... 你甚至意识到你在要求我做什么吗? 显然你对那个... 女孩很在意, 但我不是你的船员! 抱歉, 但这一切听起来不像是个严肃的爱情故事。 ";
				link.l1 = "恐怕, 侯爵夫人, 我必须坚持。 我不能失去她。 ";
				link.l1.go = "Julianna_127";
				link.l2 = "我们都会犯错, 朱莉安娜。 你最应该明白这一点。 我请求你帮助我。 ";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "查尔斯, 抱歉打断一下, 但你是不是忘了问我对这一切的看法? 在那些吱呀作响的棺材里待上几周... 你甚至意识到你在要求我做什么吗? 你的感情值得写进骑士文学, 但我只是个普通的交际花。 我敬佩你并想帮助你, 但凡事都有个限度! ";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "我理解, 查尔斯。 我愿意相信完美的真爱, 但我想这世界上不存在这样的东西。 ";
				link.l1 = "谢谢你, 侯爵夫人。 这次我会把一切做好。 我从这个故事中学到了很多, 祈祷我不会为所做的事付出太可怕的代价。 ";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "你已经下定决心, 我一直支持你, 但够了。 为了你在我卧室里已经放弃的爱情而牺牲一切, 这很感人, 查尔斯, 但我不再年轻天真了。 ";
				link.l1 = "恐怕, 侯爵夫人, 我必须坚持。 我不能失去她。 ";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "好吧, 船长, 你想怎么做就怎么做。 我不会反抗, 但要知道我是被迫的。 ";
			link.l1 = "随你怎么看我, 朱莉安娜, 这是我应得的。 但无论如何我都会把她救回来。 朱莉安娜, 听着, 我知道我在要求你什么。 放弃一切, 让别人把你拖入一场可疑的赌博。 但现在你是我唯一的希望! 我需要你的帮助, 我会永远欠你的人情! ";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "很好, 船长。 最终, 安杰伦必须被彻底解决。 我会帮你, 但告诉我你打算怎么把我从他的船上救出来? ";
			link.l1 = "... ";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "等等。 你可以拿走我项链上的珍珠, 英国人不是在找黑珍珠吗? 这颗能让他们听你说话。 接下来呢? ";
			link.l1 = "接下来我会带上调查员, 我们航行到瓜德罗普。 等德.谢沃的护卫舰载着你返回时, 我们会进行正式搜查.'墨丘利'事件涉及我们的盟友, 是严重事件, 因此德.里昂必须允许搜查! ";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "他会告诉所有人是他的人把我从囚禁中救出来的。 注意, 船长, 我还没决定该怎么跟他们说。 ";
				link.l1 = "什么都不说就好, 侯爵夫人。 相信我, 我会把你救出来, 让安杰伦付出代价。 ";
			}
			else
			{
				dialog.text = "我会告诉他们我是被陌生人从家里绑架, 然后被带上安杰伦的船。 这看起来就像他雇了雇佣兵绑架我。 ";
				link.l1 = "又给安杰伦的棺材钉了颗钉子, 侯爵夫人。 ";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "给我到早上的时间, 除非你想把我装在麻袋里扛走。 再派几个人来帮我 —像我这样身份的女人出行不能没有必需品。 查尔斯, 你救了我, 我会帮你, 也请收下这颗无价的黑珍珠, 作为我的礼物。 如果这能成功, 我们就两清了。 ";
				link.l1 = "如你所愿, 侯爵夫人。 祝你们好运! 事情结束后在这里再见。 ";
			}
			else
			{
				dialog.text = "我天亮前就能准备好。 我不想在货舱里颠簸, 所以确保给我准备一个像样的房间, 不管你怎么称呼它。 查尔斯, 拿着这个。 这是珍贵的黑珍珠。 我知道它比这地方还值钱, 但有些东西无法用黄金衡量。 希望它对你有用。 上帝保佑你! ";
				link.l1 = "祝你们好运! 事情结束后在这里再见。 ";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "恭喜你, 船长。 你的计划成功了。 你策划了一场多大的丑闻啊! 英国人逮捕了安杰伦和他的船, 除了我之外的所有东西都被没收了。 ";
				link.l1 = "威廉爵士甚至没来道别。 他答应过会道歉的。 ";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "查尔斯, 我们成功了! 他们随时会释放你! 不过我们必须尽快离开这个岛。 总督对安杰伦最近被捕非常不满。 ";
				link.l1 = "很高兴见到你, 朱莉安娜。 你怎么样? 交换进行得如何? 她没事吧? ";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "我猜他太忙了没时间。 就像我们的总督现在一样。 你最好在他想起你之前离开镇子。 他确实喜欢亨利的儿子, 但英国报纸把他逼得走投无路了。 我不会等他决定把所有怨气都发泄在你身上。 ";
			link.l1 = "有道理。 而且她在马提尼克等我。 交换进行得如何? 她没事吧? ";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "原谅我, 但我不想谈这个。 你问她吧。 再见, 船长。 我自己回去。 我需要远离大海休息一下 —弗朗索瓦在不被无聊的英国官员打扰时是个不错的主人。 ";
			link.l1 = "对此我真心抱歉, 夫人。 无论如何感谢你的合作。 很高兴听说你有了新的... 朋友。 ";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "也谢谢你, 查尔斯, 谢谢你信守承诺。 去圣皮埃尔我的家里找巴塞洛缪。 再见。 我们会再见面的。 ";
			link.l1 = "再见, 朱莉安娜。 祝你平安。 ";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "我没见到她, 但巴塞洛缪把她活着健康地带走了。 那个英国人就在当地总督的眼皮底下逮捕了德.谢沃和他的财产 —他甚至一句话都没说! 太神奇了! ";
			link.l1 = "你知道吗, 考虑到这次逮捕的背景, 事情进展得异常顺利。 尽管如此, 这以后肯定会有麻烦。 不管了! 我必须立刻去马提尼克, 我必须尽快见到她! ";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "毫无疑问你们有很多话要对彼此说。 哦, 查尔斯, 我希望身边有个像你这样眼神充满热情的男人。 我们快点吧, 我真的想念热水澡和干净的床单。 巴塞洛缪会在圣皮埃尔我的家里等我们。 ";
			link.l1 = "是啊, 海上的浪漫被高估了。 你可以用我的船舱, 侯爵夫人, 这是我至少能做的。 走吧。 ";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "查尔斯, 你已经为我做了所有可能的事。 你让一个愤世嫉俗的女人再次相信了。 ";
			link.l1 = "我也是, 朱莉安娜。 我也是。 ";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "查尔斯, 真高兴你来了! 你的那位女士怎么样了? 她没事吧? ";
				link.l1 = "一切都好, 谢谢你, 朱莉安娜。 我想再对你说一次。 你是个了不起的女人, 我会永远感激你的勇气和智慧。 ";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "查尔斯, 真高兴你来了! 你的那位女士怎么样了? 她没事吧? ";
				link.l1 = "一切都好, 谢谢你, 朱莉安娜。 我想再对你说一次。 你是个了不起的女人, 我会永远感激你的勇气和智慧。 ";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "也许该是我欠你人情了。 毕竟你把我从两个极其讨厌的主顾手中救了出来。 我想我还欠你。 查尔斯, 你想要什么都可以开口。 ";
			link.l1 = "既然如此, 我确实有个小忙想请, 我的女士。 你可以做件事让我们两清。 ";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "我洗耳恭听, 我的船长。 是什么? ";
			link.l1 = "人都会犯错, 但这并不意味着世界是坏的。 记住这点, 开心点, 朱莉安娜。 你值得幸福。 ";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "我... 我会试试, 查尔斯。 谢谢你。 你会时不时来看我吗... 作为朋友? 你在我这里永远受欢迎! ";
			link.l1 = "感激不尽, 侯爵夫人。 再见, 记住你答应我的事。 ";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "但显然我还不够了不起... 但我很高兴你有个好结局。 你不欠我什么, 你所做的一切让我感激不尽! 你靠岸时来看我。 作为朋友, 你在我这里永远受欢迎! ";
			link.l1 = "谢谢你, 侯爵夫人。 祝你一切顺利。 再见! ";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "查尔斯, 我的朋友, 你太无礼了 —多久才来看我一次! 你知道吗, 我想你了? 想来点酒吗? 我迫不及待想亲耳听听精彩的故事! 还有试试你那著名的运气! ";
			link.l1 = "侯爵夫人, 我只是想打个招呼, 确认你没事。 ";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "我的朋友, 你终于来了! 很高兴再次见到你! ";
			link.l1 = "... ";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "好吧, 先生, 你对待我朋友的方式让我别无选择。 我接受你的挑战。 时间和地点? ";
			link.l1 = "就在这里, 现在。 叫仆人来, 让他们拿蜡烛来, 这样舒适的暮色可不行。 这地方必须亮如白昼! ";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "我的朋友, 请不要太个人化。 安杰伦确实是个讨厌的家伙, 但你不应该狙击他。 把这留给我吧。 ";
			link.l1 = "您确定吗, 大人? 他喝得像我那在岸上待了一周的军需官, 但他肯定知道如何用剑。 我一眼就能看出来。 ";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "上帝保佑, 查尔斯! 我不会和他决斗。 我们会赌博, 牌是文明人的武器。 我会让他输光, 让他去找你借钱才能安全返回魁北克。 ";
			link.l1 = "这确实是个可靠的计划。 但如果你问我, 我宁愿那混蛋死了, 而不是变穷。 祝您好运, 大人! ";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "该死的, 安杰伦, 那里不可能是十点! 不可能! ";
			link.l1 = "这是在指控吗? 是你发的牌, 先生。 ";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "不是。 我只是... 有点激动, 我道歉。 这是个意外, 我要求重赛的机会! 这艘船, 我... 必须赢回来! 或者去他的游戏, 直接告诉我你愿意以多少价格卖给我? 说出价格, 我保证明天中午前付清! ";
			link.l1 = "唉, 但我真心相信, 赌输的战利品无法买回来。 你只能赢回来。 现在长笛号是我的了, 我无意出售。 很抱歉你的热情让你陷入这种境地, 有时我们应该更现实地看待自己的能力... 也许你还有更多船的文件? ";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "你是个人渣, 安杰伦, 你把我逼到了墙角。 我相信我能给出一个你会接受的赌注。 ";
			link.l1 = "... ";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "查尔斯, 你是我唯一的希望, 我求你帮帮我! 那艘长笛号和她的... 货物已经卖给了荷兰公司。 我明天必须把所有文件交给他们。 我本想在这里待一整晚, 所以把文件带来了。 如果交易失败, 我将面临灾难性的局面! ";
			link.l1 = "但是‘亲爱的雅克’, 你不觉得你喜欢的那个女人现在面临着更灾难性的局面吗? 我也赌过, 我理解赌船这种事, 即使船不是自己的。 但赌一个女人? 你真让我惊讶, 真的! 现在你只关心你交易的命运? ";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "别评判我, 查尔斯。 喜欢一个有权势伯爵的前女友, 甚至只是短暂地爱上, 与欠彼得.斯特伊弗桑特一百万比索相比算不了什么。 我该如何向他的代理人解释? 想象一下所有的名誉损失! ";
			link.l1 = "我以前也有过类似的债务, 但我当时一无所有, 还是挺过来了。 你也会的。 回头见, 雅克。 我不能保证什么, 甚至不会问是什么货物值得一百万, 让你把它放在长笛号上。 ";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "你来了, 查尔斯。 我正要派人找你。 德.谢沃坚持要决斗, 已经拒绝任何和解的机会。 你牌打得很好, 但你确定要继续这样做吗? ";
			link.l1 = "我有个强烈的怀疑, 大人, 这结果正是你一直想要的。 所以我说好。 这必须彻底解决。 决斗的条件是什么? ";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "你太自以为是了, 我的朋友。 我们世界的某些部分仍然不围绕你转。 相信我, 我对昨晚的一切深感失望。 非常失望。 但首先, 让我们谈谈你... winnings的命运。 ";
			link.l1 = "好吧。 你想知道如何归还你的长笛号, 还是朱莉安娜夫人怎么样了? ";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "我看你把不恰当的讽刺变成了恶意? 查尔斯, 我们是同一阵线的, 别忘了。 ";
			link.l1 = "这论点值得商榷, 大人。 简而言之。 现在我们从哪里开始: 船还是那位女士? ";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "当然是斯特伊弗桑特的交易 —他的代理人一早上都在等我, 我已经找不到借口了。 我需要长笛号的文件, 查尔斯。 ";
			link.l1 = "好吧。 她是你的了。 我认为德.谢沃玩得不诚实, 因此你可以以半价15万赎回你的财产。 ";
			link.l1.go = "governor_18";
			link.l2 = "我很乐意帮忙。 你说这艘船的成本是多少? 50万? 对我来说可以。 ";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "现在, 包括税费在内是四十六万比索。 成交。 13.5万。 ";
			link.l1 = "听着... 我吵累了。 所以付钱吧, 拿到你的文件, 结束这件事。 ";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "你对老朋友一点都不怜悯, 对吧查尔斯? 现在, 包括所有税费... ";
			link.l1 = "牌债和友谊毫无共同之处, 大人。 作为买家, 你得自己交税, 否则我就把船卖到勒弗朗索瓦。 注意, 我还没打算利用你的地位... 暂时。 ";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "好吧, 就这样。 现在, 决斗的事。 我不想和德.列维.旺塔杜尔伯爵惹麻烦, 因此一切都必须尽可能合法。 你听到了吗, 查尔斯? 依法行事! 我会派两名驻军军官陪同你 —他们都是高贵且受人尊敬的人。 他们将成为你的副手, 而不是你通常的... 同伴。 我希望在事情解决之前一切都清清楚楚! ";
			link.l1 = "你真好。 如果我们的好朋友决定耍阴招怎么办? 我更愿意把后背交给我称为朋友的人, 那些知道在这种情况下该怎么做的人, 而不是出生在名门望族的人。 ";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "查尔斯, 别表现得好像这场决斗是你我之间的事。 这是严肃的事。 德.谢沃不是那种你杀了就能逃脱的人。 任何结果都会伴随着调查, 甚至可能是法庭。 我们需要可靠的证人。 看, 我在照顾你! 但最重要的是你不能杀他。 我知道, 安杰伦意志坚定, 很可能是个不错的战士, 但是查尔斯, 你不能杀他! 打伤他, 甚至羞辱他, 但到此为止。 如果你杀了他 —会有后果, 我们都无法逃避或幸存。 尽管德.列维.旺塔杜尔伯爵从未正式承认过他的私生子, 但他没有其他儿子。 他的愤怒将无穷无尽。 ";
			link.l1 = "太好了, 所以我宁愿让自己被杀, 也不愿让愤怒的伯爵把你从总督的位置上踢下来? ";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "恐怕如果你不听, 我们活不了多久, 安杰伦.德.谢沃会比我们活得长。 记住这一点, 小心点。 决斗定在今晚十点, 在镇门外。 我的军官会在那里等你。 现在, 最后一件事: 朱莉安娜.博托夫人 —她怎么样了? ";
			link.l1 = "你想知道我是否已经利用了我的战利品? 不, 大人, 还没有, 或者永远不会 —这不重要。 重要的是你永远不能再去侯爵夫人的家。 她对此非常明确。 我不能为此评判她。 朱莉安娜会自己选择下一个主顾。 ";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "你总能给人惊喜, 查尔斯。 不管怎样, 我有个和公司代理人的乏味会议要参加。 你也该走了, 做好准备, 记住我警告过你的话。 ";
			link.l1 = "我一定会试试, 大人。 但这是场战斗, 所以不能保证。 谢谢你的帮助。 ";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "你还活着, 查尔斯! 真让人放心, 你怎么样? 这是血吗? ! 德.谢沃怎么样了? ";
			link.l1 = "不幸的是, 他还活着。 他受伤了, 不严重。 他不得不逃跑, 但他还派了暴徒攻击我们。 简而言之, 有些血不是我的。 ";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "混蛋! 我的人呢? 他们还活着作证吗? ";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "他们没事, 大人。 有点受伤, 但能活下来。 ";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "不是所有人都没事, 大人。 有一位绅士没挺过来 —德.谢沃特意带了火枪手。 我无能为力。 ";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "那里简直是地狱, 大人。 两位勇敢的绅士都在战斗中牺牲了。 如果不是他们, 我就麻烦了。 德.谢沃策划了一场完美的伏击。 ";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "太好了! 我会在可靠证人面前拿到他们的书面证词。 德.谢沃会为此付出代价! ";
			link.l1 = "我认为我们甚至无法对他的名声造成丝毫损害。 我宁愿找到他, 不顾你的所有警告, 亲自完成这件事。 这样的懦夫不值得活着。 ";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "太可怕了。 但我们至少会从一个证人那里拿到书面证词。 德.谢沃会为此付出代价! ";
			link.l1 = "我认为我们甚至无法对他的名声造成丝毫损害。 我宁愿找到他, 不顾你的所有警告, 亲自完成这件事。 这样的懦夫不值得活着。 ";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "该死的他! 他们是好人, 查尔斯! 我发誓, 那混蛋会付出代价! ";
			link.l1 = "我认为我们甚至无法对他的名声造成丝毫损害。 我宁愿找到他, 不顾你的所有警告, 亲自完成这件事。 这样的懦夫不值得活着。 ";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "忘了吧, 查尔斯。 那混蛋自己已经造成了所有必要的伤害。 我敢打赌他现在在逃亡, 躲在某个贫穷殖民地的角落里。 他现在不太可能对你构成威胁了。 这种恶行只是逃跑的蛇咬了一口。 你看起来也受伤了, 需要医生吗? ";
			link.l1 = "谢谢您的关心, 大人, 但我没事。 ";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "很高兴知道。 现在你可以松口气了, 故事结束了。 放松一下, 回到你的事情上去。 顺便说一句, 关于那个... 我们之前没聊完你最近的 winnings。 你决定怎么处理... 它了吗? ";
			link.l1 = "我不太明白你的意思, 雅克。 什么‘它’? 你是指侯爵夫人吗? 该死! 博托夫人! 德.谢沃在逃亡, 他不再威胁我了, 但他很绝望, 什么都做得出来! 我该走了! 派卫兵去侯爵夫人家! 现在! ";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "你说的是那位著名船长? 就是几乎把这个小镇夷为平地击退西班牙进攻的那位? 我知道了。 你想喝什么? ";
			}
			else
			{
				dialog.text = "你说的是那位著名船长? 我从没听说过你... 你想喝什么? ";
			}
			link.l1 = "... ";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "黑皮诺, 和我们美丽的女主人一样? 在尝过这么多海盐之后, 你确定还能好好品尝吗? 通常, 你这种身份的人更喜欢喝能溶解旧靴子的东西。 ";
			link.l1 = "如果这是建议我们一起出门, 那我同意。 我也不喜欢你, 很高兴我们想法一致。 别废话了, 反正你也不擅长。 我让你选择条件和武器。 ";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "一股泥土和猫尿的味道? 真迷人! 他们甚至不在桶里陈酿这种酸垃圾, 因为它永远成不了酒。 告诉我, 海盐把你的味觉破坏得这么严重吗? ";
			link.l1 = "如果这是建议我们一起出门, 那我同意。 我也不喜欢你, 很高兴我们想法一致。 别废话了, 反正你也不擅长。 我让你选择条件和武器。 ";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "哈, 真是个勇敢的男孩! 现在冷静点, 保持距离。 我们不在酒馆, 我也不是你的酒友。 你远低于我的阶层, 我们甚至不应该说话, 但那位女士要求这样。 现在, 雅克和我有笔未了结的生意... ";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "朱莉安娜, 你没事吧? 水, 你们这些蠢货! 拿水来! ";
			link.l1 = "... ";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "你说得对, 这里很闷热。 到目前为止, 这是一场非常有趣的游戏, 但在决赛前让我们稍作休息。 再见, 雅克 —记住我们比赛的规则? \n还有这位查尔斯.德.莫尔, 对吗? 我记得你, 一个品味很差的船长。 别担心, 等我在这里结束后, 你就只能喝水了。 所以慢慢享受, 喝点东西。 等你准备好了, 到这个小房间来见我。 我们将在更舒适的环境中结束今晚... ";
			link.l1 = "很期待, ‘先生’。 ";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "你终于来了。 准备好输钱了吗? ";
			link.l1 = "我宁愿把你的钱赢过来。 请吧! ";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "说得好, 可惜我们亲爱的总督在他可耻的失败前坚持要改变规则。 现在我们必须在赌注之外再加些东西。 赌注必须被双方认可为平等。 我的赌注是带银饰的长笛号。 ";
			link.l1 = "得了吧, 这太无聊了 —我突袭几周就能弄到五艘带黄金的。 给我更大的赌注。 ";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "是的, 我见过你的船, 必须承认它确实很壮观。 那我们提高赌注吧 —两艘对一艘。 我的护卫舰和带银饰的长笛号换你的船? ";
				link.l1 = "一场有价值的游戏! 博托夫人错了 —这场决斗将成为传奇。 成交! ";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "看看我们的船长, 真是个调皮的男孩! 不过, 私掠是神圣的。 那来艘战船怎么样? 一艘48门炮的护卫舰。 比许多轻巡洋舰还快 —皇家造船厂的产品, 又被世界上最好的造船师进一步改进。 她携带的长炮射程和精度都很好。 你觉得如何? ";
					link.l1 = "好多了, 我加入! 开始吧! ";
				}
				else
				{
					dialog.text = "我听说了你停在这里的船, 船长。 你应该庆幸我同意接受你那破旧的船作为赌注。 来吧, 除非你拒绝? ";
					link.l1 = "好吧, 你说得有道理。 开始吧。 ";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "游戏结束, 船长, 你得到了想要的。 如果你想幸灾乐祸就来吧。 我建议我们明天中午讨论赎回我护卫舰的条件。 ";
					link.l1 = "就这样? 我真心相信, 和你一样, 赌输的东西无法赎回, 只能赢回来。 或者我可以把她当木材卖给当地渔民, 告诉他们你慷慨的捐赠。 ";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "看来命运有她的安排。 这结果真有趣。 恭喜你, 德.莫尔船长。 我建议我们明天中午讨论赎回我护卫舰的条件。 ";
						link.l1 = "这么快? 我们让其他客人失望了, 先生。 如果我没记错, 你还有一艘船。 我真心相信, 和你一样, 赌输的东西无法赎回, 只能赢回来。 ";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "看来命运有她的安排。 这结果真有趣。 恭喜你, 德.莫尔船长。 你该喝杯像样的酒, 试试桑娇维塞。 我想雅克会出高价买你这艘破船, 他似乎对它的感情比对其他东西深得多。 这足够买瓶像样的酒了。 ";
						link.l1 = "已经投降了? 我们让其他客人失望了, 先生。 如果我没记错, 你还有一艘船。 我用你的护卫舰换我的长笛号加银饰, 因为你觉得我的船太普通了。 ";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "运气不好, 船长。 不过, 我欣赏你的勇气, 加上我今天心情好。 我拿走你的黄金, 但你可以保留你的船。 滚出我的视线, 以后别再赌博了。 总有一天, 这会要了你的命。 ";
				link.l1 = "你真高尚, 我没料到。 再见, 德.谢沃先生。 ";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "幸灾乐祸和嘲笑被击败的对手之间有明显区别, 德.莫尔先生。 ";
			link.l1 = "已经认为自己输了? 但一切才刚刚开始... 啊! 博托夫人, 相信你的沙龙又有了一个关于言行不一的精彩故事! ";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "你还想要什么? 我没有更多的船了, 甚至没有足够的现金来支付哪怕一艘船的费用。 在我们今晚所见之后, 赌金币已经不严肃了。 ";
			link.l1 = "你比我们亲爱的雅克.迪勒.杜.帕克还缺乏资源吗? 我给你一个绝佳的机会来证明不是所有的爱都可以买卖。 命运也不售卖她的青睐。 银船和你的护卫舰, 赌你比黄金更看重的东西。 ";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "船长, 这一点都不好笑。 我们结束吧 —天快亮了。 我们明天讨论我护卫舰的赎回问题。 ";
			link.l1 = "好吧, 你赢了 —三艘船! 包括一艘真正的战船, 赌新世界最... 昂贵的女士。 你能拒绝这样的赌注吗? ";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "这太疯狂了。 不过, 这确实是疯狂, 德.莫尔先生。 来吧。 但记住, 这是你的主意。 ";
			link.l1 = "这将成为一年内上流社会私下里津津乐道的传奇! 喂, 再来点酒和蜡烛! 游戏必须继续! ";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "就在不久前, 你还认为这艘长笛号不足以作为对抗我们船只的赌注。 发生了什么变化? ";
			link.l1 = "觉得无聊了。 让我们给决斗加点料 —你的护卫舰和我的船赌... ";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "你如此轻视的长笛号? 你发烧了吗? 你看起来不太好。 ";
			link.l1 = "我好得很, 谢谢你。 你没听明白。 二比一的赌注不够精彩, 所以我们把赔率拉平! 不是所有贵重物品都能用黄金衡量, 你不同意吗? 或者也许你只是不想逆风而行, 如果事情不按计划进行, 你就改变方向? 真遗憾, 看来我错看你了。 博托夫人, 我相信你的沙龙又有了一个关于言行不一的精彩故事... ";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "别想激怒我, 德.莫尔先生, 你太天真了, 做不到。 ";
			link.l1 = "确实。 缺乏意志不是罪... 当然, 除非你是军人。 或者贵族, 你可能知道, 家族荣誉有时是种负担。 不过你不太可能熟悉这种困境。 ";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "你是想开始决斗还是继续游戏? ";
			link.l1 = "两者都行。 在你振作起来的时候, 我会称赞侯爵夫人的酒藏。 ";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "那就这样吧。 今晚应该有个 proper 的结局。 两艘伟大的船, 赌装满白银的破船和新世界最棒的女人! 深呼吸, 德.莫尔先生, 这个赌注将成为上流社会八卦中的传奇。 ";
			link.l1 = "你的失败确实会成为传奇, 德.谢沃先生。 给我们再来些酒和蜡烛! 开始吧! ";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "你被运气冲昏了头脑, 德.莫尔先生。 你在这儿冒险, 运气的眷顾是短暂的。 ";
			link.l1 = "短暂的眷顾是通往真爱的道路。 而买来的忠诚只能带来轻蔑或厌倦。 ";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "你想激怒我的尝试很有趣。 你最好问问朱莉安娜夫人关于眷顾。 爱情以及所有能买或不能买的东西。 但动作快点 —她明天就离开镇子了。 ";
			link.l1 = "至少你对这个话题的了解是片面的。 你无法通过赢牌或花钱来赢得命运女神的眷顾, 因此你不懂她的爱。 这需要勇气, 先生, 以及承担风险的坚定意志。 更不用说更多... 世俗的女士也看重这些东西。 我用我的两艘船赌你的一艘, 你敢吗? ";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "你这么急切地想继续? 好吧, 随便。 但至少让我们加点戏剧性, 德.莫尔先生。 你刚才在说爱情和代价? 我特此建议平衡我们的赌注 —你的那艘破船和带银饰的长笛号, 赌我的护卫舰和新世界最棒的女人。 你现在怎么说? ";
			link.l1 = "我说你绝对知道如何优雅地赌博, 先生! 再来点酒和蜡烛! 开始吧! ";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "难以置信, 德.莫尔先生, 这太难以置信了! ";
				link.l1 = "是啊, 自罗克鲁瓦战役以来, 欧洲还没见过这样的惨败, 德.谢沃先生。 我体内某个艺术家正渴望描绘这一历史时刻。 可惜我不像年轻时那样画画了。 但朱莉安娜夫人身边一定有才华横溢的画家, 对吧? ";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "运气不好, 船长。 不过, 我欣赏你的勇气, 加上我今天心情好。 我拿走你的黄金, 但你可以保留你的船。 滚出我的视线, 以后别再赌博了。 总有一天, 这会要了你的命。 ";
				link.l1 = "你真高尚, 我没料到。 再见, 德.谢沃先生。 ";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "不, 你不明白。 这太难以置信了, 简直不可能! ";
			link.l1 = "我们都看到了牌, 德.谢沃先生 —命运从不说谎。 ";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "命运不说谎, 但你, 德.莫尔先生, 你说谎! 在我看来, 你的傲慢背后不是激情, 而是计划。 你是个骗子 —我准备在所有客人面前证实这一点。 ";
			link.l1 = "... ";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "德.谢沃先生, 我没听错吧? 你准备好不仅用言语证实你的怀疑了? 看来你的侮辱太过分了, 而我, 与你不同, 看重家族荣誉。 ";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "次子。 骗子和骗子没资格跟我谈家族荣誉! 闭嘴, 朱莉安娜, 我稍后再跟你说! 查尔斯.德.莫尔, 我坚持你立即给我满意的答复! 用剑还是手枪? ";
			link.l1 = "两者都要。 说实话, 我很高兴你改变了主意。 还记得我建议我们出门走走吗? 你说我阶层低下? 也许牌局终于给了你点勇气? ";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "太荣幸了, 但我同意侯爵夫人的看法。 我会像个贵族一样了结你, 德.莫尔, 尽管你不配。 我挑战你明天中午决斗, 通过总督大人。 你自己来见他, 或者派副手来讨论条件。 再见, 夫人, 向你致敬。 ";
			link.l1 = "... ";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "你来了, 命运的宠儿。 照顾好你的东西了吗? 没忘记忏悔吧? 据说没有忏悔的地狱会很不舒服。 ";
			link.l1 = "空谈无用, 先生。 你牌打得不好, 现在让我们试试你的击剑技巧... 来跳舞吧! ";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "漂亮... 一回合, 该死的你。 但我还活着! ";
			link.l1 = "你的伤口看起来不妙, 但无论如何你应该去看医生。 显然, 你不能再这样下去了, 否则会死的。 看来我们在这里结束了。 我赢了, 而且我没有作弊。 我会把你的船还给你, 你离开圣皮埃尔。 我们再也不会见面了。 ";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "多么伟大的骑士精神! 看, 德.莫尔先生, 你可能是个天生的剑客, 但你打牌肯定作弊了。 我三次动了牌堆。 三次, 该死的! 世界上没有奇迹能救你, 但你还是赢了! 我希望知道你是怎么做到的... 不管了, 很快你就会把一切都告诉魔鬼。 上啊, 伙计们! ";
			link.l1 = "你这个混蛋! 我对你仁慈, 你就这样回报我? ! 先生们, 拿起武器! ";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "我承认, 德.莫尔先生, 看到你在这里我有点惊讶。 这意味着我对你的看法没错, 那个野丫头对你很重要? ";
			link.l1 = "我想知道你的好朋友德.里昂对绑架我们海军 respected 船长的军官是什么态度? 也许我们应该请他加入我们, 告诉他整个故事? ";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "相信我, 这对你一点帮助都没有。 而且我对待你的女人比对待被俘的将军还好。 目前是这样。 但一切都可能改变, 这取决于你, 查尔斯。 ";
			link.l1 = "我不记得我们和你有过情人之间的争吵。 别叫我查尔斯, 德.谢沃先生。 直奔主题, 告诉我你想从我这里得到什么? ";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "从你这里? 什么都不要, 上帝保佑! 你和我只是在一场丑闻般的牌局后解决了一场不幸的争斗, 喝了几杯, 然后像老朋友一样离开了这个房间。 ";
			link.l1 = "安杰伦, 尽管你最近受了伤, 但你看起来还不错, 而这场无意义的闲聊让我越来越想纠正这一点。 甚至想到要弄脏弗朗索瓦.德.里昂的这些精美地毯, 我就越来越感兴趣。 ";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "但老弗朗索瓦喜欢这些地毯, 查尔斯。 每个人都有喜欢的东西。 既然你来了, 你一定喜欢你那位穿军装的小女朋友。 我准备用我的财产交换她。 你搞砸了游戏, 尽管我通常不原谅这种违规行为, 但我可以为你破例。 你把我想要的奖品给我, 我也把你的给你。 然后我们优雅地分道扬镳。 这就是爱。 ";
			link.l1 = "你以为我把侯爵夫人像他妈的珠宝一样带在钱包里吗? 胡说! 我怎么可能把她给你? ! ";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "我一点都不在乎, 查尔斯。 你有两周时间处理这件事。 是的, 我希望这个奖品是秘密交接的。 比如说, 某个赢了一个贵得离谱的交际花却没能赢得她青睐的船长, 可能会为此做些蠢事, 对吧? 我觉得你已经够绝望了, 查尔斯? ";
			link.l1 = "我想先看看我的军官, 以确保她还活着。 ";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "不可能。 你得相信我的话。 她在一个安全的地方, 在我得到我的奖品之前她会一直待在那里。 但如果你继续坚持要先见她, 我会很高兴地送你她的一部分。 你最喜欢哪部分? 一只耳朵, 一个鼻子, 还是几根手指? ";
			link.l1 = "你敢碰她一根手指, 你这个混蛋, 我发誓会亲手掐死你! 别他妈考验我! ";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "冷静点。 即将发生的一切完全取决于你。 我不喜欢暴力, 我只在必要时使用。 别逼我。 只要在两周内到多米尼加的斯科特角把我的奖品交给我, 你就会得到你的。 我不在乎你怎么做。 如果你想偷 —就偷, 毕竟你是个海盗, 只是穿得好点。 ";
			link.l1 = "你真是痴心妄想, 海盗和该死的奴隶贩子之间有很大区别... ";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "深呼吸, 我们即将在老弗朗索瓦面前优雅地游行。 我们现在是朋友了, 记得吗? 微笑, 查尔斯, 来吧! 我们分道扬镳。 多米尼加, 斯科特角, 两周。 别迟到。 ";
			link.l1 = "我会去那里见你。 ";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "晚上好, 博托夫人, 德.莫尔船长。 请保持冷静。 ";
			link.l1 = "侯爵夫人, 到我后面去, 现在! 先生, 这是什么意思? ! ";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "我在门后有十几个人, 还有你们国家授权的紧急权力。 卫兵帮不了你。 因此, 请把剑放下, 先生。 我只是想谈谈。 目前是这样。 ";
			link.l1 = "先生, 你是谁, 怎么进来的? ! 你应该解释一下! ";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "请允许我自我介绍 —威廉.科特尼爵士, 科特尼男爵。 现在让我们都冷静下来谈谈。 ";
			link.l1 = "好吧, 科特尼先生, 我们洗耳恭听。 ";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "请原谅我偷听, 但当前的情况让我别无选择。 尽管我在圣皮埃尔保持匿名, 但我正在代表英国王室进行一项极其重要的调查。 关于一艘在海上失踪的信使船。 听说过双桅帆船‘雷吉娜’号吗? ";
			link.l1 = "没听说过, 我也不明白你这些模糊的暗示, 先生。 我是个诚实的船长... ";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "我他妈一点都不在乎你那些见不得人的小交易, 先生。 我调查过你, 说实话, 当我听说你在‘雷吉娜’号失踪后不久就访问了马提尼克岛时, 我就把你列为了首要嫌疑人。 然而, 你不是傻瓜, 你的人也没在这里摆弄珍珠。 因此, 你暂时排除在我的怀疑之外。 ";
			link.l1 = "珍珠? 你在胡扯什么珍珠? ";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "从西班牙西印度群岛行动中精选的大颗粒珍珠。 而且这些珍珠是黑色的, 这意味着它们极其稀有, 你听说过吗? ";
			link.l1 = "我想听说过, 但我一直以为这只是又一个水手的鬼故事。 就像关于‘飞翔的荷兰人’的故事一样。 朱莉安娜, 怎么了? ";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "我必须请你在这里出示它, 夫人。 这是极其重要的事情。 同时, 先生, 你必须告诉我关于莫雷诺船长的一切。 我怀疑是他给了你那条线索。 我非常想知道他在这场戏中扮演的角色。 ";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "莫雷诺不是他的真名, 科特尼先生。 他的名字是埃尔南多.巴斯克斯, 也被称为‘血腥唐’, 一个西班牙海盗, 曾是臭名昭著的葡萄牙人巴塞洛缪的‘信天翁’号的军需官。 ";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "我们只说了几句话。 我没什么可告诉你的。 他看起来像个真正的海狼。 ";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "天哪。 我可以问问你是怎么知道的吗? ";
			link.l1 = "我以前认识他的船长。 实际上, 是我抓住了他并把他交给了荷兰人。 说来话长。 可惜那时我没抓住巴斯克斯本人... ";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "你自己也是个海狼, 先生。 我不相信你没注意到更多。 ";
			link.l1 = "只是一点口音, 他的样子和举止。 我打赌他是西班牙人, 科特尼先生。 ";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "这是个关键发现, 先生。 而且很糟糕。 夫人, 你找到项链了吗? 让我检查一下。 是的, 这确实是西班牙黑珍珠之一。 看看, 这水手的鬼故事其实是真的。 剩下的就是弄清楚那个德.谢沃是怎么弄到其中一颗的。 顺便说一句, 他不是德.列维.旺塔杜尔公爵的私生子吗? ";
			link.l1 = "正是他。 据我们所知, 他和勒弗朗索瓦的当地海盗男爵有交易。 也许他从他那里买了这颗珍珠? ";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "也许吧。 但我一点都不喜欢这里面的西班牙线索。 不管怎样, 谢谢你的合作。 恐怕我明天同一时间必须再来拜访你。 我也会请德.莫尔船长到场。 也许我会有更多问题问你。 我现在该去勒弗朗索瓦了。 ";
			link.l1 = "科特尼先生, 等等。 也许我可以加入你? 雅克.巴尔巴宗得到他的绰号不是因为他是个可爱温柔的人, 而且这件事我也有点兴趣。 ";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "船长, 我被你的关心感动了, 但不行。 这是国家事务。 那个恶棍知道自己的位置, 不敢对王室使者动手, 否则他那可怜的村庄就不复存在了! 再次为打扰道歉, 夫人。 晚上好。 ";
			link.l1 = "明天晚上见, 男爵。 ";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "别生她的气, 船长。 我很有说服力。 你的故事令人印象深刻, 真的。 我相信我可能会用到你。 ";
			link.l1 = "你看起来很满意, 在勒弗朗索瓦怎么样? ";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "正如我所料, 你的那位男爵像羔羊一样温顺。 他告诉了我所有我想知道的。 正如我所说, 我可以非常有说服力。 ";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "今天我是自己来的, 那扇门后面没有我的人。 搞什么鬼? ! ";
			link.l1 = "我有不好的预感。 朱莉安娜, 到我后面去, 现在! 男爵, 王室使者打起架来也像他们说的那样好吗? ";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "你确实知道如何用剑, 船长! 嗯, 说实话, 这不是在公园散步。 这些人到底是谁? ! ";
			link.l1 = "我们应该问问他们的朋友 —我听到更多脚步声。 真希望是卫兵... ";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "难以置信! 你认为那个混蛋敢这么做吗? ! 他会付出代价的, 我发誓! ";
			link.l1 = "冷静点。 巴尔巴宗会逃避任何指控。 他会告诉你这只是普通的小偷袭击富人住宅。 此外, 他是个该死的海盗, 为什么要在乎当局! 不过, 现在我确定你确实学到了一些真正有用的东西。 我请你与我分享这些知识。 ";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "我不能拒绝, 对吧? 否则下一次尝试可能会成功? 好吧, 我会假装没注意到你语气中的威胁。 就当我是在还你人情。 雅克.金德没有把珍珠卖给你那位高贵的混蛋。 他在买。 就这样。 ";
			link.l1 = "所以是德.谢沃拦截了‘雷吉娜’号? 他是个恶棍, 但很难相信他会自降身份去做普通海盗。 ";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "很难说‘雷吉娜’号是海盗的常规战利品, 船长。 我们认为她至少有半打黑珍珠。 即使一颗黑珍珠也是无价的。 我绝对必须不惜一切代价见到那位德.谢沃先生。 ";
			link.l1 = "我可以在这里帮上忙, 先生。 但让我先弄清楚。 我似乎并不关心博托夫人的项链, 因此珍珠不是你在这里的原因。 ‘雷吉娜’号上还有什么? ";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "很好, 考虑到... 情况, 我得告诉你更多。 看, 与船本身相比, 货物并不那么重要。 信使双桅帆船‘雷吉娜’号被派往特立尼达的圣何塞港。 她的船长过去收集情报并为我们做一些... 差事。 他的最后一项任务是运输我们的私掠船从西班牙珍珠行动中获取的战利品。 我们花了三年时间才得到那条线索。 黑珍珠当然很重要, 但失去‘雷吉娜’号是致命的。 这不是意外, 知道她载有珍珠的人也一定知道其他事情。 ";
			link.l1 = "太好了, 所以这毕竟是情报机构的事! 你是担心你建立的整个间谍网络处于危险之中吗? 现在我能看到你麻烦的全貌了。 ";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "听说过约翰.瑟洛吗? 他是王室情报部门的负责人。 有一天我会在伦敦, 亲自向他报告‘雷吉娜’号的命运。 我必须找到漏洞在哪里... 并处理源头。 另外, 还有你那位神秘的莫雷诺船长。 如果西班牙人追踪到我们的殖民间谍网络, 多年的辛勤工作将付诸东流! ";
			link.l1 = "如果你从更大的角度看, 这一切开始有意义了。 我开始认为某个有西班牙口音的人告诉了德.谢沃关于‘雷吉娜’号和黑珍珠的事。 ";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "我们想法一致。 这是利用暴露的间谍网络的最佳方式。 涉及如此高层人物的外交事件... 这样的事件会严重损害英法关系, 你所需要做的就是提供正确的线索, 然后等待国际丑闻。 也许甚至关于黑珍珠的线索也是故意喂给我们的。 ";
			link.l1 = "那些该死的卡斯蒂利亚人, 对吧? 那么我们该怎么处理德.谢沃? ";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "说实话, 我不知道。 如果这是西班牙的挑衅, 那么忽略它是明智的。 但我必须了解他是如何知道‘雷吉娜’号的, 以及这对我们在西班牙殖民地的网络有多糟糕。 我还欠你一条命, 我打算偿还。 ";
			link.l1 = "坦诚相待, 男爵。 我可以利用任何能得到的帮助。 我已经绝望到考虑绑架侯爵夫人了。 ";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "你意识到这正是德.谢沃掩盖踪迹的方式吗? 把这一切都归咎于你会很容易, 包括‘雷吉娜’号的失踪。 因此, 我提议如下。 博托侯爵夫人告诉我, 德.谢沃不会参加交换, 会安全地留在巴斯特尔。 要么是他意识到自己陷入了麻烦, 要么是他开始怀疑什么。 他会像厨房老鼠一样小心。 这就是为什么我要和你一起去多米尼加。 ";
			link.l1 = "但他的囚犯是我的首要任务, 我不能拿她的生命冒险! 她是人质, 等待交换! ";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "别担心 —我会向雅克.迪勒.杜.帕克施压, 拿到逮捕德.谢沃船只的许可证。 我怀疑他的人并不完全了解他们所处的情况, 否则他们会对那些珍珠更小心。 我们将乘长艇去找他们, 直接向他们出示 warrant。 ";
			link.l1 = "是的, 我记得你的强制手段, 先生, 但这是一个风险。 而且是很大的风险。 ";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "你说得对, 但如果你想接受我的帮助, 就必须承担这个风险。 一旦我们在多米尼加完成任务, 我会去巴斯特尔, 要求德.里昂总督交出你的对手。 我的权力允许这样做。 我们不能让德.谢沃溜走。 ";
			link.l1 = "你真的准备好这么做了吗, 先生? 这可能会引发战争, 对吗? ";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "我打赌他们绝不会允许这种情况发生。 既然我们已经知道了真相, 这绝对是不可能的。 政治是个婊子, 船长。 我保证会把德.谢沃介绍给英国的地牢, 专门为你。 这听起来像是一个连他父亲都会认为合理的解决方案。 ";
			link.l1 = "我不能说我喜欢你的计划, 但我看不到其他办法。 ";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "我向你保证我们会成功。 我现在该去见总督, 给我的人下命令了。 如果你见到侯爵夫人, 告诉她可以保留那颗珍珠, 作为她协助调查的感谢。 ";
			link.l1 = "谢谢, 男爵。 在我的船上见, 我们很快起航。 ";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "威廉.科特尼, 科特尼男爵, 为您服务。 凭借大英帝国赋予我的权力, 并得到她值得信赖的盟友法国的全力支持, 你的船现已被逮捕。 这是文件, 请务必阅读, 并告诉你的人把手远离武器。 你被拘留但尚未被捕。 如果你不做蠢事, 将在第一个港口被释放。 ";
			link.l1 = "男爵, 我必须找回我的... 我的军官! ";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "别担心, 船长, 我会把她送到你的船上。 我请你现在回到长艇。 我将接管这艘船, 航行到巴斯特尔。 如果你不想亲自嘲笑你的宿敌, 随时可以离开我们。 我只请你调派几名你的手下给我, 帮助我们前往瓜德罗普。 ";
			link.l1 = "很好, 先生。 我宁愿不。 代我向他致以最恶劣的问候。 再见, 再次感谢! ";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "查尔斯, 很高兴见到你。 我曾希望你回来, 但从未真正相信过。 ";
			link.l1 = "我也是, 男爵。 你是来拜访侯爵夫人的吗? 顺便问一下, 她在哪里? ";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "你还是不明白, 是吗? 她逃跑了。 另外, 安杰伦.德.谢沃向你致以诚挚的歉意。 我设法说服他, 你从来都不是游戏的一部分, 只是另一个受害者。 就像他一样。 这个好人懒得写信, 但他对事情的发展深感抱歉。 ";
			link.l1 = "深感抱歉, 是吗? ! 你在说什么, 先生? ";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "你和我, 我们忽略了最主要的事情。 他是怎么知道珍珠的? 谁邀请了那位西班牙船长到这所房子? 谁能促使那个混蛋追求这样的奖品? ";
			link.l1 = "你是认真的吗? 不可能是... ";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "绝对可能。 侯爵夫人完美地扮演了她的角色, 她几乎成功了。 然而, 由于我们的调查, 我接触了德.谢沃, 不是把他当作小偷和海盗, 而是当作他实际上是的欺诈受害者。 他很快发现了她把他拖入了什么, 但他没有证据, 决定自己行动。 你知道后来发生了什么。 ";
			link.l1 = "你是说这一切都是侯爵夫人策划的? 德.谢沃像个粗心的婴儿一样上当了! ";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "正是如此。 激情是非常危险的东西, 查尔斯! 还记得你在这所房子里赌博的那个晚上吗? 安杰伦当时打算通过获得侯爵夫人的资助来套取他需要的证据。 是的, 他作弊了, 但在多年无望的激情以最毁灭性的背叛告终后, 他绝望了! 但你介入了, 自称是她的捍卫者, 并成功扮演了这个角色。 德.谢沃认为你和她是一伙的。 他偷了你从他那里赢来的船, 以阻止你得到它的日志。 他用你的军官来试图让她和你对立 —他认为你们是他的死敌。 ";
			link.l1 = "我无话可说! ";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "现在你知道了, 查尔斯! 侯爵夫人很聪明, 美得惊人, 同样危险。 我不知道她操纵新世界的精英多久了。 我想说, 很多年了。 不管怎样, 这与你无关了。 很高兴再次见到你, 但我还有更多房间要翻个底朝天, 这是个大房子。 我们可能什么也找不到, 但至少得试试。 在我们分道扬镳之前还有一件事。 拿着这个。 作为纪念。 也许当你准备好时, 可以把它送给你的女性朋友。 你很幸运, 知道吗。 尤其是和德.谢沃那个可怜的混蛋相比! ";
			link.l1 = "你说得对, 我是幸运的。 再见, 祝你搜索顺利, 男爵! ";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "今天天气真好, 是吧, 船长? 我听说了你的壮举, 但从未想过你是个普通的海盗。 如此无礼 —在你做了那些事后还敢来圣琼斯! ";
			link.l1 = "我可能是个海盗, 这千真万确, 先生, 但我看起来像个白痴吗? 在洗劫‘墨丘利’号并夺走她的西班牙珍珠后, 我究竟为什么要来这里? ";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "我承认, 这就是为什么你现在在谈话而不是在绞刑架上挥手的唯一原因。 看, 我们在这个案子中隐瞒了一个小细节。 我不是在说我们在你身上找到的珍珠。 而是双桅帆船的名字。 ";
			link.l1 = "什么意思? ";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "一艘信使双桅帆船, ‘雷吉娜’号过去两年被派往圣何塞港。 她的船长为我们收集情报, 也执行... 各种任务。 我们正式以寻找她携带的丢失外交邮件为借口寻找她。 我承认, 这不是什么高明的策略。 尽管如此, 你不可能在没有彻底搜查她船长舱的情况下知道这艘船的真实名字。 ";
			link.l1 = "我之前瞎了眼, 但现在我明白了。 请听我说, 先生, 我会解释! ";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "好吧, 再努力点, 船长。 你的生命悬于一线。 ";
			link.l1 = "我与这个间谍故事无关! 西班牙人也无关。 你的网络是安全的, 别担心。 然而, 你有一个漏洞, 有人利用了它。 然后, 我和这个人发生了争执。 我发现了他参与‘墨丘利’事件的证据, 我想用这些证据打败他。 ";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "上帝为证, 我以为这个案子只是普通的海盗行为, 我甚至没想到王室情报部门会与此有关! 我只有这颗珍珠, 但我非常清楚你何时何地可以找到更多。 ";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "听说过约翰.瑟洛吗? 他是王室情报部门的负责人。 有一天我会在伦敦, 亲自向他报告‘墨丘利’号的命运。 因此, 告诉我你那位可怜的对手的名字。 ";
			link.l1 = "安杰伦.德.谢沃, 德.列维.旺塔杜尔伯爵的私生子。 我认为他认为‘墨丘利’号只是私掠船掠夺品的运输船。 他可能知道珍珠, 但不知道与英国情报部门的联系。 ";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "你没让我失望, 船长, 我承认! 多么有趣的娱乐和敌人选择! 很好。 除了珍珠, 你还有什么其他证据? ";
			link.l1 = "德.谢沃有一艘护卫舰。 我曾经拥有过它... 只有一个晚上, 但我设法了解了一些情况。 他是个极其拘泥细节的人, 你会从他的日志中了解到他袭击‘墨丘利’号的全部情况。 我很确定他还拥有部分战利品。 也许甚至有更多黑珍珠, 如果不止一颗的话。 ";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "不止一颗, 你可以相信。 我们绝不会为了一批普通珍珠而让‘雷吉娜’号冒险。 我希望你意识到我绝对必须和德.谢沃先生谈谈。 我一点都不在乎珍珠, 但我必须了解更多关于漏洞的信息。 如果我不向我的上级提供完整的情况, 他们会把我埋了。 ";
			link.l1 = "我很乐意帮你安排一次会面, 但我们必须快点! 此刻德.谢沃的护卫舰正在前往瓜德罗普的路上, 它的主人目前在当地总督的保护下居住在那里。 我确信他知道自己做了什么, 并会尽快逃离新世界。 ";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "这些是对非常严肃的人的非常严重的指控, 船长。 你意识到这可能引发的... 风暴吗? 袭击悬挂盟友旗帜的船只? 这会严重复杂化两个伟大国家之间的关系。 我很难想象他得把你惹得多生气, 才会让你渴望冒这么大的风险。 ";
			link.l1 = "他从我这里拿走了一些东西, 大人。 我最看重的东西。 比我的生命还重要。 我必须弥补。 如果这导致战争, 那么我将在国旗的指引下为我的国家服务。 尽管如此, 德.谢沃会得到他应得的, 他是唯一该受责备的人! ";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "有没有人告诉过你, 你是个极其危险的人, 船长? 准备好在地球的另一半发动战争来实现你的目标? 很好, 就按你的方式办。 我会和你一起去巴斯特尔。 我不能放过这样的线索。 我会派一个抄写员记录你的证据, 同时我准备我的船。 ";
			link.l1 = "谢谢你, 先生。 但我警告你, 我们在这里没有时间可浪费! ";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "德.莫尔船长, 我们会及时赶到的, 我对你毫不怀疑。 然而, 如果这次冒险不成功... 你明白我的意思吗? 我甚至不能保证你有一个像样的坟墓。 ";
			link.l1 = "是的, 大人。 我完全明白你的意思。 ";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "木已成舟, 船长。 我要求与安杰伦.德.谢沃会面。 他的护卫舰一到达就会立即被搜查。 弗朗索瓦.德.里昂有他的疑虑, 但我文件上的印章暂时阻止了他。 我请你留在镇上, 直到情况解决。 ";
			link.l1 = "当然, 大人, 我明白。 ";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "那么我希望你也能明白这一点。 把你的剑交给那边的先生们, 跟着他们, 这样我才能确保你会遵守承诺。 ";
			link.l1 = "难以置信... 科特尼大人, 你是认真的? ! ";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "非常认真。 你仍然是我的主要嫌疑人之一, 在这种情况下让你走将是非常愚蠢的。 如果你的话被证明是真的, 我会以任何我认为合适的方式向你道歉。 ";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "问候你, 德.莫尔先生。 我们开始吧? ";
			link.l1 = "乐意之至, 规则是什么? 说实话, 我刚才忙着吃东西, 可能听错了条件。 ";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "规则很简单。 一张牌1万比索, 我们打到一方投降为止。 不接受收据和赊账。 ";
			link.l1 = "对我来说可行。 我们开始吧, 上校。 ";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "该死的! 再也不玩了! 很好, 德.莫尔先生, 下一轮好运。 ";
				link.l1 = "我的荣幸, 上校。 再见。 ";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "你打得很好, 但命运女神有她自己的计划。 再见, 德.莫尔先生。 谢谢你的游戏。 ";
					link.l1 = "是的, 我想我在这方面高估了自己。 再见, 上校。 ";
				}
				else
				{
					dialog.text = "你决定拒绝继续游戏, 从而承认失败! 你打得很光荣, 但命运的裁决不同。 再见, 德.莫尔先生, 谢谢你的游戏。 ";
					link.l1 = "是的, 我想我在这方面高估了自己。 再见, 上校。 ";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "查尔斯.德.莫尔船长, 真是个该死的惊喜! ";
					link.l1 = "船长。 莫雷诺个鬼! 你怎么会在这里? ! ";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "查尔斯.德.莫尔船长, 幸会。 ";
						link.l1 = "我们以前见过吗, 莫雷诺先生? ";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "查尔斯.德.莫尔船长, 幸会。 ";
						link.l1 = "我们以前见过吗, 莫雷诺先生? ";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "查尔斯.德.莫尔船长, 幸会。 ";
				link.l1 = "我们以前见过吗, 莫雷诺先生? ";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "说来话长。 和往常一样, 船长。 我从你眼中看到你有问题。 保持安静, 假装你在嘲笑一个普通水手。 ";
			link.l1 = "是啊, 这套漂亮的西装穿在你身上很好看, 我简单的朋友。 我得说你知道怎么穿。 ";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "只在罕见的场合, 靠运气。 今天就是。 我们赌博吧, 船长。 人们在看着, 让他们等待不礼貌。 ";
			link.l1 = "对, 我们稍后再谈。 发牌... 莫雷诺船长, 如果你愿意的话。 ";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "我有点了解你, 但这不重要。 发牌, 德.莫尔船长, 人们想看表演。 ";
			link.l1 = "好奇。 尤其是你带着西班牙口音, 还有博托夫人对你的信任。 很好。 海对海, 开始吧! ";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "我当然记得你。 当你和我的前船长在勒弗朗索瓦刺穿我的手下时。 那个混蛋反正罪有应得, 不过我记得没有你的帮助也不行。 但别指望我会感激你, 你杀了弗朗茨.加克, 我不会原谅你。 ";
			link.l1 = "葡萄牙人的军需官? ‘血腥唐’, 对吧? 这个夜晚只会变得更好。 开始吧! ";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "你决定拒绝继续游戏, 从而承认失败! 我想命运女神已经说了话。 再见, 船长。 ";
				link.l1 = "同样, 莫雷诺先生。 谢谢你的游戏。 ";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "我想命运女神已经说了话。 再见, 船长, 也许我们会再见面。 ";
					link.l1 = "同样, 莫雷诺先生。 谢谢你的游戏。 ";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "我想命运女神已经说了话。 再见, 船长, 也许我们会在不同的情况下再见面, 呵呵。 ";
						link.l1 = "期待, 莫雷诺先生。 ";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "就这样。 命运已经决定, 船长。 再见。 ";
						link.l1 = "再见, 莫雷诺先生。 ";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "就这样。 命运已经决定, 船长。 再见。 ";
				link.l1 = "再见, 莫雷诺先生。 ";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "很高兴见到你, 德.莫尔船长先生! 说实话, 我期待见到任何人, 包括全体卫兵, 但没想到是你。 ";
			link.l1 = "莫雷诺先生, 你和当地官员有麻烦吗? 顺便说一句, 见到你也很高兴哈哈! ";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "我说, 没人能拒绝我们女主人的邀请。 至少, 不是那种邀请。 来吧, 查尔斯, 别演喜剧了。 侯爵夫人确保我知道她知道我的真实身份。 ";
			link.l1 = "... ";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "夫人, 你真迷人! 你的这位新朋友曾经试图告发我。 实际上, 结果不太好, 事实上他救了我好几次, 我都数不清了。 不管怎样, 现在我欠他一个人情, 所以不用担心威胁, 别担心。 ";
			link.l1 = "感激不尽, 巴塞洛缪。 安杰伦.德.谢沃把我逼到了极其不舒服的境地, 我必须把他打倒。 ... 某个我非常亲爱的人的生命取决于此。 相信我, 这次没有什么能阻止我。 ";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "够了, 船长, 我们是朋友, 对吧? 还记得穿越半个群岛的那场比赛吗? 那对我意义重大。 我会尽力帮助你。 听说过‘墨丘利’号吗? ";
			link.l1 = "现在, 那是什么? 一艘船? ";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "确切地说, 是一艘英国双桅帆船。 她的角色是运载迪奥利上校的私掠船从西班牙西印度群岛珍珠行动中掠夺的战利品。 那些偶尔捕捞传奇黑珍珠的行动, 听说过吗? 如果我的消息来源可靠, ‘墨丘利’号上存有数颗这样的珍珠。 一个月前, 我在马提尼克和瓜德罗普之间设下埋伏, 等待那些绅士们。 但徒劳无功! 我们在海上待了一周, 直到不得不承认失败。 ";
			link.l1 = "对, 所以你的消息来源不可靠, 你自己也没拿到奖品。 这和德.谢沃有什么关系? ";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "我也这么想, 直到我发现‘墨丘利’号从未出现在安提瓜。 想象一下我的惊讶, 当他们在库拉索附近看到她, 而她不可能在马提尼克附近经过我。 英国人在愤怒! 想象一下错过了这样的奖品! 无论如何, 我很好奇, 开始调查那个破坏了大家乐趣的特别人物。 这样的战利品无法快速出售, 所以我去勒弗朗索瓦找那个混蛋, 拿回他欠我的东西。 ";
			link.l1 = "你的故事听起来很熟悉。 听说过‘因果报应’这个词吗? 你肯定知道如何给自己惹麻烦。 但我还是不明白这对我有什么用? ";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "别着急, 船长, 我正要告诉你我故事中最精彩的部分。 你那位没洗过澡。 穿着讲究的朋友 —他的手下在当地商店留下了大量珍珠的明显踪迹。 西班牙珍珠行动的骄傲, 他们大量浪费。 ";
			link.l1 = "... ";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "你听到了吗, 船长? ";
			link.l1 = "认为德.谢沃从‘善良的雅克’和他的手下那里买了偷来的珍珠? 恐怕这... 不够。 ";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "够了, 船长。 他不是在买, 他在卖! 我和巴尔巴宗谈过, 他证实他从某个合伙人那里买了一大批完美的珍珠。 之后他把它送到了欧洲。 我们还有项链上的那颗黑珍珠, 以及德.谢沃的船进行了维修的事实。 工人们告诉我, 他的护卫舰有12磅炮的弹孔。 哪个头脑正常的人会用这种小炮攻击护卫舰? ";
			link.l1 = "听起来像我们的双桅帆船! 另外, 我记得德.谢沃吹嘘过他的护卫舰有多快。 但为什么这么疯狂? 我们和英国处于和平状态, 为什么要冒这么大的风险, 为了什么? 黑珍珠确实极其稀有, 但并非不可得。 ";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "这就是他错的地方! 英国人已经开始对‘墨丘利’号的失踪进行正式调查, 尽管他们称她为失踪的信使船, 载有一些重要文件。 任何线索都将得到慷慨奖励, 任何责任人都将受到严厉惩罚。 最精彩的部分是他们已经派了一位特别的贵族官员到安提瓜, 现在他正在不知疲倦地调查这个案子。 我不记得他的名字, 就像他那得意的脸一样奇特, 但我很高兴他不是在追捕我! ";
			link.l1 = "现在有戏了! 看来他们非常想要那些黑珍珠。 我想知道‘墨丘利’号上有多少, 以及这些知识对我有什么用? ";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "你听到了吗, 船长? ";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "说了这么多, 我需要一杯像样的酒。 侯爵夫人, 既然我们现在是朋友了... ";
			link.l1 = "我觉得这房子里没有朗姆酒, 巴塞洛缪。 ";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "是啊, 那就把他的护卫舰交给那位英国调查员! 如果这就是我们的计划, 那我都不认识我们的老德.莫尔船长了! ";
			link.l1 = "你会笑的, 但这就是计划。 我需要你们俩的帮助。 夫人 —你将成为我雇佣的海盗的囚犯 —巴塞洛缪, 这是你的角色。 ";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "还有我这恶名昭彰的角色! 葡萄牙人巴塞洛缪可从没绑架过女人! ";
			link.l1 = "你也不会, 但要让德.谢沃的人看起来像那么回事。 另外, 没必要告诉他们你的名字。 把我们的女士带上船, 在斯科特角附近与安杰伦的护卫舰会合。 用朱莉安娜交换我的军官, 然后返回马提尼克。 然后等侯爵夫人和我。 ";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "这一切都很精彩, 查尔斯, 你天生就是个骑士。 但交换之后我们到底怎么把她救回来? ";
			link.l1 = "我会处理。 我们时间不多, 分头行动吧。 你和侯爵夫人去多米尼加, 我则赶往圣琼斯。 我会找到迪奥利上校或那位英国调查员, 告诉他谁该为‘墨丘利’号的失踪负责。 ";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "船长, 你想过这种事件之后肯定会引发的风暴吗? 此刻的安提瓜就像一个马蜂窝, 而你让我往里面扔石头。 我记得战争的爆发往往只因更小的事! ";
			link.l1 = "一次解决一个问题... 我会不惜一切代价把她救回来! 如果德.列维.旺塔杜尔像传说中那么有权势, 就让他自己收拾烂摊子吧! 另外, 德.谢沃也很难解释博托夫人怎么会出现在他的船上。 ";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "准备好了吗? 听天由命! 侯爵夫人, 你准备好被绑架了吗? ";
			}
			else
			{
				dialog.text = "准备好了吗? 听天由命! 侯爵夫人, 你收拾东西需要多长时间? ";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", 德.莫尔先生。 我叫"+GetFullName(npchar)+", 这位是"+GetFullName(characterFromId("GG_SecundantGG_2"))+"。 总督大人请我们来见证你与德.谢沃先生的决斗。 ";
			link.l1 = "晚上好, 先生们。 希望一切顺利, 今晚别出人命。 但无论如何都要做好准备, 这位‘绅士’可能会让人失望。 ";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "你的担忧毫无根据。 根据决斗的预设条款, 副手在任何情况下都不得干涉。 不过还是谢谢你的提醒。 你的对手已经到了。 祝你好运, 船长。 总督大人让我转告你, 他会为你的... 谨慎祈祷。 ";
			link.l1 = "我相信这会对我大有帮助。 不管了, 开始吧。 ";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "船长, 我们有麻烦了。 我们的船... 嗯, 没了。 ";
			link.l1 = "等等, 什么? ! 怎么回事, 谁干的? 本应派了一整队守卫在上面, 你他妈在说什么? ! ";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "不, 船长, 不是我们的船。 她还好好的。 是你昨天赢的那艘护卫舰, 现在也是我们的了, 对吧? 我们只派了十二人的战利品船员过去, 她说那足够了。 ";
			link.l1 = "别他妈绕圈子, 从头告诉我到底发生了什么! ";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "不知道, 船长。 护卫舰在清晨的薄雾中起航了。 几小时后雾散时, 守卫才发现她不见了。 ";
			link.l1 = "这不可能! 她绝不会这样对我! 虽然... 该死, 我们最近刚吵过架。 难道她... ";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "恐怕更糟, 船长。 渔民清晨发现了我们战利品船员中的两个小伙子, 都死了, 喉咙被割开。 ";
			link.l1 = "真是噩梦! 德.谢沃! 我忙着处理侯爵夫人的时候, 他把船偷回去了! 希望她还活着... 如果她少了一根头发, 我... ";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "船长, 你要下令让弟兄们准备吗? 我们两小时后就能起航, 大家一早上都绷紧了神经, 尤其是你的副手, 我们差点没拦住他追上去。 ";
			link.l1 = "现在还太早。 我必须... 好好想想, 和人谈谈。 对! 准备船只! 我要所有人都准备好, 我一回来就起航。 ";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "德.莫尔船长, 发生什么事了? 有人袭击夫人了吗? ";
			link.l1 = "你不该来这里。 好吧, 上帝为证, 我不想这样。 ";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "先生, 我们几乎以为你不会来了。 我看到你的长艇上有博托侯爵夫人。 我甚至不想问这是怎么发生的。 你的同伴在等你, 她安然无恙, 带上她赶紧离开这里。 ";
			link.l1 = "如果你敢碰她一根手指, 我会把你这艘破船撕成碎片! ";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "真是意外的关心。 别担心, 她被当作女王一样囚禁着。 你的威胁对我没用。 顺便说一句, 德.谢沃骑士向你问好。 ";
			link.l1 = "去他的问好。 我的... 军官呢? 我们开始交换吧。 ";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "先生, 我们几乎以为你不会来了。 你的同伴在等你, 她安然无恙... 等等, 这他妈是谁? 侯爵夫人呢? ";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "先生, 交剑。 别耍花样, 我的伙计们最近有点暴躁。 你不想吃枪子儿吧? ";
			link.l1 = "你认真的? 好吧, 拿着, 但轻点, 这剑比你整个营房都值钱。 我要求见科特尼男爵, 大人! ";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "别担心, 我相信他会抽出时间来拜访你的。 ";
			link.l1 = "当你想帮别人的时候... ";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "我也不喜欢这样, 先生。 唉, 这位无礼的英国人权力太大, 连德.里昂先生也无能为力。 抱歉, 船长, 请交出你的剑。 ";
			link.l1 = "希望德.谢沃先生不会和我关同一间牢房。 走吧, 先生们, 我累坏了, 终于能睡会儿了。 ";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "先生, 我不想显得无礼, 但我现在没时间聊天, 你也看到情况了, 我不想错过任何事! ";
			link.l1 = "如你所愿, 先生。 ";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "我感觉这个夜晚将载入史册! 人们会从这里谈到凡尔赛! 我的玛丽安会很高兴, 想知道所有细节。 先生, 请让一让, 你挡住我的视线了。 ";
			link.l1 = "我这就走, 先生, 好好欣赏吧, 向令人难忘的玛丽安问好... 不管她是谁。 ";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "哈! 这不是德.莫尔先生吗! 打扰一下... 查尔斯.德.莫尔船长! 请加入我们, 这里有来自旧世界的精选葡萄酒。 你想从哪种开始: 新品 —来自我们亲爱的吉伦特海岸的赤霞珠, 还是永恒经典 —意大利桑娇维塞? ";
			link.l1 = "谢谢你, 先生, 我稍后再和你喝。 ";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "哦, 德.莫尔船长! 再来点酒吗... 嗝? 看看我们刚上的 —1643年的西拉, 产自罗纳河谷的北部山区。 这可是, 该死的, 真正的珍宝! 那年各方面都很出色, 我告诉你... 在加特角击败西班牙人就值了! 顺便问一下... 为什么大家都这么大惊小怪, 你知道吗? 有人不舒服吗? 算了... 干杯... ";
			link.l1 = "至少有人在享受美食。 再见, 先生。 ";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "哦, 查尔斯.德.莫尔船长, 我和这城里的人一样听说过你! 请允许我自我介绍 --"+GetFullName(npchar)+", 见到你是我的荣幸, 相信我! 你真的和我们的总督关系很好吗? 能介绍我们认识吗? 我想向他表达最深的敬意, 还有... ";
			link.l1 = "以后吧。 晚上好, 先生。 ";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "德.莫尔先生, 你看到了吗? 我们尊贵的总督和德.谢沃先生本人 —我以为他们会在这里杀了对方! 太壮观了! 博托侯爵夫人今天真是超水平发挥 —一切都太他妈刺激了! 我迫不及待想看接下来的发展。 顺便说, 现在是时候了吗? 你答应过要介绍我... ";
			link.l1 = "我不记得答应过什么。 抱歉, 我得走了。 ";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "德.莫尔先生, 你终于来到了才华横溢的博托夫人的沙龙! 她已经好几次说想见你了。 欣赏过她的‘门生’了吗? 是啊, 像侯爵夫人这样的明星不是你我这样的凡人能企及的。 但相信我: 这些女士都是真正的艺术品, 也许不如米开朗基罗或提香, 但依然... ";
			link.l1 = "有趣的比喻, 先生。 好吧, 我让你享受夜晚... ";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "不, 这里总是很有趣, 但现在空气中明显弥漫着奢华丑闻的味道, 你感觉到了吗? 杰奎琳女士在楼上等我, 但我还是舍不得离开赌桌! 总督大人和德.谢沃先生是值得尊敬的对手, 而且决心很大。 看来今天的赌注不仅会飞向星辰, 还会冲破苍穹直达地狱! ";
			link.l1 = "地狱在下方, 先生。 苍穹之上想必有天使。 ";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "至少有个愉快的会面! 我们见过面, 德.莫尔船长, 但你可能不记得了。 "+GetFullName(npchar)+" —我曾是驻军第六步兵团的上尉, 和你一起在街头与西班牙人作战。 真的, 我膝盖中了一枪, 大部分战斗时间都躺在沟里看着妓院燃烧。 现在又来了 —同样的混乱, 同样的欣赏, 只是这次在里面。 ";
			link.l1 = "很高兴见到你, 先生。 那天确实激烈, 但不得不说, 从那天起这地方漂亮多了! ";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "船长, 你觉得这里的氛围如何? 看来这些上流社会的家伙决定搞他妈的一团糟! 有趣的是, 总督的位置能像牌桌上的赌注一样被赌吗? 记住我的话 —最后会动刀子。 可惜, 我这膝盖再也享受不了这种娱乐了。 不过我好像看到杰奎琳了 —她的男伴对正在发生的事很感兴趣... 趁这里还平静, 我去试试运气。 ";
			link.l1 = "明智的决定, 祝你成功, 先生。 我得回去找... 那些家伙了。 ";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
