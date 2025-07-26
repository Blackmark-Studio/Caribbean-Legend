// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "先生, 您找我有何贵干? 我不和陌生人说话。如果您只是来闲聊, 或者想问1640年西班牙银船什么时候到Maricaibo, 那我得让您失望了。我的时间可不浪费在无聊的对话上。";
					link.l1 = "下午好, Fadey先生。您或许还不认识我, 但您肯定认识我的兄长。请允许我自我介绍——我是Charles de Maure, Michel de Monper的弟弟。";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "哈哈, 又是你啊, Charles! 你好吗? 这次又有什么事? ";
					link.l1 = "你说你被抢了……找到凶手了吗? ";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "所以, Charles, 你去跟那个野蛮人谈过了吗? ";
					link.l1 = "我有……这就是我为什么又来找你。";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "啊, 又是你啊, 我亲爱的朋友! 怎么样, 你带来给印第安人的赎金金币了吗? ";
					if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
					{
						if (PCharDublonsTotal() >= 80) // belamour legendary edition
						{
							link.l1 = "是的。这是你的八十枚达布隆。";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "不, 还没凑够呢。";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 100) // belamour legendary edition
						{
							link.l1 = "是的。这是一百枚达布隆。";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "不, 还没攒够呢。";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "哈, 原来是de Maure先生亲自来了! 我都说了进来, 别杵在那儿! 啥风把您吹到俺这破地方来了? ";
					link.l1 = TimeGreeting()+", Fadey, 我哥哥让我来找你。他说你能帮我找点活干。";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "哈, 是你啊! 什么风把您吹来了, de Maure先生? ";
					link.l1 = TimeGreeting()+", Fadey。哥哥坚持让我别跟你提这事, 可我实在忍不住……";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "哎呀, 老朋友! 快进来, 快进来, "+pchar.name+"! 你最近怎么样? ";
					link.l1 = TimeGreeting()+", Fadey。很高兴见到你。其实, 我有要紧的事要谈。黑金。";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "啊, 又是你啊, 亲爱的朋友! 你把战利品带来了吗? 找到足够的达布隆金币了吗? ";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "“是的, Fadey先生! 您的金币在这儿。”";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "没呢, 刚路过。我还在找合适的数量。";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, 我突然有个主意。那些奴隶我已经不需要了。请你见谅, 咱们回头见! ";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "啊, 我的老朋友! 快进来, 快进来, "+pchar.name+"! 你最近怎么样? ";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", 我又需要你的帮忙了。";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey。很高兴见到你。我有事要找你。";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "啊, 原来又是你啊, 我亲爱的朋友! 怎么样, 钱找到了吗? ";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "我已经准备好了, Fadey先生! 这是您的300枚达布隆金币。";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "我带来了, Fadey先生! 这是您的四万比索。";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "不, 只是来看看。我还在找合适的价钱。";
						link.l3.go = "exit";
					}
					link.l4 = "抱歉, Fadey, 我实在负担不起。只能自己想办法了。再见! ";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "快进来, 快进来, "+pchar.name+"! 我一看你那眼神就知道, 你是想听听俺的辉煌事迹吧。";
					link.l1 = "没错, Fadey。老子相信你已经带来了我要的东西。";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "啊, 又是你啊, 我亲爱的朋友! 怎么样, 钱找到了吗? ";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "拿上这三百枚达布隆。我会让水手们把这个箱子搬到我的船上。哎呀, 要不是有你, Fadey, 俺可怎么办啊? ! 你都不知道你帮了俺多大的忙! ";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "拿去, 四万比索。我让水手们把这箱子搬到我的船上。哎呀, 要不是有你, Fadey, 老子可怎么办啊? ! 你根本不知道你帮了我多大的忙! ";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "没呢, 刚过来。我还在凑够钱。";
						link.l3.go = "exit";
					}
					link.l4 = "抱歉啊, Fadey, 俺现在身无分文。定金你就留着吧, 希望能补偿你这次的花销, 剩下的俺自己想办法。后会有期! ";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "哎, 带记号的——我是说"+pchar.name+"! 快说说, 你给俺带了啥好东西? ";
					link.l1 = TimeGreeting()+", Fadey。很高兴见到你。我来是想和你谈点生意。";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"。我猜你肯定很想知道我和神父推心置腹谈话的结果吧。";
					link.l1 = "当然是我! 结果怎么样? ";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "啊, 原谅我, 你口袋里那叮当作响的声音实在太让我分心了! ";
					link.l1 = "这么贪心啊, Fadey! 给你金币。";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "哈哈, 老朋友! 快进来, 快进来, "+pchar.name+"! 怎么样, 有什么新鲜事吗? ";
					link.l1 = "你好, Fadey。我又来请求你的支持了。";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "你咋的? 杵那儿当雕像啊? 有屁快放, 没事就赶紧滚蛋, "+pchar.name+"! ";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "看看吧, Fadey。我猜这是一把波斯弯刀, 可能就是从你的收藏里偷走的那种? ";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "我有个好消息要告诉你。我这里还有一把波斯弯刀要给你。";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "我这里有第三把波斯弯刀。正如你所要求的, 我一拿到手就带回来了。";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "我是来谈我们之前说过的轻甲的事。";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, 我想买点你那有名的绳索。";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, 俺需要你帮忙。";
				link.l1.go = "help";
 				link.l9 = "现在没有什么事。";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "请问有什么可以帮您的, 先生? 我一般不和陌生人说话。";
				link.l1 = "哦, 我只是路过, 想看看这里住着谁。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "啊, 原来你就是老Michel的亲弟弟! 这可就不一样了! 快进来, 快进来, 先生, 请坐。要不要来一杯伏特加, 为咱们的相遇干一杯? 我这儿还剩几瓶, 能和好朋友的弟弟一起喝上一瓶, 真是荣幸, 达! ";
			link.l1 = "请原谅, Fadey先生, 今晚我就不喝酒了。我更希望直接谈正事。";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "你说啥! 这本地朗姆酒跟俄国伏特加比起来就是稀尿水! 你们根本不知道自己错过了啥, 要是老子撒谎就让大海吞了我! 行吧, 说正事吧。Charles, 老子洗耳恭听。";
			link.l1 = "先生, 我怀疑接下来我要说的话您可能会觉得很不愉快, 但无奈职责所在, 我必须如实告知! Michel告诉我, 您欠了他不少赌债。他还让我代为收取, 因为我兄弟现在……暂时无法亲自来见您。";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "哦, 年轻人! 当然, 我什么都记得, 我承认我欠你哥哥钱。 赌债是神圣的, 履行那个责任是唯一能让我们免受致命无政府状态和危险强盗侵害的东西! 但我求你, 请理解我的处境! 我最近发生了一件不愉快的事 --我被以最无礼的方式抢劫了! \n该死的小偷拿走了他们能拿的一切, 我多年劳动挣来的所有东西, 我的钱, 还有我无价的收藏品! 我现在根本无法清债, 不行\n但是, 德.莫尔先生, 我不会放弃我的义务! 我只请求你迁就我一下。 既然我现在身上也没有硬币, 我就把这把极好的稀有匕首给你。 看看! \n这是真正的钢铁杰作, 我被盗收藏中的骄傲。 此外, 它被印第安萨满施了魔法, 有强大的隐藏力量! 印第安人称之为‘酋长之爪’\n我本来绝不会同意把它送出去, 因为我为这把匕首付了一大笔钱, 比我的债务多得多, 但考虑到情况和我与你大哥的关系, 我准备把它给你。 拿着, 这是非常划算的交易! ";
			link.l1 = "相比一把刀, 我真的更想要钱... ";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "可我手头没钱, 只有这件稀有的魔法宝物! 你说说, 我的朋友, 换做别的时候, 老子会用这把华丽的魔法匕首来抵你那点破银币吗? 比索大街上都能捡到! 你得承认, 老子现在确实走投无路。光是想到要和这件绝世工艺品分开, 老子的心都在滴血, 但赌债如山, 这是老子的荣誉。虽然这宝贝对我意义重大, 但老子愿意只给你, 因为你是真正的君子, 也是老子的挚友。";
			link.l1 = "好吧, 既然你发誓身上没钱, 那老子就拿走你这把魔法匕首。希望能卖个好价钱……";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "“‘把它卖了’! ? 快滚吧, 呃——Charles! 不行, 老子简直不敢相信自己的耳朵! 老子把最宝贵的东西白白送给你, 这玩意儿在欧洲至少能卖十倍的价钱, 你倒好, 居然还厚着脸皮说要拿去当铺! ? 你知不知道, 这把匕首可是救过人命的! 老子跟你说——”";
			link.l1 = "那你刚才说的它的隐藏力量到底是什么? ";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "哦, 哈哈哈! Charles, 俺可是个虔诚的基督徒, 你懂的, 可不是啥印第安巫师。俺哪懂这把刀子里头藏着啥神秘力量。不过它确实有, 没错! 你把这匕首拿在手里, 自己就能感受到里面的力量! 拿着, 兄弟! 怎么样! 有没有啥感觉? ";
			link.l1 = "嗯……我什么感觉都没有。不过握在手里倒是挺顺手的。";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "哈哈! 这就对了! 不过这还只是它最不起眼的本事罢了。要是你在战斗中挥舞这把匕首, 肯定能见识到它各种惊人的威力! 那么, 你要收下吗? ";
			link.l1 = "好吧, 难道我还有选择吗? 既然你没钱, 那我就收下了……";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "多谢, Charles。你绝对不会后悔的, 真的不会! 给你。记得替我向Michel问好! 告诉他有空一定要来看看我。";
			link.l1 = "哦, 我会告诉他的……";
			link.l1.go = "exit";
			link.l2 = "你说你被抢劫了……找到凶手了吗? ";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "问题就在这, 俺可是一点都没剩下。那些混账把俺家洗劫一空, 银器、金子, 还有俺这些年辛辛苦苦攒下的积蓄, 全都卷跑了。其实这些俺倒也不太在意, 毕竟真正的绅士, 即便一无所有, 也绝不动声色! 钱财对绅士来说, 低贱得连皱眉都不值得。但最让俺心痛的是, 他们还把俺那一整套波斯弯刀也抢走了! 整个新大陆加旧大陆, 都找不到第二份这样的收藏。那可都是了不起的波斯骑兵佩刀啊……";
			link.l1 = "波斯刀剑? 听起来挺有意思啊。那你是个收藏家咯? ";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "嗯, 俺喜欢收集稀罕玩意儿……听着, Charles, 也许你能在这事上帮帮俺……";
			link.l1 = "帮忙? 可怎么帮? 你是说抓住那些贼吗? ";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "不, 不感兴趣那些小偷。俺只想拿回俺的波斯骑兵军刀。要是你能帮俺找回来, 俺一定不会让你白忙, 俺保证。";
			link.l1 = "嗯。但我到底该去哪儿找他们呢? 整个加勒比海? 还是说全世界都要找一遍? ";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "也许你能在那些岛上的街头小贩那里瞧见它们, 那帮混账根本不懂骑兵佩剑的价值, 肯定会当破铜烂铁卖掉。要是你在哪儿见到波斯佩剑, 就带来给我。你认得出来吗? ";
			link.l1 = "我想我会的。好吧, 我会留意的, 如果看到有符合描述的奇特刀剑, 一定会带来给你。";
			link.l1.go = "Sharlie_12";
			link.l2 = "说实话, 俺可不是什么兵器行家, 恐怕帮不上你。要是给你虚假的希望, 那可就不厚道了。";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "好极了! 希望你能走运, 找到那些神器, 到时候我一定不会亏待你。祝你好运, 猎人——呃我是说船长! 对了, Charles, 你能想象吗, 最近又有人想抢劫我! \n几天前有个贼想闯进我家\n这也太过分了! 不过这次他没跑掉, 被我逮住狠狠揍了一顿, 然后交给了城里的守卫。我希望他们赶紧把他吊死! ";
			link.l1 = "你觉得他是偷你弯刀的那些贼之一吗? ";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "可惜啊, 可是哭天喊地也没用。对了, Charles, 你能想象吗, 最近又有人想抢劫我! \n几天前有个贼竟然想闯进我家里\n这可真是太过分了! 不过他没能逃出我的手掌心: 我逮住了他, 好好教训了一顿, 然后把他送进了本地监狱。不能靠别人的痛苦来让自己高兴。我真希望他们早点把他吊死! ";
			link.l1 = "你觉得他是不是偷你弯刀的那些贼之一? ";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "不, 俺可不这么觉得。他就是冲着钱来的。俺逮住他在俺屋里翻俺的箱子。\n是个来自西班牙领地深丛林的印第安人。看起来滑稽极了, 跟这儿本地的完全不一样, 满身都是战纹, 还穿着花里胡哨的衣服……你要是有兴趣, 趁那小丑还活着, 自己去地牢瞧瞧吧。";
			link.l1 = "嗯……也许我该过去看看他。";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "去吧, 去看看这场怪胎秀... 好的, 夏尔, 这是一次愉快的聊天。 祝你回马提尼克的旅途顺利, 一路顺风!";
			link.l1 = "祝你一切顺利, Fadey。";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "有意思! 我洗耳恭听。";
			link.l1 = "Fadey, 我已经和那个印第安人谈过了。我来找你, 是想让你帮忙把他弄出来。那可怜的家伙只是想找点吃的……";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "哈哈哈, 你居然信了那种鬼话? 现在的年轻人真是太容易上当了……";
			link.l1 = "Fadey, 虽然我年纪比你小, 但我也能分得清别人是在说实话还是在撒谎。再说了, 你真觉得绞刑适合这种罪行吗? 这也太过头了。在我们家乡, 顶多挨几鞭子, 或者惯犯才会被烙个印。";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "过分! ? 他闯进了老子的家! 那野蛮人就不该来这儿! 要是你处在老子的立场, 你会怎么做? 老子敢打赌你也会把他肚子剖开, 扔给虫子吃, 对吧? ! ";
			link.l1 = "才不是呢, Fadey, 你还在为你那把被偷的弯刀生气吧。要不是那事儿, 你早就想揍这傻红皮一顿, 再踹他屁股走人了, 我说得不对吗? ";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "啊——Charles……你还真跟你哥哥一个样……好吧。咱们就像正经商人那样解决这事。既然你这么想要这个印第安人, 那你就赔偿俺因他造成的精神损失和财产损害, 俺就会跟指挥官说俺不打算追究责任。怎么样? ";
			link.l1 = "多少钱? ";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "哈, Charles, 你已经开始学会加勒比的规矩了。一百五十枚金币达布隆, 一个子儿都不能少。";
			link.l1 = "Fadey, 愿上帝怜悯……";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "好吧, 好吧。一百枚金达布隆。这可是我的最终报价了。咱们说的是达布隆, 不是比索。我们的银行家肯定能凑出这么多钱来兑换。";
			if(PCharDublonsTotal() >= 100) // belamour legendary edition
			{
				link.l1 = "我现在就有你要的数目。拿去吧, 这是一百枚达布隆。";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("值得信赖", "Trustworthy");
				link.l2 = "值得信赖的Fadey, 听我说……我明白你有多郁闷, 但现在只有我愿意用真金白银补偿你这点麻烦。";
				link.l2.go = "Tichingitu_7_TW";
			}
			else notification("特质检查失败", "Trustworthy");
			link.l3 = "好吧, 我这就去拿你要的东西。";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "朋友, 你在这儿前途无量, 老子跟你说。好吧! 八十金币——一分都不能少! ";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "快点, Charles! 你只有十天时间, 他就要被处决了。";
			link.l1 = "我会记住的。再见! ";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(pchar,"questTemp.Sharlie.Tichingitu80"))
			{
				RemoveDublonsFromPCharTotal(80);
				DeleteAttribute(pchar,"questTemp.Sharlie.Tichingitu80");
			}
			else RemoveDublonsFromPCharTotal(100); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "很好。我这就写个便条盖上印章, 稍等片刻……给你。把这个交给指挥官, 你就能把你的印第安人带走了。我是真不明白你为啥这么操心他, 不过那是你的事。你打算干啥, 把他带去假面舞会当展品? 哈哈, 真有意思! ";
			link.l1 = "上帝无所不见, Fadey。救人一命是高尚的行为。";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "我同意你说的第一句话, 但第二句就见仁见智了, Charles。要是你救下的那个人其实是个杀人犯或者强奸犯, 本该上绞刑架接受正义的审判呢? 哼, 算了, 这事儿跟我没关系了。愿上帝与你同在。快去找指挥官吧, 免得你那红皮肤的朋友还没吊上去就吓得脸都白了……";
			link.l1 = "我这就去。回头见, Fadey。";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "你看起来很严肃, 朋友! 是不是要给我带来什么坏消息? ";
			link.l1 = "事情就是这么回事, 没错。我跟你直说吧, Fadey: Michel说你用这破玩意儿‘酋长的爪子’耍了我。他说这根本不是什么古董, 随便哪个街头小贩花几百比索都能买到。我去打听了一下那些卖金属货的小贩, 他们给我的报价也正是这个数。";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "哎呀, de Maure先生……我可是受伤了! 你哥哥真让我意外。街上的那些半吊子骗子怎么胡说八道都无所谓, 可他竟然也这样! 你说说看, Charles, 要是有人拿着一把查理曼大帝时代的双手骑士剑来卖给你, 你会出多少钱买? ";
			link.l1 = "双手大剑? 你他妈在逗老子吗, Fadey? 老子要那把生锈的刽子手大刀有啥用? 现在可是主耶稣的十七世纪! 老子一分钱都不想给! ";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "唉, 你看看你这目光短浅的样子, 朋友! 你这种态度, 永远成不了大事。要是你把那样的神器带来给我, 俺会出三百达布隆买下。你问为啥? 因为那是古董, 是如今世上难得一见的历史珍宝! 你啥也不懂, 还敢妄下断语! \n以天主和圣母为证, 酋长的利爪可是一把大师级的匕首, 我的消息说, Cortez本人曾经拥有它。没错, 就是那个Hernan Cortez! 传说中的征服者, 攻陷特诺奇提特兰、活捉阿兹特克皇帝的传奇人物! 你倒好, 还敢嗤之以鼻, 说这玩意儿是破烂! \n再说了, 我早跟你说过, 这可不是普通的匕首, 这是把附魔的匕首! 你还嫩得很, 连加勒比的奇迹都没见识过? 法术、魔咒、仪式、诅咒? Charles, 这里可是新大陆, 是玛雅和阿兹特克的故乡, 他们的邪术造诣高得让咱们基督徒都难以想象! \n这匕首有隐藏的力量。可惜现在还没人知道到底是什么力量。你有独一无二、不可思议的机会亲自去发现它的秘密, 可你还在说这东西是“狗屎”, 还说你那可怜的老朋友Fadey想坑你! \n要是俺有钱还你兄弟的债, 俺立马就用你那点可怜的臭钱把它换回来……这可是真正的宝贝, 它的价值远不止金钱能衡量, 是的! ";
			link.l1 = "好啦好啦, 别激动, Fadey。我信你。你的说辞确实有说服力, 你表现出来的那股火热劲儿, 要么证明你是真心的, 要么说明你撒谎的本事无人能及。";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "多谢! Charles, 你做得很好, 没有生气, 还直接来找我解释。我相信现在这事就算揭过去了吧? ";
			link.l1 = "是的, Fadey先生。完全正确。现在请允许我告退……";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "站住, Charles! 说实话, 老子挺喜欢你的风格。说不定哪天咱俩还能成最铁的兄弟。既然如此, 何不现在就迈出友谊的第一步? 俺在地窖里用冰泉水冰着两瓶上好的俄国伏特加。你说咋样, 咱俩开一瓶, 为你兄弟的健康干一杯? ";
			link.l1 = "嗯, 抱歉了, Fadey先生, 但我已经该启航出海了。我现在有点赶时间。";
			link.l1.go = "vodka_no";
			link.l2 = "上次你提过, 俺拒绝了……要是再拒绝就太不给面子了。行吧, Fadey, 俺加入! ";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "真可惜啊。跟伏特加比起来, 朗姆酒就是水, 淡得要命的便宜货。不过既然你赶时间, 老子就不耽误你了。祝你好运, Charles! ";
			link.l1 = "彼此彼此, Fadey先生……";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "这话说得好! 太棒了! 快请坐, 歇歇脚! Monsieur, 您就当自己家一样, 我去拿伏特加。唉, 好久没和朋友们这样下午小聚了! 伏特加冰得正好, 您一定会喜欢, 来, 干杯! 我再摆点腌黄瓜和熏火腿。";
			link.l1 = "……";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "哇……所以, Fadey, 你跟俺说说, 这到底咋回事? 嗝! 咱俩……喝了两瓶伏特加……顺便说一句! ——你看起来一点都没醉, 俺却醉得跟烂泥一样。为啥会这样啊, 嗯? ";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, 我的朋友, 放轻松点。一只臭鼬跟这事有啥关系? 咱们刚喝了上好的伏特加。赶紧睡一觉, 醒来你就精神百倍, 连宿醉都没了, 脑袋也清爽多了。你等着瞧吧。";
			link.l1 = "呃——对, 伏特加……这、这伏特加真是太棒了。我从来没喝过这么厉害的酒。";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "哈! 你说得没错! 那种伏特加可是按照祖传秘方酿的, 从俺的祖国俄罗斯运过来的, 就连在那儿也不是谁都能酿得出来。俺只买最好的! 就像咱们刚才喝的这瓶一样。";
			link.l1 = "可、可是你告诉我, Fadey: 你、你怎么能喝那么多还不醉? 你、你是怎么做到的, 嗯? 把秘诀教教我呗。说不定以后用得上……嗝! ";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "哈! 你我可没法比啊, 小Charles! 瞧瞧你, 瘦得跟根鞭子似的。再说了, 你还不习惯痛快喝酒, 对吧! 不过咱俩是铁哥们, 老子就教你几招, 怎么喝酒还能不尿裤子。";
			link.l1 = "请……求你了……嗝! ";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "如果你想喝酒又不想立刻被放倒, 那就得遵循几条关键规矩。最重要的是, 千万别空腹喝酒。开喝前先吃点实在的东西垫垫肚子\n其次, 每喝一杯别忘了再吃点东西。肉或者鱼最好, 咸一点的更合适。第三, 别用伏特加漱口, 直接一口吞下去\n还有, 正餐前来上一小杯——不超过半品脱——能让身体提前适应后面的烈酒。可别喝多了开胃酒, 不然效果适得其反, 还没出海就先把自己喝趴下了\n最后, 关键还是得靠平时的锻炼, 定期适量喝点朗姆酒或者其他酒精饮品, 慢慢你就能扛得住了。";
			link.l1 = "嗯嗯……原、原来是这么做的! 俺一、一定会……嗝! ……记住你说的每一步, Fadey。谢、谢谢你。现、现在俺觉得最好还是去眯一会儿, 因为俺现在真有点不舒服……";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "休息一下吧, Charles。今晚我们过得很愉快! 祝你好运, 狩猎顺利! ";
			link.l1 = "再、再、再见了, Fadey! 老子要去——嗝! ——找许愿神啦! ";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "什么, 他真说过我要帮你? ";
			link.l1 = "差不多就是这样。你愿意帮帮你多年老友的弟弟吗? 我又不是乞丐来讨施舍, 只是想求你给个赚钱的机会。";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "哎呀, Charles! 你来晚了。要是你早点来, 俺肯定能给你安排个合适的活儿, 可现在——没办法。别担心, 去各个城里转转, 多跟人聊聊。在加勒比这地方, 活儿多得是。";
			link.l1 = "明白了, 真遗憾。告辞! ";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "嗯。不是, 当然不会拒绝你。如果你想让一个人吃饱, 别给他鱼, 给他鱼竿才对。是不是这样, de Maure先生? 所以你需要份差事……这简单。我去和我认识的一个人聊聊, 把你推荐给他。剩下的就看你办事的本事了。";
			link.l1 = "太好了。我该去找谁谈? ";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "明天来店里一趟。有个叫Gerard LeCroix的人会在那儿等你, 他会给你安排点活儿。他只会在这殖民地待到明天傍晚。尽快去见他, 把事情办利索点。别让我难做人。";
			link.l1 = "成交。谢谢你, Fadey! ";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "啊, 我的朋友, 有什么我能帮忙的吗? ";
			link.l1 = "Fadey, 听我说, 俺真的得从走私贩那儿买五十个奴隶。问题是俺在他们那儿没名气, 需要你帮俺引荐一下。没你出面, 他们根本不会理俺, 这事关系到一个大人物的生死。";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "哦吼! 看来你是要拓展生意啊! 真是会赚钱! 老朋友, 俺当然愿意帮你。不过你也知道, 俺可不是白干活的。想让卖家相信你是真心想买黑奴, 得花上一百五十枚金币——当然, 还得给俺点辛苦费……";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "这正是我所期待的, Fadey先生! 这是你的金币。";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "我这就去找放债人! 等着, Fadey先生, 我马上回来! ";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, 我好像有了新主意, 现在不需要那些黑奴了。抱歉啦。再见! ";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "很好, 朋友。不过要是你想拿买东西的借口来糊弄我, 结果却是些没用的事儿, 你会把我惹火的。你可不想那样。明天黄昏十点, 卡普斯特湾泳滩, 老子会给你安排见面, 别耍老子。";
			link.l1 = "你放心吧, 货我一定会带回来。";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "你好你好! 说说看, 朋友, 是什么风把你吹到俺这寒舍来的? ";
			link.l1 = "我需要武器。本地商人凑不齐我需要的数量, 但我觉得你能帮上忙。";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "首先, 亲爱的朋友, 请告诉我你到底需要什么。然后我会如实告诉你, 我能否帮得上忙。";
			link.l1 = "我要三十把士兵用的手枪, 两支火绳枪, 七十发配套的子弹, 还有九十瓶治疗药水。";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", 你吓到我了。先是五十个黑奴, 现在又是武器。伙计, 你这是想搞奴隶起义吗? ";
					link.l1 = "很敏锐啊, Fadey。正如我之前说的, 这一切都是为了拯救一个重要的人。别担心, 他会从西班牙人的魔爪中被救出来, 你在这里的名声不会受影响。";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "听到这个消息真好。我可以帮忙。";
			link.l1 = "很高兴听到这个消息。多少钱? ";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "很高兴你解释清楚了。如果这事真的跟西班牙人有关, 我会帮你。但要是让我发现你耍了我, 我可就要发火了。";
			link.l1 = "相信我一点吧, Fadey。多少? ";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "好吧, 那么……手枪, 还有几支火枪, 每支都要配火药和弹丸……所以……我不能保证能把你要的东西全都弄齐, 但我一定尽力而为。与此同时, 我需要你先付四万比索的定金, 或者你愿意的话, 也可以付三百枚达布隆。";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "把金币拿去吧, Fadey。正好老子身上现在就有几枚。";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "俺的达布隆全花光了, 拿比索吧, Fadey。";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "我要去找我的银行家, 马上回来! ";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "抱歉, Fadey, 我实在付不起。只能自己想办法了。再见! ";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "明天再来, "+pchar.name+", 我就把你要的物资准备好。";
			link.l1 = "那我就不打扰了。明天见! ";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "明天来吧, "+pchar.name+", 我会把你需要的物资准备好。";
			link.l1 = "那我就不打扰了。明天见! ";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "小子, 老头我能在这么紧的时间里把你要的东西全都找齐, 算你走运! 你可得感恩戴德! 好了, 最后一笔钱。把之前押金同样数目的钱再给我一份, 然后拿走你的武器吧。";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "拿着这三百枚达布隆。我会让我的人把武器搬到我的船上。要不是有你, Fadey, 老子可怎么办啊? 你根本不知道你帮了我多大的忙! ";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "拿上四万比索吧。我会让我的人把武器搬到我的船上。要不是你, Fadey, 俺还真不知道该怎么办! 你根本不知道你帮了俺多大的忙! ";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "该死, 我怎么能把钱忘了? 我很快就回来。";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "抱歉, Fadey, 老子身无分文。押金你就留着吧, 希望能补偿你这次的花销, 剩下的老子自己想办法。后会有期! ";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey 的武器已装载到船上");
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "帮助有需要的人是荣誉, 帮助付钱的人是乐趣。下次你到巴斯特尔, 记得来找我打个招呼。";
			link.l1 = "这太荒唐了——人在巴斯特尔却不去见我的朋友Fadey! 下次见! ";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey 的武器已装载到船上");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "帮助有需要的人是荣誉, 帮助付钱的人则是乐趣。下次你到巴斯特尔, 记得来找我打个招呼。";
			link.l1 = "这太荒唐了——都到巴斯特尔了还不见我的朋友Fadey! 下次见! ";
			link.l1.go = "exit";
		break;
		// <-- legendary edition

		case "guardoftruth":
			dialog.text = "哎呀, 谁还会怀疑你是来办正事的呢, 伙计! 可惜现在没法请你喝伏特加, 都被我喝光了。说说吧, 这次你又惹上什么麻烦了? ";
			link.l1 = "有个私掠者为了赎罪, 向本地教区献上了一枚镶有青金石的黄金胸十字架。这东西独一无二, 价值连城。问题是, 这枚十字架是从另一座教区偷来的。不仅如此, 抢劫时还有一位神父被杀了。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "哎呀, 圣洁的圣母啊! 你竟然这么说! ";
			link.l1 = "嗯。俺是代表被抢劫的教区信徒, 想把十字架还给原本的主人。";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "高尚之举, 虔诚至极。是在向上帝邀功吗? ";
			link.l1 = "可那位本地神父就是不肯还给我, 不管我怎么解释他都不听。我真不明白, 怎么能把一只沾着无辜者鲜血、被偷来的十字架, 心安理得地摆在上帝的殿堂里? 这简直是亵渎! ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "严格来说, 每一只被祝圣的圣杯都承载着无辜基督的圣血……不过我扯远了。我猜你是想让我帮忙吧? ";
			link.l1 = "当然! 您在巴斯特尔很有影响力, 大家都很尊敬您, 也许神父会听您的劝告。";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", 你把这个被盗的十字架的严谨的故事告诉我们的神父了吗? ";
			link.l1 = "当然! 我呼唤过他的宗教情感, 基督徒的团结, 他那该死的良心, 看在上帝的份上, 但他充耳不闻。 ";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "嗯……你有没有试过用别的方法说服他? ";
			link.l1 = "你是说贿赂他? 老子可不会去贿赂神父。如果他是个银行家、商人, 甚至总督, 老子或许会用这种办法解决问题, 但神父可不行! ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "我亲爱的天真朋友啊, 如果神父的耳朵真对良心的呼声充耳不闻, 那他的手肯定会对黄金敞开……或者反过来也说得通。我会帮你的, 我觉得把这么一笔带着污点的宝藏留在这儿, 迟早会惹出更大的麻烦。不过, 这事可得花点钱。"link.l1 ="我就知道会这样。这次要多少钱? ";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "明天再来吧, "+pchar.name+", 俺现在还定不了价。不过你放心, 那被偷的十字架肯定会还给你。";
			link.l1 = "好吧, Fadey, 那我就不打扰你了。明天见! ";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "正如承诺的那样, 十字架我已经带来了。至于细节……算了吧……一切荒唐都因我们至圣救主的宝血而被宽恕";
			link.l1 = "我还欠你多少钱? ";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "二百五十枚达布隆。算是补偿俺的花销, 当然, 俺这正义之举要是能再给点小费, 俺可更高兴……";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "遵命, Fadey先生。您的金币在这儿。";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "我得去船舱拿金币, 马上回来。";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "好吧。被偷的十字架在这儿。";
			link.l1 = "谢谢你, Fadey。你根本想象不到你帮了我多大的忙! ";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "我总是很乐意帮忙, 尤其是对善良——更重要的是大方——的朋友。以后常来坐坐, 说不定哪天老家那边的伏特加送到, 我请你喝一杯。";
			link.l1 = "乐意之至! ";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "哟哟, 大海还没把你吞了啊! 说说吧, 这次是什么倒霉事把你带到老子门前的? ";
			link.l1 = "我也说不清这些算不算倒霉事, 但不管怎样, 我现在就在这儿。Fadey, 咱们第一次见面时你送了我一把稀有的匕首, 叫酋长之爪。现在我知道那匕首原本属于一个叫Archibald Calhoun的人。拜托了, 把你知道的关于他的事都告诉我吧。";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "什么都瞒不过你, "+pchar.name+"。你看得一清二楚, 和你兄弟一个样。没错, 这把匕首是我在骰子游戏里从Calhoun手里赢来的。他是谁? 老实说, 我自己也不知道。我们在酒馆偶遇, 聊了几句, 喝了点酒, 他就开始跟我吐露自己过去的一些罪孽, 说那些事一直压在他心头……";
			link.l1 = "你是他忏悔神父吗? 什么罪? ";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald一直被某个因他而被宗教裁判所折磨致死的男人的记忆所折磨, 还有那些他杀害的无辜灵魂。他不停地称自己为犹大, 说上帝在惩罚他的罪孽, 宗教裁判所正在追捕他。\n他还提到西班牙宗教裁判官Vincento亲自要他死, 派雇佣兵在整个加勒比追杀他。后来酒精战胜了他的理智, 我们就赌起了这把旧匕首。";
			link.l1 = "就这些? 你再也没见过他? ";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "当然不是, 他已经死了。一帮可怜的海盗把他的弗吕特船送进了Davy Jones的海底地狱, 整船人都归了Mictlantecuhtli。说实话, 传言他们其实是被装成海盗的专业杀手袭击的……宗教裁判所的爪牙。都说Vincento神父从不放过目标。";
			link.l1 = "Archibald Calhoun还活着。我不久前刚见过他, 和一个叫William Paterson的人在一起。他现在是Paterson的副手。";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "哟呵, 这可真是意外! Archibald好歹能在Paterson船长的庇护下喘口气, 身边也算有好人。西班牙人一提起Paterson就跟见了瘟疫似的, 谁敢在他罩着的时候动Archibald的歪心思? ";
			link.l1 = "你认识Paterson吗? ";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "谁不知道William Paterson! ? 他和你一样, 都是刚到加勒比的新面孔。可他也像你一样, 已经闯出了响当当的名声。Patterson先生是Fox上校最亲密的朋友, 还和加勒比所有英属殖民地的总督Windsor勋爵关系匪浅。他经常去牙买加皇家港的总督府做客。";
			link.l1 = "明白了。多谢你的消息, Fadey! ";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "哎呀, 别客气, 朋友。哪天来找我玩啊! 祝你好运! ";
			link.l1 = "那是当然! ";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "让我看看, "+pchar.name+"……哈! 就是这个! 好样的, 今天多亏了你! 你是在哪儿找到的? ";
			link.l1 = "这无关紧要。重要的是它最终回到了你手中。";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "只要你能彻查此事, 俺会给你丰厚的报酬。三百枚金达布隆, 应该足够补偿你的辛苦……";
			link.l1 = "你是用之前从老子这儿榨出来的金币付钱吗? 不过嘛, 老子也不会嫌弃。你的弯刀, 拿好。";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "多谢你, 我的朋友! 感谢你的佩剑, 也感谢你那带刺的话语。"+pchar.name+", 你年纪轻轻却如此睿智, 不过人类之间的情谊比黄金还要珍贵。说到黄金——我会全额付清。这些达布隆拿去吧。";
			link.l1 = "谢谢。";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "说到友谊的纽带, 尤其是你我之间的, "+pchar.name+"。我这里有个你一定感兴趣的东西。";
			link.l1 = "让我猜猜, 又要伏特加? ";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "哈! 伏特加是好东西, 但我的祖国闻名的不止这个。 有一种特殊材料只有俄罗斯能生产。 我从国内联系人那里运来这里交易。 每个船长都想要, 因为它能改善任何船只。 我说的是麻绳\n防潮又抗海盐的麻绳。 据说这是做索具的最佳材料\n每个月我从雷瓦尔收到一定数量。 通常每月中旬我的仓库里会有几百卷。 所以, "+pchar.name+", 我提议卖给你一批五十卷。 每卷十枚达布隆\n我只有两个条件: 第一, 我会把你的绳子留到每月20号; 第二, 你只能买整批。 五十卷五百枚达布隆。 悄悄说, "+pchar.name+", 据说有些地方可以把这些绳子卖得贵得多, 但我知道什么呢! 我对自己现在的生意很满意, 不需要自己找经销商。 如果你找到好商人, 可以大赚一笔。 ";
			link.l1 = "明白了。 好提议, 法捷伊! 我想抓住你给的机会。 那么, 每月二十号, 五百达布隆买五十根? ";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "去吧, 把你买的东西拿走。不过, 等等, 等等, 亲爱的朋友! 除了这把你出于善意归还给我的弯刀之外, 还有另外两把。我恳求你, 如果你能找到它们, 请务必带回来, 老子一定会给你比公道价更高的报酬。";
			link.l1 = "当然, Fadey。如果让我找到他们, 我一定带回来。";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "有好消息给你。俺又弄到了一把波斯弯刀。";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "哎呀, 我的好朋友! 你刚刚帮我擦干了眼泪! 让我看看……哈! 就是它, 我心爱的弯刀! 来吧, 说到做到, 这里有三百杜布隆赏金给你。";
			link.l1 = "谢了! ";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "请接受我的谢意, 以及一份微薄却极其实用的小礼物。我用不上它, 但你或者你的船匠一定会觉得很有用。\n来, 看看这枚精美的戒指! 现在归你了。不过, 这可不是普通的戒指, 而是一枚附有魔力的戒指。它能帮你铺设地毯, 也能修理船只。许多工匠都想要它, 但我一直留着, 等着特别的时刻。收下吧, 朋友, 希望它能减轻你的负担! ";
			link.l1 = "你身上果然带了不少有趣的宝贝。多谢啦, Fadey! ";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "我那失落藏品里只剩最后一把弯刀还没找到。我全指望你了, "+pchar.name+", 也指望你的好运。如果你找到了, 别犹豫, 赶紧回来找我。";
			link.l1 = "当然! 很快再见……";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "我为何要着急? 剑就在我身边。";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "哦, 感谢上帝, 我偏偏找了你帮忙, "+pchar.name+"。 你是个奇迹之人, 我的朋友! 给我看看... 哦哦! 是它, 是她。 我的宝贝! 美人! 太感谢了, 好伙计, 我向你鞠躬! 给, 这是你的钱。 四百枚达布隆, 一分不少! 我不会小气。 ";
			link.l1 = "谢谢你, 法捷伊。 帮忙很荣幸。 ";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "俺的弯刀收藏终于又齐了! 这回谁也别想再从俺手里偷走, 俺会亲自看着! 你可是帮了大忙的好汉, 俺有份特别的奖赏给你。两周后, 会有个商人从欧洲给俺带来一套顶级击剑护甲。这可是贵族定制的, 世上独一份的护甲。\n如果你想要, 只需七百枚金达布隆就能买下。俺会跟那贵族说, 这护甲在运输途中丢了。";
			link.l1 = "这身盔甲有什么好的? ";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "这件又舒服又耐用, 防护效果跟铁甲一样好, 而且外观也很棒! 你过两周再来看看吧。不过可别超过一个月, 不然我就把它卖回给原本的客人了。";
			link.l1 = "成交。两周后我会去你府上拜访。";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "是的, 已经送到了, 就等你来取。钱带来了没? ";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "是的。这里有七百枚达布隆。";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "该死, 钱忘在船上了。我马上拿来! ";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "是的, 老兄! 来, 拿去吧。这身藤甲可不一般, 俺跟你保证, 全加勒比海也找不出第二件! ";
			link.l1 = "是的, 我看出来了。谢谢你! 迫不及待想试试了……";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "你还等什么? 快试试吧。看看合不合适。";
			link.l1 = "好的, 回头见, Fadey先生! ";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "进来吧, 亲爱的朋友。货物已经为您备好, 二百五十件, 总共二千一百二十五金币。";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "一切都按我们说好的来。拿钱吧。";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "让我去船舱把钱拿来。";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "进来吧, 亲爱的朋友。货物已经为您备好, 五百达布隆可以买五十件。";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "一切都按咱们说好的, 拿钱吧。";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "让我去船舱把金币拿来。";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, 我们能不能扩大一下交易的规模? 我现在愿意从你这儿多买五倍的货! 我觉得这对咱们俩都有好处。你怎么看? ";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, 我把钱带来了! 三千枚金币达布隆, 按约定的数目。";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "很高兴和你做生意, "+pchar.name+"。我这就让手下把绳索搬到你的船上去。";
			link.l1 = "谢谢! ";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "如果你还需要更多的绳索, 一个月后再来吧。";
			link.l1 = "好吧, Fadey。回头见! ";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "亲爱的朋友, 有什么可以为您效劳的吗? ";
				link.l1 = "Fadey, 你可是个有头有脸的人物。总督的朋友, 据说在宫廷里也有人脉。要是我哪天惹上官司, 你能不能帮我在当局那儿说句话? ";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "有什么我能帮忙的吗, 朋友? ";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "我和英国当局有点麻烦。";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "我惹上了法国当局的麻烦。";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "我和那些走私贩有大麻烦了。";
				Link.l5.go = "contraband";
            }
			link.l9 = "抱歉, 我觉得我自己能应付。";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "哎哟哟, 我的好兄弟, 谁跟你说的这些? 人人都会撒谎。不过既然你是Michel的弟弟, 又是我的好朋友, 我可以试着帮你摆平点事。我只能帮你向英国和法国当局求情, 毕竟我的关系也有限。西班牙人和荷兰人那边, 老子可不掺和。\n我还得提醒你, 我的影响力也就只能帮你摆平点小麻烦。要是你只是犯了点小错, 或者惹了点小怒气, 我还能劝他们网开一面。可要是你真去挑起战争, 还指望我给你擦屁股, 那可别怪我不管! \n还有, 我一次只能安抚一个国家: 法国或者英国。老子可没本事一分为二, 左右开工。当然, 打点贿赂的钱也是少不了的。如果你觉得我的条件还行, 随时可以来找我帮忙。";
			link.l1 = "谢谢你, Fadey。我会记住的。";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "当然。我可是听说过你的那些冒险——或者说倒霉事。你的小麻烦, 交给我吧, 只要金子够多, 什么事都能摆平。三百个金路易, 老子就能把你从锅里捞出来。";
				if (PCharDublonsTotal() >= 300) // belamour legendary edition
				{
					link.l1 = "太好了! 金子在这儿。";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "那正好是俺去拿金币的时候。";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "当然。你的那些冒险——或者说倒霉事, 俺可是听说过的。你那点小麻烦, 俺能搞定。只要金子给得够, 啥事都能摆平。六百枚金达布隆, 俺就能把你从锅里捞出来。";
					if (PCharDublonsTotal() >= 600) // belamour legendary edition
					{
						link.l1 = "太好了! 金子在这儿。";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "那正好是俺去拿金币的时机。";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "是啊, 你现在可是麻烦大了! 这事儿老子也没法全给你摆平。不过, 眼下这场要劈在你罪恶脑袋上的霹雳, 老子倒是能帮你缓一缓。以后只要你有钱有心, 咱们随时还能再行贿一次。七百枚金达布隆, 老子就能开始替你摆平这些烂事。";
					if (PCharDublonsTotal() >= 700) // belamour legendary edition
					{
						link.l1 = "老子受够了那些海盗猎人追着不放。金子给你。";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "那正好是俺去拿金币的时候。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "好吧, 给我十到十五天左右。这期间我会安排见面, 把这些事都处理好。大概两周内就能搞定。";
			link.l1 = "谢谢你, Fadey! 我会等着的……";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "你干嘛要去惹他们啊, 老兄? 在这片地方, 走私贩可不算最坏的人, 他们还能让你赚上一笔。行吧, 我帮你, 我知道怎么哄他们高兴……七百达布隆, 别讨价还价。";
			if (PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				Link.l1 = "好吧, Fadey, 我同意。拿走你的金币吧。";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "我现在身上没那么多金币, 等会儿再来! ";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "好吧, 这事包在我身上, 别担心。他们很快又会跟你做生意, 就像以前一样。";
			Link.l1 = "谢谢! ";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "哈哈哈, 看你生意红火, 胃口也越来越大! 你说得对, 咱们的货确实上乘, 价钱也公道。不过可别忘了, 想做大买卖还得投入本钱! 这种生意得认真对待, 才能做到尽善尽美。";
			link.l1 = "我要是没留个几百枚达布隆当底子, 会来给你提这种条件吗? ";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "我知道你箱子里肯定有不少金币, 绝不止几枚, 装下五十枚都绰绰有余! 可咱们这买卖可不是寻常生意——不仅仅是搬货, 更得讲究个……低调。要做这么大的买卖, 你得下血本, 不只是付钱, 还得投资, 才能赚到大头! 还得保证你的钱不会凭空蒸发。如果你舍得拿出三千枚金达布隆, 那你尽管放心, 老哥我一定替你办得妥妥当当, 像对待好兄弟一样, 绝不会在价格上坑你。";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "三千达布隆! 哎呀, 我得承认, 就算是最富有的商人, 在最离奇的传说里也难得听到这么慷慨的报价! 很少有人愿意如此大方地投资这种冒险。但幸运的是, 俺正是其中之一。钱在这儿, Fadey先生。";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "三千金币达布隆! Fadey, 这么大一笔钱俺可拿不出来, 真是遗憾。俺以后再来吧。";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "你说三千? 嗯……说实话, 这种数目还真让人佩服你的野心。不过我得承认——这事儿老子可干不了。";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "真是变脸比翻书还快! 你刚提了个条件, 转头就反悔! 说实话, 我挺失望的, 但咱们的交情还在, 不会因此断了。就按老规矩来: 之前说好的, 每月二十号, 五十捆, 每捆十达布隆, 照旧。";
			link.l1 = "你能明白我就好, Fadey。老子也想改主意, 可惜这种花销实在超出我的能力。唉, 这事上我实在是力不从心。";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "既然你已经决定了, 那就没什么好谈的了。这次选择不会影响咱们的友谊。记得常来, "+GetSexPhrase("好先生","美丽的女士")+"。";
			link.l1 = "告别了。";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "这才明智! 你不是空谈之人, 而是知道如何行动。 对于像你这样的商人, 总能找到折扣! 未来所有 shipments 都打八五折! 我们的协议是: 我每月为你准备二百五十卷麻绳。 你可以像以前一样在20号来取, 付两千一百二十五枚达布隆, 不找零。 ";
			link.l1 = "完美, 法捷伊! 和你做生意太轻松了。 我相信我们会成功。 下次见! ";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}