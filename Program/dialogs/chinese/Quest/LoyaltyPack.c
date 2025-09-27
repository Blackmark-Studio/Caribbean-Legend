void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "船长, 我能说句话吗? ";
					link.l1 = "稍后再说, 阿隆索。";
					link.l1.go = "exit";
					link.l2 = "说吧。";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "船长, 我能说句话吗? ";
					link.l1 = "稍后再说, 阿隆索。";
					link.l1.go = "exit";
					link.l2 = "说吧。";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "船长, 我能说句话吗? ";
					link.l1 = "稍后再说, 阿隆索。";
					link.l1.go = "exit";
					link.l2 = "说吧。";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "船长, 我能说句话吗? ";
					link.l1 = "稍后再说, 阿隆索。";
					link.l1.go = "exit";
					link.l2 = "说吧。";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = "没什么要报告的, 船长。";
			link.l1 = "继续保持, 阿隆索。";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "船长, 您还好吗? ";
			link.l1 = "你什么意思? ";
			link.l1.go = "Alonso_2";
		break;

		// Основная развилка стадии 1
		case "Alonso_2":
			dialog.text = "您在加勒比海航行已经好几个月了, 而有些人在这里连一周都撑不过。船员们都敬重您, 这毫无疑问, 但我呢? 我担心您的未来。\n"+
						  "跟我们分享一下您的想法吧, 也让船员们安心。"+pchar.ship.name+"要去哪里? ";
								  
			link.l1 = "我没有计划。想先熟悉这片海域。冒险自会找上门来。";
			link.l1.go = "Alonso_Choice_1";
			
			link.l2 = "这片海域充满了掠食者, 阿隆索。而"+pchar.ship.name+"是其中最小的。暂时是。";
			link.l2.go = "Alonso_Choice_2";
			
			link.l3 = "我喜欢赚钱。最好是合法的。但到时候再说吧。";
			link.l3.go = "Alonso_Choice_3";
			
			if (!SandBoxMode)
			{
				link.l4 = "你是知道的。自从在'尤利西斯号'上那次难忘的谈话后, 一切都变得更复杂了......";
				link.l4.go = "Alonso_Choice_4";
			}
		break;

		case "Alonso_Choice_1":
			dialog.text = "这就是自由! 重要的是有足够的钱维护船只, 还要在箱子里留点应急的。\n"+
						  "无论心情、任务还是藏宝图把您带到哪里------顺路接些载客、货运, 什么小活都行。\n"+
						  "做点小买卖也无妨------哪里便宜显而易见就在哪买, 能卖就卖。\n"+
						  "要是路上看到落单的商船......嘿嘿。您说得对, 船长。冒险确实会自己找上门。";
			
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
			
			link.l1 = "谢谢你的忠告, 阿隆索。";
			link.l1.go = "Alonso_Common_End";
		break;

		case "Alonso_Choice_2":
			dialog.text = "如果船只条件允许, 这买卖很赚。找那些落单的商人, 让他们明白什么叫'贪小便宜吃大亏'。\n"+
						  "不幸的是, 还有另一句话: '纸包不住火'。船员里总有长舌妇, 一到港口就把你的事迹说个遍。\n"+
						  "所以要么每个国家都抢一点, 要么就选定一个终生之敌。\n"+
						  "不过我可能说过头了。真要是走投无路, 皇家港有个律师, 给够钱就能摆平当局的任何麻烦。就当是海盗税吧, 嘿嘿! ";
			
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			link.l1 = "谢谢你的忠告, 阿隆索。";
			link.l1.go = "Alonso_Common_End";
		break;

		case "Alonso_Choice_3":
			dialog.text = "呃, 这方面我帮不上忙, 船长。您需要一艘真正的商船: 三桅帆船, 或者更好的是三桅货船。我可能会后悔这么说, 但最好装轻型火炮, 或者干脆扔掉。\n"+
						  "从店主那里接货运合同, 沿途自己做买卖, 还可以载客。\n"+
						  "攒够钱后, 投资商店和银行。您等着瞧吧, 船长------总有一天钱会生钱, 到时候您就能买得起一艘大船, 船上有两百号人。\n"+
						  "顺便说一句, 到时候付钱的不是您, 而是您的生意。";
			
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			link.l1 = "谢谢你的忠告, 阿隆索。";
			link.l1.go = "Alonso_Common_End";
		break;

		case "Alonso_Choice_4":
			dialog.text = "我看法不同, 船长。在'尤利西斯号'上您只是个乘客------那些可怜的人无法掌控自己的命运。现在您是个赢得了船长帽的船长, 这意味着您能解决任何问题。我早就说过------在我们这个世界里没有比这更高的地位了。\n"+
						  "我的直觉告诉我, 您和您兄弟的这场恩怨还要拖上好几年, 所以先照顾好自己吧。米歇尔先生又跑不了, 嘿嘿......\n"+
						  "在加勒比海有麻烦的不只是您。正好帮助别人, 同时赚钱、搞装备、拉关系。顺便学会处理这桩家族事务所需的一切......";
			
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			link.l1 = "谢谢你的忠告, 阿隆索。";
			link.l1.go = "Alonso_Common_End";
		break;

		case "Alonso_Common_End":
			dialog.text = "别把自己限制在一个角色里, 船长。想做什么就做什么。只取不予。一切都会顺利的。";
			link.l1 = "也谢谢你的鼓励。";
			link.l1.go = "Alonso_Common_End_2";
		break;

		case "Alonso_Common_End_2":
			dialog.text = "呃, 您付我钱就是为了这个, 船长。您以为船员们就为了那点微薄的薪水就会服从您的命令? \n"+
						  "几十个大男人挤在狭小的空间里, 谁也不知道什么时候能见到陆地, 或者还能不能见到。而毁掉一艘船? 太容易了。";
			link.l1 = "是是是, 熟悉的说辞, 阿隆索。你刚才是怎么说船的来着? ";
			link.l1.go = "Alonso_Common_End_3";
		break;

		case "Alonso_Common_End_3":
			dialog.text = "嘿! 船就是监狱、军营和修道院的结合体。总之就是一群男人聚在一起。所以问题要么用嘴解决, 要么用鞭子。您这种情况, 后者嘛, 嘿嘿, 用不上, 所以我想跟您聊聊。让您轻松点。";
			link.l1 = "你自己进过监狱吗? 当过兵? 进过修道院, 上帝保佑别有这事? 说起来, 阿隆索, 跟我说说你自己吧。我对你几乎一无所知。";
			link.l1.go = "Alonso_Story_1";
		break;

		// История Алонсо
		case "Alonso_Story_1":
			dialog.text = "修道院我确实没进过, 不骗你。不过我倒是在宗教裁判所服过役......";
			link.l1 = "你怎么会去那种地方? ";
			link.l1.go = "Alonso_Story_2";
		break;

		case "Alonso_Story_2":
			dialog.text = "哦! 事情是这样的。我在欧洲战争中当雇佣兵。鬼知道战争怎么开始的, 谁跟谁打。我们只知道战争打了三十年了, 哪个指挥官还算按时发饷。那才叫冒险呢! \n"+
						  "那是四二年......还是四一年? 无所谓了。两支连队, 都是为皇帝效力的, 在森林里遭遇了。大雾天。然后就开始互相砍杀! 三天的屠杀! ";
			link.l1 = "怎么会这样? ";
			link.l1.go = "Alonso_Story_3";
		break;

		case "Alonso_Story_3":
			dialog.text = "你试试在雾里分清敌友。再说我们三个月没拿饷了, 所以人人都想着战利品。\n"+
						  "我们互相杀了一半人。等发现的时候已经晚了。就在那时我认识了一个莫斯科人。像熊一样壮, 但心地善良! ";
			link.l1 = "然后呢? ";
			link.l1.go = "Alonso_Story_4";
		break;

		case "Alonso_Story_4":
			dialog.text = "你知道战争中是怎么回事吗? 谁先报告谁就是英雄。所以我们想------不如从这场灾难中捞点好处! \n"+
						  "我们跟弟兄们商量好, 去找军需官, 报告了一场'光荣的战斗'。死人的饷银没了, 活人拿到了钱, 我和我朋友得了奖金, 指挥官也有份。";
			link.l1 = "那你是富翁了, 阿隆索。";
			link.l1.go = "Alonso_Story_5";
		break;

		case "Alonso_Story_5":
			dialog.text = "哈! 然后我们喝了一周酒, 打了一周牌。幸好我这位来自遥远莫斯科王国的新朋友喜欢稀奇古怪的东西, 不然我就得进债务监狱了。他从我这儿买了件战利品: 一把华丽的三管手枪, 价钱还不错------没有趁人之危。";
			link.l1 = "故事很精彩, 阿隆索。但我觉得你是现编的。";
			link.l1.go = "Alonso_Gift";
		break;

		// Вручение подарка
		case "Alonso_Gift":
			dialog.text = "您这是冤枉我了, 船长。来, 收下这个小礼物。";
			link.l1 = "这是什么? ";
			link.l1.go = "Alonso_Gift_2";
		break;

		case "Alonso_Gift_2":
			// Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
			
			dialog.text = "火枪战斗用的弹药带。我那莫斯科朋友说, 在他家乡人人都戴这个。\n"+
						  "希望它对您有用, 船长。就当是船员们的礼物吧。";
			link.l1 = "真没想到! 谢谢, 阿隆索。那你在宗教裁判所的事呢? ";
			link.l1.go = "Alonso_Escape";
		break;

		case "Alonso_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
			dialog.text = "呃......\n"+
						  "钟声响了, 船长! 该干活了, 下次再说吧。";
			link.l1 = "我们一定会继续这个话题的。谢谢你的礼物! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
		break;
		
		// (Level 8) - Continuing the story
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "自从上次谈话以来您取得了很大成就, 没有人------无论是船员还是我------再怀疑您的才能了。";
			link.l1 = "曾经有过怀疑? ";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "当然有过。我们都是普通人------习惯做最坏的打算。享受您的自由吧, 船长。继续这样下去, 您会看到加勒比海完全不同的一面。";
            link.l1 = "很高兴听到这个。现在说说你在宗教裁判所的事吧。上次你从军队故事开始, 也以军队故事结束。";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "有什么好说的? 在那场毫无意义但收获颇丰的森林屠杀之后, 我和那个莫斯科人成了铁哥们, 又干了不少买卖。\n"+
                          "记得有一次我们决定抢劫皇家车队。侦察兵说他们运着战利品、黄金、武器......";
            link.l1 = "那么, 成功了吗? ";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "小菜一碟。我们从两边进攻, 驱散了守卫, 打开货车------里面是白菜! 给某个要塞的臭烂白菜! 但你知道吗? 我们一周没吃东西了, 所以连这个都高兴! ";
            link.l1 = "好像我船上的伙食就好到哪去似的。";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "现在我习惯了。但那时候......在野外觅食一周后------恨不得啃树皮! \n"+
                          "但我朋友没有灰心。他拿出一瓶自制的烈酒------说是莫斯科配方。我们才不管呢, 只要不是醋就行! 喝了几口后, 连白菜都像美味佳肴! ";
            link.l1 = "真恶心。";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "恶心的是我们淡水桶的状况, 但那莫斯科烈酒那天救了我的命。";
            link.l1 = "怎么回事? ";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "我们就在路边泥地里喝得烂醉, 白菜在泥水里漂着。然后一来二去, 我和一个小贵族吵起来了。是个德国人, 打扮得整整齐齐, 趾高气扬的。不屑于和我们一起喝酒, 只顾着擦他的火枪, 说些尖酸刻薄的话。\n"+
                          "我们坐在那儿, 休息着, 对着白菜借酒浇愁。他就开始给我们讲军事智慧。说我们信赖的剑和长矛很快就会被遗忘, 但刺刀------那才是未来, 是一切的关键。\n"+
                          "所以我和他争论起来, 不知怎么就约定要决斗到死------还是用刺刀。别问我怎么回事, 我自己都不记得了。\n"+
                          "但我们整个连队只有两把刺刀。一把是那个小军官的, 另一把是福克斯的, 一个英国人。我借了他的火枪, 把那德国人打死了, 然后就跑了。";
            link.l1 = "但你又饿又醉。";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "后来我才明白, 我朋友的酒确实能在挥舞沉重火枪时稳定手臂。所以现在我更倾向于同意那个死去的德国人的观点。";
            link.l1 = "这跟你在宗教裁判所的事有什么关系? ";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "您又不相信我了, 船长! 来, 拿着这个。";
            link.l1 = "一个瓶子和一张纸? ";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "这就是我跟您说的那种酒。还有配方。万一您喜欢呢, 嘿嘿。";
            link.l1 = "抱歉, 朋友, 但这些涂鸦和浑浊的液体不……";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "好吧好吧, 船长。反正我也打算送给您。这种武器不适合我, 但对您有用。刺刀是稀罕物。但一旦学会使用, 您就会忘记挥舞军刀了。";
            link.l1 = "等等, 这就是那个帝国军官的火枪? 你杀的那个? ";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "就是那把。如您所见, 我说的是实话, 船长。";
            link.l1 = "但我问的不是这个。";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "钟声响了, 船长! 该干活了, 下次再说吧。";
            link.l1 = "我们一定会继续这个话题的。谢谢你的火枪! ";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

       // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "船长, 关于新招募的船员......";
			link.l1 = "出什么事了吗? ";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "想向您报告, 晚饭时有个新兵提到, 他就是想上您的船。";
            link.l1 = "这到底意味着什么? ";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "很快会有更多这样的人。您现在有名气了, 船长。";
            link.l1 = "有趣的是, 我还是不知道你名字背后的故事。关于宗教裁判所的事你也没讲完。";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "哦, 我说到哪了......对了! 然后我们决定当军需供应商。战争快结束了, 得考虑未来。我朋友脑子里总是装满了对未来的打算。";
            link.l1 = "这可是职业生涯的大飞跃。不久前你们还在被抢劫的白菜车旁喝醉呢。";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "怎么了? 我们接到了为某个团做一百顶头盔的订单。预付款也不错。我们很高兴, 去庆祝了......打起了牌。\n"+
                          "早上醒来------钱没了, 军队两天后出发, 我们一顶头盔都没有! ";
            link.l1 = "那你们怎么办? ";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "去了刚打完仗的战场, 从死人身上收集帽子。然后钉上各种铁片, 装上护板......看起来很可笑, 但管用! 肯定能挡住军刀。嗯, 至少能挡一次。不就是头盔吗? ! ";
            link.l1 = "军需官欣赏你们的机智吗? ";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "把我们送上军事法庭, 罪名是贪污和欺诈。但你知道吗? 后来士兵们说, 那些帽子不止一次救了他们的命。结果也救了我们的。";
            link.l1 = "怎么回事? ";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "我们俩都进了监狱。而我们的连队被派去执行任务。不知道去哪里, 对付谁, 他们自己可能也不知道。再也没回来。\n"+
                          "...\n"+
                          "抱歉, 船长。下次再继续吧。拿着这顶帽子和说明书。昨天做的, 想让您高兴......但只是白白让自己难过了。";
            link.l1 = "当然, 阿隆索。谢谢你的礼物。";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "船长, 只是想报告, 您的船员现在在酒馆和妓院都受到贵宾待遇。如今在您的旗帜下服役意味着什么! ";
			link.l1 = "谢谢, 阿隆索......可惜我自己还没怎么享受到这种\"贵宾待遇\"。";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "很快就会了。加勒比海是几十个船长分享的蛋糕。很快您就会在那张桌子旁有一席之地, 抓住属于您的那块。\n"+
                          "谁知道呢? 也许您会成为拿走整个蛋糕的加勒比传奇。";
            link.l1 = "那你会讲完你的故事吗? 我们停在你进监狱那里。";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "哈! 伟大的帽子窃贼案。一个莫斯科人和一个葡萄牙人关在佛兰德斯某处的小牢房里。等待判决。当然是死刑。\n"+
                          "救了我们的是个重要人物------原来是莫斯科大使! 法杰伊的老朋友。路过这里, 听说了我们的困境, 把我们赎了出来! ";
            link.l1 = "法杰伊? 就是那个法杰伊? 你还瞒着不说? ! ";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "是啊。我们就此分别: 他回了莫斯科, 要么去打波兰人, 要么做大买卖。我在老家又转了转, 现在就在这儿了。";
            link.l1 = "令人印象深刻, 阿隆索。过了这么久, 你设法告诉了我一切, 就是没说你自己。奇怪的是, 像你这样聪明的人怎么会说漏嘴提到宗教裁判所。";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "我说的都是实话, 船长! 不信的话------去问法杰伊本人。在巴斯特尔不难找到他。";
            link.l1 = "也许我会去问。那礼物呢? ";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "啊? ";
            link.l1 = "每个故事结束时你都会给我礼物。";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "听到了吗? 钟声响了。该干活了。";
            link.l1 = "继续保持, 阿隆索。";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
	}
} 