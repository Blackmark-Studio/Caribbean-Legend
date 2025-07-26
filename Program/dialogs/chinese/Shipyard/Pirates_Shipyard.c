// 城市对话
// 这是改装大师
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "呼... 这气候太糟糕了... 我叫" + GetFullName(npchar) + ", 如果我不是这些被上帝遗忘的岛屿上最好的造船师, 就让上帝惩罚我。 但这湿气简直要把我打倒了... ";
				Link.l1 = pcharrepphrase("一千条鲨鱼作证, 我正缺一个老头唠叨呢。 我叫" +GetFullName(pchar)+ ", 相信你听说过我。 ",
					"这不是湿气, 是年纪大了, 先生。 我叫" +GetFullName(pchar)+ ", 相信你听说过我。 ");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "哦, 又是你, 总在说你的麻烦事... (咳嗽) 。 ";
				link.l1 = pcharrepphrase("没错, 又是我。 但趁你还没把灵魂交给上帝, 我们谈谈生意吧。 ",
					"你记性不错, 现在如果可以, 我们来问些具体问题。 ");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("我听腻了你的唠叨。 再见。 ",
					"我该走了。 抱歉打扰你。 ");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ---------------------------------—— 亚历克斯的航海钟 ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "啊哈, " +GetFullName(pchar)+ "船长! 真高兴你能过来! ";
				Link.l1 = "看来你有事找我, 对吧? 你平时可没这么客气。 ";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "我看你空手回来了, 船长! 那些... 客人怎么样了? ";
				Link.l1 = "他们走了。 我问过之后他们就走了。 ";
				Link.l1.go = "clock_complete";
				break;
			}
		//<—— 亚历克斯的航海钟
			dialog.text = "哦, 又是你, 总在说你的麻烦事... (咳嗽) ";
			link.l1 = pcharrepphrase("没错, 又是我。 但趁你还没把灵魂交给上帝, 我们谈谈生意吧。 ",
	            "你记性不错, 现在如果可以, 我们来问些具体问题。 ");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("我听腻了你的唠叨。 再见。 ",
				"我该走了。 抱歉打扰你。 ");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "现在的年轻人... 一点敬意都没有。 急性子, 笨手笨脚, 你需要什么? ";
			link.l1 = pcharrepphrase("说得对。 但凡事总有尽头, 看来你的时间快到了... ",
				"我觉得你年轻时未必对长辈有多尊重。 对吗? ");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "别跟长辈顶嘴, 小子。 ";
			link.l1 = pcharrepphrase("好了, 冷静点。 别太激动, 不然会心脏病发作。 我可不想被指控害死加勒比最好的造船师。 我们谈正事吧。 ",
				"出于对你年龄的尊重, 我原谅你的无礼。 现在如果你说完了, 我们谈正事吧。 ");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("好了, 教训够多了! 再见! ",
				"看来我们意见不合。 再见。 ");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(咳嗽)... 总有人打扰老人。 这次你需要我做什么, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = pcharrepphrase("我需要使用造船厂的服务。 ", "我想使用造船厂的服务。 ");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "我有个问题。 ";
			Link.l2.go = "quests"; //(跳转到城市文件)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "我想谈谈财务问题。 ";
				link.l3.go = "LoanForAll";//(跳转到城市文件)
			}
			link.l9 = pcharrepphrase("该死, 我有几件急事要处理, 再见。 ", "我该走了。 抱歉。 ");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = "我可以为你提供船体框架的大修服务。 这里的人根本不懂如何建造像样的船, 一炮就散架... ";						
				Link.l1 = "太好了! 我正好有艘船需要修理。 你能看看能做些什么吗? ";
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = "拜托, 你想怎样? 别烦老人... ";
			}	
			link.l2 = "我只是想使用造船厂的服务。 ";
			link.l2.go = "shipyard";
			link.l3 = "我需要船上的武器。 ";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "我想更换船帆的外观。 ";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "我的船很... 特别。 我想做些改动。 ";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "我有更多箱子用于船舱改造。 ";
					link.l50.go = "FDM_cabin_pay";
			}
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "我来处理船只改造的事。 ";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "我来处理船只改造的事。 ";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <—— Xenon
			link.l9 = pcharrepphrase("该死, 我有几件急事要处理, 再见。 ", "我该走了。 抱歉。 ");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = RandPhraseSimple("啊... 又是你。 想再修船? ",
				RandPhraseSimple("向著名船长问好。 怎么, 还需要大修? ",
                                           "唉... 一刻不得安宁。 你不让老人集中精力... 又要修船? "));
				Link.l1 = "是的。 你说得对。 我们看看能做什么? ";
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = "这次又怎么了? 你就不能让我清静点... ";
			}				
			link.l2 = "我只是想使用造船厂的服务。 ";
			link.l2.go = "shipyard";
			link.l3 = "我需要船上的武器。 ";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = "我想更换船帆的外观。 ";
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "我的船很... 特别。 我想做些改动。 ";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "我有更多箱子用于船舱改造。 ";
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = "我有个问题。 ";
			Link.l4.go = "quests"; //(跳转到城市文件)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "我想谈谈财务问题。 ";
				link.l5.go = "LoanForAll";//(跳转到城市文件)
			}
			Link.l9 = "不。 我对现状很满意。 ";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = "哦, 我知道你还在考虑! 你会有出息的! 决定好要什么再来, 别拿鸡毛蒜皮的事烦我。 ";
			Link.l1 = RandPhraseSimple("谢谢! 一切顺利。 ", "再见, 大师。 少点讽刺。 ");
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "船在哪儿? 搞什么鬼? ! ";
			    Link.l1 = "是, 您说得对... 我是... 抱歉。 ";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "我虽然是工作狂, 但也要吃午饭。 过会儿再来! ";
			        Link.l1 = "好吧... ";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = "唉... 你的船彻底报废了。 我不会做大修的, 别问了... 要是你早点来... ";
    			        Link.l1 = "好吧... 太糟糕了... ";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = "搞什么鬼... 你的船跟新的一样... 船架亮得发光, 没什么可修的。 ";
						Link.l1 = "好吧... 那我过会儿来... ";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = "好吧, 看看这里... 啊哈, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + "。 ";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " 呸! 这船转手太多次了, 好多划痕。 你有海盗执照吗? 开玩笑... 言归正传。 ";
    			    }
                    dialog.Text = s1;
					Link.l1 = "看看我们能做什么。 ";
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l2 = "等等! 我改变主意了。 ";
    			    Link.l2.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = "看看我们能做什么。 目前船架强度是" + shipCurHP + ", 最高值是" + shipBaseHP;			
			s1 = s1 + "。 大修需要: 铁木-" + Matherial1 + "。 树脂-" + Matherial2 + "。 船用丝绸-" + Matherial3 + "。 绳索-" + Matherial4 + "。 ";
			s1 = s1 + "人工费收" + HPPrice + "杜布隆... 孙子们一直叫我回欧洲, 不想空手回去。 就这些, 钱要先付。 ";
            dialog.Text = s1;
			Link.l1 = "听起来不错, 我接受条件, 会按约定交付材料。 ";
			if (CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = "不, 我不满意。 ";
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = "好的... 付款... 可以现在付, 或者派个跑腿回船上取。 你想怎么做? ";
			link.l1 = "现在付。 ";
			link.l1.go = "ship_repair_HP_start";
			link.l2 = "派跑腿去, 我记得箱子里有点金子... ";
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = "太好了, 我等你带材料来。 ";
			    link.l1 = "去收集材料... ";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "大修" + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    "需要: 铁木-" + NPChar.Repair.Matherial1 + "。 树脂-" + NPChar.Repair.Matherial2 + "。 船用丝绸-" + NPChar.Repair.Matherial3 + "。 绳索-" + NPChar.Repair.Matherial4 + 
				"。 已付定金" + NPChar.Repair.Money + "杜布隆... 他说要回欧洲, 我觉得这老鬼在撒谎。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple("没看到定金... ", "搞什么鬼... ");
				link.l1 = "我过会儿来。 ";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "太好了, 我等你带材料来。 ";
			link.l1 = "这就去... ";
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText", "大修" + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    "需要: 铁木-" + NPChar.Repair.Matherial1 + "。 树脂-" + NPChar.Repair.Matherial2 + "。 船用丝绸-" + NPChar.Repair.Matherial3 + "。 绳索-" + NPChar.Repair.Matherial4 + 
				"。 已付定金" + NPChar.Repair.Money + "杜布隆... 他说要回欧洲, 我觉得这老鬼在撒谎。 ");
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "时间紧迫, 材料齐了吗? ";
			    Link.l1 = "齐了, 我弄到了。 ";
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = "没, 还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = "先生, 您好像换船了, 之前的约定得重新算... ";
			    Link.l1 = "是的, 真可惜定金没了... ";
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = "材料齐了! 好, 开始干活... ";
			    link.l1 = "好, 我等着。 ";
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "还需要带: " + sti(NPChar.Repair.Matherial1) + "铁木。 " + sti(NPChar.Repair.Matherial2) + "树脂。 " + NPChar.Repair.Matherial3 + "船用丝绸。 " + NPChar.Repair.Matherial4 + "绳索。 ";
				link.l1 = "知道了。 ";
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "剩余材料: 铁木-" + NPChar.Repair.Matherial1 + "。 树脂-" + NPChar.Repair.Matherial2 + "。 船用丝绸-" + NPChar.Repair.Matherial3 + "。 绳索-" + NPChar.Repair.Matherial4 + "。 ");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = "... 好了... 保证这船现在很难撞坏! ";
			Link.l1 = "谢谢! 我不想试验, 但信你一次。 ";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
/////////////////////////////// 任务分支
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你刚才已经问过我问题了... ", "在我的造船厂或镇上其他任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题做什么? 我的工作是造船, 咱们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可谈的。 "), "嗯, 我的记性哪儿去了... ",
                      "嗯, 好吧... ", "好吧, 我们... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "听着, 我想过去, 但那扇门是锁着的... ";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "我想提议做笔交易。 ";
				link.l1.go = "Al_ShipLetters_1";// 生成器 "找到的船舶文件"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "我来是为了护卫舰的材料。 ";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "听着, " + npchar.name+ ", 你最近在宝藏岛见过米格尔.迪乔索吗? ";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** 生成器 - "找到的船舶文件" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "说说你的条件。 ";
			s1 = "我幸运地找到了一整套完全合法的船舶文件, 还没被要求搜查过。 ";
			s1 = s1 + "船还在航行, 也没有从登记册中除名, 别担心。 只是一个愚蠢的船主不幸弄丢了这些文件... ";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "让我看看! 看起来确实是刚填写的。 嗯, 先生, 你运气真好! ";
			s1 = s1 + "我其实正需要这样一套文件。 作为回报, 我给你" + sti(pchar.questTemp.different.GiveShipLetters.price5) + "比索。 你觉得怎么样? ";
			dialog.text = s1;
			link.l1 = "真是皇家般的慷慨! 我当然同意! ";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "不, 我觉得不行。 ";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //移除计时器 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** 开门 ***************************
 		case "Step_Door_1":
			dialog.text = "没错。 如果你想穿过这扇门, 得付我20000比索。 不付钱, 我就不开。 这不是施舍处。 而且我也不建议你去那里, 你最好别去... ";
			if (sti(pchar.money) >= 20000)
			{
    			link.l1 = "给你钱, 开门。 ";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "我没那么多钱。 ";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "没门! 我绝不会为一扇门付钱。 ";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // 修复
			dialog.text = "进去吧, 门开了。 别担心谢我! ";
			link.l1 = "不, 为什么不呢。 谢谢你, " + npchar.name+ "... ";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "好吧, 等你有钱了再来。 否则别想说服我, 没用的... ";
			link.l1 = "啊, 我完全无语了! ";
			link.l1.go = "exit";
		break;
		
	// -----------------------------------------—— 亚历克斯的航海钟 ----------------------------------------------// Addon-2016 Jason 到处将杜布隆替换为比索
		case "clock_begin":
			dialog.text = "别对一个老人这么严厉... 我真的需要你的帮助, 船长。 ";
			link.l1 = "告诉我, 大师。 你怎么了? ";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "史蒂文.多德森";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "马库斯.泰雷克斯";
			dialog.text = "我们新的海岸兄弟会领袖, " + sTotalTemp + ", 订购了一艘新船, 一艘护卫舰。 他还提出了相当苛刻的要求: 防护船体。 快速航行和良好的机动性, 还要尽可能大口径的加农炮\n我知道, 舰队司令的船, 抱歉, 兄弟会领袖的船必须特别, 但这意味着我需要特殊材料来建造。 你肯定听说过这些材料: 铁木。 树脂。 船用丝绸和绳索... ";
			link.l1 = "那你去告诉兄弟会领袖啊。 还是你担心" + sTotalTemp + "会为此砍你的头? ";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "我告诉他了... 问题是我们的新领袖没有时间也没有机会找到并带来这些材料。 你得知道这有多稀有。 没有这些材料, 我根本无法建造具有上述特性的护卫舰。 ";
			link.l1 = "你可能是想让我去为这艘船找材料? ";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "嗯, 是的。 你是我们领袖的好朋友。 " + sTotalTemp + "自己说他欠你很多, 还说要对你百般尊敬... 所以我想: 既然你是他的朋友, 也许你不会反对帮助他? 同时, 你也明白我现在的处境有多尴尬吧? 所有材料都会付钱的, " + sTotalTemp + "不会吝啬他的金子。 ";
			link.l1 = "很抱歉, 大师, 但我和" + sTotalTemp + "一样忙。 恐怕收集材料可能需要一辈子。 所以你最好问问别人。 ";
			link.l1.go = "clock_exit";
			link.l2 = "好吧, 如果" + sTotalTemp + "向你订购了船, 那我当然会尽力帮忙。 我们确实是朋友, 朋友就应该互相帮助。 你需要多少材料? ";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "太遗憾了, 真的太遗憾了。 我本来就指望你了。 好吧, 正如他们所说, 不愿意就是不愿意... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "我还缺100单位铁木。 150容器树脂。 110卷船用丝绸和90卷麻绳。 你觉得怎么样? 你能在四个月内帮我找到这些吗? 我想我没有更多时间了。 ";
			link.l1 = "我至少可以试试。 至于报酬呢? ";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "我的价格是: 铁木每单位4000比索, 树脂每容器1400比索, 丝绸每卷2500比索, 绳索每卷1500比索。 如果你把这些都带给我, 你会收到我一份非常好的礼物。 ";
			link.l1 = "我想知道是什么? ";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "先把材料带给我。 但我向你保证: 这东西会对你很有用, 而且是独一无二的。 在加勒比海, 甚至全世界都还没有第二件。 我希望这点好奇心能激发你为我收集材料的兴趣。 ";
			link.l1 = "好吧, 大师, 你真狡猾! 好吧, 就这么说定了。 ";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "我很高兴。 我期待你的归来。 ";
			link.l1 = "我希望不会太久... ";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // 计时器
			AddQuestRecord("alex_clock", "1");
			// 记住变量
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "太好了! 你今天给我带来了什么? ";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "铁木, 数量为" + FindRussianQtyString(iSan) + "。 ";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "树脂, 数量为" + FindRussianQtyString(iOil) + "。 ";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "船用丝绸, 数量为" + FindRussianQtyString(iSil) + "。 ";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "麻绳, 数量为" + FindRussianQtyString(iRop) + "。 ";
				link.l4.go = "ropes";
			}
			link.l5 = "目前什么都没有。 我只是想确认我们的协议是否仍然有效。 ";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // 全部带来
			{
				dialog.text = "太棒了! 我已经得到了所需数量的所有材料。 非常感谢你的帮助, 船长。 你帮了我大忙。 ";
				link.l1 = "是的, 随时效劳, 大师。 我也很高兴: 我帮助了朋友, 还赚了些钱。 现在让我们回到之前的话题, 谈谈你答应我的那个神秘物品。 ";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "船长, 还有什么惊喜给我吗? ";
				link.l1 = "唉, 目前就这些了。 继续等着吧。 ";
				link.l1.go = "exit";
				link.l2 = "是的, 我还有一样东西... ";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "铁木。 你已经给我带来了" + FindRussianQtyString(iSan) + "。 所以, 你还需要给我带来" + FindRussianQtyString(iTemp) + "。 好的, 按每单位4000比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! 剩下的很快就会带来。 ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // 还需带来的数量
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "铁木。 你已经给我带来了" + FindRussianQtyString(iSan) + "。 所以, 我们现在已经解决了铁木的问题! 好的, 按每单位4000比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // 树脂
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount - iOil;
			if (iTemp > 0) // 还未全部带来
			{
				iSum = 1400*iOil;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "树脂。 你已经给我带来了" + FindRussianQtyString(iOil) + "。 所以, 你还需要给我带来" + FindRussianQtyString(iTemp) + "。 好的, 按每容器1400比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! 剩下的很快就会带来。 ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "树脂。 你已经给我带来了" + FindRussianQtyString(iOil) + "。 所以, 我们现在已经解决了树脂的问题! 好的, 按每容器1400比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "船用丝绸。 你已经给我带来了" + FindRussianQtyString(iSil) + "。 所以, 你还需要给我带来" + FindRussianQtyString(iTemp) + "。 好的, 按每卷2600比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! 剩下的很快就会带来。 ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "船用丝绸。 你已经给我带来了" + FindRussianQtyString(iSil) + "。 所以, 我们现在已经解决了船用丝绸的问题! 好的, 按每卷2600比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "绳索。 你已经给我带来了" + FindRussianQtyString(iRop) + "。 所以, 你还需要给我带来" + FindRussianQtyString(iTemp) + "。 好的, 按每卷1500比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! 剩下的很快就会带来。 ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "好的, 行。 我还需要" + FindRussianQtyString(amount) + "绳索。 你已经给我带来了" + FindRussianQtyString(iRop) + "。 所以, 我们现在已经解决了绳索的问题! 好的, 按每卷1500比索计算, 你的报酬总计" + FindRussianMoneyString(iSum) + "。 请收下。 ";
				link.l1 = "谢谢! ";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "是的, 是的... 当然是关于我的东西。 嗯... 嗯... 我把它放在哪里了... 啊... ";
			link.l1 = "怎么了, 大师? 你看起来很担心。 有什么问题吗? 遇到什么麻烦了? ";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "正是。 麻烦。 最近的麻烦。 该死的那些寻宝者... ";
			link.l1 = "冷静点, 冷静点。 你这年纪这么担心可不好。 上帝保佑, 你可能就差那么一下了。 那到时候谁来为兄弟会领袖建造护卫舰呢? 冷静下来, 给我解释一下这些寻宝者是谁? ";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "我桌子那边有一扇门。 它直接通向一个古老的地窖。 在地窖的一个宝箱里, 我放着一个金属盒子, 里面装着二十年前我被卷入那个该死的漏斗时带在身上的东西, 然后我就来到了这里... ";
			link.l1 = "什么漏斗? 你在说什么? ";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "啊, 抱歉, 我又胡思乱想了。 上了年纪不容易啊, 年轻人。 请原谅。 但这不重要。 重要的是, 给你的礼物盒子在那个宝箱里, 现在那个地窖被一些混蛋占据了。 他们不是我们的人, 也不是宝藏岛的人\n是寻宝者, 肯定有人告诉他们这个地方到处都是宝藏。 他们不敢在这里露面, 但是我太害怕了, 不敢去见他们, 明白吗? 他们的样子... ";
			link.l1 = "我明白了。 打开你的门。 我会把这些不速之客赶出去。 ";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "就这么办? 你要把他们赶出去? 一个人? 你不害怕吗? 只要你开口, 我们整个定居点的人都会为你而战... ";
			link.l1 = "少废话, 多行动, 大师。 打开这扇门, 剩下的交给我。 你把东西放在哪个宝箱里了? ";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "走廊尽头有一整排空木桶。 在它们后面的地板隐蔽处有一个小宝箱。 我在上面锁了一把锁, 所以我怀疑那些闯入者即使找到了它, 也没办法把他们的脏手伸进去。 给, 拿着钥匙。 ";
			link.l1 = "很高兴你考虑得这么周到。 在这里等着, 哪里也别去。 ";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "他们就听了你的话离开了? ";
			link.l1 = "没错。 他们原来是些有礼貌的好人。 我跟他们解释说他们的存在吓坏了这位著名的老造船师, 出于对你年纪的尊重, 他们就离开了这里。 你可以放心下去了。 ";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "啊哈, 你在嘲笑一个老人! 好吧。 把我的盒子给我, 我打开它, 把你应得的装置给你。 ";
			link.l1 = "请拿去吧... ";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "感谢! 我们打开它。 给, 拿着这个。 自动机械计时器, 这里没人能制造这种装置, 未来三百年也不会有人能... 嗯, 抱歉, 请原谅一个老人。 我想说的是这东西独一无二\n它完全自动工作, 你不再需要愚蠢的沙漏之类的东西。 没有误差! 只要避免直接撞击和进水, 否则你会失去它。 即使是猿猴也能使用这个计时器。 ";
			link.l1 = "看看这个! 我这辈子从没见过这么神奇的东西! 谢谢, 大师。 ";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("你获得了一个自动机械计时器");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "不客气。 现在你总能确切知道时间了。 别问我是从哪里弄来的。 我不会告诉你的。 ";
			link.l1 = "每个人都有自己的秘密, 不是吗, 大师? 好吧... 保守你的秘密, 我不会干涉你的事。 谢谢你的礼物! ";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "也谢谢你的帮助, 船长。 有空来看看我。 别忘了我这个老造船师。 ";
			link.l1 = "我怎么可能忘记你... 不管怎样, 我肯定会的, 大师亚历克苏斯。 再见! ";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <—— 亚历克斯的航海钟任务结束
		
		// 玛雅城任务
		case "tieyasal":
			dialog.text = "啊哈, 米格尔! 我的老相识。 我还记得他。 他一遍又一遍地询问每个细节。 但当他连简单的电报都没见过时, 我怎么跟他解释里面的收音机是如何构造的呢? ";
			link.l1 = "什么? ... 您在说什么, 大师? ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "哦, 抱歉, 年轻人。 别太在意我的胡言乱语... 我们好奇的米歇尔满足了好奇心后就消失了。 就在三天前我们还聊过天。 ";
			link.l1 = "如果您不介意我问的话, 米格尔现在在哪里? ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "谁知道呢。 也许他在夏普敦忙自己的事, 或者已经离开宝藏岛了。 ";
			link.l1 = "明白了。 谢谢您, 大师! ";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// 卡莱乌切船只改造任务
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime")) // 检查NPC是否有二次改造标记
				dialog.text = "又来谈你的'幽灵船'... 听着, 我之所以还在处理它, 是希望它能变得像样点。 否则我根本不会碰它。 我想海上的人都有同感。 这次你想怎么改? ";
			else	
				dialog.text = "啊, 那艘'幽灵船'! 母亲们都用你的大帆船来吓唬调皮的孩子。 而你居然没把它沉了, 还留着这艘该死的船! 水手们在地平线看到它都会发抖... 你想对它做什么? ";
			if (!CheckAttribute(npchar, "quest.FDM_cabin")) // 检查船舱改造状态
			{
				link.l1 = "我喜欢看胆小鬼被吓得屁滚尿流的样子。 但船舱内部太糟糕了。 你看过那船舱吗? 像口棺材似的, 全是霉菌和灰尘。 我想翻新一下, 你能做到吗, 大师? ";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails")) // 检查船帆改造状态
			{
				link.l2 = "我受够了那些破烂的黑布帆。 虽说它们和普通帆一样能兜风, 但那外观... 恶心死了。 我想要普通的雪白船帆。 你能接这活吗, 大师? ";
				link.l2.go = "FDM_sails";
			}
			
			if (!CheckAttribute(npchar, "quest.FDM_hull")) // 检查船体改造状态
			{
				link.l3 = "嗯, 我觉得是时候让它变像样了。 船本身不错, 船员也习惯了, 但让一位体面的船长驾驶一艘能把成年人吓破胆的船 --更别说孩子了 --实在有失尊严。 我想彻底重建, 让其他船长看到我的船时只有羡慕的份, 而不是吓得画十字。 除了群岛上最棒的造船师, 我还能找谁呢? ";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "为什么不呢? 我的手还稳当着呢。 你的大帆船这么大, 我甚至可以给你造一个像战列舰那样的皇家船舱。 或者保留标准船舱。 你选哪个? ";
			link.l1 = "造战列舰级别的船舱! 让他们羡慕得眼红... ";
			link.l1.go = "FDM_cabin_m";
			link.l2 = "没必要太奢华。 保留标准的吧。 ";
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "好的。 十箱杜布隆, 五天内完工。 ";
			link.l1 = "成交! ";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "十箱? 一千五百杜布隆? 嗯, 这么大的开销我得考虑一下... ";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "好的。 七箱杜布隆, 五天内完工。 ";
			link.l1 = "成交! ";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "七箱? 一千多杜布隆? 嗯, 这么大的开销我得考虑一下... ";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "好的, 我等你付款。 ";
			if (iTemp > 0)
			{
				link.l1 = "我随身带着箱子。 看, 这里有" + FindRussianQtyString(iTemp) + "箱。 ";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "我得去把硬币装到箱子里。 ";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "好的, 我等你付款。 ";
			if (iTemp > 0)
			{
				link.l1 = "我随身带着箱子。 看, 这里有" + FindRussianQtyString(iTemp) + "箱。 ";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "我得去把硬币装到箱子里。 ";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = "所以你需要带" + FindRussianQtyString(sti(npchar.quest.FDM_cabin)) + "箱, 现在带来了" + FindRussianQtyString(iTemp) + "箱。 钱已收到, 现在该我干活了。 去四处走走吧, 别担心, 我会尽力的。 ";
				link.l1 = "好的... ";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "所以你需要带" + FindRussianQtyString(sti(npchar.quest.FDM_cabin)) + "箱, 现在带来了" + FindRussianQtyString(iTemp) + "箱。 还剩" + FindRussianQtyString(amount) + "箱。 ";
				link.l1 = "好的, 大师。 ";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = "当然可以! 嗯... 这意味着我们要扔掉所有脏兮兮的旧帆布, 换上崭新的棉质白帆。 这可是个大工程。 材料和工时费一共十万比索。 成交? ";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "没问题, 成交! ";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "嗯... 我得考虑一下... ";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "好的, 钱已收到, 该我干活了。 在完工前四处走走吧, 别担心。 ";
			link.l1 = "好的... ";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon (代码标记) 
		case "FDM_hull":
			dialog.text = "哦, 很高兴终于听到你这么说。 说真的, 你看起来是个不错的人, 但你现在开的船简直不忍直视。 不过我得先提醒你, 这活可不是几小时能搞定的, 而且价格不菲。 ";
			link.l1 = "好吧, 你能说具体点吗? ";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "行, 我们算一下... 彻底翻新船壳需要150单位铁木。 130卷绳索。 170卷船用丝绸和200桶树脂。 全部费用25万比索。 别这么看我, 大部分钱都是花在工费上的! 毕竟我们不是在修小渔船。 ";
			link.l1 = "我觉得不行。 我可不想拖着这么多材料, 还要付25万比索。 看来我还是继续用这艘船吧。 ";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "唉, 为了我的船还有什么不能做的... 好吧, 成交。 ";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "好, 少说多做。 你把钱带来, 我就开始采购所需材料。 一旦收到钱, 你就可以开始送材料了, 我也会开始动工。 ";
			if(sti(pchar.money) >= 250000)
			{
    			link.l1 = "钱不是问题, 我现在就有。 给你, 大师。 ";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else // 资金不足时
            {
    			link.l1 = "目前我没这么多钱。 稍等, 我会给你带来的。 ";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			addMoneyToCharacter(pchar, -250000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "带着这么一大笔钱在海盗定居点走动不害怕吗, 呵呵? 开玩笑的, 他们都是些守规矩的人。 现在我等你送材料来。 提醒一下, 你需要带150铁木。 130卷绳索。 170卷船用丝绸和200桶树脂。 ";
			link.l1 = "等着吧, 我会把材料带来的。 ";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "非常好! 你今天给我带来了什么? ";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "铁木, 数量为" + FindRussianQtyString(iSan) + "。 ";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "树脂, 数量为" + FindRussianQtyString(iOil) + "。 ";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "船用丝绸, 数量为" + FindRussianQtyString(iSil) + "。 ";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "绳索, 数量为" + FindRussianQtyString(iRop) + "。 ";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "还没带什么。 只是想确认一下交易是否仍然有效。 ";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
			{
				dialog.text = "太棒了! 所有材料都已收齐。 现在, 让我来处理这艘船吧。 它终于要焕然一新了。 ";
				link.l1 = "好了, 别唠叨了, 大师。 我迫不及待想看到结果了。 ";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "船长, 还有什么能让我开心的东西吗? ";
				link.l1 = "唉, 目前就这些了。 ";
				link.l1.go = "exit";
				link.l2 = "是的, 我还有别的东西给你... ";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // 铁木
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "让我看看... 我需要" + FindRussianQtyString(amount) + "单位的铁木。 你带来了" + FindRussianQtyString(iSan) + "单位。 因此, 你还需要再给我" + FindRussianQtyString(iTemp) + "单位。 ";
				link.l1 = "谢谢! 我很快就会把剩下的带来。 ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "铁木");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "让我看看... 我还需要" + FindRussianQtyString(amount) + "单位的铁木。 你给我带来了" + FindRussianQtyString(iSan) + "单位。 因此, 铁木已经收齐了! ";
				link.l1 = "谢谢! ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "铁木"); 
			}
		break;

		case "FDM_oil": // 树脂
			amount = 200 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "让我看看... 我需要" + FindRussianQtyString(amount) + "单位的树脂。 你带来了" + FindRussianQtyString(iOil) + "单位。 因此, 你还需要再给我" + FindRussianQtyString(iTemp) + "单位。 ";
				link.l1 = "谢谢! 我很快就会把剩下的带来。 ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "树脂");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "让我看看... 我还需要" + FindRussianQtyString(amount) + "单位的树脂。 你给我带来了" + FindRussianQtyString(iOil) + "单位。 因此, 树脂已经收齐了! ";
				link.l1 = "谢谢! ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "树脂");
			}
		break;

		case "FDM_shipsilk": // 船用丝绸
			amount = 170 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "让我看看... 我需要" + FindRussianQtyString(amount) + "单位的船用丝绸。 你带来了" + FindRussianQtyString(iSil) + "单位。 因此, 你还需要再给我" + FindRussianQtyString(iTemp) + "单位。 ";
				link.l1 = "谢谢! 我很快就会把剩下的带来";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "船用丝绸");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "让我看看... 我还需要" + FindRussianQtyString(amount) + "单位的船用丝绸。 你给我带来了" + FindRussianQtyString(iSil) + "单位。 因此, 船用丝绸已经收齐了! ";
				link.l1 = "谢谢! ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "船用丝绸"); 
			}
		break;

		case "FDM_ropes": // 绳索
			amount = 170 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "让我看看... 我需要" + FindRussianQtyString(amount) + "单位的绳索。 你带来了" + FindRussianQtyString(iRop) + "单位。 因此, 你还需要再给我" + FindRussianQtyString(iTemp) + "单位。 ";
				link.l1 = "谢谢! 我很快就会把剩下的带来";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "绳索");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "让我看看... 我需要" + FindRussianQtyString(amount) + "单位的绳索。 你给我带来了" + FindRussianQtyString(iRop) + "单位。 因此, 绳索已经收齐了! ";
				link.l1 = "谢谢! ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "绳索");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "那么, 你把钱带来了吗? ";
			if(sti(pchar.money) >= 250000)
			{
    			link.l2 = "是的, 带来了。 25万比索, 按约定。 ";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "还没, 再等等, 大师。 ";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("五天过去了... " + NewStr() + "亚历克苏斯大师完成了工作", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); // 时间流逝
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
			RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
			RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
			/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
			RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
			RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
			if(Get_My_Cabin() == "My_Cabin") RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";	
			else RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0); // 白色棉质船帆
			RealShips[sti(Pchar.Ship.Type)].HP = GetCharacterShipBaseHP(pchar);
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
		break;
		//<—— Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部有通过return退出的情况, 不要忘记卸载
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "材料" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}
