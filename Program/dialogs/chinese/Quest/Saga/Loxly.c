// 阿尔伯特.洛克斯利 - 律师
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // 索引在末尾
		// 检查已有的协议
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "我叫阿尔伯特.洛克斯利, 是一名律师。 我在审判中代表客户的利益。 我的服务价格不菲, 但物有所值, 我可以向你保证。 ";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "我与英国当局有麻烦。 ";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "我与法国当局有麻烦。 ";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "我与西班牙当局有麻烦。 ";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "我与荷兰当局有麻烦。 ";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "我和走私者吵架了。 ";
						Link.l5.go = "contraband";
					}
					Link.l7 = "谢谢, 但幸运的是, 到目前为止我还不需要律师的服务。 ";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
				}
				link.l1 = "谢谢, 但幸运的是, 到目前为止我还不需要律师的服务。 ";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "我需要你的服务。 我是一位名叫海伦.麦克阿瑟的年轻女士的授权代表, 她是著名的Nicholas Sharp的孙女。 她是母亲和叔叔去世后唯一的合法继承人。 根据她叔叔的遗嘱, 她对特索罗岛拥有所有权利。 你帮助海伦成为该岛的合法主人需要多少钱? ";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // 第一次因传奇任务求助
					{
						dialog.text = "先生, 你需要我的服务吗? 我可以向你保证, 你会满意的。 ";
						link.l1 = "是的, 我需要。 我是一位名叫海伦.麦克阿瑟的年轻女士的授权代表, 她是著名的Nicholas Sharp的孙女。 她是母亲和叔叔去世后唯一的合法继承人。 根据她叔叔的遗嘱, 她对特索罗岛拥有所有权利。 你帮助海伦成为该岛的合法主人需要多少钱? ";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "先生, 我还不熟悉你事务的材料。 请稍后再来见我, 正如我已经告诉你的。 ";
						link.l1 = "好的。 ";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // 如果没有完全完成关于巴考特的任务
						dialog.text = "先生, 不幸的是, 我需要更多时间在档案馆收集所有需要的文件。 我还没准备好。 请稍后再来见我。 ";
						link.l1 = "好的。 ";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // 已解决巴考特问题
					{
						// 第四次时间检查
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "先生, 你为什么工作这么慢? ! 你的委托人一切都完了。 遗嘱的有效期已过, 特索罗岛现在属于英国。 它很快将成为军事基地。 "
							link.l1 = "哇! 看来我所有的努力都白费了... ";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "啊, 你来了, 先生。 我已经熟悉了材料, 现在是预付款的时候了。 你把达布隆带来了吗? ";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "是的, 我带来了。 这是你的达布隆。 ";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "请原谅我的记性不好, 我把它们留在船上的箱子里了。 我马上带来。 ";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// 第五次时间检查
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "先生, 你为什么工作这么慢? ! 你的委托人一切都完了。 遗嘱的有效期已过, 特索罗岛现在属于英国。 它很快将成为军事基地。 "
							link.l1 = "哇! 看来我所有的努力都白费了... ";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "先生, 你能找到任何可以证明你委托人血统的东西吗? ";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "还没有。 但我正在努力。 ";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "是的。 我确实有详尽的证据。 ";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // 禁止保存, 以免被那些用GK的聪明人抢走任务链 - 林务员
						InterfaceStates.Buttons.Save.enable = false;//禁止保存																																			   
						dialog.text = "啊, 你来了, 先生。 很高兴见到你。 我必须承认, 我已经等你很久了。 这是你的委托人吗? ";
						link.l1 = "是的。 让我把你介绍给海伦.麦克阿瑟。 ";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "先生, 你需要我的服务吗? 我可以向你保证, 你会满意的。 ";
					link.l1 = "谢谢你, 但我现在不需要。 ";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "日安, 先生。 我想你已经带来了我的费用? ";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "是的, 我带来了。 这是你的达布隆。 ";
						link.l1.go = "saga_36";
					}
					link.l2 = "你知道, 洛克斯利先生, 我认为... 我的意思是900达布隆对你的工作来说已经足够了。 ";
					link.l2.go = "saga_38";
					link.l3 = "我记得, 洛克斯利先生。 我稍后会带来... ";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "先生, 你需要我的服务吗? 我可以向你保证, 你会满意的。 ";
				link.l1 = "谢谢你, 但我现在不需要。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// 第三次时间检查。 带上海伦, 清理任务战利品, 给斯文森旗帜, 引发变化
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "先生, 你一定在海上待得太久了。 特索罗岛现在是英国海军的军事基地! 是的, Sharp的遗嘱存在, 但它已经过期, 特索罗岛已成为英国王室的财产。 唉! "
				link.l1 = "哇! 看来我所有的努力都白费了... ";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "这位女士声称拥有整个岛屿? 嗯... 看来这不是一件容易的事。 特索罗岛几乎已经是英国的殖民地了... ";
				link.l1 = "还没有。 根据遗嘱, 出示地图两部分的人将成为特索罗岛的主人。 我们有Sharp地图的两部分, 这是遗产的主要证明。 ";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicholas Sharp... 好吧, 好吧。 我需要访问档案馆, 熟悉与特索罗岛相关的材料。 你带地图了吗? ";
			link.l1 = "我带了, 但我只会在我们签订合同后给你。 那么, 你的服务价格是多少? ";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " 你尊贵的参与也不会被忽视。 卡塔赫纳... 会有问题的。 ";
			dialog.text = "正如我所说 - 这并不容易。 你需要证明对整个岛屿的所有权, 而不是一些旧船或小屋。 此外, Nicholas Sharp是一名海盗, 帮助海盗或其亲属是昂贵的。 "+sTemp;
			link.l1 = "你打算告诉我实际的金额吗? ";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "四百五十";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "一千";
			dialog.text = "先生, 最终金额将在审判期间确定。 我还不知道这会有多困难。 但我准备估算预付款 - "+sTemp+"达布隆。 这笔黄金可能需要再支付一两次, 具体取决于我们的事务进展如何。 \n一周内把钱带给我, 我需要时间检查档案馆并做好准备。 然后我们再做安排。 成交? ";
			link.l1 = "他们推荐你作为群岛上最好的律师, 所以我们成交。 一周后见! ";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // 更新标志
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("你给了1450达布隆");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("你给了450达布隆");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "很好。 我准备接手你的案件, 并在法庭上代表你的利益。 现在让我们切入正题。 我在档案馆做得很好, 并与重要人物交谈过。 Sharp遗产的案件并不容易。 你获得了地图的两部分, 这很好。 但这可能还不够。 \n Doyle上校对特索罗岛有很大的计划, 因为他未能控制托尔图加。 它有天然防御, 可以作为该地区未来的军事基地。 ";
			link.l1 = "但根据英国法律, 海伦对该岛拥有所有权利! ";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "你可能不知道, 已故的Sharp先生对他的遗嘱做了补充。 继承人必须有他的姓氏。 据我记忆, 你的女孩有不同的姓氏。 你说过是麦克阿瑟, 对吗? ";
			link.l1 = "这是她继父的姓氏, 但海伦完全有权使用Sharp作为她的姓氏, 因为她是已故Beatrice Sharp的女儿, 尼古拉斯的女儿。 ";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "太棒了! 但谁能宣誓证实这一点? 海伦的养父母认识Beatrice Sharp吗? ";
			link.l1 = "据我所知, 他们不认识。 麦克阿瑟先生认为她是格莱迪斯的女儿, 而格莱迪斯只熟悉这个女孩的父亲。 ";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "真遗憾。 看, 我在档案中没有找到任何提到Beatrice Sharp曾经有任何后代的记录。 有可能根本没有关于孩子出生的官方记录。 任何人都可以称自己为Sharp的孙子, 并声称有权使用他的姓氏。 ";
			link.l1 = "但只有海伦拥有完整的地图! ";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "这是她的王牌, 如果地方当局没有自己对特索罗岛的计划, 这可能就足够了。 档案馆里有一份Beatrice的笔迹和她签名的文件。 我们需要找到一些由她写的文件, 证明她女儿的出生事实, 这个女儿被交给了那个格莱迪斯... 呃, 她姓什么? ";
			link.l1 = "钱德勒。 来自伯利兹的格莱迪斯.钱德勒。 ";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "正是。 你有机会找到这样的东西吗? ";
			link.l1 = "我怀疑。 很多年过去了。 根据传说, 屠夫船长本人可能是海伦的父亲。 也许圣约翰的前刽子手可以告诉我们一些关于这个的事情。 他是最后一个看到她父亲活着的人。 ";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "嗯。 他确实是个有趣的人。 据我记得, 他的名字是雷蒙德.贝克。 我很幸运曾经和他聊过一次。 他是一个聪明且受过良好教育的人。 好吧, 试着在安提瓜找到一些东西, 我会继续在档案馆搜索, 也许我会找到一些有用的东西。 ";
			link.l1 = "好的。 对我有用。 ";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "把Sharp的地图给我, 快点, 和贝克谈谈, 也许你能在他的帮助下找到一些文件。 你甚至可能找到她出生的证据。 ";
			link.l1 = "呃, 我希望我能。 好吧, 再见, 洛克斯利先生。 ";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "是这样吗? 让我们看看这个证据。 ";
			link.l1 = "这是Beatrice Sharp给她哥哥的私人信件。 这里写着她生了一个女儿, 她的父亲实际上是劳伦斯.贝尔特罗普。 这个女孩被送到了一位名叫格莱迪斯.钱德勒的年轻寡妇那里。 劳伦斯.贝尔特罗普也被称为屠夫船长。 给, 拿着这封信... ";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "格莱迪斯准备宣誓证实这一点。 她也准备证实父亲自称是屠夫船长。 ";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // 贝尔特罗普被杀
			{
				dialog.text = "等一下! 屠夫船长, 这个邪恶的海盗和英国臣民的杀手, 二十年前在圣约翰的堡垒被绞死。 而理查德。 Doyle 的密友劳伦斯.贝尔特罗普不久前悲惨地去世了。 最重要的是, Doyle 想让他成为夏普敦的新总督! ";
				link.l1 = "哈! 当然, 没人知道... 我有圣约翰前刽子手雷蒙德.贝克的书面证词, 他在死亡威胁下被迫伪造了屠夫的处决! 给, 看看... ";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "等一下! 屠夫船长, 这个邪恶的海盗和英国臣民的杀手, 二十年前在圣约翰的堡垒被绞死。 而劳伦斯.贝尔特罗普还活着, 住在皇家港最好的豪宅之一。 最重要的是, Doyle 想让他成为夏普敦的新总督! ";
				link.l1 = "哈! 当然, 没人知道... 我有圣约翰前刽子手雷蒙德.贝克的书面证词, 他在死亡威胁下被迫伪造了屠夫的处决! 给, 看看... ";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "嗯。 好吧, 好吧... ";
			link.l1 = "这不很巧妙吗? 屠夫船长设法活了下来, 回到了英国。 他把名字改回劳伦斯.贝尔特罗普, 并不被注意地回到了这里。 ";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "但这... 这改变了一切! 公布Beatrice的信将表明, 军事总督一直隐藏着逃亡的海盗屠夫, 他应该被当场逮捕, 并因过去的罪行出庭! \n而贝克的证词将彻底摧毁任何反对的理由! 这太好了! 有了这样一张王牌, 我们将公平地击败 Doyle! ";
			link.l1 = "我很高兴。 我在这次审判中依赖你。 另外, 告诉我, 劳伦斯.贝尔特罗普是怎么死的? ";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "这是一个令人毛骨悚然的故事, 先生。 他被发现死在自己的卧室里, 脸上扭曲。 很难想象是什么让这个无畏的人如此害怕。 他们说他浑身是霜。 他的身体布满了可怕的撕裂伤, 但地板上没有一滴血! 想象一下! 一滴都没有! ";
			link.l1 = "是的, 这似乎直接出自噩梦。 看来他是被谋杀的... 但谁能做到呢? ";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "未知。 太复杂了... 驻军医生说他的伤口没有致命。 贝尔特罗普死于恐惧。 疼痛或其他原因。 无论如何, 这是一个神秘的死亡。 ";
			link.l1 = "我明白了... 审判什么时候开始? ";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "这都取决于你, 先生。 一旦你支付我第二部分费用 - 450达布隆, 我就会将所有文件提交给法庭。 一周后海伦将获得她的权利。 ";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "很好。 这是你的达布隆。 ";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "是的, 当然。 我会给你带来你需要的金额。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// 第六次时间检查
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "先生, 你让我震惊! 你做了这么多, 岛屿几乎在我们手中, 但现在因为你延迟支付我的费用, 一切都结束了! 遗嘱过期了, 特索罗岛现在属于英国王室。 它将成为一个军事基地。 "
				link.l1 = "哇! 看来我所有的努力都白费了... ";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "先生, 你带来了我的第二部分费用吗? ";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "是的, 当然。 这是你的达布隆。 ";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "请原谅我的记性不好, 我把它们留在船上的箱子里了。 我马上带来。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "但这... 这改变了一切! 公布Beatrice的信将意味着劳伦斯.贝尔特罗普必须立即被捕, 并因过去的罪行出庭! \n而贝克的证词将彻底摧毁任何反对的理由! 这太好了! 有了这样一张王牌, 我们将公平地击败 Doyle! ";
			link.l1 = "我很高兴。 审判什么时候开始? ";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("你给了450达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "太好了, 先生。 与你做生意很愉快。 现在, 这是协议。 明天回到这里。 是的-是的, 你没听错-明天! 毕竟我是群岛上最好的律师, 我有联系。 \n带上你的委托人, 没有她审判不会发生。 不要迟到, 不要离开城市。 如果你能的话, 带上最后一部分付款, 我完全相信我们会胜利。 ";
			link.l1 = "好的。 我们明天会到你的办公室, 洛克斯利先生。 ";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // 更新标志
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// 关闭城市出口
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// 林务员那里没有这个码头
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//禁止等待
			// 移除传奇的总计时器! 
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "麦克阿瑟? 不, 是Sharp! 好吧, 现在跟我来! ";
			link.l1 = "... ";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// 打开城市出口
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // 林务员太早 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以加速时间
		break;
		
		case "saga_28":
			dialog.text = "请允许我祝贺你, 先生, 和你的委托人。 她现在是特索罗岛的合法统治者。 为此值得喝些香槟! ";
			link.l1 = "绝对的, 洛克斯利先生。 你的演讲非常出色。 我以为当你告诉法庭劳伦斯.贝尔特罗普是屠夫船长时, Doyle上校会心脏病发作。 ";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "是的, Doyle先生将不得不告别他在特索罗岛建立军事基地的梦想。 他能做什么? 法律就是法律, 它适用于每个人, 甚至是受人尊敬的上校。 ";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "所有文件都没问题并确认了海伦对该岛的权利吗? ";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "我听说法官已下令逮捕劳伦斯.贝尔特罗普。 我想他会被绞死? ";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "当然, 先生。 我检查了它们上面的每个逗号。 你可以确定它们没问题。 ";
			link.l1 = "非常好... ";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "好吧, 我的工作完成了。 这个案子很棘手, 但我们一起赢了。 现在, 先生, 你只需要支付我最后一部分费用。 没有压力, 我知道你一定很忙。 但我相信你会在一周内找到时间给我带来最后450达布隆。 \n此外, 像你这样的客户可以一直享受大幅折扣。 我可以帮你很多忙, 我在群岛的每个首都都有联系, 甚至是敌对的, 所以你遇到的任何法律问题都可以解决。 ";
			link.l1 = "太好了。 现在我知道该问谁了。 ";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "即使在最困难的情况下, 我也保证会有积极的结果。 ";
			link.l1 = "很好。 我现在得走了, 我和海伦有很多事情要做。 ";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "再见, 先生。 ";
			link.l1 = "再见, 洛克斯利先生。 ";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "我想是的, 他是屠夫船长, 一个海盗和强盗。 尽管他现在不在皇家港。 他很幸运地离开了, 深入岛内。 但追捕已经开始, 他肯定会被抓住。 ";
			link.l1 = "我明白了... 文件都检查过了吗? ";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // 支付服务费用的计时器
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("你给了450达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "太棒了! 与你做生意很愉快, 先生! 现在你可以在任何事情上寻求我的帮助, 并获得折扣。 与法律的纠纷, 对你的悬赏... 欢迎。 我将永远高兴见到你。 ";
			link.l1 = "如果我能完全避免麻烦会更好, 但... 事情总会发生。 谢谢你, 再见, 洛克斯利先生。 ";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //移除计时器
			NextDiag.CurrentNode = "Loxly"; // 律师服务
		break;
		
		case "saga_38":
			dialog.text = "先生, 你是什么意思? 你打算违反我们的协议条款吗? ";
			link.l1 = "正是。 我做了大部分工作。 你甚至无法想象我为了获取证据必须做什么。 而你只是拿了那些文件去了法庭。 九百达布隆已经足够了, 我确定。 ";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "你说话像个海盗, 先生! 好吧, 我不会因为损失四百五十达布隆而变穷, 但你也不会因此致富。 事实上, 你刚刚失去了更多! 也许你将来会失去一些东西... 立即离开我的房子, 再也不要出现在这里! ";
			link.l1 = "我正要那样做。 再见, 洛克斯利先生。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //移除计时器
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // 关闭洛克斯利的入口
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "我不想和你说话。 滚开, 否则我就叫卫兵! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// 传奇任务失败
		case "saga_l3":
			dialog.text = "先生, 如果您早点来看我, 我们就会赢了您的案子。 遗嘱已经过期了。 我很抱歉。 ";
			link.l1 = "呃, 我更抱歉! 好吧, 再见, 洛克斯利先生。 ";
			link.l1.go = "saga_l3_1";
			// 海伦 - 对话
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // 调用特索罗岛的变化
			pchar.questTemp.Saga = "late_l3"; // 用于斯文森
		break;
		
	//------------------------------------ —律师服务 ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", 先生。 很高兴见到你。 你需要我的服务吗? ";
			link.l1 = "是的。 这就是我来这里的原因。 ";
			link.l1.go = "loxly_1";
			link.l2 = "不, 幸运的是我目前不需要。 只是想问候你。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "我准备好听你说。 你需要什么样的帮助。 ";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "我与英国当局有麻烦。 ";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "我与法国当局有麻烦。 ";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "我与西班牙当局有麻烦。 ";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "我与荷兰当局有麻烦。 ";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "我和走私者吵架了。 ";
				Link.l5.go = "contraband";
            }
			Link.l7 = "对不起, 我改变主意了... ";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // 已付款
			dialog.text = "我已经在处理你的事情了。 会没事的, 我可以向你保证。 ";
			Link.l1 = "谢谢你。 我会等待。 ";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> 移除国家敌对状态
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "好吧, 我不会称之为麻烦。 只是一个小问题。 我会立即解决这件事";
			if (iRate > 10 && iRate <= 30) sTemp = "是的, 你的声誉略有受损, 但我没有看到任何关键问题。 我会立即解决这件事";
			if (iRate > 30 && iRate <= 60) sTemp = "是的, 你与当局走了错误的道路。 这并不容易, 但我相信我能够顺利解决你的分歧";
			if (iRate > 60 && iRate <= 90) sTemp = "先生, 你是怎么做到的? 你的麻烦不仅仅是严重, 而是真的很严重。 当局非常渴望抓住你。 我将不得不付出很多努力来解决你的分歧";
			if (iRate > 90) sTemp = "嗯... 情况是灾难性的 - 你被认为是最激烈的敌人。 这将是艰难的, 但毕竟我是加勒比地区最好的律师, 所以我会解决你的分歧";
			dialog.text = ""+sTemp+" 与 "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+"。 这将花费你 "+FindRussianMoneyString(iSumm)+"。 ";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "很好, 洛克斯利先生, 我同意。 这是你的钱, 并尝试尽快解决问题。 ";
				link.l1.go = "relation";
			}
			link.l2 = "我现在没有你要的金额。 我稍后会回来! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "与你做生意很愉快, 先生。 你可以再次自由呼吸, 你的问题将在未来两周内消失。 请避免与 "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl") +" 发生任何对抗, 而我正在谈判中。 ";
			link.l1 = "好的, 我会考虑你的警告。 谢谢你, 再见! ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// < —移除国家敌对状态
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "你为什么要那样做? 走私者是好孩子, 他们以自己的方式诚实。 我们都需要生活和吃饭... 好吧, 这不是什么大事, 只需要花费你 "+FindRussianMoneyString(sti(npchar.quest.contrasum))+"。 ";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "很好, 洛克斯利先生, 我同意。 这是你的钱, 并尝试尽快解决问题。 ";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "我现在没有你要的金额。 我稍后会回来! ";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "太好了, 我会解决你的问题。 他们很快会想再和你做生意。 ";
			Link.l1 = "谢谢! ";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}