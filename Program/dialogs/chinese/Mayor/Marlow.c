// 扎卡里亚.马洛, 黑牧师, 太子港, 古巴
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------愤怒状态块-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) // 首次触发陷阱
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) // 这里编写愤怒反应。 npchar.angry.name中已删除空格!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } //< —愤怒状态块

    switch(Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = NPCStringReactionRepeat("你有什么事要找我吗? 如果没有, 就离我远点! ",
                         "我想我已经说得很清楚了。 ", "尽管我已经说得很清楚了, 你还是一直烦我! ",
                         "对, 我已经受够这种无礼了。 ", "repeat", 3, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "当然, 牧师。 ",
                                               "对不起, 牧师。 ",
                                               "哦... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";
            
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都对你很生气, 小子, 你最好离开这个地方。 ", "看来你发疯了, 小子。 想伸展一下你的手? 无意冒犯, 但你在这里无事可做。 滚! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个问题... ");
                link.l1.go = "pirate_town";
                break;
            }
            
            //--> 传奇任务
            if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
            {
                link.l1 = "我在找鲨鱼.多德森。 他们说你是最后一个见过他的人。 你能帮我吗? ";
                link.l1.go = "Shark";
            }
            if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
            {
                link.l1 = "你为什么这么无礼? 还是说你对从我这里得到你想要的书不感兴趣? ";
                link.l1.go = "book";
            }
            //< —传奇任务
            // 船长委托 - 赎回
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
            {
                if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
                {
                    link.l1 = "我想谈谈你的囚犯。 ";
                    link.l1.go = "CapComission1";
                    DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
                }    
                if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // 护林员。 新检查。 排除直接完成任务而不经过15天的可能性。 
                {
                    link.l1 = "你好, 牧师。 我想谈谈你的任务。 ";
                    link.l1.go = "CapComission3";
                }
                if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
                { // 护林员。 第二次对话检查, 如果主角还没有带来赎金。 
                    link.l1 = "我想谈谈你的囚犯。 ";
                    link.l1.go = "CapComission6";
                }
            }
        break;
        
        case "shark":
            dialog.text = "史蒂文.多德森? 我不知道我的故事对你有什么帮助, 因为鲨鱼已经失踪几个月了, 没有人见过他。 不过这并不奇怪, 他杀了Blaze Sharp, 还因为这个愚蠢的行为败坏了自己的名声。 他树了几个有权势的海盗为敌。 ";
            link.l1 = "我有充分的理由认为鲨鱼对Sharp的死是无辜的。 我无法证明这一点, 也许鲨鱼自己能做到。 你能告诉我关于他的任何事情吗? ";
            link.l1.go = "shark_1";
        break;
        
        case "shark_1":
            dialog.text = "几个月前, 史蒂文来找我, 提出了一个非常奇怪的交易: 他把他的护卫舰'财富号'抵押给我一个月, 以换取一艘装满补给品的双桅横帆船。 然后他要么把双桅横帆船和补给品的钱还给我, 要么我就留下他的护卫舰。 一个月过去了 —鲨鱼。 我的双桅横帆船和钱都不见了踪影。 \n此外, 我听说Blaze被谋杀了, 鲨鱼是嫌疑人。 我能怎么想? 没错! 我以为史蒂文已经逃之夭夭了。 我把他的护卫舰卖给了一个叫威廉.帕特森的英国人, 他非常满意, 为这艘船付了一大笔达布隆。 \n因此, 我已经完全弥补了我的开支, 也不怨恨他。 我不在乎Sharp的死, 我有自己的问题要担心。 ";
            link.l1 = "你不觉得如果他想逃跑, 他就不需要你的双桅横帆船了吗? 他有自己的船, 比任何双桅横帆船都好一百倍。 看起来鲨鱼有一个计划, 但出了什么问题, 他没能及时回来。 ";
            link.l1.go = "shark_2";
        break;
        
        case "shark_2":
            dialog.text = "正如我已经告诉你的, 我不在乎多德森的问题。 我已经履行了我的交易部分。 关于那艘船, 你最好问他为什么需要那该死的双桅横帆船。 我没有强迫他拿。 ";
            link.l1 = "好吧, 我们别再谈这个了。 你当然是对的。 告诉我, 你知道史蒂文驾驶你的双桅横帆船要去哪里吗? ";
            link.l1.go = "shark_3";
        break;
        
        case "shark_3":
            dialog.text = "谁知道呢。 但我有一些猜测。 他向西北方向驶向大陆。 所以要么是以敌对印第安人闻名的危险海湾, 要么是以天主教徒和宗教裁判所闻名的新西班牙。 \n我怀疑他不会去这些地方。 但他们说在古巴西北方向有一个奇怪的地方叫'废弃船只之城'。 很多人认为这是个神话, 但我不这么认为。 不是因为我是个浪漫的人, 而是因为有真正的人乘坐他们的长艇去那里。 至少他们曾经去过。 ";
            link.l1 = "他们是谁? ";
            link.l1.go = "shark_4";
        break;
        
        case "shark_4":
            dialog.text = "来自古巴的海盗。 他们曾经把公牛的尸体装上他们的帆船, 向西北方向航行。 他们总是晚一点回来, 口袋里装满了钱或稀有珍贵的货物。 ";
            link.l1 = "有趣! 我在哪里可以找到那些海盗? ";
            link.l1.go = "shark_5";
        break;
        
        case "shark_5":
            dialog.text = "你为什么问我? 在古巴的森林里找找看。 即使你找到了他们, 他们也不会告诉你任何事情, 他们为什么要暴露自己美好生活的来源呢? 所以别浪费你的时间了, 很久以来都没有人再看到他们这样做了。 \n此外, 我听说有一位西班牙水手阿尔瓦拉多写的笔记, 他自己去过那个岛屿。 所以我很好奇, 也许史蒂文真的去了那里。 ";
            link.l1 = "未知的岛屿, 地图上没有... 嗯。 这可不是什么有希望的信息。 ";
            link.l1.go = "shark_6";
        break;
        
        case "shark_6":
            dialog.text = "我一开始就告诉你, 我的故事对你没有帮助。 你为什么需要多德森? ";
            link.l1 = "我和森林恶魔想推选他为海岸兄弟会的领袖。 正如我已经告诉你的, 有一些严重的理由表明Blaze是被别人谋杀的。 ";
            link.l1.go = "shark_7";
        break;
        
        case "shark_7":
            dialog.text = "嘿! 我猜扬支持他? 好吧, 你知道规则 —多德森必须得到每个男爵的投票。 ";
            link.l1 = "我知道规则。 那么我的第二个问题是。 你会在选举中投票给多德森吗? ";
            link.l1.go = "shark_8";
        break;
        
        case "shark_8":
            dialog.text = "嗯, 他首先得回来。 实际上, 我不在乎谁来领导兄弟会, 只要他把生意做好, 不打扰我就行。 正如我所说, 我有自己的问题。 你知道我们岛上有多少女巫和法师吗? 不知道? 我告诉你: 一大群! 此外, 圣地亚哥和哈瓦那也有很多天主教徒。 \n说到法师。 有一本书叫《女巫之锤》。 我真的很想得到它, 但只要英文版的, 我不需要拉丁文。 德文或西班牙文的翻译, 我不懂这些语言。 把书带给我, 我就投票给多德森。 \n请注意, 杰克曼也答应过帮我找到它, 所以如果他先成功了... 别怪我。 ";
            link.l1 = "好吧, 我会考虑的。 谢谢你的时间。 再见。 ";
            link.l1.go = "shark_9";
        break;
        
        case "shark_9":
            DialogExit();
            pchar.questTemp.Saga.SharkHunt = "after_marlow";
            npchar.quest.sharkbegin = "true";
            AddQuestRecord("SharkHunt", "2");
        break;
        
        case "book":
            dialog.text = "那本书? 我猜你说的是《女巫之锤》? ";
            link.l1 = "当然。 我设法为你找到了它。 正如你所要求的, 是英文版的。 ";
            link.l1.go = "book_1";
        break;
        
        case "book_1":
            dialog.text = "哈, 抱歉这么粗暴地欢迎你, 伙计。 不会再发生了... 让我看看那个宝贝! ";
            link.l1 = "当然, 看看吧。 ";
            link.l1.go = "book_2";
        break;
        
        case "book_2":
            RemoveItems(pchar, "witches_hammer", 1); // 移除论文
            dialog.text = "终于! 现在颤抖吧, 地狱的仆人们! 在我的手再也挥不动之前, 我不会放过你们... ";
            link.l1 = "我为你高兴, 牧师。 那么你的投票呢? ";
            link.l1.go = "book_3";
        break;
        
        case "book_3":
            dialog.text = "正如我告诉你的,'我不在乎谁会成为首领'。 我相信斯文森不会选择一个不配的人。 所以拿着我的投票。 随你怎么处理。 这是我的碎片。 ";
            link.l1 = "谢谢你, 撒迦利亚。 到时候见! ";
            link.l1.go = "book_4";
        break;
        
        case "book_4":
            GiveItem2Character(pchar, "splinter_zm"); // 给予碎片
            DialogExit();
            NextDiag.CurrentNode = "I_know_you_good";
            AddQuestRecord("BarbTemptation", "27");
            if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
            ChangeCharacterComplexReputation(pchar, "fame", 1);
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", 很高兴见到你! 你想要什么? ",
                         "你还想要什么? ", "又来了? 如果你没事就别烦别人! ",
                         "你是个" + GetSexPhrase("优秀的私掠者", "好女孩") + ", 所以你现在可以活下去。 但我不想再和你说话了。 ", "repeat", 10, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我只是来拜访一下。 ",
                                               "没什么... ",
                                               "好吧, 牧师, 对不起... ",
                                               "该死, 是我的错! ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "I_know_you_good";
            
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都对你很生气, 小子, 所以你最好离开这个地方... ", "看来你发疯了, 小子。 想伸展一下你的手? 无意冒犯, 但你在这里无事可做。 滚! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个问题... ");
                link.l1.go = "pirate_town";
                break;
            }
            // 船长委托 - 赎回
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
            {
                link.l1 = "是关于你的囚犯的事。 ";
                link.l1.go = "CapComission1";
                DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
            }        
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
            {
                link.l1 = "是关于你的囚犯的事。 ";
                link.l1.go = "CapComission1";
                DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
            }    
            if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")// 护林员修改, 新检查, 排除立即完成任务的可能性
            {
                link.l1 = "你好, 牧师, 我是为了你的任务而来。 ";
                link.l1.go = "CapComission3";
            }
            if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
            { // 护林员。 绑架者 (在DLC《龙与海》之后, 当巴巴索萨已经不在时)
                link.l1 = "我听说你从事与囚犯有关的生意... ";
                link.l1.go = "Marginpassenger";
            }
        break;
        
    //-----------------------------------船长委托 - 赎回-------------------------------------------------
        case "CapComission1":
            dialog.text = "哈哈。 你以为我这里只有一个囚犯吗? 说出他的名字。 ";
            link.l1 = pchar.GenQuest.CaptainComission.SlaveName + "。 他在这里吗? ";
            link.l1.go = "CapComission2";
            DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
        break;

		case "CapComission2":
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "他以前在这儿。 一周前巴巴多斯的种植园主毕晓普上校来的时候, 我把他卖给那家伙了。 ";
				link.l1 = "该死的... ";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "啊, 你终于来了。 我正打算把他卖给那个巴巴多斯的种植园主, 他一两周内就会到这儿... 你有赎金吗? ";
				link.l1 = "听着, 有点小问题... 其实我没那么多钱。 但我可以干活抵账。 ";
				link.l1.go = "CapComission2_2";
				if (makeint(pchar.money) > 150000)
				{
					link.l2 = "幸好你还没卖掉他。 这是15万比索, 我去哪儿接他? ";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "你太慢了... 你为什么在乎他? 我之前只和他的亲戚谈判过。 ";
			link.l1 = "是他们让我来这儿的。 ";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "好吧, 你迟到了。 我无能为力。 ";
			link.l1 = "听着, 如果不是秘密的话, 你把他卖了多少钱? ";
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "呃, 这不是秘密。 但我不会告诉你... 我说了你会笑我的。 哈哈哈哈! 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//护林员修正。 在SGE中下面的记录不工作
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if (rand(3) == 1)
			{
				dialog.text = "好吧, " +pchar.name+ ", 你知道这不是那么回事。 带钱回来, 你就能领走那个弱鸡, 哈哈。 ";
				link.l1 = "好吧。 再见。 ";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "嗯, 嗯... 我有一桩生意... 甚至不知道怎么开口。 我需要干掉一个越界的海盗。 ";
				link.l1 = "不能在丛林里直接杀了他吗? ";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "你知道, 生意不是这么做的... 我不需要他死, 我需要教训一些人别碰我的战利品分成。 但他死了我也不会后悔。 ";
			link.l1 = "你为什么不派自己的人去? ";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // 贝拉美尔生成
			dialog.text = "嗯... 好吧, " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " 说服了一些海盗, 让他们以为我们藏在 " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " 附近的藏匿点里有他们的战利品分成。 他们的两艘船‘" + pchar.GenQuest.CaptainComission.ShipName1 + "’和‘" + pchar.GenQuest.CaptainComission.ShipName2 + "’不久前起锚驶向 " + sLoc + " 了。 现在你明白为什么我不能信任我的人去做那件事了吧? ";
			link.l1 = "明白了。 我有多少时间? ";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12到15天, 不能更多了。 如果他们到不了藏匿点, 那击沉他们就没意义了, 这对我很重要, 否则击沉载有贵重货物的船就太荒谬了。 在那种情况下, 他们把货物带到这儿来会更好... ";
			link.l1 = "好的, 我接了。 我会试着拦住他们。 ";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//修正
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // 贝拉美尔生成
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // 贝拉美尔生成
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// 护林员 - 替换为直接完成任务的检查
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "别担心。 我的人会把他送到你的船上。 你为什么在乎他? ";
			link.l1 = "我不在乎。 是他的亲戚让我来接他的。 ";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "啊, 那好吧。 我差点为把你这个人卖这么低价感到遗憾。 哈哈哈哈。 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// 贝拉美尔生成
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // 新检查, 如果夏尔支付了囚犯赎金。 护林员
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// 护林员
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// 在SGE中不工作
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "那么, " +GetFullName(pchar)+ ", 你把我的那些伙伴击沉了吗? 嘿嘿嘿... ";
			if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "没有。 我没能拦住他们。 而且我在他们返程时也没遇到。 ";
				link.l1.go = "CapComission4";
			}
			if (pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "击沉了。 我把他们送去喂鲨鱼了。 ";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "该死! 遇没遇到他们现在都不重要了! 你接下来有什么打算? ";
			link.l1 = "也许你有更简单的活给我干? ";
			link.l1.go = "CapComission4_1";
			link.l2 = "听着, " + Npchar.name+ ", 把囚犯的价格降下来... ";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "没有。 ";
			link.l1 = "那再见了... ";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "降价? ! 因为你的无能, 我刚丢了藏匿点! 现在我还能涨价! 如果你想要他, 就付20万比索, 否则就滚出这里。 ";
			link.l1 = "太贵了... 再见... ";
			link.l1.go = "CapComission4_4";
			if (sti(pchar.money) >= 200000)
			{
				link.l2 = "该死, 拿去吧。 ";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// 护林员
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // 修正	// 护林员
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "你可以带走这个弱鸡... ";
			link.l1 = "再见。 ";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // 护林员修正SGE中的名字
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// 在SGE中不工作
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "嗬嗬! 干得好! 带走你的弱鸡, 祝你好运。 ";
			link.l1 = "谢谢。 再见。 ";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // 如果首次拒绝任务, 则让傻瓜们去找
		     否则重复交付任务会让任务变成一团糟.. 护林员
			dialog.text = "你把赎金带来"+ GetSexPhrase("","啦") +"? 我之前说要把他卖给种植园主可不是开玩笑的。 ";			
			link.l1 = "听着, " + Npchar.name+ ", 是这么回事... 总之, 我没有那么多钱。 但我准备"+ GetSexPhrase("","啊") +"干活抵账。 ";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "幸好你还没卖掉他。 这是15万比索, 你在哪儿能让我接到他? ";
				link.l2.go = "CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // 护林员。 让夏尔自己找钱, 或者不管那个囚犯
			dialog.text = "你把钱带来了吗? 我之前说要把那人卖给种植园主可不是开玩笑的。 ";			
			link.l1 = "我没钱, " + Npchar.name+ ", 但我正在想办法。 ";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "幸好你还没卖掉他。 这是15万比索, 你在哪儿能让我接到他? ";
				link.l2.go = "CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------绑架者------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "你为什么关心我的所作所为? 你知道的, 你最好离开... ";
			link.l1 = "嘘, 冷静点。 我是来和你谈生意的, 关于你抓的那个囚犯。 ";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "啊, 好的。 你想赎谁? ";
			link.l1 = "等等, 我不是来赎人的, 我是来提议你买下一个囚犯。 这样你也有机会拿到他的赎金。 ";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "嗯。 那你为什么需要我的中介? 为什么不自己直接拿钱? ";
			link.l1 = "这对我来说太冒险了, 可能会和当局产生麻烦。 ";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "哈哈... 那好吧, 我们看看。 你的囚犯是谁? ";
			link.l1 = "这是" + pchar.GenQuest.Marginpassenger.Text + " " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + "。 ";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
			dialog.text = "我明白了... 如果你没撒谎, 这会是笔不错的交易。 我想我可以给你" + iTemp + "比索来买这个人, 或者给你一些有趣的情报作为交换。 你选吧。 ";
			link.l1 = "我还是拿钱吧, 这生意我已经受够了... ";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "哈! 多告诉我些情报, 我肯定你会给我些有趣的东西。 ";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "那就拿钱吧。 拿着。 现在, 这不再是你的问题了, 把要卖的人送到这里来。 ";
			link.l1 = "他已经在城镇门口附近了。 谢谢! 你真的帮了我大忙。 ";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
			dialog.text = "不客气, 再给我带更多人来... 再见! ";
			link.l1 = "祝你好运... ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10) * 10;
			switch (hrand(1))
			{
				case 0: //南部大陆的海湾
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "和聪明人做生意真好。 现在听着: 几天后, 一支西班牙探险队将从大陆抵达" + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat") + ", 船上装载着贵重货物。 他们会等待一艘船来接货。 如果你一周内赶到那里, 就有机会把货物占为己有。 \n如果我是你, 现在就该往我的船上赶了。 把囚犯带到这里来。 ";
					link.l1 = "谢谢! 这些货物会是对我麻烦的不错补偿。 而且我的乘客已经在城镇门口附近了, 他会被带给你。 ";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //只是一艘船
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "和聪明人做生意真好。 现在听着: 大约一周后, 一艘载有贵重货物的西班牙双桅帆船‘" + pchar.GenQuest.Marginpassenger.ShipName1 + "’将从" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + "驶往" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + "。 如果你抓紧时间, 很容易就能追上它。 \n你还在这儿? 如果我是你, 现在就该往我的船上赶了。 把囚犯带到这里来。 ";
					link.l1 = "谢谢! 这些货物会是对我麻烦的不错补偿。 而且我的乘客已经在城镇门口附近了, 他会被带给你。 ";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat"));//护林员 - 在SGE中结束 // belamour gen: Abl - 这是到"湾", 需要与格
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : 奇怪的是, 提示由扎卡里给出, 而SGE中默认是好人
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Acc")); // 护林员 - 在SGE中结束
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
		break;
		
		// ============== 在光天化日之下抢劫, 试图打开箱子 =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("抢劫!!! 这太不像话了! 准备好, " + GetSexPhrase("小子","丫头") + "... ", "嘿, 你他妈的在那儿干什么? 以为能抢我? 你完蛋了... ", "等等, 搞什么? 把手拿开! 原来你是个小偷! 死到临头了, 混蛋... ");
			link.l1 = LinkRandPhrase("该死! ", "卡兰巴!! ", "真他妈的!! ");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== 愤怒节点块 ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("" + GetSexPhrase("离开 ","离开") + "这里! ", "滚出我的家! ");
			link.l1 = "哎呀... ";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "别用你那廉价的话语来烦我。 下次你不会喜欢结果的... ";
        			link.l1 = "我知道了。 ";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("够了, 别说话了。 ", "我不想再和你说话了, 所以你最好别烦我。 ");
			link.l1 = RandPhraseSimple("如你所愿... ", "嗯, 那好吧... ");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "我希望你能表现出更多尊重, 不再粗鲁无礼? ";
        			link.l1 = "您放心, 牧师, 我会的。 ";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town", "reload", "reload6");
		break;
		// <<<<<<<<<<<<============= 愤怒节点块 =============================
		case "pirate_town":
            dialog.text = "解决问题? 你知道自己做了什么吗? 不管怎样, 给我一百万比索, 我会说服伙计们忘记你的行为。 如果不喜欢这个主意, 那你可以去死了。 ";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "好的, 我准备付钱。 ";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "知道了, 我这就走。 ";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//关闭传送
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "很好! 算你没事了。 但我希望你再也不要做这种恶心的事了。 ";
			link.l1 = "不会了, 这对我来说太贵了。 再见... ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "马拉开波";
			pchar.GenQuest.Marginpassenger.Southcity1 = "哈瓦那"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "卡塔赫纳";
			pchar.GenQuest.Marginpassenger.Southcity1 = "圣地亚哥"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "贝洛港";
			pchar.GenQuest.Marginpassenger.Southcity1 = "圣多明戈"; 
		break;
	}
}