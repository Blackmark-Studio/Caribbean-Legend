void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "这是一个bug。 联系开发者, 让他们知道你是如何以及在哪里发现它的";
					link.l1 = RandSwear() + "我会让他们知道的! ";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // 任务"海湾会面"中的士兵
			{
				dialog.text = "我无权与你打交道。 去和我们的军官谈。 ";
					link.l1 = LinkRandPhrase("当然...", "我明白了。 ", "当然可以! ");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // 任务"海湾会面"中的军官
			{
				dialog.text = "介绍你自己! 我想知道我在和谁说话! ";
					link.l1 = "我的名字是" + GetFullName(PChar) + "。 这里发生了什么事? ";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // 生成任务"海湾会面"中的任务人物
			{
				dialog.text = "船长, 你的名字是" + GetFullName(PChar) + ", 对吗? ";
					link.l1 = "是的, 你说得对。 ";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "不。 你把我错认成别人了。 ";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar,"GenQuest.ContraMeetMan.ContraIsDead")) // 酒馆房间里杀死 Contra 之后
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name + ", 非常感谢你! 如果不是你, 我的命运将不堪设想... 我该如何感谢你? ";
					link.l1 = "我不需要任何东西...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "我不会拒绝一点小小的奖励。 ";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // 任务"海湾会面"房间里的 Contrick
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar,"GenQuest.ContraMeetMan.ManIsTraitor")) // 只是付钱
				{
					dialog.text = "...嗯, 确实是他... 谢谢你, " + GetSexPhrase("伙计", "姑娘") + ", 没有你的帮助我们会很困难, 我们根本无法出城。 拿着" + FindRussianMoneyString(iMoney) + ", 你可以走了。 我们将和我们的朋友好好'谈谈'...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...嗯, 确实是他... 谢谢你, " + GetSexPhrase("伙计", "姑娘") + ", 没有你的帮助我们会很困难, 我们根本无法出城。 拿着" + FindRussianMoneyString(iMoney) + ", 你可以走了。 我们现在就把这个肮脏的叛徒开膛破肚! ";
						link.l1 = "当然。 先生们, 后会有期...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "什么? ! 不, 我不会允许你们谋杀一个人, 不管他是谁... 而且我不需要你们的血腥钱! ";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // 房间里的士兵
			{
				dialog.text = "那么... 我们在这里发现了什么? 海盗? ! 你必须跟我们去指挥官办公室接受调查...";
					link.l1 = "我们根本不是海盗! 我甚至不认识这个人! 他刚租下并搬进这个房间, 我还没来得及收拾行李离开! ";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "那么你刚才说什么? 你有消息要给我? ! 我等着呢! ";
					link.l1 = "给你...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "嘿, 你! 是的, 就是你。 我看你是个体面又富有的人。 ";
					link.l1 = "我可不能说你同样如此。 ";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "站住! 嘿, " + GetSexPhrase("兄弟", "姑娘") + ", 让我们看看你的钱包有多鼓! ";
					link.l1 = "那么, 你已经把教堂的钱都挥霍光了吗? ";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "嘿, 船上的人! 嗝... 让开航道 - 我需要和这些伙计谈谈...";
					link.l1 = "伙计, 你是不是有点晕乎乎的? 去睡一觉醒醒酒吧。 ";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "嘿, 船长! 抛锚! ";
					link.l1 = "我究竟为什么要....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "你是不是太粗鲁了! ? ";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("向你致敬! 终于, 上帝听到了我们的祈祷, 派了一位勇敢的船长来到这个荒芜的海岸! ",
					"感谢上帝! 现在当地的拾荒者不会啃食我们腐烂的骨头了! ");
				link.l1 = "你好, 好人, 我是" + GetFullName(PChar) + "船长。 我看你在这里遇到了很大的麻烦。 ";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "好人, 我有自己的事要处理, 没有时间浪费在你的麻烦上。 ";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("哦, 船长! 上帝让你顺风顺水, 把你引到这个荒凉的地方, 真是太幸运了! ",
					"船长! 感谢上帝, 你决定在这个荒凉的海岸抛锚! ");
				link.l1 = "你好, 好人, 我是" + GetFullName(pchar) + "船长。 我看你在这里遇到了严重的麻烦。 ";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "好人, 我有自己的事要处理, 没有时间浪费在你的麻烦上。 ";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("等等, " + GetAddress_Form(pchar) + "! 你能为我们抽出宝贵的一分钟吗? ", "尊贵的" + GetSexPhrase("先生", "女士") + ", 能听听这些微不足道的人卑微的请求吗? ", "尊贵的" + GetSexPhrase("先生", "女士") + ", 请给不幸的人一点宝贵的时间来交谈。 ");
				link.l1 = LinkRandPhrase("我没时间做这个。 ", "滚开, 我有很多事要做, 没你不行。 ", "别烦我, 我没时间理你。 ");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("你想要什么? ", "你需要什么? ", "有什么麻烦? ");
				link.l2.go = "Convict_Begin";
			}
			
			// 战船, 15.05.11。 生成器"正义待售"。 
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "嗨, 船长! 你对印度饰品和普通商店买不到的商品感兴趣吗? 或者也许是现金? ";
					link.l1 = "像你这样的衣衫褴褛的人通常只会索取 - 而不是提供任何东西。 你为什么如此奇怪地客气? ";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "我的手枪通常会和你这样的混蛋说话! ";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// 生成器"货舱情况 - 赎金"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "我在听你说, 船长。 你是来谈生意的吗? ";
			link.l1 = "我在找" + pchar.GenQuest.Hold_GenQuest.Name + "先生? ";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("我就是" + pchar.GenQuest.Hold_GenQuest.Name + "先生。 请问您是哪位? ", "你找到他了。 我能为你做什么? ");
			link.l1 = "我是" + GetFullName(pchar) + "船长, 我想和你谈谈关于" + pchar.GenQuest.Hold_GenQuest.CapName + "的事。 ";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "那是谁? ";
					link.l1 = "等等... 你是" + pchar.GenQuest.Hold_GenQuest.Name + ", 你不认识" + pchar.GenQuest.Hold_GenQuest.CapName + "? ";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "哇! 我上次听到那个老狐狸的消息已经有一段时间了? 这次他又发生了什么事? ";
					link.l1 = "这次他遇到了大麻烦... 他被俘虏了, 需要你的帮助。 ";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "好吧, 我洗耳恭听。 ";
					link.l1 = "他的船被海盗袭击了, 现在被俘虏了。 他建议我来找你谈谈赎金的事。 ";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "是的, 听到老朋友的消息我很高兴。 他最近怎么样? ";
					link.l1 = "他的处境非常糟糕, 难以想象。 ";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "Indeed, I am " + pchar.GenQuest.Hold_GenQuest.Name + "! But why should I know anything about that " + pchar.GenQuest.Hold_GenQuest.CapName + "?!";
			dialog.text = "没错, 我就是" + pchar.GenQuest.Hold_GenQuest.Name + "! 但是" + pchar.GenQuest.Hold_GenQuest.CapName + "这个名字我没听说过。 "; // belamour 生成
			link.l1 = "对不起。 也许我搞错了...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "哇! 你期望我怎么帮助他? 通过杀死他所有的敌人来释放他还是什么? 哈哈哈! ";
			link.l1 = "不, 不需要那样。 你只需要交出" + pchar.GenQuest.Hold_GenQuest.RansomSum + "比索作为赎金。 ";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "真是厚颜无耻! 我为什么要为他支付赎金? ! 他既不是我的亲戚也不是我的朋友! ";
			link.l1 = "嗯... 他告诉我你是他唯一的希望。 他还提到你欠他一些债务...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("真是个无礼的家伙! 告诉你, 是他欠我钱! 但这不是我赎他的理由, 指望他能还清两笔债务。 ",
				"真是个无赖! 我们分业务时他骗了我, 现在他竟然有脸让我为他支付赎金! ",
				"现在这真是个惊喜! 我为什么要为他支付赎金? ! 我们没那么亲近。 ");
			link.l1 = "那么, 我可以告诉他你拒绝支付他的赎金, 并且不承认你的债务吗? ";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "哦, 我的天! 你在说什么债务? 我已经向你解释了一切! 如果你除了这个愚蠢的故事之外没有其他问题, 那么请允许我离开。 ";
			link.l1 = "我明白了。 好吧, 我没有更多问题要问你了, 但我对你的那个伙伴有很多问题。 ";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // 准备吊死NPC? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour 生成				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "嗯... 我猜, 你就是那个关押他的人... 好吧, 我想我会帮他的。 ";
			link.l1 = "非常好。 赎金将是" + pchar.GenQuest.Hold_GenQuest.RansomSum + "比索。 ";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "你误解我了: 我是市议会的成员。 我们监督宪章的遵守情况。 \n" + 
				"卫兵! 卫兵! 以涉嫌贩卖奴隶和掠夺" + NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)) + "船只的罪名逮捕他! ";
			link.l1 = "好吧,'伙计', 让我靠近你...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour 生成	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "你在说什么? ! 我怎么帮助他? ";
			link.l1 = "他被俘虏了, 他让我和你谈谈赎金的事。 ";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "当然, 当然。 我会尽我所能。 他们把他关在哪里? 赎金是多少? ";
			link.l1 = "海盗要求" + pchar.GenQuest.Hold_GenQuest.RansomSum + "比索。 我必须把钱送到港口, 然后你的朋友就会被释放。 ";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "给你钱。 幸运的是, 我身上有足够的钱。 ";
			link.l1 = "是的, 确实很幸运。 那么去港口吧, 很快你就会再次见到你的伙伴。 ";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour 生成 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour 生成
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// 生成器"货舱情况 - 赎金"
		
		// 生成器"货舱情况 - 犯罪伙伴"
		case "Hold_GenQuest80":
			dialog.text = "你好, 船长, 抱歉我还没荣幸被介绍。 他们说你在找我。 ";
			link.l1 = "确实, 如果你是" + pchar.GenQuest.Hold_GenQuest.Name + "先生的话。 我是" + GetFullName(pchar) + "船长, 我想和你谈谈。 ";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "那是什么生意, " + GetFullName(pchar) + "船长? ";
			link.l1 = "我听说你拥有一些你不介意放弃的东西。 ";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "你是什么意思? ";
			link.l1 = "别这么固执, 我的好人, 我很清楚你的阴暗过去, 以及一张临时地图, 上面标有" + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC) + "宝藏的位置。 ";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "该死的! 我就知道那个混蛋" + pchar.GenQuest.Hold_GenQuest.CapName + "迟早会把这件事说出去! 我当初向他提议这个交易时在想什么? ";
			link.l1 = "别再抱怨了。 我没有恶意... 把这张地图卖给我, 过你习惯的生活吧。 ";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "要是我能确定就好了... 你打算出多少钱买它? 你肯定知道箱子里有很多金子。 它是由四个人抬的, 愿上帝让他们安息...";
			link.l1 = "但是" + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM) + "可能已经拿走了他的宝藏...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "说得也对... 好吧, 我愿意以" + pchar.GenQuest.Hold_GenQuest.Sum + "比索的价格卖给你。 反正我也不敢打扰死者。 ";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "好的。 成交。 ";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "不, 我的好人, 那张破纸不值这么多钱。 再见...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour 生成
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// 生成器"货舱情况 - 犯罪伙伴"
		
		// 生成器"船只失事"
		case "ShipWreck_1":
			dialog.text = "这怎么可能, 船长? ! 上帝永远不会原谅你这样的罪孽。 ";
			link.l1 = "这由他决定。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("你好, 我是" + pchar.GenQuest.ShipWreck.Name + ", " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")) + "'" + pchar.GenQuest.ShipWreck.ShipTypeName + "的船长, 我的船在离海岸不远的礁石上失事了。 " + 
					"全体船员中只有少数水手幸存下来。 潮水把我们冲到了这个荒凉的海岸。 到现在为止, 我们已经饥渴了" + (5 + hrand(7)) + "周了",
					"你好, 我是" + pchar.GenQuest.ShipWreck.Name + ", " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + "'" + pchar.GenQuest.ShipWreck.ShipTypeName + "的船长。 我们的船在不远处失事了。 " + 
					"我们设法乘失事船只到达了这个海岸, 但这个地方似乎无人居住。 到现在为止, 我们被迫靠贝类和棕榈果生存了" + (5 + hrand(7)) + "周了。 ");
				link.l1 = RandPhraseSimple("你们还剩下多少人? ", "你们有多少人幸存下来? ");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour 生成 引号
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "哦, 船长, 我们的伤亡真的很惨重... 你好, 我是" + pchar.GenQuest.ShipWreck.Name + ", " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + "'" + pchar.GenQuest.ShipWreck.ShipTypeName + "的船长和船主。 或者, 我应该说, 前船长和船主。 " + 
					"这个混蛋" + pchar.GenQuest.ShipWreck.BadName + ", 我在" + XI_ConvertString("Colony" + pchar.GenQuest.ShipWreck.City + "Voc") + "雇佣的人, 煽动我的船员叛变。 最后, 我们被扔到了这个失落的地方。 这是" + (5 + hrand(7)) + "周前发生的事。 ";
				link.l1 = "然后呢? 你的全体船员都加入了叛变者? ";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("全体船员中, 只有" + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + "人幸存下来。 其他人都已死亡;其中几人已经在这里因伤和发烧死亡",
				"只有" + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + "人幸运存活。 其他人都已遇难... 要么在深海中, 要么在这个海岸的沙丘上。 ");
			link.l1 = LinkRandPhrase("是的, 那是个不幸的命运。 但这就是水手的命运 - 任何人都可能落到你们的处境。 ",
				"我明白了... 上帝掌握着每一个生命, 只是他太忙了, 记不住每个人。 ",
				"确实。 谋事在人, 成事在天。 ");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "当然不是! 拒绝加入叛变者的人很多, 但这些恶棍占领了武器库, 幸好我们没有抵抗, 否则我们会被当场杀死。 许多人已经在这里死于发烧和毒虫的毒素, 只有" + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + "人幸存下来。 感谢上帝, 我们的磨难终于结束了。 ";
			link.l1 = RandPhraseSimple("是的, 那肯定是运气不好。 ", "哦, 好吧, 在这些被上帝遗弃的地方, 很多奇怪的事情都可能发生。 ");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "等等, 朋友。 我怎么知道你们不是作为叛变的煽动者被送上岸的? ";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("船长, 我确实希望你的船上有几个空柜子。 我们都有家人, 当我们在这里交谈时, 他们可能正在为我们的损失哀悼。 我们会非常感激你。 ",
				"船长, 我们完全绝望了, 你是我们唯一的希望。 请不要拒绝帮助我们, 把我们从这个被上帝遗弃的地方带走。 ");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "哦... 你想让我把你带到哪里去? ";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("我真的很抱歉, 但甚至没有一个空的吊床, 更不用说客舱了。 水手们睡在甲板上, 他们值班后甚至不能好好休息...",
				"我真的不想让你失望, 但船上超载了, 人们不得不在恶劣天气中睡觉。 如果爆发疾病, 我将失去一半的船员。 "), 
				RandPhraseSimple("我真的很抱歉, 但我的船上绝对没有多余的船员空间。 我不能再搭载任何乘客了。 ",
				"不得不让你失望, 但我的船超载了。 我担心会有流行病。 "));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "你是一个经验丰富的水手, 你应该知道, 有船只失事的人在场是非常不好的兆头。 我的水手们只会把你们都扔到海里。 ";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "你在说什么, " + GetAddress_Form(npchar) + " " + pchar.lastname + "? ! 发发慈悲吧! 我是一个商人, 在加勒比海很有名! 嗯... 我想我曾经是。 现在没有船也没有钱...";
			link.l1 = "是这样吗... 我打赌你们才是叛变的真正煽动者, 现在你们得到了应有的惩罚。 ";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "但是那个" + pchar.GenQuest.ShipWreck.BadName + "是个多么卑鄙的人啊! 你真的打算让他逍遥法外, 接受你的命运吗? ";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "到" + NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)) + "的任何定居点。 ";
					link.l1 = "好吧, 我有足够的空柜子和吊床。 你们上船吧。 ";
					link.l1.go = "ShipWreck_10";
					link.l2 = "嗯... 我们前面有战斗, 我不知道你在哪里更安全, 在我的船上还是在这个舒适的海湾里。 ";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "去敦刻尔克! 我妈妈住在那里...";
					link.l1 = "你疯了吗? 我看你是脑袋被打坏了...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // 把一个疯子带上船 :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "你想去哪里都行, 反正对我们来说没关系。 我们也没有什么可以支付给你的...";
				link.l1 = "好吧, 我有足够的空柜子和吊床。 你们上船吧。 ";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "嗯... 我们前面有战斗, 我不知道你在哪里更安全, 在我的船上还是在这个舒适的海湾里。 ";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "但拒绝你肯定会让我们死亡! 好吧, 我们会尝试冲向船只, 即使这需要我们付出生命! ";
					link.l1 = "什么? 看看你们自己, 你们几乎站不稳...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "你们可以试试...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "但你不能把我们留在这里! 没有你的帮助, 我们很快都会灭亡! ";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "我能为你们做的唯一事情就是给你们留下足够的食物和药品, 并给你们一艘船。 至少你们不会饿死和渴死。 至于航海, 我不需要教你。 ";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "我能为你们做的唯一事情就是给你们留下足够的食物和药品, 并给你们一艘船。 至少你们不会饿死和渴死。 至于航海, 我不需要教你。 ";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "我可以给你们留下足够一个月的药品。 弹药。 朗姆酒和食物。 我会自己回来或者派人来接你们。 ";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // 坏人
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "但拒绝你肯定会让我们死亡! 好吧, 我们会尝试冲向船只, 即使这需要我们付出生命! ";
						link.l1 = "什么? 看看你们自己, 你们几乎站不稳...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "你们可以试试...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "我能为你们做的唯一事情就是给你们留下足够的食物和药品, 并给你们一艘船。 至少你们不会饿死和渴死;至于航海, 我不需要教你。 ";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // 好人
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "但拒绝你肯定会让我们死亡! 好吧, 我们会尝试冲向船只, 即使这需要我们付出生命! ";
							link.l1 = "什么? 看看你们自己, 你们几乎站不稳...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "你们可以试试...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "你怎么能这样对我们? ! .. 你不仅无视了海洋法典, 还玷污了你的荣誉! ";
							link.l1 = "当然, 你不是那个谈论我荣誉的人, 小矮子! ";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "我能为你们做的唯一事情就是给你们留下足够的食物和药品, 并给你们一艘船。 至少你们不会饿死和渴死。 至于航海, 我不需要教你。 ";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "你说得对, 我们没有机会。 好吧, 愿上帝审判你, 愿每个人都得到应有的报应。 ";
			link.l1 = "好吧, 我可以处理...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "好吧... 你让我们别无选择... 我们会祈祷那些风暴和口渴不会在我们到达有人居住的地方之前夺走我们的生命...";
			link.l1 = "再见。 愿上帝保佑你们...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("你花费了" + pchar.GenQuest.ShipWreck.FoodQty + "单位的食物。 ");
			Log_SetStringToLog("你花费了" + pchar.GenQuest.ShipWreck.MedicamentQty + "单位的药品。 ");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "显然, 我们别无选择... 但我恳求你, 船长, 请尽快回来或派一艘探险船来接我们。 ";
			link.l1 = "我会想办法的。 等着吧。 ";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("你花费了" + pchar.GenQuest.ShipWreck.FoodQty + "单位的食物。 ");
			Log_SetStringToLog("你花费了" + pchar.GenQuest.ShipWreck.MedicamentQty + "单位的药品。 ");		
			Log_SetStringToLog("你花费了" + pchar.GenQuest.ShipWreck.AmunitionQty + "单位的武器。 ");
			Log_SetStringToLog("你花费了" + pchar.GenQuest.ShipWreck.RumQty + "单位的朗姆酒");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("船长, 请记住你是我们唯一的希望...", "你为什么要逗留? 在这里每一分钟对我们来说都是难以忍受的...");
			link.l1 = "我会尽我所能。 再见...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("再见, 船长... 我们必须为旅程做好准备。 ", "再见... 为拯救我们的灵魂点上蜡烛...");
			link.l1 = "再见。 愿上帝保佑你们...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour 生成
			dialog.text = "你怎么能这样对我们? ! 你不仅无视了海洋法典, 还玷污了你的荣誉! ";
			link.l1 = "当然, 你不是那个谈论我荣誉的人, 小矮子! ";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "谢谢你, 船长! 装载应该不会花太多时间。 上帝啊, 我们祈祷这一刻的到来! ";
			link.l1 = "太好了。 我希望你们的磨难很快就会结束。 ";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
				// --> belamour 按人数结束
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				// < —belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
				// --> belamour 按人数结束
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				// < —belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour 生成
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: 需要分开, 否则会得到遭遇海难的双桅帆船
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "失事");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "失事");
				}
				// < —belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "谢谢你, 船长! 装载应该不会花太多时间。 上帝啊, 我们祈祷这一刻的到来! ";
			link.l1 = "太好了。 我希望你们的磨难很快就会结束。 ";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour 按人数结束
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				// < —belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
				// --> belamour 按人数结束
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名水手");
				}
				// < —belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour 生成
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: 需要分开, 否则会得到遭遇海难的双桅帆船 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "失事");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "失事");
				}
				// < —belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "来吧! 真的吗, 船长? ! 我们害怕死亡吗? ! 我们已经骗过它一次了, 我们可以再做一次。 我们只是不想这样失去生命。 独自在这里腐烂\n我们很乐意加入你的船员, 在你的旗帜下勇敢战斗。 只是不要把我们留在这里...";
			link.l1 = "我看你们为了离开这里什么都愿意做。 但看看你们自己, 你们能成为什么样的水手? ";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "这是个好主意。 我想我可以雇佣你们。 ";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "不, 不, 我没有开玩笑! 请带我离开这个加勒比屠宰场... 离开这个地狱! 你知道, 我是个有钱人... 非常有钱的人。 甚至连教皇本人在他的一生中都没见过那么多金子。 我会用金子 shower 你...";
			link.l1 = "哦, 我的天... 好吧, 上船吧...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour 生成
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour 生成
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: 需要分开, 否则会得到遭遇海难的双桅帆船
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "失事");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "失事");
			}
			// < —belamour
		break;							

		case "ShipWreck_13": // 把他们当乘客
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("你为什么要逗留, 船长? 下令起锚。 ", "对不起, 船长, 但我们必须准备起航了。 ", "我们真幸运, 你决定来这里! ");
			link.l1 = "快点。 船不会等人的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "船长, 我们没什么可失去的了。 死亡已经紧随我们的脚步... 我们宁愿在公平的战斗中死去, 也不愿被臭 coyotes 吞噬...";
			link.l1 = "哦, 这是一个挑战, 那么? ! 好吧, 让我们像男" + GetSexPhrase("", "人") + "一样解决我们的争端! ";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "我发誓, 船长, 你不会后悔的。 我们将成为整个群岛最好的水手。 ";
			link.l1 = "太好了! 上船吧...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаeм в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen 按人数
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("你的队伍增加了" + pchar.GenQuest.ShipWreck.Qty + "人" + sText + "。 ");
			// < —belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // 移除离开地点的中断			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("我发誓, 船长, 您不会后悔的。 ", "您做了正确的选择, 船长。 ", "船长, 请放心, 您和我们一样幸运! ");
			link.l1 = RandPhraseSimple("希望如此。 ", "快点, 船不会等人。 ");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "船长, 您为什么要用这种不信任来冒犯诚实的人呢? 看看他们的脸, 您真的认为他们会是叛变者吗? ";
			link.l1 = "好吧, 但我现在该怎么处理你们? ";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "我能做什么呢? 至少现在我还活着... 感谢上帝我逃出来了! 但如果您帮我夺回我的船, 为我的屈辱报仇, 我愿意把这个恶棍从货舱里抢走和藏匿的任何东西都给您。 ";
			link.l1 = "好吧, 成交。 ";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // 定时器 伐木工 寻找船只的定时器																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour 按人数结束
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名他的水手");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + "名他的水手");
			}
			// < —belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "我们没有资格发号施令。 由您决定, 要么带我们去任何定居点, 要么让我们加入您的队伍。 ";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "好吧, 我让你们加入我的队伍。 但别耍花样! 我的船上纪律严明! ";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "我不会带你们去任何地方。 我的队伍里已经有足够多的暴徒了。 ";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "好吧, 上船, 我带你们去某个地方。 ";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "哦, 好吧... 您没给我们选择的余地... 我们会祈祷天意怜悯我们, 让我们离开这个危险的地方。 愿上帝保佑, 我们或许还能到达有人居住的陆地... ";
			link.l1 = "再见。 愿主保佑你们... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "非常感谢您, " + GetFullName(pchar) + "船长! 您为我们做了这么多, 任何感激之情都不足以回报您。 虽然我们所有的财物不值一文, 但请允许我把这个护身符送给您。 这对经常参加海战的船长会非常有用。 ";
				link.l1 = "感谢您的礼物! 这个小饰品确实非常有用! 再见, " + pchar.GenQuest.ShipWreck.Name + "船长, 祝您旅途顺利。 ";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "船长, 非常感谢您。 您为我们做了很多, 任何奖励都比不上我们的感激之情。 请接受这个小小的礼物, 作为我们感激的象征。 ";
				link.l1 = "真的, 您不必费心... 你们比我更需要钱。 不过, 您真是太好了。 谢谢, 再见。 ";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "船长, 要知道从现在起, 有人会为您赴汤蹈火。 可惜我没有什么可以感谢您的。 不过... 请接受这个小饰品, 我在那个不幸的海湾找到的。 希望它能给您带来好运。 ";
			link.l1 = "任何人在我这个位置都会这么做的。 再见。 ";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: 仅仅 pchar.location 什么也不会给
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("船长, 已经是敦刻尔克了吗? ", "船长, 我们真的在敦刻尔克吗? "), RandPhraseSimple("船长, 这是欧洲吗? ", "我们这么快就航行到欧洲了吗? "));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "啊哈... ";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("还没... ", "什么敦刻尔克? 什么欧洲? 看看周围! ", "哦, 我的上帝! ");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("但是, 船长, 您答应过的! ", "船长, 您怎么能食言呢? ", "我们什么时候到欧洲? ");
			if(rand(100) < 70)
			{
				link.l1 = "好吧。 先生, 召集您的人, 带上您的财物, 想去哪里就去哪里。 ";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("您确定我们真的需要去敦刻尔克吗? ", "您知道, 我的船不适合跨洋航行。 ", "船长, 加勒比海有什么不好? "), 
					LinkRandPhrase("但我有不同的计划... ", "您为什么一开始就想去欧洲... ", "想想那些迷人的混血女人吧! 在欧洲您永远遇不到她们... "));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "但是怎么会? ! 您怎么敢? ! 这是什么背叛? ! 我会教您如何信守诺言! ";
			link.l1 = "好吧, 这是您自找的... ";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("不! 我需要去敦刻尔克! ", "您与其教我地理, 不如履行您的义务! "), 
				RandPhraseSimple("我不想听任何借口! 您答应过带我去欧洲! ", "不, 船长, 那不行。 我们要航行到欧洲。 "), "我不想在这个鬼地方过一辈子悲惨的生活! ");
			link.l1 = "哦, 我不知道这会如何结束... ";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta 修复了船长任务的阻塞
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "看! 这才是个正派的人! 欧洲! 该死的老欧洲! 是的-是的-是的! \n哦, 对! 您已经履行了您的部分约定, 我也会履行我的。 给, 拿着这半张地图。 另一半在我伙伴那里。 安息吧, 或者在水里安息? 不管怎样。 是他说服我参加这次冒险的。 ";
			link.l1 = "等等, 这么说您不是水手? 您的伙伴是船长? ";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "哦, 我的天! ... 当然不是! 嗯, 是的, 我不是水手。 当他决定驶离海岸更远时, 他被一个巨浪卷下了船。 然后我接管了指挥权, 命令驶入海湾... 我们在穿过礁石时做得很好, 直到一场致命的事故决定了一切。 船撞到了一块岩石碎片, 沉没了... ";
			link.l1 = "这真是无能的表现... ";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "听着, 这真的是敦刻尔克吗? 想想看, 才六个月, 整个地方都变了\n给, 拿着这张地图, 或者更确切地说, 它的一部分。 宝藏在一个山洞里! 不知道是哪个岛, 但您是个有经验的水手, 总有一天您会找到确切的位置... 我保证那里有海盗名叫啊... 的无数财富。 ";
			link.l1 = "谢谢你, 我的好人。 即使根本没有宝藏, 我也不会太难过。 再见, 我真的希望我们再也不要见面... ";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("据说最近岛上出现了一个疯子。 他告诉每个人他丢了证件, 现在正试图申请一艘去敦刻尔克的船的船长职位。 ",
				"据说最近岛上出现了一个疯子。 他在当地商店偷了一把铁锹, 现在正在镇门外挖坑... "),
				RandPhraseSimple("想象一下, 最近有个穿着破旧衣服的欧洲访客试图求见总督! 他声称需要尽快见到敦刻尔克的总督。 ",
				"最近市政厅发生了一起丑闻。 抓住了一个流浪汉, 他声称自己认识敦刻尔克的总督。 "),
				"最近有个疯子在找您。 他声称您欠他钱... "), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("船长, 您没有忘记我们, 真是太好了! 我们都在为您祈祷! ", "船长, 我们的救赎近了吗? 我们是多么祈祷它的到来! 有些人已经开始绝望了... ");
			link.l1 = "问候您, " + pchar.GenQuest.ShipWreck.Name + "! 我怎么能把我的同事们留在这种状态呢? 去哪里? ";
			link.l1.go = "ShipWreck_45";
			link.l2 = "问候您, " + pchar.GenQuest.ShipWreck.Name + "! 恐怕我有坏消息要告诉您。 计划有变, 我不能让你们上船了。 ";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "我们不在乎去哪里, 只要离这个被诅咒的地方足够远... 您能允许我们开始装载吗? ";
			link.l1 = "是的, 去吧。 你们的考验很快就会结束。 ";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen 移除30天的定时器	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "谢谢您, 船长。 我们已经开始绝望了, 但您真的让我们重获新生。 ";
			link.l1 = "没什么... 再见。 ";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "你到底想从我这里得到什么? ";
			link.l1 = "我"+ GetSexPhrase("","") +"是来给您捎个名叫" + pchar.GenQuest.ShipWreck.Name + "的人的问候。 您认识他吗? "; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "真遗憾我之前没勒死那个恶棍。 好吧, 那么, 我想是时候为我的仁慈付出代价了... ";
			link.l1 = "确实... 时间刚刚好... ";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // 重要方法
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "干得好, 船长! 那么一切如我们约定的那样? 我们得到船, 您得到货物? ";
			link.l1 = "当然。 把船拿走, 好好利用它。 ";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "我问候您, " + GetFullName(pchar) + "船长。 ";
			link.l1 = "那么, 您觉得您的船怎么样? ";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "嘿, 它像我一样吱吱作响。 我想我们俩在公海上航行的时间都不多了... ";
			link.l1 = "那么, 祝你好运... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// 生成器 "Shipwrecked"
		
		// 生成器 "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "船长, 请帮助我们弄一艘船或一艘长艇。 一艘格子呢船, 不管什么, 真的没关系。 我们处于必须逃离这个荒凉地方的境地, 但我们不能出现在定居点。 ";
					link.l1 = "那到底是什么样的境地? ";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "船长, 您能借给我们几百比索吗? 我们不会要求的, 但我们真的急需。 ";
					link.l1 = "您说急需? 我敢打赌您只是朗姆酒喝完了, 那肯定是急需。 ";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "船长, 您能好心把我们这群谦卑的人送到" + XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen") + "的灯塔吗? ";
					link.l1 = "看着你们, 我不会说你们太谦卑。 ";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("我星期五不给施舍。 ", "我没时间处理这种废话。 ", "我不帮助陌生人。 ");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "我们是逃犯... 来自" + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + "。 很快前主人就会注意到... 然后我们肯定死定了。 ";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "那么你们知道如何管理帆吗? ";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "你们打算用什么来支付? ";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "现在不是我们考虑朗姆酒的时候。 我们逃出来已经一个星期了, 现在躲在丛林里挨饿。 ";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "好吧, 假设我可以给你们钱... 然后呢? 你们打算一直躲着, 直到最终被巡逻队发现? ";
				link.l1.go = "Convict_12_1";		
				link.l2 = "好吧, 你们需要多少? ";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "我跟你们这种人没什么好谈的, 直接上断头台, 就这样! ";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "那我们还能做什么? 我们很乐意找份水手的工作, 但考虑到我们是逃犯, 谁会雇佣我们呢? ";
				link.l1 = "如果你们知道如何管理帆, 并且不会表现出懦弱, 我就雇佣你们。 ";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "我们已经和当地水手达成协议了。 要离开这里, 我们只差三千。 ";
				link.l1 = "好吧, 这是你们的三千, 如果这真的能帮到你们的话。 ";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "嗯, 我不知道... 这些是你们自己的问题, 我不会帮你们解决。 ";
			link.l2.go = "Convict_12_1_End"; // 离开地点并关闭任务
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "请, 船长, 雇佣我们吧, 您肯定不会后悔的! 我们曾和" + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + "在亚得里亚海当海盗, 直到他最终被绞死, 我们" + pchar.GenQuest.Convict.ConvictQty + "个人被流放到这个地方。 ";
			link.l1 = "好吧。 附近有个地方, 叫做" + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + "。 午夜左右我会在那里接你们。 我希望你们不会迷路。 ";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "当然, 这对我们帮助很大! 如果风向有利, 渔民也不辜负我们, 我们今天就起航。 谢谢您, 船长, 愿上帝帮助您... ";
				link.l1 = "也祝你好运。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "现在这真是幸运! 我们甚至没希望这么快拿到钱。 船长, 请允许我把我们从以前老板那里拿的一个小饰品送给您。 也许它也会给您带来好运。 ";
				link.l1 = "谢谢, 这确实是个不错的东西。 祝你好运。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "现在, 有一个不害怕花钱的慷慨之人, 因为他知道如何赚钱! \n昨晚我们看到当地走私者在装载" + MerPrm.QuestGoodsIdx + "。 天很黑, 但我们设法辨认出其中一艘船侧面的名字,'" + MerPrm.ShipName + "'... 那艘船挂着" + MerPrm.nation + "的旗帜航行。 也许您会觉得这个信息有用, 嘿嘿。 ";			
				link.l1 = "嗯... 好吧, 也许我会。 再见, 追踪者们。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "哦, 我的天, 我们没有资格提出要求。 无论您能拿出什么, 我们都感激不尽。 ";
			link.l1 = "300比索。 ";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000比索。 ";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000比索。 ";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "谢谢您, 船长, 愿上帝保佑您... ";
			link.l1 = "也祝你好运。 ";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "现在这真是幸运! 我们甚至没希望这么快拿到钱。 船长, 请允许我把我们从以前老板那里拿的一个小饰品送给您。 也许它也会给您带来好运。 ";
				link.l1 = "谢谢, 这确实是个不错的东西。 祝你好运。 ";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "谢谢您, 船长, 愿上帝保佑您... ";
				link.l1 = "也祝你好运。 ";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "现在这真是幸运! 我们甚至没希望这么快拿到钱。 船长, 请允许我把我们从以前老板那里拿的一个小饰品送给您。 也许它也会给您带来好运。 ";
				link.l1 = "谢谢, 这确实是个不错的东西。 祝你好运。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "现在, 有一个不害怕花钱的慷慨之人, 因为他知道如何赚钱! \n昨晚我们看到当地走私者在装载" + MerPrm.QuestGoodsIdx + "。 天很黑, 但我们设法辨认出其中一艘船侧面的名字'" + MerPrm.ShipName + "'... 那艘船挂着" + MerPrm.nation + "的旗帜航行。 也许您会觉得这个信息有用, 嘿嘿。 ";
				link.l1 = "嗯... 好吧, 也许我会。 再见, 追踪者们。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "不要咒我们, 船长! 我们有一个像样的小饰品, 请接受它作为赎金, 让我们走吧... ";
				link.l1 = "那就交出来, 趁你们还能走的时候消失。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "现在我们别无选择, 一个人反正不会死两次。 最后一战, 兄弟们! ";
				link.l1 = "这才像话! ";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "嗯, 我们当然不是圣人, 但我们也不想无缘无故地争吵... 我们是逃犯, 我们需要尽快离开这里。 ";
			link.l1 = "你有什么可以用来支付通行费的吗?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "哦, 我明白了... 不, 我不会因为你们而玷污我的声誉。 再见。 ";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "当然! 我们很习惯登船之类的事情。 将近两年, 我们和已故的" + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + "一直在恐吓当地商人, 但唉! 他被绞死了, 我们" + pchar.GenQuest.Convict.ConvictQty + "个人被判服苦役。 ";
			link.l1 = "加入我的队伍怎么样? 我很慷慨"+ GetSexPhrase("","") +", 但我不能保证你们过平静的生活。 ";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "是的, 我们用" + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Gen")) + "抢了一些东西, 所以我们可以付双倍。 所以我相信价格已经商定好了。 而且你们敢带卫兵来。 我们不原谅背叛... "; // belamour gen
			link.l1 = "好吧, 在" + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen") + "海滩等我。 接近午夜会有一艘船给你们... 我不想看到任何诡计! "; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "不, 我的朋友们。 如果我给你们船, 你们在背后捅我一刀怎么办? 不, 我不会在这件事上帮助你们。 ";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "非常乐意, "+ GetSexPhrase("先生","小姐") +"船长。 我们对此很熟悉, 而且我们肯定不会以这样的推荐被海军录取, 嘿嘿。 ";
			link.l1 = "好吧。 附近有个地方, 叫做" + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + "。 午夜过后我会在那里接你们。 我希望你们不会迷路。 ";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "但是, "+ GetSexPhrase("先生","小姐") +"船长, 我们承担的风险更大? 如果您决定把我们交给指挥官怎么办? ";
			link.l1 = "那是真的... 好吧, 如果我天亮前没到, 那交易就取消。 ";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) // 最大声誉 90
			{
				dialog.text = "哦, 船长, 我们一直指望您... ";
				link.l1 = "没问题。 如果你们有钱, 就会找到通行的办法。 再见。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "您是个聪明人, 船长, 我看得出来。 我相信您会直接跑去找指挥官, 不是吗? 您认为您能逃脱吗? ";
				link.l1 = "而且我看得出来, 你们打算阻止我? ! 那你们会得到应有的惩罚! ";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen 数量用文字
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "有一些。 我们翻了我们老板的箱子, 但后来为此发生了争吵, 我们不得不打了一架才冲出来。 只有" + PChar.GenQuest.Convict.ConvictQty + "个人幸存下来。 ";
			link.l1 = "考虑到情况, 我给你们的通行费不会低于每人" + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "比索的价格。 ";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "我看你们不是懦夫。 你们愿意加入我的队伍吗? ";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "我们有选择吗? 好吧, " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "... ";
			link.l1 = "那么去" + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat") + "。 午夜后我会派一艘船去接你们。 "; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "为什么不呢? 我们知道那些事情, 在被困在这里之前, 我们曾和" + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + "在" + RandPhraseSimple("直布罗陀","英吉利海峡") + "当海盗。 ";
			link.l1 = "好吧。 附近有个地方, 叫做" + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + "。 午夜左右我会在那里接你们。 我希望你们不会迷路。 ";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen 数量用文字
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("唉, 船长, 您也曾贫穷过, 口袋空空。 现在您却鄙视像我们这样的普通人。 ", "船长, 这样对待普通人是不对的。 我们都在同一个上帝之下。 "), 
											RandPhraseSimple("嘿, 现在的人真的太自私了。 您活得好像还有两个世纪的时间。 ", "哦, 我看您刚从欧洲来, 还没闻到我们热带垃圾场的恶臭。 "));
			link.l1 = LinkRandPhrase("您想让我感到羞耻吗? 我会把您的舌头缩短几英寸! ", "您在威胁我吗? 现在等着瞧! ", "您是哲学家还是什么? 我会打醒您! ");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("那么, 船长? 你给我们弄来船了吗? ", "问候你, 船长。 那么, 我们的交易怎么样了? ", "你好, 船长。 我们已经开始担心了。 我猜一切顺利吧? ");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "是的, 这是你们的破船。 别忘了付款。 我花了" + pchar.GenQuest.Convict.ShipPrice + "枚硬币买的, 所以你们欠我" + sti(pchar.GenQuest.Convict.ShipPrice) * 2 + ", 就像我们约定的那样。 ";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "不, 我改变主意了。 自己另找帮手吧。 再见...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "当然! 他们剥夺了我们的自由, 但没有剥夺我们的良知! 请接受你的钱以及我们无尽的感激。 你真的帮了我们大忙。 你介意我们用银锭支付你吗? ";
					link.l1 = "当然不介意。 祝你们旅途顺利。 祈祷我不会在公海上遇到你们, 我会很快解决你们的。 ";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "船长, 你知道, 我们认为金钱在生活中真的没那么重要。 坦率地说, 目前我们比你更需要它。 但我们有一样从以前老板那里偷来的东西。 也许它会比金子让你更感兴趣。 想看看吗? ...";
					link.l1 = "是的, 你说得对。 这确实是个了不起的东西。 好吧, 成交, 谢谢, 再见。 ";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "船长, 你为什么需要那么多钱? 反正你很富有, 如果我们得不到这艘船就死定了。 所以...我们打算直接从你那里夺走它。 不要介意。 ";
					link.l1 = "那是你最后的错误。 没有船你还能游走, 但现在你要么漂浮要么沉没。 ";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("那么, 船长? 我们可以开始装货了吗? ", "终于! 我们已经开始担心了, 还以为你改变主意了。 ");
			link.l1 = "抱歉, 我改变计划了。 你们现在得另找船长了。 ";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "上船装货, 我没多少时间。 ";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "上船装货, 我没多少时间。 ";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "该死的你! 你肯定已经派巡逻队追我们了? ! 你不会得逞的! ";
				link.l1 = "你在说什么? ! 你想找死吗? ! ";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = GetSexPhrase("船长, 你是个守信用的人吗","船长, 你是个守信用的人吗") + "? 还是你只是个该死的空谈家...";
				link.l1 = "你最好注意你的言辞...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("哦, 谢谢你, " + GetSexPhrase("善良的先生","美丽的小姐") + "。 ", "谢谢你, 船长, 你真的把我从绞索下救了出来。 ", "非常感谢这次美好的航行。 ");
			link.l1 = LinkRandPhrase("那很好, 但我在等钱。 ", "该付钱了, 你知道的。 ", "当场付现, 正如我们约定的。 ");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "当然, 还有什么问题! 这是你用金锭装的钱, 请接受我们最诚挚的感谢。 ";
					link.l1 = "也祝你好运。 再见。 ";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "船长, 你知道, 我们认为金钱在生活中真的没那么重要。 坦率地说, 目前我们比你更需要它。 但我们有一样从以前老板那里偷来的东西。 也许它会比金子让你更感兴趣。 想看看吗? ...";
					link.l1 = "是的, 你说得对。 这确实是个了不起的东西。 好吧, 成交, 谢谢, 再见。 ";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "你为什么需要那么多钱? 反正你很富有。 你帮助了我们, 我们会在另一个场合帮助你。 ";
					link.l1 = "不会有那样的场合了。 祈祷吧, 恶棍们, 我不宽恕债务。 ";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// < —生成器 "State convicts"
		
		// 生成器 "A reason to hurry" -->
		// 在岸边与OZG相遇
		case "ReasonToFast_Hunter1":
			dialog.text = "我是被"  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "本人派到这里来的...";
			link.l1 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "已经等你回复几个小时了。 你走后他立刻派我来了。 ";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "我已经跟着你的踪迹有一段时间了, 但你太快了。 ";
			link.l1 = "那又怎样? ";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "最好告诉我总督付给他的下属多少钱? ";
			link.l1 = "该死的! ";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "我没喝酒! 我在找水手长...";
			link.l1 = "现在走吧...我会告诉"  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ", 说你在丛林里迷路了。 ";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //OZG不计算
			pchar.GenQuest.ReputationNotChange = 1; //不改变声誉
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// 与海盗船船长战斗
		case "ReasonToFast_FightCap": 
			dialog.text = "你是个聪明人。 祈祷上帝你的诡计不会被" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "知道。 ";
			link.l1 = "如果你不告诉他...他就不会知道, 不是吗? ";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "为什么不? 当然, 我会的, 而且很乐意! ";
			link.l1 = "反正他会因为那个愚蠢行为绞死你。 所以我们别浪费时间了, 我会帮你逃脱绞刑架。 ";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "嗯...你打算怎么做? ";
			link.l1 = "我会亲自杀了你...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// 在官邸与男仆相遇
		case "ReasonToFast_Lakey":
			dialog.text = "你有什么事吗, " + GetSexPhrase("先生","小姐") + "? ";
			link.l1 = "不, 不, 我是应总督迷人的妻子邀请来的, 参观这座真正豪华的住宅。 ";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "我有你认识的人带来的口信。 ";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "是的。 我想将你绳之以法! ";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "哦, 是的, 我真幸运能在这么漂亮的房子里服务。 ";
			link.l1 = "难怪...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "别忘了看看我们的花园! ";
			link.l1 = "谢谢你, 好心人! ";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "嗯... " + pchar.questTemp.ReasonToFast.password + "? ";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "你不会得逞的, 叛徒! ";
			link.l1 = "站住, 恶棍! ";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "快点! 带上所有值钱的东西跑! ";
				link.l1 = "我想你也应该跑。 ";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "嗯, 对不起, 我得走了。 ";
				link.l1 = "站住, 恶棍! ";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //移除计时器
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是" + GetSexPhrase("个小偷, 我看到了! 卫兵, 抓住他","个小偷, 我看到了! 卫兵, 抓住她") + "! ", "真不敢相信! 我刚转过身, 你就钻进我的箱子里! 抓小偷! ", "卫兵! 抢劫! 抓小偷! ");
			link.l1 = "啊啊啊, 魔鬼! ";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// 生成器 "A reason to hurry" <--
		
		// 被俘船只船长的情况
		// 船上爆炸
		case "ShipSituation11": // 海盗或DU
			dialog.text = RandPhraseSimple("嗨, " + GetSexPhrase("伙计","姑娘") + "! 我给你准备了个惊喜, 我点燃了通往火药舱的导火索。 它会炸到天国去! ", "你为什么站在那里? 火药舱着火了! 它会爆炸的, 烟火在欧洲都能看到! ");
			link.l1 = RandPhraseSimple("你这个恶棍, 你骗不了我! 战斗吧, 懦夫! ", "我看到老鼠弃船了, 你是第一个? ");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("如果你珍惜生命, 你也应该跑...哦, 好吧, 我没时间了, 船在等我。 祝你钓鱼愉快! ", "我没时间扮演英雄了, 船上的兄弟们在等我。 祝你钓鱼愉快, 胜利者! ");
			link.l1 = RandPhraseSimple("该死的! 切断护舷! 离开! ", "哦, 上帝, 我们怎么会陷入这样的困境! 打开海水入口! 离开! ");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // 军用船只 (非旗舰) 
			dialog.text = "那又怎样? ! 你以为你赢了战斗? ! 没门。 我已经放火烧了火药舱, 你不会活着离开这艘船的。 ";
			link.l1 = RandPhraseSimple("你这个恶棍, 你骗不了我! 战斗吧, 懦夫! ", "我看到老鼠弃船了, 你是第一个? ");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("我受誓言约束, 但这并不意味着我必须白白送死。 抱歉没在船上给你留位置, 水手们不会理解的。 ", "船只在登船时相互绑定, 所以你的命运已定。 对不起, 但我的船在等...");
			link.l1 = RandPhraseSimple("该死的! 切断护舷! 离开! ", "哦, 上帝, 我们怎么会陷入这样的困境! 打开海水入口! 离开! ");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // OZG
			dialog.text = RandPhraseSimple("你胜利了! 欢迎来到地狱! 我已经放火烧了火药舱。 ", "给你, 我的好人! 你完了, 我已经放火烧了火药舱。 ");
			link.l1 = RandPhraseSimple("你这个恶棍, 你骗不了我! 战斗吧, 懦夫! ", "我看到老鼠弃船了, 你是第一个? ");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("我跟踪你很久了。 可惜我不得不牺牲我的船, 但你的脑袋反正值两艘新船。 祝你钓鱼愉快! ", "看看你怎么走? 像放烟花一样, 像个印度王" + GetSexPhrase("子","妃") + "。 但我不会输, 你的脑袋比我的船值钱多了。 现在再见, 我的船不会等太久...");
			link.l1 = RandPhraseSimple("该死的! 切断护舷! 离开! ", "哦, 上帝, 我们怎么会陷入这样的困境! 打开海水入口! 离开! ");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// 流行病
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("等等, 船长! 说几句话。 ", "等等, 船长! 我想这对你来说可能有趣。 ");
			link.l1 = LinkRandPhrase("为什么在战斗中说话? ! ", "我该和一个死人说什么? ", "怎么了? 你想立我的遗嘱? ");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "船上爆发了疾病。 我在旅途中失去了四分之一的船员。 你们都死定了...";
			link.l1 = RandPhraseSimple("你这个卑鄙的混蛋! 你为什么不展示船上有灾难的信号? ! ", "你忘了海上规则吗? 你应该在桅杆上展示船上有灾难的信号! ");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "反正我们都要死了。 这就是为什么我们没有放弃, 我们想带你们和你们的魔鬼一起去另一个世界! 现在我很满意。 你可以完成你肮脏的行为了。 ";
			link.l1 = RandPhraseSimple("我会让你为此付出代价! ..", "我喜欢你先死的想法。 我会看着的。 ");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("我不会用你肮脏的血玷污我的刀刃, 你可以活着, 尽管...为了什么? 我要带我的船员离开那艘腐烂的旧船。 ", "你应该为此被送上绞刑架, 但现在没必要了。 我要带我的人走...你可以活着, 尽管你的时间应该很短...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // 敌方船长因体内铁和铅过量而濒临死亡
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // 敌方船长存活
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// 被俘船只船长的情况
		
		// 生成器 "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "你好, 船长, 有人告诉我你在找我。 ";
			link.l1 = "我是 - 如果你是" + pchar.GenQuest.EncGirl.sLoverId + "的话。 ";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "我是。 有什么重要的事吗? ";
			link.l1 = "我不知道这对你是否重要, 但我带来了" + pchar.GenQuest.EncGirl.name +"。 她离家出走了, 现在在酒馆不远处等你。 ";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "哦, 我的...我就知道会这样结束...她为什么跑掉? 她告诉你了吗? ";
			link.l1 = "她父亲想把她嫁给放贷人的儿子。 ";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "哦, 不, 我们不能让这种事发生! 船长, 你知道, 我现在处境很尴尬...我想请你带我们去" + XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc") + "一个叫" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + "的城镇, 但现在我没有钱, 还没找到工作。 我在" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + "有富裕的家庭和有前途的职业...\n我向你保证, 我父母会很高兴看到我带着年轻的未婚妻, 他们会好好奖励你。 那么, 你愿意吗? ";
			link.l1 = "...现在听着, 我有完全不同的计划。 我可以给你一个建议, 找份水手的工作, 用你的工资为你的新娘租个船舱。 人们就是这样去欧洲的, 而你们那个定居点就在不远处。 ";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "哦, 年轻人...你知道你在让我做什么吗? 未经父母允许就把一个女孩从她父母身边带走? ...什么样的男人会拒绝这样的事情, 当然我愿意! ";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("你听说了吗, " + pchar.GenQuest.EncGirl.name + "和她的爱人跑了。 她决定不把自己的生命绑在一个病人身上。 这肯定是她父母的错, 他们不应该被她未婚夫的钱诱惑, 试图把这样一个美人嫁给一个怪物。 ",  
				"你听说了吗? " + pchar.GenQuest.EncGirl.name + "欺骗了她的父亲和她的准未婚夫。 据说一位高贵的船长帮助她和她的爱人到了另一个岛, 她爱人的父母住在那里...想象一下, 还有人没有忘记激情的滋味! "), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "谢谢你, 船长。 我们余生都会记住你的帮助。 ";
			link.l1 = "没什么。 我希望你们一切顺利。 ";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "我答应过要把你介绍给我父母。 如果你有空, 请来到" + sTemp + ", 我父亲在那里工作, 我会告诉他你为我们做了什么。 我相信他会很高兴见到你。 ";
			link.l1 = "好的, 我一有时间就来。 祝你们幸福, 互相照顾, 你们俩...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // 未婚夫的爸爸为儿子高兴 :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // 未婚夫的爸爸因儿子带女人回家而生气 :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// 生成器 "A damsel in the jungle"
		
		// 生成器 "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("等等! 等等, 船长! 求你了。 ", "船长, 求你了, 等等, 我求你...");
			link.l1 = LinkRandPhrase("什么? 喘不过气了? ", "举起你的剑, 懦夫! ", "怎么了? 你忘了立遗嘱了? ");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "等等...我受伤了, 虚弱得无法继续战斗...我不是请求怜悯, 但我有未完成的事。 请答应我你会完成一个将死之人的最后遗愿。 ";
			link.l1 = RandPhraseSimple("别像个懦夫, 船长, 像个男人一样接受死亡! ", "船长, 多么多愁善感? 周围正在战斗, 让我们结束我们开始的事情。 ");
			link.l1.go = "CaptainComission_21";
			link.l2 = "现在说, 快点。 ";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "告诉" + pchar.GenQuest.CaptainComission.Name + "来自" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City) + "定居点的人, 我未能完成他的请求...在我有时间之前...愿他原谅我...";
				link.l1 = RandPhraseSimple("就这样? ! 好吧, 我可以做到。 嘿, 朋友...", "好吧, 如果我有时间我会告诉他。 嘿, 朋友...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "我不这么认为。 我没有时间做这种 nonsense。 让我们结束我们开始的事情。 ";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "请告诉" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + "巡逻队船长'" + pchar.GenQuest.CaptainComission.ShipTypeName + "'" + pchar.GenQuest.CaptainComission.Name + ", 他不应该在" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + "露面... " +
							"当局知道他死亡的真实情况 " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")) + "'" + pchar.GenQuest.CaptainComission.VictimShipName + "...时间不多了, 他要被捕了...从" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + "航行到" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc") + ", 航程将近十五天...啊...应该快点..."; // belamour gen
				link.l1 = RandPhraseSimple("我不保证什么, 但有机会我会试试。 嘿, 朋友...", "好吧, 如果我有时间我会告诉他。 嘿, 朋友...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "如此残忍! 我希望你会为此付出代价。 ";
			link.l1 = "还有更多...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("我在听你说, " + GetAddress_Form(pchar) + "。 ", "你想要什么? ", "我能帮你什么? ");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // 护林员 - 额外检查是否有任务。 用于过渡.
			{	
			link.l1 = "你是" + pchar.GenQuest.CaptainComission.Name + "吗? 我和你有生意。 " + pchar.GenQuest.CaptainComission.CapName + "船长让我给你传递一个重要信息。 ";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "不, 没什么...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // 护林员 - 过渡以免重复调用时引发错误
		break;
		
		case "CaptainComission_4":
			dialog.text = "是吗? 好吧。 那么" + pchar.GenQuest.CaptainComission.CapName + "船长想让我知道什么? ";
			link.l1 = "他让我告诉你, 他无法完成你的请求。 ";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "你在说什么? ! 我认识他很久了, 他是个非常诚实的人。 他根本不可能告诉你那个! ";
			link.l1 = "可以说, 这是由于他无法控制的原因。 换句话说 - 那是他的最后愿望。 ";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "啊, 这完全不合适! 浪费了这么多时间\n"
					+ "船长, 在这种情况下, 我不得不请你帮助我。 " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen") + "的海盗俘虏了我的亲戚" + pchar.GenQuest.CaptainComission.SlaveName + ", 并要求赎金。 你能承担这个任务吗? 报酬应该相当丰厚。 ";
				link.l1 = "不幸的是, 我有其他计划。 ";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "如果你详细解释, 我会尽力帮助你。 ";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "啊, 这完全不合适! 浪费了这么多时间\n那些箱子呢? ";
				link.l1 = "嗯...什么箱子? ";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "真遗憾, 船长...很遗憾你不愿意帮助我。 ";
			link.l1 = "这不是我愿意的问题, 我的朋友。 你必须理解。 再见。 ";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "昨天我收到了" + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + "的一封信, 他在信中通知我赎金会更高, 还威胁要把他卖为奴隶。 已故的船长应该通知" + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", 说我同意以前的条件, 并支付预付款。 但现在我明白为什么海盗提高了赌注。 ";
			link.l1 = "你建议什么? ";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "哦, " + GetSexPhrase("伙计","姑娘") + ", 我感觉到这里有诡计。 我警告你这非常危险, 可能导致可怕的后果。 " + pchar.GenQuest.CaptainComission.CapName + "船长有三个装满金子的箱子, 他应该在" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + "把它们交给" + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT) + "作为赎金, 赎一个人 - " + pchar.GenQuest.CaptainComission.SlaveName + "。 如果他想让你来找我们, 他不可能忘记告诉你箱子的事。 ";
			link.l1 = "他说最后一句话时, 似乎没有说完。 我希望你能告诉我更多。 ";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // 如果派去见鬼则删除。 护林员.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "我别无选择...我已经筹集了所需的金额, 15万比索。 我请你把它送到" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + ", 并把我的亲戚带到这里。 一旦完成, 我会付你4万。 ";
			link.l1 = "好的, 我准备好了。 ";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "不幸的是, 我有其他计划。 ";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "那就拿着钱, 愿上帝保佑你。 但请快点。 我担心" + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM) + "不会等, 会把这个可怜的人卖为奴隶。 ";
			link.l1 = "在这里等我。 我想不会花太多时间。 ";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "这不重要\n筹集赎金的人不会在意。 他们只需要结果, 活着且完好无损 —" + pchar.GenQuest.CaptainComission.SlaveName + "。 所以别浪费时间。 ";
			link.l1 = "如果我拒绝呢? ";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "实际上, 我不需要你的同意。 我只是通知你, 如果你不把" + pchar.GenQuest.CaptainComission.SlaveName + "活着送到酒馆, 我会派赏金猎人追你...";
			link.l1 = "嗯...这很严重。 如果我照做呢? ";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "那我们再进一步讨论。 ";
			link.l1 = "好吧...看看会怎样。 ";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("你好, " + GetFullName(pchar) + "船长。 有什么消息吗? ","那么, 船长, 你已经交付赎金了吗? ","你好, 希望你带来了好消息? ");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "不幸的是, 我的计划改变了, 所以我必须打破我们的约定。 ";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "还没有。 我还在忙那件事。 ";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("哦, 很高兴见到你, " + GetFullName(pchar) + "船长。 有什么好消息吗? ","那么, 船长, 你救出我们受苦的朋友了吗? ","很高兴看到你安然无恙, 船长。 我们共同的事情进展如何? ");
					link.l1 = "到目前为止没有消息, 但我正在处理。 ";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "听着, 朋友, 你为什么要让我对那笔交易负责? ";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("你好, " + GetFullName(pchar) + "船长。 有什么消息吗? ","那么, 船长, 你已经交付赎金了吗? ","你好, 希望你带来了好消息? ");
					link.l1 = "是的。 你的要求已完成, " + pchar.GenQuest.CaptainComission.SlaveName + "在我的船上, 正准备上岸。 ";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("哦, 很高兴见到你, " + GetFullName(pchar) + "船长。 有什么好消息吗? ","那么, 船长, 你救出我们受苦的朋友了吗? ","很高兴看到你安然无恙, 船长。 我们共同的事情进展如何? ");	
					link.l1 = "我带来了我们谈论的那个人。 他在我的船上。 ";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("你好, " + GetFullName(pchar) + "船长。 有什么消息吗? ","那么, 船长, 你已经交付赎金了吗? ","你好, 希望你带来了好消息? ");
					link.l1 = "问候你, " + pchar.GenQuest.CaptainComission.Name + ", 我不得不让你失望了。 ";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("哦, 很高兴见到你, " + GetFullName(pchar) + "船长。 有什么好消息吗? ","那么, 船长, 你救出我们受苦的朋友了吗? ","很高兴看到你安然无恙, 船长。 我们共同的事情进展如何? ");
					link.l1 = "你为之说情的那个人死了。 ";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "谢谢你, 船长, 你帮了我们家一个大忙。 这是你的奖励...有三个箱子 —正好相当于40000比索。 请原谅, 我现在必须见他。 ";
			link.l1 = "当然, 祝你俩见面愉快, 好运。 ";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "我完全理解你的急切, 但出现了一些意外情况, 迫使我承担了额外的费用。 ";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("你收到了信用箱");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("你收到了信用箱");
			PlaySound("interface\important_item.wav");
			dialog.text = "我不明白...我们不是已经就你的报酬金额达成一致了吗? ";
			link.l1 = "是的, 但我被迫支付了200000比索, 而不是150000比索, 更不用说去巴巴多斯的旅行了。 ";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "船长, 这只是你自己行动迟缓的结果。 海盗没有向我提出任何额外要求。 真是个奇怪的家伙, 试图以别人的苦难为代价获利? ";
			link.l1 = "好吧, 我明白试图向你解释任何事情都是徒劳的...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "太好了! 你之前还怀疑我们合作不好。 ";
			link.l1 = "但我在这件事上花了很多钱。 ";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "我知道, 我知道...但这也有你的错。 你怎么能把三个装满金子的箱子沉了, 我们不得不从国库中好不容易才弄出来, 这样" + NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)) + "才能有这样一个" + pchar.GenQuest.CaptainComission.SlaveSpeciality + "专家? ";
			link.l1 = "要知道, 没有适当的补偿, 我不会把他交给你。 ";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "嗯, 你是个聪明人, 当然明白现在讨价还价已经太晚了。 我们本可以扣押你的船只和货物。 \n但之前已经提供了补偿。 因此, " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "政府祝贺你成功完成行动, 并向你赠送这件珍贵的礼物和一份微薄的奖励。 ";
			link.l1 = "嗯...好吧, 总比什么都没有好。 带走你宝贵的专家吧。 ";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "哦, 太遗憾了! 我已经浪费了太多时间。 你真的让我失望了, 船长! ";
			link.l1 = "我明白, 但情况无法克服。 这是你的钱。 ";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "你能快点吗? 我担心海盗会再次改变交易条件。 ";
			link.l1 = "别担心, 我们会处理好的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "我希望你意识到你正在与时间赛跑? ";
			link.l1 = "再说一次! 我正在处理。 请耐心等待。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "上帝保佑我们! 没有压力, 只是来自谦虚清教徒的帮助\n这是你自己的错。 你杀了" + pchar.GenQuest.CaptainComission.CapName + "船长, 丢了我们的金子, 还没能赎回一个非常有价值的人。 现在这是个麻烦, 是你的责任。 别以为你被原谅了...你会为此付出代价的。 ";
			link.l1 = "去你的! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// 与种植园管理者的对话
		case "CaptainComission_10":
			dialog.text = "你好, 你想要什么吗? ";
			link.l1 = "我可以见这个种植园的主人吗? ";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "他不在这里, 他在找一个逃跑的奴隶, 叫刀锋或布拉德, 我不记得了...我是当地的管家" + npchar.name + ", 老板休假时我有权处理所有事务。 ";
			link.l1 = "是吗? 那很好...卖奴隶也是你的事吗? ";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "当然。 你想买多少? ";
			link.l1 = "只买一个。 ";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "唉...你确定你只需要一个奴隶吗? ";
			link.l1 = "当然确定。 他的名字是" + pchar.GenQuest.CaptainComission.SlaveName + "。 ";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "但你肯定意识到, 单个奴隶的价格会比批量购买中单个奴隶的价格高? ";
				link.l1 = "我当然知道。 你能说个价吗? ";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "嗯...我希望你知道你在为谁说情? ";
					link.l1 = "你是什么意思? ";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "哦, 那个懒汉。 我连一个铜板都不会给他。 自从他被带到这里, 他从未做过任何实际工作。 我不知道上校为什么要在这些国家罪犯身上浪费钱。 现在黑人就不同了。 他们是伟大的工人, 这是他们的天性, 既强壮又顺从。 相信我, 他们可以做任何工作。 收割甘蔗或担任管家 —他们会以最好的方式完成, 只要给他们一点‘说服’...";
					link.l1 = "我的朋友, 我一点也不在乎你的黑人。 我只对那个你说的懒汉感兴趣, 他反正活不了多久, 我需要他当炮灰, 我会为他多付钱。 ";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "当然, 当然。 让我看看价格\n哦! ! ! 150000比索。 ";
			link.l1 = "哇...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "价格应该在价目表里。 给你。 你知道, 我不太明白。 其他奴隶以合理的价格出售, 但那个奴隶却被卖了一大笔钱...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "我想我明白这里的情况了...好吧, 这是钱, 我要带他走。 ";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "嗯...但我不是在赎回人质, 我想买一个普通奴隶。 你不认为用这么多钱可以买一艘装备精良的好船吗? ";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "那不是普通奴隶。 毕晓普上校甚至下令看守他。 ";
			link.l1 = "所以我甚至不能买他? ";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "为什么, 你当然可以。 上校给他定了价 —根据价目表, 200000比索。 ";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "哇! 好吧, 那上校一定知道那个奴隶是什么样的人...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "嗯...但我不是在赎回人质, 我想买一个普通奴隶。 你不认为用这么多钱可以买一艘装备精良的好船吗? ";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "啊, 是的。 请原谅我。 让我看看毕晓普留下的价格。 \n啊哈, 在这里。 嗯。 哦! ..150000比索! ..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "显然这是某种错误。 你肯定意识到没有奴隶可能值那么多钱。 我想是多了一个零, 金额应该是15000比索。 考虑到他是个懒汉和白痴, 这仍然太多了。 ";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "嗯...但我不是在赎回人质, 我想买一个普通奴隶。 你不认为用这么多钱可以买一艘装备精良的好船吗? ";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "太好了! 那太好了! 他们马上就会把他带到这里...唉...也许来杯茶? ";
			link.l1 = "不, 谢谢...向毕晓普上校问好...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "请问你是哪位? ";
			link.l1 = "嗯...没关系, 别麻烦了。 再见。 ";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "对不起, 我无能为力。 这是价目表。 ";
			link.l1 = "哦, 别再提‘价目表, 价目表...’了。 没有毕晓普, 你们都不能决定最简单的事情。 告诉他...算了, 什么都别告诉他。 ";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "所以你不打算买那个奴隶。 ";
			link.l1 = "不买。 再见。 ";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "我对此一无所知。 我只有关于出售那个特定奴隶的具体指示。 ";
			link.l1 = "胡说...好吧, 不管怎样。 这是钱。 把奴隶带来。 ";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "当然。 他会立刻被送到这里。 ";
			link.l1 = "再见。 ";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "嗯...是的, 也许你是对的。 应该是个错误。 ";
			link.l1 = "好吧, 如果我们已经就价格达成一致, 我现在可以带他走吗? ";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "是的, 当然。 他马上就会被带到这里。 ";
			link.l1 = "很好。 这是你的钱...再见。 ";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "想喝点茶吗, 船长? ";
			link.l1 = "不, 谢谢。 ";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "你决定买他了吗? ";
			link.l1 = "不买。 再见。 ";
			link.l1.go = "exit";
		break;
		
		// 与奴隶的对话
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "你好, 船长。 我能为你做什么? 我不敢相信这场折磨终于结束了。 ";
				link.l1 = "你应该感谢的不是我, 而是你来自" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + "的亲戚" + pchar.GenQuest.CaptainComission.Name + "。 他筹集了赎金。 ";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "你好, 船长。 我听说你为我支付了赎金。 我必须为此感谢你, 尽管我知道你只是个信使。 ";
				link.l1 = "你看起来对重获自由不太高兴。 你在担心什么吗? ";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "拜托, 如果不太影响你的计划, 请带我去见他。 我想亲自感谢他。 ";
			link.l1 = "当然, 我会的。 来吧, 我带你去船上。 ";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "为了确保我的自由, 我需要知道那些为此付费的人的名字。 ";
			link.l1 = "嗯, 是我付的钱, 尽管不是出于自愿。 ";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "那么, 我的怀疑得到了证实。 你是被" + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "强迫这样做的? ";
			link.l1 = "是的, 是来自" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + "的" + pchar.GenQuest.CaptainComission.Name + "。 ";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar,true);// 护林员 。 回滚了 。 和保护  以免智者杀死。 
			dialog.text = "我明白了。 我不知道他们答应了你什么, 但这是交易: 把我带到" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + "的酒馆, 我在那里才会真正安全。 作为回报, 我会和你分享我掌握的一些信息。 ";
			link.l1 = "很好, 更何况他们到目前为止什么都没答应。 跟我来, 我带你去我的船。 ";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "我不会因为一些可疑的信息而冒险给自己招来麻烦。 ";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar,PChar,"OpenTheDoors", -1.0); //护林员  跟着主角
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "不幸的是, 我现在不能告诉你。 这对我们俩都可能意味着麻烦。 ";
			link.l1 = "更是如此...请跟我来, 别做傻事。 认为自己再次被捕了。 ";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //护林员 - 好像是把他带到船上
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "什么? ! 海盗又改变了交易? 但我再也无法从生意中拿出钱了! 这样我很快就会破产! ";
			link.l1 = "不...你的亲戚在巴巴多斯的种植园里, 在一次失败的逃跑尝试中丧生了。 ";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "哦...我完全崩溃了...这是怎么发生的? ";
			link.l1 = "海盗没有等待赎金, 把他卖为奴隶。 我去巴巴多斯找他, 但没能救他...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "天啊! 这是怎么回事? \n好吧, 船长, 谢谢你的参与。 请把我给你的钱还回来。 ";
			link.l1 = "我的花费超出了所有预期, 所以我会保留你的钱...再见。 ";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "当然, 拿去吧...抱歉我没能帮到你...再见。 ";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "那太糟糕了。 你不知道这有多糟糕...";
			link.l1 = "我对此无能为力。 我甚至很高兴事情就这样发生了。 再见。 ";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// 在监狱中与奴隶的对话
		case "CaptainComission_70":
			dialog.text = "喝...船长, 带些水来...";
			link.l1 = "嘿, 伙计, 你不是" + pchar.GenQuest.CaptainComission.SlaveName + "吗? ";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "是的...是我...";
			link.l1 = "听着! 如果你不想像浅滩上的比目鱼一样死在这里, 振作起来听我说。 你知道巴巴多斯的灯塔在哪里吗? ";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "我知道...";
			link.l1 = "一旦你有机会, 就跑到那里。 我会尽量为你安排这样的机会。 ";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// 奴隶守卫对话
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("说吧, 船长, 但要快点, 我在值班。 ", "说吧, 但要快点, 别用琐碎的事情烦我。 ");
			link.l1 = RandPhraseSimple("你能告诉我怎么找到某个奴隶吗? 他的名字是" + pchar.GenQuest.CaptainComission.SlaveName + "。 ", "在这个种植园的某个地方应该有一个名叫" + pchar.GenQuest.CaptainComission.SlaveName + "的奴隶。 你能告诉我怎么和他说话吗? ");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "今天他受到了惩罚, 被看守着。 ";
			link.l1 = "谢谢。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "谢谢你...船长, 你救了我的命...";
			link.l1 = "跑到巴巴多斯的灯塔那里等我。 ";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "船长, 我该如何感谢你? 我仍然不敢相信这场折磨终于结束了。 ";
				link.l1 = "我已经收到了你来自" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + "的亲戚" + pchar.GenQuest.CaptainComission.Name + "的感谢。 我是按他的指示行动的。 ";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "谢谢你, 船长。 我不知道你是代表谁行动的, 但即使是不好的自由也比好的奴役强。 ";
				link.l1 = "你是什么意思? ";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "如果这不会太影响你的计划, 请带我去见他。 我只是对这一切太累了。 ";
			link.l1 = "当然我会...如果我们能活着离开这里的话。 ";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "我可以知道为我的自由买单的人的名字吗? ";
			link.l1 = "嗯, 实际上, 我没有得到报酬。 他们让我别无选择。 ";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "那么, 我的怀疑得到了证实。 你是被" + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "强迫这样做的? ";
			link.l1 = "是的, 是来自" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + "的" + pchar.GenQuest.CaptainComission.Name + "。 ";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// 米特罗科斯塔
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar,true);// 林务员 。 回滚了 。 并保护 以免聪明人杀死。 
			dialog.text = "我不知道他们向你承诺了什么, 但这是交易: 把我带到" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + "的酒馆, 我在那里才会真正安全。 作为回报, 我会和你分享我所拥有的一些信息。 ";
			link.l1 = "很好, 更何况他们到目前为止还没有承诺任何东西。 跟我来, 我会带你到我的船上。 ";
			link.l1.go = "CaptainComission_95";
			link.l2 = "我不想因为一些可疑的信息而冒险给自己招来麻烦。 ";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // 在日志中设置记录 林务员
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "不幸的是, 我现在不能透露给你。 这对我们俩来说都可能意味着麻烦。 ";
			link.l1 = "更何况...请跟我来, 不要做蠢事。 考虑到你又一次被捕了。 ";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "谢谢你, 船长。 现在我终于安全了。 我不会给你钱, 因为我相信知识及其熟练应用比易腐烂的金属更有价值。 ";
			link.l1 = "我在等待信息";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "事情是这样的, 我是一名科学家, " + pchar.GenQuest.CaptainComission.SlaveSpeciality + "专家, 而且" + NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)) + "很久以来一直向我提供合作, " + 
				"但我是一名军事工程师, 我信守我的效忠誓言。 他们试图偷走我, 不过当海盗得知我的真实身份和重要性时, 真正的问题才开始\n" +
				"最后, 他们设法抓住了我, 但黄金是他们唯一想要的东西, 他们从不需要我的知识。 我的朋友和敌人未能及时赎回我, 我被卖给了种植园。 剩下的你知道了。 ";
			link.l1 = "是的, 正如他们所说, 智慧多舛, 确实如此。 ";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "在战斗中保护你的船和船员。 ";
				break;	
				case 1:
					sTemp = "在扬尘条件下快速重新装载你的大炮并进行瞄准射击。 ";
				break;					
				case 2:
					sTemp = "在战斗中快速管理帆和操纵。 ";
				break;					
			}
			dialog.text = "嗯, 你可以这么说。 所以, 如果你注意我能告诉你的, 你将在" + sTemp + "的技能上变得更加熟练。 ";
			link.l1 = "谢谢你, 那个信息确实非常有用。 ";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "那么, 再见, 感谢一切。 ";
			link.l1 = "也谢谢你。 再见, 下次尽量不要被抓住。 ";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// 现在分发大象 !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// 生成器"船长的请求"
		
		// 生成器"大帆船行动"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //修正
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// 甲板上与船长的对话 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // 检查如果对话已经发生过 。 以免重复。 林务员
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("喂, 我是" + GetFullName(NPChar) + "船长, 是什么风把你吹到我的'" + pchar.GenQuest.CaptainComission.ShipTypeName + "'号甲板上来的? ", "喂, 我总是很高兴我的船上有客人。 " + GetFullName(NPChar) + "船长为你服务。 ");
			link.l1 = "你好, 我是" + GetFullName(pchar) +"船长, 代表某个" + pchar.GenQuest.CaptainComission.CapName +"船长行事。 他让我告诉你, 你将在" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + "被捕。 当局知道关于" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + "的事。 "; // 修正 + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "你到底在这里做什么? 我们已经安排好了一切! 回到你的船上去! ";
			link.l2 = "呃..是的, 对! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // 以免出现错误跳转 - 等等。 林务员 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "啊, 真遗憾! 让我想想\n那么" + pchar.GenQuest.CaptainComission.CapName + "船长在哪里? ";
			link.l1 = "他死了。 ";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "该死的! 事情越来越糟了...听着, " + GetFullName(pchar) + ", 我还没准备好面对这样的变故。 " + pchar.GenQuest.CaptainComission.CapName + "船长和我约定在" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + "见面。 计划是在他的船上装些货物。 现在船长死了, 我不能出现在定居点\n看来我除了请你帮忙之外, 别无选择。 ";
			link.l1 = "我的同意将取决于你需要什么样的帮助。 ";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "帮我带人和长艇。 我需要把货物从" + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + "运走。 你可以保留已故船长的那份货物。 ";
			link.l1 = "嗯...显然, 你承担了超出能力范围的事情。 我需要更多信息。 ";
			link.l1.go = "CaptainComission_305";
			link.l2 = "不幸的是, 我现在没有时间浪费在那上面。 ";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "好吧, 我会给你详细信息\n" +
				"在一次常规巡逻中, 我遇到了一艘挂着" + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "旗帜的船只。 他们无视我投降的命令。 " +
				"当经过短暂的追逐后, 我们追上了" + sTemp + "'" + pchar.GenQuest.CaptainComission.VictimShipName + "', 于是他们升起了黑旗。 堡垒很远, 所以我们不得不独自战斗。 他们摧毁了我们的船首斜桅, 这就是为什么我们无法避免登船。 \n" + 
				"很接近, 但多亏了圣母玛利亚和一支火枪手部队, 我们设法杀死了他们所有人。 想象一下, 当我们发现" + sTemp + "里装满了什么时, 我们有多高兴。 " +
				"我们认为这是对我们的伤口和战友死亡的体面奖励\n天已经黑了, 我们把" + sTemp +"带到最近的海湾, 把货物藏在岸上。 然后我们引爆了" + sTemp +", 我报告说那是一艘沉没的海盗船。 当然, 我没有提到货物。 ";
			link.l1 = "显然, 还是有人泄密了...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "真遗憾, 船长...很遗憾你不愿意帮助我。 ";
			link.l1 = "这不是我的意愿问题, 亲爱的。 你必须理解。 再见。 ";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "我不认为是我的人。 最有可能的是, 货物的主人渴望减轻损失的痛苦\n那么? 我能指望你的帮助吗? ";
			link.l1 = "是的, 听起来不错。 ";
			link.l1.go = "CaptainComission_308";
			link.l2 = "不, 我的朋友。 首先: 我不知道有多少货物会进入我的货舱。 其次: 不能保证当局还没有找到它并拿走了, 同时在藏匿处留下了埋伏队。 ";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "那么我们在" + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + "见面, 就在午夜之后。 我目前的位置需要保密。 我们必须避开巡逻队。 "; // belamour gen
			link.l1 = "好的, 在那里等我。 ";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "真遗憾, 但你没有给我选择的余地。 一艘船不足以装载所有货物。 我用我的职业生涯和自己的生命来冒险。 当然, 你的船员会很高兴帮助我, 以换取可观的分成。 ";
			link.l1 = "你在建议什么? ";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "我将乘坐你的船, 把你留在" + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + "。 "; // belamour gen
			link.l1 = "我觉得你不太可能成功。 即使我不得不砍倒你所有的船员, 我也会回到我的船上。 ";
			link.l1.go = "CaptainComission_311";
			link.l2 = "看来, 我别无选择。 好吧, 我会屈服于暴力...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //甲板上的争吵之后 - 海上战斗		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // 林务员 临时记忆用于对话 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "船长, 我们必须快点。 我担心巡逻队可能会发现我们。 ";
			link.l1 = "好的, 我们快点。 ";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "船长, 命令放下所有救生艇。 我们得走几次, 我担心巡逻队可能会来到海湾。 ";
			link.l1 = "别担心, 一切都会好的。 小船已经到岸边了。 ";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "哦, 该死的。 现在我们有伴了...";
			link.l1 = "真的, 如果你提到某个傻瓜, 他马上就会出现...";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.pizdezh_uze_bil"); // 删除对话重复检查 林务员
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// 海岸巡逻队对话
		case "CaptainComission_317":
			dialog.text = "船长, 我们正在寻找战犯" + pchar.GenQuest.CaptainComission.Name + ", 他向当局隐瞒了一批有价值的货物。 请出示你的文件。 ";
			link.l1 = "什么文件, 官员? 我们上岸是为了补充淡水供应。 ";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "他在这儿, " + pchar.GenQuest.CaptainComission.Name + "本人。 放下武器, 跟我来, 你们两个! ";
			link.l1 = "时机真糟糕, 官员...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // 林务员 。 取消事件如果活着。 
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "我们必须在增援到达之前快点。 装载即将完成, 你的份额是" + pchar.GenQuest.CaptainComission.GoodsQty + "单位的" + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +"。 ";
			link.l1 = "太好了。 现在该离开了。 和你做生意很愉快。 ";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "还有一个请求。 当局肯定会追捕我们, 你能护送我的船到" + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + "吗, 它在" + XI_ConvertString(GetIslandByCityName(sTemp) + "Voc") + "上? "; // belamour gen
			link.l1 = "不, 我的朋友, 从现在起各人自扫门前雪。 再见...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "当然, 为了丰厚的回报, 我可以那样做。 ";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar,sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar,sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// 重载
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar,sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar,sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// 重载
			dialog.text = "当然。 对于护送, 我愿意支付" + pchar.GenQuest.CaptainComission.ConvoyMoney + "比索。 但还有一个条件, 不能超过" + pchar.GenQuest.CaptainComission.iDay + "天。 这很重要。 ";	
			link.l1 = "成交。 我们立即出发。 ";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // 锁定休息界面 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("船长, 我们在浪费时间。 他们随时可能找到我们。 ", "船长, 我们在和时间赛跑。 别忘了他们在找我。 ", "船长, 我们不能再拖延了。 我的船太大了, 无法避开巡逻队的注意。 ");
			link.l1 = LinkRandPhrase("是的, 你说得对。 我们得快点。 ", "那就别再拖延了, 把你们自己装进小船里。 ", "够了...召集你的人。 我们要走了。 ");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "船长, 我需要和我的人谈谈。 ";
			link.l1 = "去吧。 ";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "你好, " + pchar.CaptainComission.Name + "船长。 那么, 你把全部货物都带来了吗? " + pchar.CaptainComission.CapName + "船长在哪里? ";
			link.l1 = pchar.CaptainComission.CapName + "死了。 我不得不向" + NPCharSexPhrase(sld, "这位先生","这位女士") +"求助。 我来介绍一下, 这是" + pchar.CaptainComission.FullName + "船长。 ";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "而" + NPCharSexPhrase(sld, "他是谁? 他是","她是谁? 她是") +"知道我们的事吗? ";
			link.l1 = "一般来说, 是的。 但有一个问题 -" + NPCharSexPhrase(sld, "他确信","她确信") +", 一半的货物属于" + NPCharSexPhrase(sld, "他","她") +"。 我们必须说服" + NPCharSexPhrase(sld, "他","她") +", 事实并非如此。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "我的朋友" + GetFullName(pchar) +", 你已经听到了你需要知道的一切。 我们需要进入你的货舱。 ";
			link.l1 = "你认为我的孩子们会只是站在那里看着, 当一些乌合之众清空他们的货舱时? ";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "你说得有道理。 比如说, " + pchar.GenQuest.CaptainComission.GoodsSum + "比索的现金, 将使我们不必与你的船员发生冲突。 请记住, 这涵盖了我们一半的货物, 所以一切都是公平的。 如果你同意, 那么没有人会受伤。 ";
			link.l1 = "如果我拒绝呢? ";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "在这种情况下, 暴力是不可避免的。 你将是第一个受害者, 你将在这个舒适的海湾找到安宁, 而你的船员将无法来帮助你...你觉得怎么样? ";
			link.l1 = "你让我别无选择。 好吧, 我会杀了你们所有人。 ";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "我想我别无选择。 好吧, 这是你的钱。 ";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "嗯, 这对" + GetSexPhrase("一位高贵的绅士","一位勇敢的女士") +"来说是一个合适的决定。 ";
			link.l1 = "停止哲学思考! 让我们开始做生意吧! ";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "明智的决定。 祝你好运。 ";
			link.l1 = "愿你被它噎住...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// 林务员 - 再次允许在给钱后战斗。 但在徒手战斗后不再挥舞...正如所说的那样))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "船长" + GetFullName(pchar) + ", 我们迟到了。 我希望你明白, 你现在没有资格获得奖励。 ";
			link.l1 = "我当然明白。 多亏了你, 我已经赚了不少钱。 再见...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "你能给一个为皇冠的荣耀在战斗中遭受巨大痛苦的老士兵买些朗姆酒吗? ";
			link.l1 = "酒保! 给我们倒些朗姆酒! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "哦, 谢谢你, " + GetAddress_Form(pchar) + ", 你真是太好了, 款待一个完全失去记忆的残疾人...";
			link.l1 = "你说完全失去? ";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "绝对是的, " + GetSexPhrase("先生","女士") +"船长...完全失去。 我除了一个飞向我头部的短棍什么都不记得了。 看看它在我头上打了个洞, 我想我所有的记忆一定都从那里漏出来了。 ";
			link.l1 = "伙计, 把你那可怜的故事留给家庭主妇吧。 我见过遭受葡萄弹直接命中的人, 他们的记忆完全被抹去了...连同他们的头...而你在这里谈论什么想象中的链弹。 我们最好谈谈" + pchar.GenQuest.CaptainComission.Name +"船长。 ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "哦, 好吧, 你知道。 我总得谋生。 至于" + pchar.GenQuest.CaptainComission.Name + "船长, 我喋喋不休没有任何好处...如果我每问一个关于他的问题收费一百个硬币, 我现在拥有的黄金就会比总督一年从他的臣民那里收集的还多... ";
			link.l1 = "你有没有试过出售那个船长藏匿的货物? ";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "什么? 又是一个侦探? 我再告诉你一次, 我不记得任何" + pchar.GenQuest.CaptainComission.Name + "船长! 我脑震荡了, 我有医生的证明可以证实! 你还需要什么? ! ";
			link.l1 = "哇, 别这么激动。 你知道...他太晚了。 " + pchar.GenQuest.CaptainComission.CapName + "船长让我告诉" + pchar.GenQuest.CaptainComission.Name + "不应该在那个定居点露面, 当局知道" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + "'" + pchar.GenQuest.CaptainComission.VictimShipName + "被摧毁的情况, 他将被逮捕。 ";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "呸。 你应该马上告诉我, 不要绕圈子。 是我让" + pchar.GenQuest.CaptainComission.CapName + "船长在我们返回时拦截我们的船。 " +
				"那场血腥的战斗后, 它被移到了码头。 那个该死的海盗在那里用他的货物做什么? ! 这么多小伙子因为他而死。 ";
			link.l1 = "你是怎么活下来的? ";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "阴差阳错。 说实话, 是我自己该死的错误。 我不够快, 所以我们的长艇没有离开危险区域。 不过只有我一个人受伤。 被什么残骸击中, 扔进了水里。 我甚至不记得我是怎么到达岸边的。 ";
			link.l1 = "你是怎么摆脱审讯的? ";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "我告诉他们我在登船时脑震荡了, 我不知道任何货物的事。 我还假装心智薄弱, 你知道, 我刚刚站起来, 就在" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "到达之前。 不能正常移动, 我的协调能力很差。 ";
			link.l1 = "嘿, 但到底是谁泄露了货物的秘密? ";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "海盗们给总督寄了一封信, 据称是代表受伤的商人。 他们决定为船长的坚持报复他。 这是他的错, 他愚蠢的固执把我们带入了这个烂摊子。 ";
			link.l1 = "但你们最初是如何遇到那个海盗的? ";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "我不知道。 那是一次普通的巡逻, 有一艘挂着" + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "旗帜的普通船只。 我不知道船长为什么决定检查它, 但他们对警告射击置之不理, 当我们追上他们时, 他们升起了'快乐罗杰'。 " +
				"我们没有堡垒的支持, 所以战斗并不容易。 然后是登船部分。 我仍然不知道我们是如何击败他们的。 \n" + 
				"嗯, 我们看到了所有珍贵的货物。 一定是魔鬼把它给了我们。 我们不得不把货物藏在岸上, 把被俘的船炸上天。 她损坏得太严重了。 ";
			link.l1 = "如果总督的人发现了藏匿处, 你不担心你所有的努力和牺牲都将白费吗? ";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "他们不会找到的。 毕竟, 我是整个中队最好的爆炸专家, 我把洞穴的入口炸得很好。 只有走私者才能找到我的藏匿处, 他们知道这个地方的每一寸。 \n" + 
				"看, 我自己也不知道该怎么处理这些战利品。 我自己既不能卖也不能搬走。 此外, 没有人会和一个脑壳破裂的人做生意。 我不想用我船员战友的死亡来赚钱, 但如果你带我去" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity) + ", 我可以告诉你藏匿处的位置, 要" + pchar.GenQuest.CaptainComission.Sum + "比索。 ";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "我同意。 这是你的钱。 现在说吧。 ";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "该死的! 好吧, 在这里等, 我去拿钱。 ";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "那太多了, 伙计。 此外, 我没有合适的船。 好吧, 祝你好运, 再见...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "好吧, 好吧。 今晚午夜后在" + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + "附近见面。 确保你的货舱里有空间装" + pchar.GenQuest.CaptainComission.GoodsQty + "件" + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + "。 把其中一些扔掉就太可惜了..."; // belamour gen
			link.l1 = "我会处理好的。 海湾见...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen 林务员
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "你终于来了。 我已经开始担心了。 我以为你会把我交给当局。 ";
				link.l1 = "我还没疯。 这是你的钱。 现在轮到你说话了。 ";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// 林务员 。 取消关于钱的定时器
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "那么, 钱在哪里? ";	
				link.l1 = "该死的! 好吧, 在这里等, 我去拿。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "船长, 显然我们迟到了。 走私者已经找到了藏匿处。 ";
			link.l1 = "我不会放弃我的战利品, 即使是魔鬼也不会把它从我这里夺走。 ";
			link.l1.go = "CaptainComission_351";
			link.l2 = "我退出, 你自己处理你的竞争对手吧。 ";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//设置从位置条件退出函数("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // 伐木工 - 已修正 。 之前的代码不工作
		break;
		
		case "CaptainComission_360":
			dialog.text = "船长, 我们这儿有件大事。 我建议你在我们的船只到达前, 把你的中队带走。 ";
			link.l1 = "先生们, 看来你们想拿不属于自己的东西。 ";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "哦, 真的吗? ! 你知道你在和谁说话吗? ";
			link.l1 = "我在和你说话, 朋友。 那批货物有合法的主人, 我代表他。 ";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "我们不会允许你干涉我们的事务, 即使你是我们的弥赛亚! 如果你珍惜生命, 就让开航道? ";
			link.l1 = "我没说清楚吗? 那批货物是我的, 我不会不拿到它就离开! ";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "见鬼! 如果你这么想要, 那你就永远在这里等着吧! ";
			link.l1 = "命运会决定谁将永远留在这里。 ";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "船长, 命令你的人快点, 巡逻队随时可能到达。 此外, 走私者显然也在等他们的运输工具。 ";
			link.l1 = "是的, 我们得快点...把货物装上货舱, 然后离开这里。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "谢谢你, " + GetFullName(pchar) + "船长。 如果不是你, 走私者就会得到我们的货物, 那些为保卫它而倒下的人就会白白牺牲...";
			link.l1 = "也谢谢你信任我。 ";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "我有一件小饰品, 给你, 我曾靠它活命。 请收下, 它可能是你的幸运符。 再次感谢你, 朋友。 愿风永远眷顾你。 ";
			link.l1 = "谢谢你的礼物, 我没想到。 你最好在口袋里有钱的时候照顾好自己的健康。 ";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // 伐木工结尾
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "显然, 今天是我的接待日。 你需要我吗? ";
			link.l1 = "如果你是" + pchar.GenQuest.CaptainComission.Name + "船长, 那么是的。 ";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...前船长" + pchar.GenQuest.CaptainComission.Name + "...";
			link.l1 = "我是" + GetFullName(pchar) + ", 我有几个问题要问你。 ";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "你为什么认为我会回答它们? ";
			link.l1 = pchar.GenQuest.CaptainComission.CapName + "船长让我警告你, " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + "'" + pchar.GenQuest.CaptainComission.VictimShipName + " 被摧毁的情况已为当局所知, " +
				"但我在从" + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + "出发的航行中没有看到你的船。 ";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "那" + pchar.GenQuest.CaptainComission.CapName + "船长在哪里? ";
			link.l1 = "他死了。 ";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "我明白了...原来是这样, 嗯? 现在很多事情都清楚了。 所以, 有人泄露了我们掠夺了" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + "的事。 " +
				"迟早他们会找到货物并绞死我。 " + pchar.GenQuest.CaptainComission.CapName + "船长死了, 这意味着没有人能帮助我\n除了你\n" + GetFullName(pchar) + ", 带我离开这里, 我会让你得到好处。 ";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "总督收到了货物主人的消息。 里面的数字相当可观, 你知道的。 ";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "但你肯定不会认为我会盲目帮助你吧? ";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "总督收到了货物主人的消息。 里面的数字相当可观, 你知道的。 ";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "殖民地有传言说你和走私者有交易...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "看来我得把整个故事告诉你了。 \n" +
				"在一次常规巡逻中, 我遇到了一艘挂着" + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "旗帜的船只。 他们无视我投降的命令。 " +
				"我们在短暂追逐后追上了" + sTemp + "'" + pchar.GenQuest.CaptainComission.VictimShipName + "’, 他们升起了黑旗。 堡垒很远, 所以我们不得不独自战斗。 他们摧毁了我们的首斜桅, 所以我们无法避免登船。 \n" +
				"情况很危急, 但多亏了圣母玛利亚和一个火枪手部队, 我们设法杀死了他们所有人。 当我们发现" + sTemp + "装满了贵重物品时, 你可以想象我们有多高兴。 " +
				"我们认为这是对我们的伤口和牺牲的人的体面奖励\n天已经黑了, 我们设法把" + sTemp + "带到最近的海湾, 并把货物藏在岸上。 然后我们烧毁了" + sTemp + ", 我报告说有一艘海盗船沉没了。 当然, 我没有提到货物。 ";		
			link.l1 = "我认为你骗我没有意义。 所以, 我提议做个交易, 你带我去藏匿处, 我带你去群岛上任何你想去的地方。 ";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "哈哈哈...不, 船长, 我不会不带我的那份离开定居点, 即使我必须上绞刑架。 ";
			link.l1 = "好吧。 你会得到你的一半。 ";
			link.l1.go = "CaptainComission_377";
			link.l2 = "嗯...你知道, 我不愿意为了你的利益而冒生命危险。 再见...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "这就对了。 我准备好了\n首先, 你应该把我藏在你的船上。 我会告诉你藏匿处所在的海湾。 ";
			link.l1 = "那我们就迅速而协调地行动。 我会打开你的牢房, 你跟着我。 在我们离开堡垒之前, 不要落后, 不要问问题。 ";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// 伐木工 - 禁止对话
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "谢谢你的救援。 我们去" + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat") + "吧, 我会指出藏匿处的位置。 我们应该在野蛮人找到这个地方之前赶紧走。 ";	// belamour gen	
			link.l1 = "你确定我们能把全部货物都取走吗? ";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "你说得对, 确保你有足够的空间装" + pchar.GenQuest.CaptainComission.GoodsQty + "件" + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + "。 失去这么贵重的战利品太可惜了, 而且上面沾满了鲜血。 他们不会再给我们第二次机会。 ";
			link.l1 = "我会处理好的。 ";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // 打开出口
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "船长, 我们不需要目击者。 请设法说服这些人离开海湾。 ";
			link.l1 = "好的, 我们去做。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "船长, 对不起, 但这里不是你演习的最佳地点。 那个码头已经被占用了。 ";
			link.l1 = "先生们, 我来这里不是为了观光。 我在这里有生意。 ";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "好吧, 我们也不是在这里抓水母, 把你们的船转回去, 滚出这里。 ";
			link.l1 = "我不想浪费时间说服你们离开。 要么你们自愿离开并活下去, 要么就永远留在这里。 ";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "我看你理解我的话有困难。 好吧, 这是你的葬礼...";
			link.l1 = "这样更好! ";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "我们到了。 藏匿处在那个峭壁的壁龛里。 入口被岩石堵住了。 藏匿处有" + pchar.GenQuest.CaptainComission.GoodsQty +"单位的" + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +"。 记得有一半是我的? ";
			link.l1 = "我当然记得。 我的人在装货的时候我们有时间谈谈你和你的货物要送到哪里去。 ";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "非常好。 现在告诉我, 我有什么理由要分享? ";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = pchar.GenQuest.CaptainComission.Name + "船长, 我得告诉你一件不愉快的事。 我为总督工作。 我打算把你藏的所有货物都交给他。 你应该回到监狱, 在那里等待你的命运。 ";
				link.l3.go = "CaptainComission_389";
				link.l2 = "非常好。 但事情是这样的...起初我想把你交给当局, 但我现在为什么要这样做呢? 我为什么要和你分享? ";
			    link.l2.go = "CaptainComission_3899"; // // 伐木工 。 在欺骗所有人的情况下的单独对话。 
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // 伐木工 。 移除了事件 ,否则在日志中写的不对。 
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar,sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar,sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// 重载
			dialog.text = "我需要在" + pchar.GenQuest.CaptainComission.iDay + "天内到达" + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", 在" + XI_ConvertString(GetIslandByCityName(sTemp) + "Voc") + "。 我在那里的人一定已经准备好货物出售了。 "; // belamour gen
			link.l1 = "好的。 那么是时候离开了。 ";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // 伐木工 。 在欺骗所有人的情况下的单独对话。 
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // 伐木工 。 移除了事件 ,否则在日志中写的不对。 
			dialog.text = "对。 人应该总是相信头脑而不是心。 活到老, 学到老\n尽管我没有想到这一点, 但我总是准备好战斗。 你将为你的背叛付出代价。 ";
			link.l1 = "好吧, 如果你运气好的话...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // 伐木工 。 移除了事件 ,否则在日志中写的不对。 
			dialog.text = "对。 人应该总是相信头脑而不是心。 活到老, 学到老\n尽管我没有想到这一点, 但我总是准备好战斗。 你将为你的背叛付出代价。 ";
			link.l1 = "我听候你的吩咐...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// 伐木工。 
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// 伐木工。 选择日志中的记录
			else AddQuestRecord("CaptainComission2", "26");// 看走哪条路 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "显然, 我们来晚了...顾客没等, 我也没有机会自己组织货物的储存和销售...";
			link.l1 = "在这方面你有什么特别的建议吗? ";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = GetFullName(pchar) + "船长, 我知道这有点尴尬, 但是...你能给我相当于我那份的钱吗? 我想" + pchar.GenQuest.CaptainComission.GoodsPrice + "比索可能是个不错的折衷方案。 ";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "是的, 这是个公平的价格。 我不介意。 这是你的钱, 再见。 ";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "哦, 不, 我的朋友, 那不行。 我不能永远照顾你。 如果你不想取走你的货物, 我就留着它。 放心, 我会找到储存它的方法, 最终把它卖掉。 ";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "等等, 船长。 我想感谢你救了我。 你知道, 我几乎失去了希望...给你, 我相信你会发现这件小饰品在很多困难情况下都很有用...现在再见。 ";
			link.l1 = "谢谢。 我没想到。 和你做生意很愉快。 ";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // 伐木工 。 正确的对话分配
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "我没想到你会这样...显然, 我别无选择, 只能向你挑战决斗。 ";
			link.l1 = "我听候你的吩咐...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "船长, 我需要和我的人谈谈。 ";
			link.l1 = "去吧。 ";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "你好, " + GetFullName(pchar) + "船长。 那么, 你把全部货物都带来了吗? " + pchar.CaptainComission.CapName + "船长在哪里? ";
			link.l1 = pchar.CaptainComission.CapName + "死了, 我因被揭发而被捕。 如果" + pchar.CaptainComission.FullName + "船长没有帮助我, 你就不会看到我或货物了。 ";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "那" + NPCharSexPhrase(sld, "他是谁? 他","她是谁? 她") + "知道我们的事吗? ";
			link.l1 = "当然。 " + NPCharSexPhrase(sld, "他把","她把") + "我从监狱里救出来, 并承诺把一半货物送到这里;另一半我答应给" + NPCharSexPhrase(sld, "他","她") + "作为补偿。 ";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "唉, 船长, 没门。 这是你的问题! 我建议我们把船开走, 但你太在乎你那该死的职业生涯了。 现在你看, 你亲爱的总督把你关进了监狱." +
				" 你的份额比一半小得多! 我们冒着枪林弹雨不是为了让你自己偷走整个一半! ";
			link.l1 = "听着, 水手长, 你不记得船已经完全坏了吗? 几乎要沉了? 你不明白如果我不给这个人一半, 你就再也见不到哪怕一小片货物了吗? ";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "你骗不了我! 我们怎么知道你不是串通一气? 如果根本没有逮捕呢? 如果你只是太贪婪, 决定偷我们的东西呢? 或者你认为我们忘了如何挥舞刀刃? ! ";
			link.l1 = "我看你疯了。 你除了耳朵里的钱币叮当声什么也听不见。 ";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "伙计们! 看看我们的船长现在怎么说话的! 的确, 贪婪已经完全吞噬了他! 他把我们的份额卖给了" + NPCharSexPhrase(sld, "一个无赖","一个女冒险家") + "! ! ";
			link.l1 = "现在闭上你肮脏的嘴, 否则我就永远让你闭嘴! ";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "对不起, 船长, 你不得不目睹这可笑的一幕, 甚至参与其中。 很难相信仅仅一个月前我们还是一个团结的船员, 我们每个人都愿意牺牲自己的生命来拯救朋友。 ";
			link.l1 = "我必须承认, 我无法想象, 无意冒犯。 ";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "不幸的是, 我没有机会自己组织货物的储存和销售...";
			link.l1 = "在这方面你有什么特别的建议吗? ";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = GetFullName(pchar) + "船长, 我知道这有点尴尬, 但是...你能给我相当于我那份的钱吗? 我想" + pchar.GenQuest.CaptainComission.GoodsPrice + "比索可能是个不错的折衷方案。 ";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // 以防万一 .伐木工
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // 伐木工
				link.l1 = "好吧, 我不介意。 这是你的钱, 再见。 ";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "不, 那不行。 你可以拿走你的货物, 或者把它留在货舱里, 但我不会给你任何硬币。 ";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "等等, 船长。 我想感谢你救了我。 你知道, 我几乎失去了希望...给你, 我相信你会发现这件小饰品在很多困难情况下都很有用...现在再见。 ";
				link.l1 = "谢谢。 我没想到。 和你做生意很愉快。 ";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "等等...我刚想到...你知道, 我的职业生涯现在结束了, 我没有船员, 我在祖国被流放。 你肯定需要有稳定双手。 能守口如瓶的可靠人员。 请接受我加入你的船员, 我保证你不会后悔。 ";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "说实话, 我一直期待你同意一段时间了。 当然。 船上见。 ";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "嗯...你知道, 在我看来, 你太聪明了, 不适合为任何人服务。 再见...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "好吧, 显然, 今天显然不是我的幸运日...好吧, 船长, 让我们拔出刀刃, 一次性解决这一切...";
			link.l1 = "我听候你的吩咐...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// 伐木工 。 雇佣时改变ID。 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// 生成器 "Operation'Galleon'"
		
		// 任务 "meeting in the cove" -->
		// 军官
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "与你无关。 现在告诉我你在这里嗅什么? 你不是在找一个刚被拘留的人吗? ! ";
				link.l1 = "一个人? ! 不...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "算你走运。 否则你也会和他一起进监狱。 所以别在这里乱搞, 水手。 滚开! ";
				link.l1 = "是的, 我最好走...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // 时间不再重要
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // 启用随机事件
			ContraMeetManQuest_DeletePatrolFromShore(); // 退出时从位置删除所有人
			break;
			
		// 本人
		case "ContraMeetManQuest_1":
			dialog.text = "太好了! 我们现在应该去酒馆找那个走私者。 我不想在这里逗留! ";
				link.l1 = "没问题。 我们走...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // 启用随机事件
			break;
		
		// 酒馆房间里的走私者
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "嘿嘿...看来, " + GetSexPhrase("伙计","姑娘") + ", 你很快就会和他一起下地狱...嘿, 伙计 - 我们把他们俩都宰了! ";
				link.l1 = "你这肮脏的猪! 保护自己! ";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "再次感谢你, " + PChar.name + "。 再见...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "奖励? ! 哦, 当然。 给你" + FindRussianMoneyString(iMoney) + ", 再见...";
				link.l1 = "再见...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// < —任务 "meeting in the cove"
			
		// 给走私者送信件的任务 -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "嘿! 你指望我们相信这种鬼话? ! 伙计们, 抓住这两个该上绞刑架的家伙! ";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // 尝试辩解
			//{
				link.l1 = "军官, 你试图拘留两个无辜的人是犯了一个严重的错误。 相信我, 我不认识那个人, 也不在乎他。 "
				+ " 我确信如果你们拘留两个守法公民, 你们的指挥官肯定会对你不满...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // 监狱
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "嗯...是的, 也许你是对的。 指挥官肯定会对此不满。 你知道吗 - 我们就忘了这件小事吧。 ";
				link.l1 = "谢谢你, 军官, 你为我们节省了时间。 我想请你下次更小心, 你肯定不想被降职, 对吧? ";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "不, 绝不可能。 那样的话, 请散开。 再见...";
				link.l1 = "这样更好! ";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // 不给钱
			{
				dialog.text = "太好了! 现在你可以滚了! ";
					link.l1 = "什么? ! 那钱呢? 我们有交易...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // 钱或巡逻
			{
				if(rand(2) == 1) // 巡逻
				{
					dialog.text = "谢谢你的投递。 现在你可以走了...等等, 有人来了...";
						link.l1 = "什么? ! ";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // 只是给钱
				{
					dialog.text = "太好了。 谢谢你的投递。 给你" + FindRussianMoneyString(iMoney) + "。 记住, 走私者会永远记住好人...";
					link.l1 = "我希望如此。 再见。 ";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // 信件已送达 - 提升走私者的好感度
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // 帮助了走私者 - 降低贵族声望
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // 以免杀死任何人
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "听着... 你和我之间根本没有任何交易。 向和你达成交易的人索要你的钱吧。 ";
				link.l1 = "好吧, 这肯定不是我的幸运日, 我还能说什么呢? ! 好吧, 再见...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear() + "你会为此付出代价的! 准备受死吧! ";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // 没钱离开
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "你竟敢挑战我, " + GetSexPhrase("小子","败类") + "? 好吧, 你肯定不知道什么对你有好处。 我会把你开膛破肚! ";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // 战斗
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // 带钱离开
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar,"GenQuest.ContraDeliver"); // 任务完成 - 属性将被删除
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// < —给走私者送信的任务
			
		// 教会生成器。 任务1。 我们要找的船长对话 -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar,"GenQuest.ChurchQuest_1.CapWaitOnTavern")) // 如果在酒馆等待
				{
					dialog.text = RandPhraseSimple("五百人! 还有一个死人的箱子! 嗝! ", "喝! 嗝! 然后魔鬼就把其他人都解决了 - 嗝! - 剩下的! ");
						link.l1 = "哦... 好吧。 你好, " + GetFullname(NPChar) + "先生。 ";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // 在自己船的甲板上
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "好了, 现在看看... 三块帆布, 船壳用的木板, 更换支架上的轴承和绳索...";
							link.l1 = "你好, " + GetFullName(NPChar) + "先生。 我是" + PChar.name + "船长。 ";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("马上离开我的船, 我有很多事要做, 没你在也行! ", "你已经拿到你的书了, 还想要什么? ! ", "我已经做了你想要的一切, 你还想从我这里得到什么? ! ");
							link.l1 = "别这么激动, 不然你会心脏病发作的! ";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("朗姆酒, 朗姆酒! 给我朗姆酒... 嗝! ", "已经有一段时间了... 嗝... 自从我上次那样喝得酩酊大醉...");
					link.l1 = "是的, 你的船舱满了... 也许是时候前往海湾了? ";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("请坐, 船-嗝-长! 你想喝什么? ", "请坐, 船长! 你想喝什么? 嗝...");
					link.l1 = "谢谢, 但我更喜欢和一个体面的人好好谈谈。 ";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "你是想 - 嗝! - 侮辱我吗? ... 那个酒馆里没有一个体面的人! 嗝! 只有强盗和杀手! 他们都是敲诈者, 而那个... 他们的头目, 喉咙里有一条海鳗! ";
				link.l1 = "我指的是你。 你就是我想交谈的人。 那个强盗头目是谁, 为什么他会...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = " " + GetSexPhrase("先生","女士") + "! 我亲爱的! 你叫什么名字, 再说一遍? 我尊重你! 到目前为止, 还没有人叫一个老水手为体面的人! 我愿意为你做任何事! 我会把我所有的钱都给你, 直到最后一个比索! .. 哦, 忘了。 我没钱了。 我甚至没有任何小钱了。 那个混蛋, 那个敲诈者刚从我这里拿走了最后一张纸, 愿小鬼们在地狱里用他的内脏装炮弹! ";
				link.l1 = "船长先生? 你还好吗? 你意识到你在说胡话吗? 什么纸张? ";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "不, 不! 这个老船长可能喝醉了, 但他仍然保持着清醒的头脑。 这些书和纸张是" + PChar.GenQuest.ChurchQuest_1.ToName + "神父给我的, 我正把它们带到" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "。 早上我去了当地的教堂, 向当地的神父提到了这些书。 当然, 他想看看它们, 你知道他们这种人, 他们对圣徒的生平之类的东西简直是痴迷。 所以, 我派了一个见习水手去拿装着它们的箱子。 当我在等的时候, 我决定赌一把... 不知怎么的, 我输光了所有的钱。 一切! 没有钱付酒钱了! 所以, 酒馆老板把书作为抵押, 然后我也把卷轴给了他...";
				link.l1 = "所以, 你卖了书, 神父" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + "托付给你的圣书? ";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "我知道, 我知道... 我将在地狱里永远燃烧。 我现在既无颜面对给我这个任务的神父, 也无颜面对送文件的人, 也无颜面对当地人... 谁会为我的灵魂祈祷呢? 如果他们把我逐出教会怎么办? 哦, 我真不幸... 我需要喝一杯... ";
				link.l1 = "哇, 放松点, 没那么糟糕。 你的行为很糟糕, 也不虔诚, 但我准备帮助你。 我会偿还你的债务, 买下这些手稿。 此外, 既然我已经认识提到的两位神父, 我会直接航行到" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", 以便把文件送到那里。 成交? ";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "救世主! 上帝的天使... 当然, 我同意! 我会给你一切... 一切! 如果我能再喝一杯就好了...";
				link.l1 = "我想你已经喝够了... 哦, 不管了。 我会从酒保那里再给你买些朗姆酒。 ";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...还有帆! 我们也需要更换帆! .. 哦, 你好。 请不要见怪, " + GetSexPhrase("先生","女士") + "不管你叫什么, 但现在, 如你所见, 我很忙, 所以如果你有什么事找我, 请快点说。 ";
				link.l1 = "据我所知, " + PChar.GenQuest.ChurchQuest_1.ToName + "神父在" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Voc") + "给了你一些圣书。 你答应把它们送到" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", 因为你反正要朝那个方向航行。 "; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "我本来是朝那个方向航行的, 直到那场该死的风暴几乎摧毁了我的旧船, 我被困在这里不知道多久了! 码头的那些骗子一直想把潮水冲上岸的腐烂木板卖给我做船壳, 至于帆, 是一些旧麻袋布, 他们的奶奶年轻时还在上面睡过。 ";
				link.l1 = "先生, 下次我会很乐意听你讲精彩的故事, 但现在我想了解更多关于你在" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + "收到的书籍和手稿的命运。 ";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "没有人, 你听到了吗? 没有人敢指责我延迟交付这些该死的文件! ";
				link.l1 = "哦, 不, 我当然不是那个意思。 我只是想减轻你的负担。 事情是这样的, " + PChar.GenQuest.ChurchQuest_1.ToName + "非常担心要送到" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "的书籍和文件。 实际上, 我现在正要航行到那里。 ";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "在我看来, " + GetSexPhrase("先生","女士") + ", 你每个港口都有一位精神顾问。 不过这不关我的事。 如果你在意那些垃圾, 那就拿上你的书, 滚吧! 太好了! ";
				link.l1 = "谢谢你, 船长先生。 祝你修理顺利。 ";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // 不交出卷轴
		{
			dialog.text = "别担心, " + GetSexPhrase("先生","女士") + ", 轻松地前往" +  XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "吧, 因为是我承担了交付这些文件的任务, 也将是我不惜一切代价去完成, 这样就不会有人在每个角落呼喊" + NPChar.name + "船长没有信守诺言! ";
				link.l1 = "但是船长先生, 重点其实是...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// 给手稿
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// 更改名称。 以后要改回来! 
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // 更改描述。 以后要改回来! 
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // 变量。 以后删除! 
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // 任务完成
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // 三天后删除船长
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "实际上, 重点是我和你根本没有任何业务往来。 神父给了我一个任务, 把书送到" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", 交给当地的神父。 我在那里看不到你。 完全看不到! 祝你好运。 ";
//				link.l1 = "好吧, 那你是一个非常负责任的人, 尽管这是你唯一的优点。 祝你好运, 我无礼的朋友";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // 离开, 相信他
				link.l2 = "我受够了你这种无礼的行为。 你那张笨嘴甚至能逼天使动武。 我必须完成我神父的意愿, 如果必要的话, 我会使用我的武器! ";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // 任务完成, 没有手稿
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // 三天后删除船长
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "安静, 安静, " + PChar.name + "船长! 你怎么了? 哦, 好吧, 我明白如果你不把这些文件带去, 所有那些神父都会对你非常生气, 更不用说我们在天上的父了。 好吧, 拿着你的神学宝物, 带着上帝的祝福去吧。 ";
				link.l1 = "很高兴你不仅理解了我的立场, 还记住了我的名字。 我建议你每次打算做蠢事的时候都记住它。 ";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // 离开, 相信他
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar,"Bible", 1);	// 给手稿
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// 更改名称。 以后要改回来! 
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // 更改描述。 以后要改回来! 
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // 变量。 以后删除! 
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // 任务完成
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // 三天后删除船长
			break;
			
		// < —教会生成器。 任务1。 我们要找的船长对话
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("滚开...", "别打扰我! ");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear() + "你不该那么说! 现在我得把你送到上帝那里, 为我的罪孽祈祷! ";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear() + "你不该那么说! 现在我得把你送到上帝那里, 为我们的罪孽祈祷! ";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear() + "你不该那么说! 现在我得把你送到上帝那里, 为我们所有的罪孽祈祷! ";
			}
			
				link.l1 = "不太可能, 伙计。 每个人都要自己向上帝负责! ";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "嘿, 为什么骂人? 如果我有事情要和你谈呢。 ";
				link.l1 = "这倒是新闻! 你知道, 我和你这种人说话很简短! ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "好吧, 我也不打算和你长谈。 但是, 也许你有兴趣以一个好价格买几件小饰品? ";
				link.l1 = "我看起来像一个该死的赃物收购者吗? ! ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "冷静, 冷静, 我们中间没有小偷! 这个花瓶是给我们诚实工作的! 看看... 纯金的, 镶嵌着珍珠。 但问题是我们不需要它。 所以我们只是想卖掉它, 分钱。 ";
					link.l1 = "让我仔细看看... 哦, 我的天! 这是圣餐杯! ! 所以, 你们就是那些亵渎" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "教堂的人? ! 你们在这里! ";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "安静, " + GetSexPhrase("先生","女士") + "伪君子! 你知道, 我们有点缺钱, 所以我们决定卖点东西。 看看这个花瓶... 纯金的, 镶嵌着珍珠。 给你特价, 比如说, 一千枚硬币。 ";
				link.l1 = "让我仔细看看... 哦, 我的天! 这是圣餐杯! ! 所以, 你们就是那些亵渎" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "教堂的人? ! 你们在这里! ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "等等, " + GetSexPhrase("先生","女士") + "! .. 该死, 我告诉那个笨蛋在时机成熟之前不要大惊小怪...";
				link.l1 = "你在胡说八道什么? 好吧, 做出你的选择: 要么你心甘情愿地把偷来的赃物给我, 要么我就叫卫兵。 ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "听着, " + GetSexPhrase("好人","小姐") + ", 我们不需要任何争吵, 所以让我们和平解决这个问题。 你必须相信我们, 我们实际上并没有抢劫那个教堂, 我们也没有任何钱。 是的, 我们因为模仿抢劫收到了几比索和那个黄金饰品。 而这个黄金杯子是我们在付给走私者之后剩下的唯一东西...";
				link.l1 = "所以, 你是想说...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "那个该死的神父雇佣了我们, 我就是这个意思! 但他为什么要把你送到我们这里来? .. 好吧, 我们现在扯平了。 拿着这个花瓶, 给那个伪君子看看, 你会看到他像浅滩上的鱿鱼一样扭动! ";
				link.l1 = "把杯子给我, 然后在我改变主意之前滚开。 ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "你说得很流畅, 但我没那么容易上当。 如果你想说服我, 那就先说服我的刀刃。 ";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// 这里如果有的话给杯子
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// 允许生成遭遇战, 打开出口
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear() + "我没告诉那些混蛋吗: 收起你们贪婪的爪子, 除了神父的钱什么都不要拿! ";
			}
			else
			{
				dialog.text = RandSwear() + "我没告诉那些贪得无厌的混蛋吗: 收起你们贪婪的爪子, 除了神父的钱什么都不要拿! ";
			}
			
					link.l1 = "你在胡说八道什么? 好吧, 做出你的选择: 要么你心甘情愿地把偷来的赃物给我, 要么我就叫卫兵。 ";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "我做出了不同的选择, 你闭上你喋喋不休的嘴, 把你的钱包给我, 我就饶你一命。 ";
				link.l1 = "我现在就帮你去见我们的主! ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "好吧, 我会给你一些钱, 但只是出于我自己的意愿, 这样你和你的朋友就可以过诚实的生活, 不必自甘堕落去抢劫。 ";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "嗯... 好吧, 让我们把分歧放在一边, 回到我们谈话的开头。 那么你想要多少钱买那个东西? ";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// 别忘了杯子! 
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(pchar,-sti(PChar.money)/2); // 拿走一半的钱
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // 完全失败的选项。 什么都没留下
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "我也不需要任何麻烦, " + GetAddress_Form(pchar) + ", 但现在价格已经更高了。 对于那个珍贵的杯子, 我需要你身上所有的钱。 ";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "你这个贪婪的混蛋! 我身上只有" + FindRussianMoneyString(iMoney) + "。 拿着它, 滚吧! ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "错误的选择, 贪婪的老鼠。 你不会占我的便宜! " + GetSexPhrase("我像风一样自由 - 现在在这里, 第二天在那里, 今天我很穷 - 明天我会富有...","") +"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// 给杯子
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // 别忘了更改对话。 
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "你是不是想说, 特别是今天" + GetSexPhrase("你很穷","你没有钱") + "? ! ";
				link.l1 = "正是, 我贪婪的朋友, 让你大失所望。 现在我必须告辞了, 我有很多事情要做。 ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "停下! 我们要检查一下, 如果你没有说真话, 我会把你说谎的舌头放进蚁群里! ";
				link.l1 = "说了那句话你就完了! ";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// 可以这个案例 - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// 主角可以说是搜查尸体并拿走所有赃物...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("作为一个真正的绅士, 我是诚实的","我是诚实的"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// 生成器 "无人岛上的海盗"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "哦, 没什么好决定的。 我们可以自己决定一切。 但我们会拿走你的船, 离开这里。 ";
			link.l1 = "有一个条件, 首先你得把我的刀从我这里拿走...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "你好, 船长! 显然, 天意亲自派你来拯救" + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + "和他的兄弟们。 我们在这里急需帮助。 " +
					"我们的" + GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name)) + "在风暴中撞上了当地的礁石, 海浪把幸存的船员冲到了岸上。 " +
					"在" + (5 + hrand(7)) + "周里, 我们一直凝视着地平线, 希望看到一艘来救我们的船的帆。 ";
				link.l1 = RandPhraseSimple(RandPhraseSimple("是的, 那是个不幸的命运。 但这就是水手的命运, 任何人都可能落到你们的处境。 ", "我明白... 上帝掌握着每个人的生命, 只是他太忙了, 记不住每个人。 "),
					RandPhraseSimple("确实。 谋事在人, 成事在天。 ", "是的, 那肯定是运气不好。 "));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "这很严重! 那个恶棍" + PChar.GenQuest.PiratesOnUninhabited.BadPirateName + "除了把" + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + "留在无人岛上, 像一只破旧的狗一样, 想不出别的惩罚! " +
					"他希望太阳和口渴会把我们烤干, 就像渔夫摊位上的干鲭鱼一样! 但他错了, 因为天意站在我们这边, 因为它派你来救我们...";
				link.l1 = RandPhraseSimple("别这么快, 朋友。 据我所知, 你们是自由职业者, 你们到这里来不是偶然的。 ", "已经在谈论救赎了? 据我了解, 你们到这里来是因为一些特殊的成就。 ");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("船长, 请做个好心人, 帮助" + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + "个贫困的人。 你是我们唯一的希望, 除了我们最仁慈的主。 ",
				"船长, 你的船上有足够的储物柜给" + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + "个贫困的人吗? ");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "哦... 你想让我把你带到哪里去? ";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("我真的很抱歉, 但甚至没有一个空闲的吊床, 更不用说客舱了。 水手们睡在甲板上, 他们甚至不能在值班后好好睡一觉...",
				"我真的不想让你失望, 但船超载了, 人们不得不在恶劣的天气里睡觉。 如果爆发疾病, 我会失去一半的船员。 "),
				RandPhraseSimple("我真的很抱歉, 但我的船上绝对没有多余的船员空间。 我不能再搭载任何乘客了。 ", "我不得不让你失望, 但我的船挤满了船员。 我担心流行病..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "你是一个经验丰富的水手, 你应该知道, 有遭遇海难的人在场是一个非常坏的迹象。 我的水手们只会把你们都扔到海里。 ";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "嗯... 你知道, 由于几个原因, 我们想尽可能远离当局... 请把我们送到有人居住的岛屿或大陆上的任何海湾, 然后我们就可以自己谋生了。 ";
			link.l1 = "好吧, 我有足够的空闲储物柜和吊床。 把自己装进船里。 ";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "嗯... 运气不好... 我们前面有战斗, 我不知道你们在哪里更安全, 在我的船上还是在这个舒适的海湾里。 ";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "哦, 船长! 现在是连和妻子同床都不能感到安全的时候了, 哈哈, 在海上就更不安全了... 看看这些暴徒, 他们每个人都准备赤手空拳对抗大炮。 他们根本不渴望安全和舒适, 你可以从他们的脸上看出来! ";
			link.l1 = "从他们的脸上, 我只能看到愿意背叛他们愚蠢的恩人的意愿。 ";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "嗯... 实际上, 这是个好主意。 告诉我, 朋友, 你的暴徒愿意在我的船员中服役吗? ";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "真遗憾, 船长... 我看我们不能友好地解决这个问题。 我想我得提醒你海上的规矩。 记住, 当谈到登船时, 我们不输给任何人...";
			link.l1 = "好吧, 现在我终于可以看到你们的真面目了...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// 把他们招入队伍
		case "PiratesOnUninhabited_8":
			dialog.text = "但当然! 他们会很高兴成为你登船队的一部分! 除了戴维.琼斯本人, 没有人能在战斗中击败他们! 哈哈哈! ";
			link.l1 = "好吧, 那就把你们自己装进船里...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("你的船员增加了" + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "人。 ");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // 取消离开地点的中断
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// 任务结束
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "谢谢你, 船长! 装载应该不会花太多时间。 上帝啊, 我们祈祷这一刻的到来! ";
			link.l1 = "很好, 那么。 ";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// 把他们当乘客 - 航向有人居住的岛屿
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("你的船员增加了" + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "人。 ");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // 取消离开地点的中断
			
			AddPassenger(PChar, NPChar,false); // 把主角当乘客
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: 需要分开, 否则会得到遭遇海难的双桅帆船
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// < —belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: 需要分开, 否则会得到遭遇海难的双桅帆船
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// < —belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("你为什么磨磨蹭蹭, 船长? 下令起锚。 ", "对不起, 船长, 但我们必须准备起航。 ", "我们真幸运, 你决定来这里! ");
			link.l1 = "快点。 船不会等任何人。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// 已经在另一个海湾的集市上, 有人居住的岛屿
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// 任务成功完成 - 会给奖励
				dialog.text = "谢谢你, 船长。 事实上, 我们相信自己的运气是对的... 请接受这颗宝石, 我在那个不幸的海湾找到的。 我希望它能给你带来好运。 ";
				link.l1 = "我没想到会有这样的礼物。 ";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// 索要钱财
				dialog.text = "船长, 请不要认为我们太无礼, 但我们真的很缺钱。 你知道, 我们失去了所有的一切。 你能借给我们几大把比索吗? 我们肯定会还你的... 当机会出现时...";
				link.l1 = "哇! 确实, 无礼是没有限度的。 好吧, 在我已经做了所有事情之后, 我现在能为你做的唯一事情就是不向当局举报你们。 ";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "你不是在开玩笑吧... 你想要多少? ";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// 任务结束
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("谢谢你, 船长。 ", "船长, 我们非常感谢你。 ", "我们会为你祈祷, " + PChar.name + "船长! ");
			link.l1 = "祝你好运。 再见...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "呵呵, 船长... 你知道, 我们相处得很好... 杀死你真的很可惜...";
			link.l1 = "你可以试试! ";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// 任务结束
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "好吧, 说, " + iMoney + "比索给我们每个人就很好了... 当然, 如果你不认为这个对我们所有痛苦和苦难的补偿太少了, 呵呵...";
			link.l1 = RandPhraseSimple("相反, 我确信这太多了... 给你们每个人脖子上套个绞索是最好的。 ", "我会亲自为了这么多钱把你们像猿猴一样挂在棕榈树上! ");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "好吧, 拿着。 我希望我不再欠你们任何东西了? ";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "多么慷慨! 老实说, 我之前就在想, 你已经有机会见识到我们总是能得偿所愿。 而这次我们也不会退缩... ";
			link.l1 = "你可以试试! ";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "哦不, 船长, 您在说什么? ! 如果我们哪天进教堂, 肯定会为您点一支蜡烛... 哈! ";
			link.l1 = "希望如此... ";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // 在尸体上保存物品
			NPChar.DontClearDead = true;  // 200秒后不清除尸体
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// 任务结束
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// 玩家撒谎 - 有空闲位置
				dialog.text = "哦不, 船长, 您在说什么? ! 如果我们哪天进教堂, 肯定会为您点一支蜡烛... 哈! ";
				link.l1 = "希望如此... ";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "嘿, 船长, 您知道, 这不算什么大问题。 我和我的兄弟们愿意在您的船上腾十几个吊床出来, 给那些现在占着位置的人... ";
				link.l1 = "嗯... 这听起来像威胁... ";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "好吧, 实际上, 这就是威胁。 我需要您的船, 不管您同不同意, 我都要离开这个地方! ";
			link.l1 = "好吧, 现在我终于看清你到底是什么人了... ";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "我理解您, 船长。 我完全理解您... 谁会想照顾那些一直求着被绞死的可怜海盗呢? ... 但是... 如果我跟您做个交易呢? 您把我们送到有人居住的岛屿或大陆的任何一个海湾, 我就给您一张藏宝图。 我们成交吗? ";
			link.l1 = "嗯... 您怎么保证这张地图不是伪造的? ";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "哈, 我敢肯定您的地图就跟画它的那张纸一样值钱... ";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "好吧... 您让我们别无选择... 不过, 不管您同不同意, 我们都要离开这个地方! ";
			link.l1 = "好吧, 现在我终于看清你到底是什么人了... ";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "那您又怎么保证不会在最近的港口把我们交给当局呢? 我们都在摸黑出牌... ";
			link.l1 = "好吧, 成交。 ";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// 已经在另一个有人居住岛屿海湾与首领的集市。 我们被承诺藏宝图的情况
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - 属格形式的名字
			
			dialog.text = "谢谢您, " + PChar.name + "船长。 您已经履行了承诺, 现在该" + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_DAT) + "履行我的承诺了。 我身上没带地图, 但我会告诉您宝藏在哪里。 去那个海湾... ";
			link.l1 = "哦, 现在您这么说了! 我看您从一开始就打算骗我... ";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "我一开始就知道您不可信... ";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "这就是相信海盗的下场。 你们是什么样的人? 对你们来说没有什么是神圣的! ";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "别大惊小怪... 我不是圣人, 但我说话算数! ";
			link.l1 = "您还指望我再相信您一次? 好让明天整个群岛都嘲笑我? ";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "嗯... 看来无法和平解决了。 但天知道, 我并不想这样... ";
			link.l1 = "拔出你的剑, 否则我就像碾死老鼠一样碾碎你! ";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// 任务结束
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "那我还能怎么做? 跟我的兄弟们待在那个臭水坑里等死吗? 您最好听我说... " + XI_ConvertString(sTitle + "Gen") + "的" + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + "船长在那里有个藏匿赃物的地方。 但要小心" + GetSexPhrase("","") + ", 他经常去那里。 只要你保持警惕, 找到藏匿处并不难... "; // belamour gen
			link.l1 = "您还指望我再相信您一次? 好让明天整个群岛都嘲笑我? ";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "好吧。 但如果您再耍我一次, 我会找到您。 ";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// 宝藏计时器。 10天后宝藏里会有各种破烂等
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// 航向海盗所说的海湾。 我们有10天期限, 过期宝藏会消失
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("听" + sTemp + "说, 他说得有道理。 ", "别生" + sTemp + "的气, 他只是别无选择。 ", "谢谢您, 船长。 ");
			link.l1 = "祝你们好运... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "那我还能怎么做? 跟我的兄弟们待在那个臭水坑里等死吗? 您最好听我说... " + XI_ConvertString(sTitle + "Gen") + "的" + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + "船长在那里有个藏匿赃物的地方。 但要小心, 他经常去那里。 只要你保持警惕, 找到藏匿处并不难... "; // belamour gen
			link.l1 = "您还指望我再相信您一次? 好让明天整个群岛都嘲笑我? ";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// 宝藏海湾的海盗
		case "PiratesOnUninhabited_34":
			dialog.text = "你是谁, " + GetSexPhrase("伙计","姑娘") + "? 是什么风把你吹到这个荒凉地方来的? ";
			link.l1 = "我停下来补充淡水。 ";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "我是代表" + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + "来的。 ";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "你选了个糟糕的地方... 好吧, 慢慢来。 ";
			link.l1 = "啊哈... ";
			link.l1.go = "exit";
			link.l2 = "你算哪根葱, 敢告诉我该怎么做? ";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "我告诉每个人该怎么做。 那些自以为聪明的人会被挂在棕榈树上。 ";
			link.l1 = "我会割掉你的舌头, 杂种。 ";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "那他为什么不自己来? ";
			link.l1 = "他不想来, 留在" + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen")) + "等我。 "; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "那个老无赖! 他又想耍我们, 不是吗? 这可不行。 告诉他, 他只能和我们一起拿钱! ";
			link.l1 = "他告诉我, 没拿到钱就别回来, 也不要带任何人上船... ";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "好吧, 如果你这么信任他, 你可以留在这里。 但我们会拿走你的船。 你的钱, 前往" + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen")) + "。 我们迫不及待想看看" + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + "的脸色。 "; // belamour gen
			link.l1 = "如果你这么想念他, 可以游过去... 或者死在这里。 ";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// 来自PiratesOnUninhabited_3的分支
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "你是个精明的人。 但请允许我向你保证, 我们与" + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL) + "船长的冲突纯粹是意识形态上的。 我警告过他, 他的肮脏勾当总有一天会受到惩罚, 现在我和我的" + iBanditsCount + "个兄弟正因为对上帝和正义的热爱而受苦。 ";
			link.l1 = "是这样吗... 我打赌你们才是叛乱的真正煽动者, 你们罪有应得。 ";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "当然... 不过, 听听" + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + "船长本人对你们分歧的看法会更好。 ";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "船长, 您为什么要用不信任来冒犯诚实的人呢? 看看他们的脸... 您真的认为他们是叛乱者吗? 他们谦逊得不能再谦逊了... 但在正义事业的良好指挥下, 他们在战斗中不输任何人! 我可以亲自为他们每个人担保。 ";
			link.l1 = "好吧, 但我现在该怎么处理你们? ";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "随你便。 由你决定, 把我们带到定居点, 或者让我们加入你的船员, 在我看来你是个好船长。 ";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "好吧, 我让你们加入我的船员。 但别耍花样! 我的船上纪律严明! ";
				link.l1.go = "PiratesOnUninhabited_9"; // 加入队伍
			}
			
			link.l2 = "我不带你们去任何地方。 我的船员里已经有足够多的暴徒了。 ";
			link.l2.go = "PiratesOnUninhabited_24"; // 冲突和任务结束
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "好吧, 上小船, 我带你们去某个地方。 ";
				link.l3.go = "PiratesOnUninhabited_11"; // 作为乘客去岛上
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("我发誓, 船长, 您不会后悔的。 ", "您做了正确的选择, 船长。 ", "船长, 请放心, 您和我们一样幸运! ");
			link.l1 = RandPhraseSimple("希望如此。 ", "快点。 船不会等任何人。 ");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "这很容易安排。 他驾驶着" + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name + "Voc")) + "‘" + sTitle + "’, 从事奴隶贸易... 我们这样办: 如果我们找到他, 货物归你, 船归我们。 哦, 你还可以问问他是否认识" + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + "。 我希望他听到这个名字时不会吓破胆, 因为那是我的船... "; // belamour gen
			link.l1 = "好吧, 成交。 ";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // 离开时从位置移除   从NPChar修正为rChar - 樵夫
				rChar.location.locator = ""; // 樵夫  - 同样修正。 这样就不会有错误了。 
			}
			
			Log_Info("你的船员增加了" + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "人。 ");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // 主要人物作为乘客
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // 樵夫稍后为强盗选择外观。   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // 移除离开位置的中断
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour 按人数结束
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "名水手");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "名水手");
			}
			// < —belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + "'" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // 将船放在地图上
			
			DialogExit();
		break;
		
		// 船长室与船长的对话
		case "PiratesOnUninhabited_46":
			dialog.text = "你到底想从我这里得到什么? ";
			link.l1 = "我代表" + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + "来问好。 我想你认识他吧? ";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // 从全局移除
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "真遗憾, 我之前没勒死那个无赖。 好吧, 看来是时候为我的仁慈付出代价了... ";
			link.l1 = "确实... 而且时间刚刚到了... ";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // 重要方法
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "干得好, 船长! 那么一切按约定来? 我们得到船, 你得到货物? ";
			link.l1 = "当然。 把船开走, 好好利用它。 ";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // 从船长室移除
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + "'" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// 在甲板上, 当我们的海盗船被释放时
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "问候您, " + PChar.name + "船长。 ";
			link.l1 = "那么, 你觉得你的船怎么样? ";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "嘿... 它像我一样吱呀作响。 我想我们俩在公海上航行的时间都不多了... ";
			link.l1 = "祝你好运... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// 在海湾, 需要夺取的船被击沉的情况
		case "PiratesOnUninhabited_51":
			dialog.text = "你为什么沉了我的船? ! 你还记得我们的约定吗? ";
			link.l1 = "什么, 我不想让他先沉了我。 你没看到我勉强才活下来吗? ";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "哪有人这样打仗? 你损失了这样一艘船! 该死的! 像你这样的孩子在这里做什么? ";
				link.l1 = "我会割掉你的舌头, 杂种。 ";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "哪有人这样打仗? 你损失了这样一艘船! 你知道这对我来说值多少钱吗? " + FindRussianMoneyString(iMoney) + "! 你现在欠我了... ";
				link.l1 = "这对你来说是不是太多了? 别忘了我已经帮过你一次了。 ";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "愿你和那艘该死的船一起下地狱! 拿上你的钱, 别再出现在我眼前! ";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + "'" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "现在那对你有什么好处? ! 如果" + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM) + "船长现在和我的船一起沉在海底了! 现在我既没拿到我的那份, 也没拿回我的船! 这是什么命运啊, 像个流浪汉一样死在阴沟里! ! ! ";
			link.l1 = "但为什么呢? 我可以为你安排一场壮观的葬礼。 就在这里, 如果你愿意的话... ";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + "'" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// 结束
		
		// 战船, 15.05.11。 生成"正义可售"。 
		case "JusticeOnSale_1":
			dialog.text = "我想我们或许... 可以达成某种协议? 如果你帮我们一个忙, 我们会回报的, 嘿嘿。 ";
			link.l1 = "帮忙? 什么交易, 你又能提供什么作为回报? ";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "我们的" + PChar.GenQuest.JusticeOnSale.SmugglerName + "船长被" + XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen") + "的当地巡逻队抓住了。 他们把他关了起来, 但没有足够的证据绞死他。 我们自己无法把他救出来\n" +
				"你是个受人尊敬的人。 大家都认识你。 也许你可以去谈判。 保释或者干脆把他买出来? 相信我们, 一旦救回人, 我们就会离开这个岛, 这样你的声誉也不会受损! "; // belamour gen
			link.l1 = "假设我能帮你。 但我的报酬呢? ";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "见鬼去吧, 恶魔的后代! 我不会和你们有任何交易! ";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "你想要几件印第安小饰品和护身符吗? 它们相当稀有... 或者你更喜欢当场付现金? 我觉得几千比索怎么样? ";
			link.l1 = "见鬼去吧, 恶魔的后代! 我不会和你们有任何交易! ";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "我对印第安小饰品感兴趣。 我想我同意。 ";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "现金是水手最好的朋友。 众所周知, 金钱没有臭味。 我同意。 ";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // 小饰品。 
			dialog.text = "谢谢您, 船长。 除了您的报酬, 我们还会补偿您保释金。 我想您应该和指挥官谈谈我们的船长。 也许您能说服他。 一旦您把他救出来, 就到" + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + "来, 我们的船就停泊在那里 —" + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + "‘" + PChar.GenQuest.JusticeOnSale.ShipName + "’。 我们会在岸边等您。 "; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // 金钱。 
			
			dialog.text = "谢谢您, 船长。 除了您的报酬, 我们还会补偿您保释金。 我想您应该和指挥官谈谈我们的船长。 也许您能说服他。 一旦您把他救出来, 就到" + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + "来, 我们的船就停泊在那里 —" + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + "‘" + PChar.GenQuest.JusticeOnSale.ShipName + "’。 我们会在岸边等您。 "; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// 报酬是小饰品。 
					dialog.text = "我们到了, 船长! 您干得真棒, 骗了这些大腹便便的官僚! 这是您的报酬。 伙计们, 把小饰品拿来! ";
				}
				else
				{
					// 报酬是金子。 
					dialog.text = "我们到了, 船长! 您干得真棒, 骗了这些大腹便便的官僚! 这是您的报酬。 伙计们, 把箱子拿来! ";
				}
				
				link.l1 = "把我的那份给我, 然后滚蛋! ";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// 大屠杀。 
				dialog.text = "我们到了, 船长! 我看您安排得很好。 但您知道... 我们不需要任何目击者, 所以... 伙计们, 谢谢船长! ";
				link.l1 = RandSwear() + "我当初遇到你时就该毙了你! ";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour 不速之客-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("你是谁? 为什么闯进我的房间? ","哇。 你是谁? 这当然是我的房间, 但我不介意这样的陪伴。 这是爱的投递吗? ")+"";
			link.l1 = ""+GetSexPhrase("不再是你的了。 客栈老板把房间租给了我, 既然你没付钱, 你就该出去了。 现在我们可以轻松解决, 也可以硬来。 你自己选。 ","你在做梦。 在我们这种情况下, 这是清理。 所以把你自己从这里清理出去。 现在这是我的房间, 因为不像你, 我总是付客栈老板钱。 ")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("我想我听说过你。 好吧, 你赢了, 我走, 我还想活... ","嗯, 我听说过很多关于你的事。 我想不只是你的舌头很厉害。 好吧, 别生气, 房间是你的了。 ")+"";
				link.l1 = ""+GetSexPhrase("你做了个正确的决定。 ","好孩子。 ")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("原来是这样啊? 好吧, 我选择硬来。 ","你这个婊子! 我本来想和你好好相处的... ")+"";
			link.l1 = ""+GetSexPhrase("如你所愿... ","你这也叫‘好好相处’? 我真为你感到遗憾。 不过, 也许不必。 ")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //允许战斗
			chrDisableReloadToLocation = false; // 打开位置
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("好吧, 好了, 住手! 别杀我。 我走。 ","住手! 我们现在该怎么办, 为了这个房间互相残杀吗? 噎死你, 都给你了。 臭家伙... ")+"";
			link.l1 = ""+GetSexPhrase("正确的决定。 下次用用脑子: 不是每个人都像我这么善良, 他们可能会不小心杀了你。 ","男人。 ")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //允许战斗
			chrDisableReloadToLocation = false; // 打开位置
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("嗯, 你把我赶走了吗? 在我割了你之前离开这里。 ","所以你只会喋喋不休。 庆幸我现在心情还不错, 否则我会对你做更糟的事。 滚出去! ")+"";
			link.l1 = ""+GetSexPhrase("该死的... ","该死, 我低估你了... 好吧, 好吧, 我现在就走。 ")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //允许战斗
			chrDisableReloadToLocation = false; // 打开位置
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // 如果午夜战斗失败
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// < —belamour постоялeц
		
		// belamour 醉酒水手 -->
		case "GuiltySailor":
			dialog.text = "啊? ..滚出去, 新手, 我不喝酒....嗝! ..和任何人。 ";
			link.l1 = "我现在就狠狠揍你, 让你接下来一周都喝不了酒。 ";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "什么? ! 你知道你在和谁说话吗? 我是‘"+pchar.ship.name+"’号船上的水手! 我只要告诉船长, 你连出城的时间都没有! 趁你还完好无损的时候滚出去。 "; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "船长? ..";
			link.l1 = "你将擦洗甲板一个月。 ";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "对不起, 船长! ";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// < —醉酒水手
		
		// belamour 优秀专家 -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "问候船长! 我知道你是船长, 是的。 ";
			link.l1 = "问候。 你怎么知道我是船长? ";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // 水手
			dialog.text = "哈, 我是经验丰富的海狼, 我在海上航行了十多年。 我主要从事航行工作: 在平静中航行, 在风暴中航行, 在小帆船甚至战舰上航行。 事实上, 上个月我在一场艰苦的战斗后受伤了, 当时有一场强烈的风暴, 没有人敢爬上去张帆, 所以我做了, 但我为此付出了代价, 幸运的是我只是扭伤了脚踝, 几周不能走路。 所以他们把我遣散到岸上。 现在我好多了, 坐在这里等待机会。 ";
			link.l1 = "有趣。 我不介意在这件事上有个专家。 你想加入我的团队吗? ";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "为什么不呢? 我已经开始想念船甲板和充满新风的帆的声音了。 如果需要, 我还可以指导你的团队。 但我会立即向你要一千比索, 否则我的口袋已经空了。 然后, 就像团队的其他成员一样。 我是个诚实的人。 ";
			link.l1 = "不, 我可能会拒绝。 如果所有水手雇佣都要付一千比索, 我会破产的。 别怪我。 ";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "成交。 我不介意给一个好专家一千比索。 拿着...这里。 我在船上等你。 ";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // 炮手
			dialog.text = "哈, 我是经验丰富的海狼, 我在海上航行了十多年。 我主要站在大炮旁边: 用隼炮。 卡隆炮。 长重炮。 蛇炮射击...在小帆船甚至战舰上服役过。 事实上, 上个月我在一场艰苦的战斗后受伤了, 葡萄弹的跳弹击中了我, 不严重, 只是腿上的一个划痕, 所以他们把我遣散到岸上。 现在我好多了, 坐在这里等待机会。 ";
			link.l1 = "有趣。 我不介意在这件事上有个专家。 你想加入我的团队吗? ";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "为什么不呢? 我已经开始想念炮甲板。 火药燃烧的气味和大炮齐射的轰鸣声了。 如果需要, 我还可以指导你的团队。 但我会立即向你要一千比索, 否则我的口袋已经空了。 然后, 就像团队的其他成员一样, 我是个诚实的人。 ";
			link.l1 = "不, 我可能会拒绝。 如果所有水手雇佣都要付一千比索, 我会破产的。 别怪我。 ";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "成交。 我不介意给一个好专家一千比索。 拿着...这里。 我在船上等你。 ";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // 士兵
			dialog.text = "哈, 我是经验丰富的海狼, 我在海上航行了十多年。 我主要在登船战斗中作战: 我与海盗和正规军作战, 我知道如何使用各种武器, 曾在小帆船甚至战舰上服役。 事实上, 上个月我在一场艰苦的战斗后受伤了, 只是背上的一个小军刀划痕, 那个懦夫不敢面对我, 但我反过来杀了他, 哦, 你应该看看他们看到划痕时的表情, 哈哈。 所以, 他们把我遣散到岸上。 现在我好多了, 坐在这里等待机会。 ";
			link.l1 = "有趣。 我不介意在这件事上有个专家。 你想加入我的团队吗? ";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "为什么不呢? 我已经开始想念军刀的声音。 船只侧面碰撞的噼啪声和战斗的肾上腺素了。 如果需要, 我还可以指导你的团队。 但我会立即向你要一千比索, 否则我的口袋已经空了。 然后, 就像团队的其他成员一样, 我是个诚实的人。 ";
			link.l1 = "不, 我可能会拒绝。 如果所有水手雇佣都要付一千比索, 我会破产的。 别怪我。 ";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "成交。 我不介意给一个好专家一千比索。 拿着...这里。 我在船上等你。 ";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "海上好运, 船长! ";
			link.l1 = "你也是。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// < —优秀专家
		
		//belamour 夜间冒险家 -->
		// 水手 -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "你-你是谁? ";
			link.l1 = "我是船长 "+ GetFullName(pchar)+"。 ";
			if (pchar.id == "Knippel")
			{
				link.l1 = "抱歉, 伙计, 我很匆忙。 ";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // 到酒馆
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // 骗子
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // 到码头
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // 碰撞
			}
		break;
		// 到酒馆 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "船长? ..嗝! 船-船长...护送我到酒-酒馆...嗝! ..嗯? 求你了。 好像...我在这个殖-殖民地迷路了, 是的...嗝! ..";
			link.l1 = "放开我, 我没时间! ";
			link.l1.go = "NightAdventure_End";
			link.l2 = "好吧, 走吧。 你看起来自己到不了那里。 ";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "只是...嗝! ..请...慢...一点。 我...嗝! ..不能...站...稳...";
			link.l1 = "好吧, 走吧, 慢点。 ";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // 慢-慢-慢地 ))
			bDisableFastReload = true; // 步行
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // 更新为步行
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // 用于选择对话
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// 骗子
		case "NightAdventure_Sailor_2_1":
			dialog.text = "船长? ..嗝! ..船-船长...救救我! ";
			link.l1 = "放开我, 我没时间! ";
			link.l1.go = "NightAdventure_End";
			link.l2 = "你怎么了? ";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "那里...在酒馆...嗝! ..老千! ";
			link.l1 = "好吧, 那有什么问题? 任何殖民地的任何酒馆都有老千, 像泥土一样。 ";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "船-船长, 你...不明白...嗝!...他让我...身无分文! 嗝! ..然后...把我赶走...嗝! ..";
			link.l1 = "那么, 你现在想从我这里得到什么? ";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "跟我来...嗝!...对付他! 让...嗝! ..他把我的钱还给我! 嗝! ..";
			link.l1 = "不必是老千也能在牌桌上打败一个醉汉。 下次少喝点。 ";
			link.l1.go = "NightAdventure_End";
			link.l2 = "好吧, 我为什么需要这个, 嗯? ..好吧, 走吧, 看看你的老千。 ";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "只是...嗝! ..请...慢...一点。 我...嗝! ..不能...站...稳...";
			link.l1 = "好吧, 我们慢慢走。 ";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // 慢-慢-慢地 ))
			bDisableFastReload = true; // 步行
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // 更新为步行
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // 用于选择对话
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// 酒馆中与水手的对话
		case "NA_SailorTavern":
			dialog.text = "船-船长...嗝! ..非常感谢...帮了我! 我...给你...嗝! ..这是给你的。 ";
			link.l1 = "得了吧, 没关系...别再这样喝酒了。 或者至少不要寻找冒险。 ";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar,"slave_01");  Log_Info("你收到了鱼叉");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar,"potion5");   Log_Info("你收到了姜根");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar,"cartridge"); Log_Info("你收到了纸弹药筒");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar,"amulet_8");  Log_Info("你收到了护身符'锚'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar,"amulet_9");  Log_Info("你收到了护身符'圣像徽章'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar,"obereg_7");  Log_Info("你收到了护身符'渔夫'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar,"obereg_11"); Log_Info("你收到了护身符'朝圣者'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// 谈论骗子
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "船-船长! ..那...嗝! ..老千! ..";
				link.l1 = "谁, 我? 老千? ";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "他在那里, 船长! 嗝! ..坐-坐在桌子旁...";
				link.l1 = "来吧...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// 骗子逃跑了
		case "NA_SailorGamblerBelka": 
			dialog.text = "不...嗝!...骗子!...他不见了!...";
			link.l1 = "好吧, 他走了, 所以没等你。 ";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "那...下...下一步是什么? 嗝! ..";
			link.l1 = "好吧, 你现在什么也做不了。 我绝对不会在夜里整个殖民地找他。 别再这样喝酒了。 或者至少不要在喝醉时赌博。 ";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// 骗子留在酒馆
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// 与骗子本人的对话
		case "NightAdventure_CardProf":
			dialog.text = "我建议玩骰子游戏。 你加入吗? ";
			link.l1 = "没门。 我是这艘船的船长, 我不跟老千玩。 但如果你不把钱还给那边那个好人, 我可以轻易打垮你。 ";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "跟老千玩? ! 我是老千吗? 把钱还给谁, 那个醉汉? ! 你冒犯我了, 船长...";
			link.l1 = "我可以冒犯更多。 把钱还回来。 ";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "是的, 我不是老千! 我是公平的玩家。 运气赢了, 你的朋友只是运气不好, 就这样。 ";
			link.l1 = "运气, 嗯? 把你的骰子给我, 我看看它会有多幸运。 ";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // 给了钱
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "好吧, 好吧, 放轻松, 船长。 嗯, 我打败了那个醉汉, 我也稍微骗了一下, 每个第二个玩家都这么做。 这是他的钱。 ";
				link.l1 = "那更好。 我希望你明白, 如果我的朋友现在说这不是全部金额, 那么我会回到你这里? ";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // 公平游戏
			{
				dialog.text = "是的, 请, 这是我的骰子。 两套。 检查。 我没什么可隐藏的。 ";
				link.l1 = "那么... 对子... 没什么... 对子... 葫芦... 没什么... 没什么... 两对... 三条... 没什么... 对子...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // 打架
			{
				dialog.text = "是的, 请, 这是我的骰子。 两套。 检查。 我没什么可隐藏的。 ";
				link.l1 = "那么... 四条... 四条... 葫芦... 葫芦... 四条... 同花顺... 葫芦... 同花顺... 四条... 葫芦... 嗯, 你将如何向我解释这个? ";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// 和平解决
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "我明白一切, 这是全部金额。 祝你和你的朋友好运。 ";
			link.l1 = "你也是。 ";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// 水手拿回他的钱
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "但...他不-不想承认! 嗝! ..";
			link.l1 = "是的, 他我试图逃避。 这里, 拿着你的钱。 ";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "船-船长...嗝! ..非常感谢...帮了我! 我...'在旁边呕吐'...给你...嗝! ..这是给你的。 ";
			link.l1 = "得了吧, 呃...没关系...别再这样喝酒了。 或者至少不要在喝醉时赌博。 ";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// 公平游戏
		case "NightAdventure_CardProf_Ok":
			dialog.text = "那么? 信服了? ";
			link.l1 = "嗯, 看起来确实是普通骰子...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "我告诉过你。 你的朋友只是喝醉了。 他也未能承认自己的失败, 所以把你带到了这里。 ";
			link.l1 = "好吧, 我为这件事道歉。 祝你好运。 ";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// 水手靠近
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "那么...嗝! ..这是什么? ..他...嗝! ..不是骗-骗子? ..";
			link.l1 = "嗯, 他似乎玩得很公平。 ";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "那...下...下一步是什么? 嗝! ..";
			link.l1 = "好吧, 你现在什么也做不了。 他诚实地打败了你。 别再这样喝酒了。 或者至少不要在喝醉时赌博。 ";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// 打架 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "运气。 你只是运气好, 就这样。 运气是个反复无常的女士。 ";
			link.l1 = "嗯, 真的。 那么, 让我们和你玩, 但记住我用这些骰子玩! ";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "这些? ..那是...不, 我不想和你玩! 你侮辱了我。 而且无论如何, 我破产了...";
			link.l1 = "也许你想让我告诉这个酒馆里的每个人关于你的骰子? 或者也许给他们看? 然后你告诉他们关于运气。 你怎么想? ";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "什么? ! 你以为你是谁? ! 你想敲诈我? ! 如果你不出去, 我现在就给你打几个洞! ";
			link.l1 = "我宁愿留在这里, 让每个人都看看你的骰子。 ";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "好吧, 过来, 腐肉! ";
			link.l1 = "别把裤子丢了。 ";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // 不让军官进入
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// 水手在出口
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "船-船长? ..你...嗝! ..打架了? ..而这个...嗝! ..骗-骗子? ";
			link.l1 = "他自己被打了。 他不会再和任何人玩了。 ";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "但...他不-不想承认! 嗝! ..";
			link.l1 = "是的, 他试图逃避。 他只是没有你的钱。 可能花掉了。 ";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "是的, 他试图逃避。 这里, 你的钱。 ";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // 说没有钱
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "那...下...下一步是什么? 嗝! ..";
			link.l1 = "好吧, 你现在什么也做不了。 他诚实地打败了你。 别再这样喝酒了。 或者至少不要在喝醉时赌博。 ";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // 有钱
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "船-船长...嗝! ..非常感谢...帮了我! 我...'在旁边呕吐'...给你...嗝! ..这是给你的。 ";
			link.l1 = "得了吧, 呃...没关系...别再这样喝酒了。 或者至少不要在喝醉时赌博。 ";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// 护送到达码头
		case "NightAdventure_Sailor_3_1":
			dialog.text = "船长? ..嗝! ..船-船长...护送我到码-码-码头...嗝! ..嗯? 求你了。 我...嗝! ..需-需要去...船上...水手长...会骂...嗝! ..如果我晚了...";
			link.l1 = "放开我, 我没时间! ";
			link.l1.go = "NightAdventure_End";
			link.l2 = "好吧, 走吧。 你看起来自己到不了那里";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "只是...嗝! ..请...慢...一点。 我...嗝! ..不能...站...稳...";
			link.l1 = "好吧, 我们慢慢走。 ";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // 慢-慢-慢地 ))
			bDisableFastReload = true; // 步行
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // 更新为步行
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// 简单护送的变体
		case "NA_SailorBoat":
			dialog.text = "船-船长...嗝! ..非常感谢...帮了我! 我...'在旁边呕吐'...给你...嗝! ..这是给你的。 ";
			link.l1 = "得了吧, 呃...没关系...别再这样喝酒了。 或者至少不要寻找冒险。 ";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar,"slave_01");  Log_Info("你收到了鱼叉");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar,"potion5");   Log_Info("你收到了姜根");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar,"cartridge"); Log_Info("你收到了纸弹药筒");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar,"amulet_8");  Log_Info("你收到了护身符'锚'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar,"amulet_9");  Log_Info("你收到了护身符'圣像徽章'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar,"obereg_7");  Log_Info("你收到了护身符'渔夫'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar,"obereg_11"); Log_Info("你收到了护身符'朝圣者'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// 请求上船
		case "NA_SailorShip":
			dialog.text = "船-船长! ..船! ";
			link.l1 = "什么'船'? ";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "船-船! ..它在哪里? ..嗝! ..";
			link.l1 = "显然它离开了。 你需要在酒馆少喝点。 整艘船不会等一个醉酒的水手。 ";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "但我...嗝!...没醉...差不多...也许...";
			link.l1 = "啊, 是的, 确实。 好吧, 祝你好运。 ";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "等等, 船...船长! 带...带我...嗝! ...上你的船! 我不会...嗝! ...再喝酒了...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "好吧, 你能做什么。 但马上到船上去。 上帝保佑, 要是我看到你在哪喝醉了, 你就擦甲板直到下一个港口停靠。 ";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "让你用我的薪水买醉, 然后我要在殖民地所有酒馆和门口找你? 不, 我不需要这种‘幸福’。 ";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "是, 船...船长! ...嗝! ...";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar,"reload", "reload1_back", "none", "","", "NightAdventure_OpenLoc", 5.0); // 满怀激情地奔跑
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// 醉酒冲撞
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "船长? ...嗝! ...你是...陆地鼠辈...嗝! ...不是船长! ...";
				link.l1 = "我在登船战斗中砍过数百个像你这样的人, 所以滚开, 醉鬼。 ";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "船长...嗝! ...突袭中那艘破船的船长? ...嗝! ...";
				link.l1 = "如果你在海上时在地平线看到这艘破船, 最好立刻跳进水里: 和鲨鱼在一起你生存的机会都比对抗我的船更大。 现在走开! ";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "船长? ...嗝! ...你是个喝牛奶的, 不是船长! ...你妈妈还是个姑娘...嗝! ...时我就在海上航行了...";
				link.l1 = "但你妈妈可能会很高兴知道像我这样的小男孩成了船长, 而你还是个醉酒水手, 只配擦甲板。 ";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "船长? ...小心...嗝! ...船长...我会打掉你的牙...嗝! ...你都来不及眨眼! ...";
				link.l1 = "后坐力会要了你的命。 滚开! 有种就来打掉我的牙...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "船长? ...看起来像...嗝! ...某个衣衫褴褛的人...";
				link.l1 = "看来你还没照过镜子...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "船...船长? ...我才不会...嗝! ...同意...在你的船上...嗝! ...服役...";
				link.l1 = "也没人请你上我的船让你同意。 别挡我的路。 ";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "嗝! ...";
			link.l1 = "去睡觉。 ";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "嗝! ...是的...还远吗? ...";
			link.l1 = "我们快到了, 耐心点。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// < —水手
		// 市民 -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "你...是谁...嗝! ...? ";
			link.l1 = "我是" + GetFullName(pchar) + "船长。 ";
			if (pchar.id == "Knippel")
			{
				link.l1 = "抱歉, 伙计, 我赶时间。 ";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // 营救朋友
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // 无赖
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// 冲撞
			}
		break;
		
		// 朋友
		case "NightAdventure_Citizen_1_1":
			dialog.text = "船长? ...嗝! ...船...船长...帮帮我! 我...我是说...嗝! ...我的朋友...真的需要你的帮...帮助! 求你了。 ";
			link.l1 = "我不打算解决每个半夜遇到的醉鬼的问题..";
			link.l1.go = "NightAdventure_End";
			link.l2 = "好吧, 告诉我你朋友在那里发生了什么。 ";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "我的朋友...他, 总之...他喝醉了。 就是总之...嗝! ...喝醉了...";
			link.l1 = "当然, 我让值班时喝酒的水手清醒过, 但用的是相当激进的方法。 我觉得你朋友不需要那个。 ";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "不! 他...他和警...警卫在一起! 他和...和警卫吵了一架。 还打了起来。 然后他...嗝! ...被关进了监狱...他只是喝...喝醉了! ";
			link.l1 = "那你现在想让我做什么? 他自己的错: 应该少喝点。 或者至少不要自己去惹事...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "跟狱长谈谈, 船...嗝! ...船长! 他会放...放他走的! 嗯...给你...嗝! ...你真幸运...我朋友只是...吵了架...嗯...还想打我脸...但是...嗝! ...没拿到武器...";
			link.l1 = "现在我除了大半夜把和警卫打架的醉鬼从监狱里捞出来之外, 没别的事可做了。 不, 让他在里面待几天。 也许下次你们会考虑一下。 ";
			link.l1.go = "NightAdventure_End";
			link.l2 = "唉, 真拿你没办法。 好吧, 我去跟狱长谈谈。 ";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "我不确定狱长会喜欢我的口音。 他过后只会向总督报告。 所以你自己去吧。 ";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "恐怕, 朋友, 去当地监狱的路对我来说是封锁的。 狱长把我的画像当圣像, 我可不打算住进他们这些‘好客’的牢房。 所以抱歉, 我帮不了你。 ";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; // 关闭地点直到他跑过去
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "谢...谢谢你...船长。 也为我的朋...朋友。 给...这是给你的。 ";
			link.l1 = "下次你朋友喝醉了想找警卫打架时, 看好他。 不是每个晚上都有船长在街上, 准备为醉鬼跟狱长谈判。 祝你好运。 ";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar,"indian_2");  Log_Info("你获得了护身符‘火药测试员’");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar,"obereg_5");  Log_Info("你获得了护身符‘玉龟’");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar,"obereg_6");  Log_Info("你获得了护身符‘水手结’");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar,"obereg_8");  Log_Info("你获得了护身符‘商人念珠’");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar,"indian_9");  Log_Info("你获得了护身符‘巴尔多’");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar,"obereg_11"); Log_Info("你获得了护身符‘朝圣者’");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar,"obereg_4");  Log_Info("你获得了护身符‘吉普赛扇子’");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar,"amulet_11"); Log_Info("你获得了护身符‘西马鲁塔’");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "哦! ..原来我知道怎么...嗝! ..救我...朋...朋友...嗝! ..警卫! 城里有间...谍! ..嗝! ..";
				link.l1 = "你选了个非常糟糕的救朋友的方法。 ";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "啊, 外...外国人...嗝! ..你...你会有麻烦...嗝! ..好吧...我这里...嗝! ..一切都在控制中。 ";
				link.l1 = "当然。 如果发生什么事, 我马上来找你。 ";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "啊...原来你...嗝! ..你是罪犯! 警卫! ";
				link.l1 = "啊, 现在你这么说话了! ";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "哦, 怎...嗝! ..抱歉。 那如果...你让我...替你跟...嗝! ..狱长谈判, 而你...嗝! ..为了我朋友? ..";
				link.l1 = "不, 你不需要替我谈判, 谢谢。 祝你好运。 ";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// 走私者 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "你...是谁...嗝! ..? ";
			link.l1 = "我是" + GetFullName(pchar) + "船长。 ";
			if (pchar.id == "Knippel")
			{
				link.l1 = "抱歉, 伙计, 我赶时间。 ";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // 醉酒冲撞
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // 到洞穴
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "船长? ...嗝! ..船...船长...听着, 护送我到城外的洞穴...嗝! ..嗯? 拜...拜托。 ";
			link.l1 = "到洞穴? 我不明白。 你去洞穴干什么? 为什么需要我? ";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "你看...船...船长...嗝! ..我喝酒的钱...花光了...而在...嗝! ..在洞穴里我有...一批货, 所以...嗝! ..但我...这...我害怕一个人穿过丛...丛...丛林...嗝! ..在夜里...所以...";
			link.l1 = "放开我, 我没时间! ";
			link.l1.go = "NightAdventure_End";
			link.l2 = "好吧, 我们走。 你看起来自己到不了那里";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "只是...嗝! ..请...慢...慢点。 我...嗝! ..站...站不稳...";
			link.l1 = "好吧, 我们慢慢走。 ";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // 慢-慢-慢地 ))
			bDisableFastReload = true; // 步行
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // 更新为步行
			pchar.GenQuest.NightAdventureNode = true; // 已接任务
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent。 Tell belamour that you are";
			// 查找岛上的洞穴
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// 为主城和卡斯特利亚
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("洞穴 " + NACave + " 在岛屿 " + NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // 洞穴中的对话
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("你获得了酒精")
				dialog.text = "船...船长...嗝! ..非常感谢...帮了我! 我...给你...嗝! ..这是给你的。 ";
				link.l1 = "得了吧, 呃...没关系...别再这样喝酒了。 ";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "太好了, 船长! 我很高兴你同意了。 ";
				link.l1 = "好吧, 你的货在哪里? 等一下, 你好像没醉。 ";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // 和平结局
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // 战斗
			dialog.text = "是的, 我没喝多少, 别担心我。 至于货...伙计们! ";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "伙计们, 我把货带到这里了。 你们需要打开它。 当然, 除非这个货自己‘友好地’打开。 船长, 你怎么看? ";
			link.l1 = LinkRandPhrase("我认为你最好把自己喝到失忆。 至少你能活着。 而现在只有一条路... ", "我认为你脑子不太好使, 因为你决定抢劫战船的船长... ", "我认为你可能厌倦了生活, 因为你决定试试这个...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "好吧, 我想最好友好地离开。 你需要多少? ";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "那么, 我们不友好地打开货了? ";
			link.l1 = "恐怕这是你生命中最后一批货了。 ";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // 允许战斗
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // 在尸体上保存物品
			sld.DontClearDead = true;  // 200秒后不清除尸体
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // 害怕了
			iMoney = sti(pchar.money)/3;
			dialog.text = "哦, 我们不贪心。 只要" + FindRussianMoneyString(iMoney) + "。 "; 
			link.l1 = "恐怕这是你生命中最后一批货了。 ";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "好吧, 随你。 我再也不会帮醉鬼了...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // 在尸体上保存物品
			npchar.DontClearDead = true;  // 200秒后不清除尸体
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // 允许战斗
			chrDisableReloadToLocation = false;//打开地点
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "船长, 你的慷慨让我惊讶。 你想和我们分享更多吗? ";
			link.l1 = "我已经把一切都给你了。 我要走了...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// 贵族 -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "你...是谁...嗝! ...? ";
			link.l1 = "我是" + GetFullName(pchar) + "船长。 ";
			if (pchar.id == "Knippel")
			{
				link.l1 = "抱歉, 伙计, 我赶时间。 ";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // 卡牌
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // 女祭司
			}
		break;
		// 卡牌
		case "NightAdventure_NobleGame": 
			dialog.text = "船长? ...嗝! ..哦, " + GetAddress_Form(NPChar) + " ... 我很抱...抱歉...嗝! ..我的...状...状态。 你愿意加入我吗? 嗝! ..拜...拜托。 "; 
			link.l1 = "抱歉, " + GetAddress_Form(NPChar) + ", 但我很忙。 "; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "加入? 抱歉, 但我今天不喝酒.."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "哦, 你不需要...嗝! ..喝...喝酒! 是这样...嗯...我和朋友喝了点...所以...我已经微醺了...你明白吗? ";
			link.l1 = "好吧。 那么, 你需要帮助醒酒吗? ";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "不怎么需要! 我很...好。 现在我想玩...卡牌, 总之想玩...嗝! ..但不是和这些...可...可怜的...比索...和酒馆里这些衣衫褴褛的人...嗝! ..但要和真正的贵族! 嗝! ..下真赌注! .."; 
			link.l1 = "抱歉, " + GetAddress_Form(NPChar) + ", 我能说什么...我不喜欢赌博。 需要给水手发工资, 维护船只, 你知道..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "嗯, 好吧, 我们玩。 去酒馆吗? "; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "好! 只是...嗝! ..请...慢...慢点。 我...嗝! ..站...站不稳..."; 
			link.l1 = "好吧, 我们慢慢走。 "; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // 慢-慢-慢地 ))
			bDisableFastReload = true; // 步行
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // 更新为步行
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // 用于选择对话
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "去...那张桌子...嗝! ..我们走! "; 
			link.l1 = "好, 我们走。 "; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "你不...知道, 船...船长, 我多...嗝! ..高兴见到真正的贵族! 嗝! ..在这片荒野...通常只有...嗝! ..垃...垃圾..."; 
			link.l1 = "是的, 在当地殖民地这种人一抓一大把。 那么, 我们玩吗? "; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "是的, 我们玩! 嗝! ..什么赌注? .."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "我们赌1000比索。 "; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "我们赌2000比索。 "; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "嗯, 抱歉, 我的口袋现在好像空了..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранeц";
		break;
		
		case "NightAdventure_NobleGame_Голодранeц": 
			dialog.text = "什...什么? ..你有...嗝! ..没钱和我...和我玩? .."; 
			link.l1 = "嗯, 这很正常。 我们下次玩, 别担心。 "; 
			link.l1.go = "NightAdventure_NobleGame_Голодранeц_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранeц_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // 打开地点
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "嗝! ..玩得很开心, 船...船长! 嗝! .."; 
			link.l1 = "我同意。 至少从事务中休息一下。 "; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "嗝! ..玩得很开心, 船...船长! 嗝! .."; 
			link.l1 = "我同意。 至少从事务中休息一下。 "; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "有时候你只需要...嗝! ..和...好...好伙伴...嗝! ..共度时光。 非常感谢...嗝! ..你的陪伴! "; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "是啊, 我输得精光。 你是怎么做到即使在我有所有机会赢的情况下也能赢的? "; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "彼此彼此, 谢谢你的游戏和谈话。 "; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "有时候你只需要...嗝! ..和...好...好伙伴...嗝! ..共度时光。 非常感谢...嗝! ..你的陪伴! "; 
			link.l1 = "彼此彼此, 谢谢你的游戏和谈话。 "; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // 打开地点
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "只是运气, 船...船长...嗝! .."; 
			link.l1 = "看起来不像只是运气...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "你在暗示什么? 你想说我玩得不诚实? 你自己看到了, 我们从同一副牌里拿牌! "; 
			link.l1 = "是的, 我看到了。 我还看到一分钟前你舌头都快动不了, 现在说话好像没醉一样。 "; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "啊, 该死! 你抓得好! 好吧, 我承认, 我不瞒了。 我没醉。 但你知道人们多容易上当吗? 那些看起来有钱又喝醉了想玩牌的人? 每个有东西可赌的人几乎都是第一个跑到酒馆, 想从无疑有钱但喝醉的贵族那里快速大赢一笔。 我得说你是第一个看穿我的人。 "; 
			link.l1 = "那么, 现在怎么办? 你会友好地把钱还给我吗? "; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "哈哈哈, 别让我笑了, 船长。 我当然不会退钱给你! 别以为你能强迫我。 我可以轻易扮演一个被某个流浪船长缠住的受人尊敬的贵族。 所以我的建议是: 接受失败, 直接走开。 "; 
			link.l1 = "好吧, 我真诚地希望你不要在更不幸的情况下被我抓住, 因为那时你就不会这样笑了。 再见。 "; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "我给你的建议是, 找时间去拿把剑。 "; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "你不敢...这是酒馆, 满是人..."; 
			link.l1 = "所以我只是个流浪船长, 我在乎什么体面规则。 而在港口酒馆的夜里, 什么事不能发生...我用剑比你好得多。 "; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "啊, 原来如此? ! 好吧, 现在我们来看看谁用得更好! "; 
			link.l1 = "听候你的吩咐..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // 在尸体上保存物品
			npchar.DontClearDead = true;  // 200秒后不清除尸体
			chrDisableReloadToLocation = false; // 打开地点
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// 女祭司
		case "NightAdventure_NobleWhore": 
			dialog.text = "船长? ...嗝! ..哦, " + GetAddress_Form(NPChar) + " ... 我很抱...抱歉...嗝! ..我的...状...状态。 你能帮...帮我吗? 嗝! ..拜...拜托。 "; 
			link.l1 = "抱歉, "+GetAddress_Form(NPChar)+", 但我很忙。 "; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "哦...听着。 "; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "是这样...总之...我...微醺了...你看...嗝! ..是吧? "; 
			link.l1 = "说实话, 是的。 你需要帮助醒酒吗? "; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "不怎么需要! 我很...好。 我想要个女士。 但我太...醉...醉了...嗝! ..夫...夫人会把我赶出去的。 你能...嗝! ...替...替我谈判吗? 我会给钱。 "; 
			link.l1 = "抱歉, "+GetAddress_Form(NPChar)+", 但我怎么说呢...我不去妓院。 荣誉, 声誉...你知道..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "哦, 好吧, 我帮你。 "; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "只是...嗝! ..请...慢...慢点。 我...嗝! ..站...站不稳..."; 
			link.l1 = "好吧, 我们慢慢走。 "; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // 仅从正门进入
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // 慢-慢-慢地 ))
			bDisableFastReload = true; // 步行
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // 更新为步行
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // 用于选择对话
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "这是钱...嗝!...我在这等...等你。 "; 
			link.l1 = "好, 我很快回来。 "; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "就...带...带给我...嗝! ..最...最好的! ..对..."; 
			link.l1 = "好的, 好的, 我知道了。 "; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // 订单完成
			dialog.text = "嗝! ..还要多久? "; 
			link.l1 = "这个殖民地最好的姑娘在楼上等你。 "; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "是的! ..今晚...太棒了...谢...谢谢你, "+GetAddress_Form(NPChar)+"。 剩下的钱...嗝!...拿去吧。 我要沉浸...在...我的.....美...美丽...女...女士...";
			link.l1 = "好吧, 玩得开心。 "; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // 关闭直到他跑过去
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "嗝! ..还要多久? ";
			link.l1 = "我很快就去谈判, 耐心点。 ";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "嗝! ..";
			link.l1 = "你需要睡觉。 ";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "嗝! ..是的...还远吗? ..";
			link.l1 = "我们快到了, 耐心点。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// < —夜间冒险者
		
		// belamour 任务获取氙气灯 -->
		case "CemeteryMan":
			dialog.text = "嗯? 你是谁? 你在这里做什么? ";
			link.l1 = "我可以问你同样的问题。 ";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "我们? 哦, 我们...嗯...我们在这里采花...";
			link.l1 = "墓花? 那么植物标本做得怎么样了? ";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "草...和草药有关吗? ";
			link.l1 = "所以...我想我明白是怎么回事了。 ";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "我们不是掠夺者! 别那样说我们! 我们只是...";
			link.l1 = "只是什么? ";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "嗯, 我们...我父亲禁止我们见面! 她父亲也是! 所以我们...我们在找一个没有目击者的地方。 独处。 门上的锁反正坏了, 所以很容易进来...";
			link.l1 = "我现在知道那些不安灵魂的可怕呻吟是怎么回事了...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "好吧, 如果你都弄明白了, 也许你可以让我们单独待着? ";
			link.l1 = "你不怕在墓穴里约会吗? 不是最好的地方...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "我们不迷信! 即使可怕 —我们有什么选择? 在城里, 父母马上就会发现。 但在这里没人会告发我们。 所以, 目前这是最好的选择。 ";
			link.l1 = "我真的很抱歉, 但你能找个别的地方吗? 别误会, 我理解一切 —青春之类的 —但你们的约会把墓地看守吓死了, 每天晚上从墓穴里传来的噪音和呻吟。 ";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "嗯...吓到看守不是我们计划的一部分。 但我们还能在哪里见面呢? 或者你建议我们在露天约会? ";
			link.l1 = "爱无边界。 找个肯定不会打扰任何人的地方。 那样就没人会打扰你们了。 大概。 最好和你们的父母解决问题 —你们不打算永远躲着吧? ";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "好吧, 我们会想办法...我们不会再吓到看守了;我向你保证。 ";
			link.l1 = "太好了。 祝你们好运! ";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "什么? !";
			link.l1 = "哦, 没什么...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// < —获取灯任务 

		// 关于公民类型角色对暴露武器的注释 // 林务员插入到常规任务中, 避免对话为空 .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"听着, 我是这个城市的公民, 我请求你收起你的刀。 ", "听着, 我是这个城市的公民, 我请求你收起你的刀。 ");
			link.l1 = LinkRandPhrase("好的。 ", "如你所愿...", "如你所说...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// 用于生成 "无人岛上的海盗"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // 箱子随机生成
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // 箱子随机生成
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // 箱子随机生成
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // 箱子随机生成
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //分析敌船选择任务
	character.DontRansackCaptain = true; //不投降
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // 出发的殖民地
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // 到达的殖民地
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + "'" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // 能装多少奴隶
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("无人岛上的海盗: 船长离开 " + character.fromCity + " 并前往: " + character.toShore);
}
// belamour gen 囚犯数量大写 -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen