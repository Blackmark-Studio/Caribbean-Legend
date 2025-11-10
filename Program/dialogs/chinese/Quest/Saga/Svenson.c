// 扬.斯文森 - 西梅因的海盗男爵
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "啊, 查尔斯。 感谢你过来。 只是想感谢你花时间陪海伦。 这女孩需要治愈她的伤口, 而且我听说你也玩得很开心, 哈哈! 该死, 我甚至有点嫉妒! ";
					link.l1 = "你不生气吗? 关于木桶和... 所有其他事情? ";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "啊, 查尔斯。 感谢你过来。 只是想感谢你花时间陪海伦。 这女孩需要治愈她的伤口, 而且我听说你也玩得很开心, 哈哈! 祝你在卡塔赫纳一切顺利! ";
					link.l1 = "是的, 我也很高兴昨天一切顺利。 回头见, 扬。 ";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // 时间不足时的筛选
				{
					dialog.text = "哦, 我的朋友" +pchar.name+ "! 很高兴见到你! 我能为你做什么? ";
					link.l1 = "只是顺道来看看你过得怎么样。 ";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // 巴考特贸易
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "扬, 我想买些铁木。 ";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "我能为你做什么, 先生? ";
					link.l1 = "我想请求你的帮助, 森林恶魔。 ";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "啊哈, 我的朋友" +pchar.name+ "! 有什么消息? ";
					link.l1 = "我设法从刽子手那里了解到很多有趣的事情。 ";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "那么, " +pchar.name+ ", 你和格拉迪斯谈过了吗? ";
					link.l1 = "是的, 谈过了。 扬, 看看这个... 你能告诉我这张羊皮纸碎片的事吗? ";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "我还没有什么新消息告诉你, " +pchar.name+ "。 但我正在解决我们的问题。 稍后再来。 ";
					link.l1 = "好吧, 扬。 回头见。 ";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // 开始三个男爵任务
				{
					// 第一次时间检查。 斯文森对主角的拖延非常不满。 我们认为海伦, 对斯文森的访问将关闭
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "" +pchar.name+ ", 你让我彻底失望了。 我期望你是个认真的人, 但结果你只是个傻小子。 你这段时间到底在哪里? 当你在做天知道什么的时候, 英国人占领了宝藏岛! \n我所有的计划都毁了! 老实说, 我几乎忘记了你的存在, 也不想再被提醒。 滚吧! ";
						link.l1 = "我简直不敢相信! ";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "你来了, " +pchar.name+ "。 我已经仔细考虑过我们的困境。 我不一定会称之为计划, 但是... ";
						link.l1 = "我洗耳恭听, 扬。 ";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // 进行三个男爵任务
				{
					dialog.text = "事情进展如何? 有什么我可以帮助你的吗? ";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "我和黑牧师谈过了。 遗憾的是, 我们的谈话结果让我不得不回来找你寻求建议, 我被难住了。 ";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "我找到了迪奥斯, 我们聊得很愉快。 他告诉我很多有趣的事情, 但不幸的是我们没有谈到关键问题。 ";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "哦, 扬。 我有太多事情要告诉你, 整晚都说不完, 所以我长话短说。 ";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "我从正义岛接回了纳撒尼尔.霍克。 他现在在我的船上。 ";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "我把纳撒尼尔.霍克送到米斯基托村, 由一个叫蛇眼的萨满治疗。 他答应我会恢复纳撒尼尔的健康。 ";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "目前没什么可告诉你的。 只是顺道来看看你。 ";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // 失败 - 百夫长号沉没
				{
					dialog.text = "有什么消息吗, " +pchar.name+ "? 情况如何? ";
					link.l1 = "哦, 糟糕透了。 我做了这么多工作... 我追踪到杰克曼, 我们扔掉了剑鞘, 然后我像个最大的傻瓜一样把他和他船舱里可能有的一切都淹死了。 现在我没有任何东西可以帮助我洗清鲨鱼的名声, 把责任推给巴尔巴宗。 恐怕这是一个失败的事业, 扬。 ";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // 男爵任务已完成
				{
					// 第二次时间检查。 我们带走了海伦, 与斯文森的关系是中立的 - 好吧, 虽然尝试过但没成功。 丹妮和纳撒尼尔在马龙镇
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "我听说了你的英雄事迹! 丹妮给我讲了简短的版本。 顺便说一句, 我们现在是朋友了。 纳撒尼尔看到他的'百夫长号'后完全变了! \n但我有坏消息要告诉你, " +pchar.name+ "。 我们浪费了太多时间, Sharp遗嘱的继承权早已消失, 宝藏岛已经成为英国军事基地。 我再也无法帮助你对付勒瓦瑟了。 ";
						link.l1 = "我完全说不出话来... 我们经历了这么多麻烦, 结果却一无所获。 真的没有什么我们可以做的吗? ";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "我听说了你的英雄事迹! 丹妮给我做了简报。 顺便说一句, 我们和好了。 你甚至认不出纳撒尼尔了。 他一看到他的'百夫长号', 就像摆脱噩梦一样不再抱怨了... ";
						link.l1 = "纳撒尼尔康复了? 听到这个我很高兴! ";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // 矿山已占领
				{
					dialog.text = "你来了, " +pchar.name+ "! 现在我有事情要告诉你。 ";
					link.l1 = "你好, 扬。 我太高兴了! 有什么消息? 我希望是积极的? ";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // 矿山被共同占领
				{
					dialog.text = "你来了, " +pchar.name+ "! 休息好了吗? 我可以认为你又准备好迎接伟大的冒险了吗? ";
					link.l1 = "你好, 扬。 是的, 我准备好了。 ";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // 律师处时间不足
				{
					dialog.text = "有什么消息吗, " +pchar.name+ "? 情况如何? ";
					link.l1 = "哦, 情况糟透了。 我奋力拼搏, 但最终还是输了。 正如你记得的, Sharp的遗嘱有时间限制。 嗯, 时间已经到了, 宝藏岛现在是英国军事基地。 这是一个失败的事业, 扬。 ";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // 从律师处来取钱
				{
					dialog.text = "问候你, " +pchar.name+ "! 好消息: 委员会会议已经召开, 海岸兄弟会找到了新的领袖。 ";
					link.l1 = "下午好, 扬。 我为你高兴。 ";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // 交付巴考特
				{
					dialog.text = "那么, " +pchar.name+ "? 你追上莫利根了吗? ";
					link.l1 = "是的。 他就是偷你铁木的人。 ";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // 巴考特货款
				{
					dialog.text = "一如既往地准时, " +pchar.name+ "。 我把你带来的铁木卖了。 ";
					link.l1 = "太好了。 你赚了多少钱? ";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // 自己卖了巴考特
				{
					dialog.text = "那么, " +pchar.name+ "? 你追上莫利根了吗? ";
					link.l1 = "是的。 他就是偷你铁木的人。 我碰巧也遇到了他的买家。 他是某个荷兰军事指挥官。 我把货物卖给他了。 ";
					link.l1.go = "saga_59";
					link.l2 = "是的。 我试图强迫他带我去看他的货舱... 我们发生了冲突... 现在没有莫利根了。 但货舱里除了乌木和桃花心木什么也看不到。 ";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // 关于杰茜卡的信息
				{
					dialog.text = TimeGreeting() + ", " +pchar.name+ "。 有什么新消息? ";
					link.l1 = "扬, 我想和你谈一件事。 我一直在调查海伦母亲Beatrice的过去, 碰巧发现了一个你很了解的人。 据我所知... ";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting() + ", " +pchar.name+ "。 事情进展如何? 从你的表情来看, 我可以祝贺你吗? ";
					link.l1 = "是的。 我终于设法解决了这个烂摊子。 海伦已经获得了宝藏岛的所有权利。 再也不会有人侵犯海岸兄弟会的庇护所了! ";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "哦, 我的朋友" +pchar.name+ "! 很高兴见到你! 什么风把你吹来了? ";
				else sTemp = "还有别的事吗, " +pchar.name+ "? ";
				dialog.text = sTemp;
				link.l1 = "不, 扬。 目前没有。 ";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // 巴考特贸易
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "扬, 我想买些你的铁木。 ";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// 海伦的占位符
				if(startHeroType == 4)
				{
					dialog.text = "海伦, 你好, 亲爱的。 有什么消息吗? 有什么事吗? ";
					link.l1 = "你好, 扬! 还是老样子, 只是顺道来看看你。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "我能为你做什么吗? ";
				link.l1 = "不, 我没事。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "我认识你, 该死的! 你就是那个拯救伦巴。 正面夺取英国护卫舰大炮的勇敢船长! 很高兴见到你! 海伦就像我的女儿。 从今天起, 我永远欠你的。 你可以叫我扬或斯文森。 我能为你做什么? ";
			link.l1 = "我需要除掉托尔图加的总督勒瓦瑟。 我知道在他的岛上接近他并不容易, 所以我来找你寻求建议。 ";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "天哪, 你几年前在哪里! 我自己也计划进行同样的冒险。 他破坏了我们和法国人的整个计划。 但那些日子不同。 Blaze还活着, 鲨鱼有一定的权威, 纳撒尼尔在马龙镇发号施令... 现在一切都变了, 天知道, 不是变得更好。 你了解我们吗, 了解兄弟会吗? ";
			link.l1 = "我最近才到这里, 所以我基本上什么都不知道。 除了你和杰克曼是委员会的成员。 ";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "哦, 我受不了那个杰克曼! 他来这里的时候, 我们所有的麻烦就开始了。 我会考虑你的请求。 马上没有想到什么。 ";
			link.l1 = "我有关于杰克曼的有趣事情。 ";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "嗯。 那是什么? ";
			link.l1 = "杰克曼在寻找格拉迪斯.钱德勒和她的女儿。 和希金斯谈过之后, 我开始认为他在寻找伦巴。 看来格拉迪斯不是海伦的亲生母亲, 她在嫁给肖恩.麦卡瑟之前姓钱德勒。 ";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "该死的! 这是个坏消息。 杰克曼现在比以往任何时候都强大。 除此之外, 我有一种不祥的预感, 他不是一个人在工作。 他背后有一个相当不祥的影子。 如果他真的需要海伦, 那么这个女孩急需一个守护者。 恐怕我自己太老了, 做不了那个... ";
			link.l1 = "不止这些。 杰克曼还在寻找一个名叫亨利.刽子手的人, 他是屠夫船长手下'Neptune'的前水手长。 ";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "卡拉姆巴! 我最糟糕的怀疑成真了! 这个屠夫和他的'Neptune'曾经让整个群岛感到恐惧。 那时没有兄弟会, 每个人都自顾自。 那个人做了很多坏事, 一个我亲爱的人因为他而死。 \n我从未有机会见到他.'Neptune'被英国护卫舰击沉, 屠夫在圣约翰被处决。 谢天谢地! 尽管有很多人钦佩他的运气和鲁莽的勇气。 \n杰克曼本人是他的得力助手和'Neptune'的大副。 惊讶吗? 前罪犯成为了国家英雄, 这都要归功于克伦威尔! 古老的英格兰去哪里了? \n我们必须在杰克曼的人之前找到亨利.刽子手。 也许, 他掌握着这个谜团的关键, 如果他还活着的话。 ";
			link.l1 = "我敢打赌, 你找他比大海捞针还难。 你至少有什么线索吗? ";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "亨利还是个孩子的时候我就认识他。 他是卡塔赫纳一个妓女的儿子, 一半西班牙血统, 尽管他总是保密。 他的母亲很性感! 不能说她漂亮, 但很少有像她那样的弗拉门戈舞者。 整个妓院都观看赤裸的奇卡.冈萨雷斯和她的响板表演。 \n可怜的女孩。 染上了重病, 像蜡烛一样死去了。 就在那时, 我说服亨利去普罗维登斯, 他很快在那里成名, 并加入了托马斯.贝尔特罗普的船员, 他是Nicholas Sharp的密友。 那两个人是伊丽莎白女王最后的走狗, 总是一起工作。 好时光! \n托马斯在他的伙伴死后回到了英国。 他带走了他的船员, 但亨利留在了加勒比海。 在不同的船长手下航行, 直到屠夫出现。 顺便说一句, 他因为总是随身携带的弯刀而得到了他的绰号。 ";
			link.l1 = "这些信息告诉我们什么? ";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "如果刽子手决定躲避海盗, 对他来说最好的地方就是在西班牙城市。 特别是在他卡塔赫纳的家, 那里他有朋友和亲戚。 亨利相当虔诚。 所以, 他不太可能去不同的圣徒教堂。 他可能仍然用着他从小就有的名字, 恩里克。 ";
			link.l1 = "是啊... 机会渺茫, 但至少比什么都没有好。 ";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "试着找到他, 查尔斯! 很少有人知道亨利的西班牙血统, 所以我们有一个小优势。 我会考虑如何说服伦巴加入你的船员。 这女孩有胆量, 除了她父亲, 从未在任何人手下服役过。 \n但她既没有船也没有船员, 她需要谋生。 当然, 我会继续像往常一样帮助格拉迪斯, 但我不能把海伦在布鲁维尔德村留太久。 你会发现这样的军官非常有用。 肖恩把他知道的一切都教给了她, 把她当男孩一样抚养。 \n如果她在你这样的船长手下, 我会感觉更好。 ";
			link.l1 = "伦巴已经证明了自己相当有价值。 我的船员需要更多像她这样的人。 所以, 如果你设法说服她, 我会让她成为一名军官。 但首先我想了解她到底是谁, 为什么杰克曼需要她。 我担心, 不像多诺万, 他对她的魅力不感兴趣。 所以我会尝试找到刽子手, 尽管我不能保证什么。 ";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "嗯, 太好了。 拿这张荷兰西印度公司三个月的执照。 把你的名字写在那里, 它很可能在你的搜索中派上用场。 同时, 我会考虑你所说的关于勒瓦瑟和托尔图加的事情。 ";
			link.l1 = "万分感谢! 这张纸对我来说会很有用。 那样的话, 我就去卡塔赫纳了。 ";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//前往卡塔赫纳
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//打开海伦的卧室
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // 关闭杰克曼的官邸
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "亨利死了? 等等, 是你杀了他吗? ";
			link.l1 = "别用那种大眼睛看着我! 我和他的死没有任何关系。 他是自己死的, 死于腐烂的良心和对杰克曼的恐惧。 老海盗心脏有问题, 活不了多久了。 这是我设法查明的... ";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "请告诉我! ";
			link.l1 = "二十年前, 亨利应该代表屠夫船长把一箱金子交给他亲生女儿的养母。 毫无疑问, 这个养母是麦卡瑟夫人。 那时她姓钱德勒, 住在伯利兹。 但情况让刽子手在圣约翰多呆了整整一个月, 当他终于到达伯利兹时, 那里在西班牙人的袭击后已成废墟, 格拉迪斯阿姨和肖恩已经在你的帮助下上路了。 ";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "他们把海伦当作自己的亲生女儿, 把她抚养成人。 亨利失去了他们的踪迹, 躲了起来, 知道杰克曼的报复, 从那以后整整二十年都生活在恐惧中。 事实证明, 杰克曼在寻找他船长的女儿。 但为什么, 我不知道。 ";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "也许他在执行某人的命令... ";
			link.l1 = "怀疑。 谁能给他下命令? 屠夫死了。 他的死有官方文件证实。 数十人, 如果不是数百人, 目睹了他的死亡。 ";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "也许这不是关于海伦的父亲是谁。 也许这一切都是关于她的亲生母亲。 我已经可以猜到她是谁了, 但我害怕承认。 但是格拉迪斯! 她怎么能把这个秘密藏了这么多年, 甚至没有透露给她的丈夫! 肖恩.麦卡瑟肯定会告诉我的。 我们从来没有不告诉对方的秘密。 ";
			link.l1 = "我要和格拉迪斯进行一次坦诚的谈话。 我想我有办法让她开口。 回头见, 扬! ";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "你从哪里得到的! ? ";
			link.l1 = "格拉迪斯给我的。 她说这是'海伦母亲的遗产'。 她不知道她的名字。 有什么东西告诉我这不是普通的废纸。 ";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "记得我告诉过你我有预感海伦的亲生母亲是谁吗? 现在我确定了。 她的名字是Beatrice Sharp。 她是我的老师和朋友Nicholas Sharp的亲生女儿, 我们兄弟会创始人Blaze Sharp的名义姐妹, 也是宝藏岛的共有人。 这就是杰克曼想要的地图碎片。 ";
			link.l1 = "嗯, 怎么样! 但他为什么需要半个岛屿的地图? ";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "这个岛是Nicholas Sharp发现的。 他命名为宝藏岛, 绘制了地图, 并通过他有良好关系的普罗维登斯岛公司占有了它。 \n尼古拉斯在他的遗嘱中写道, 这个岛只能由出示两部分地图的人继承。 他这样做是为了避免任何纠纷。 他在被西班牙人悲惨地杀害之前, 把这些部分给了Beatrice和他的继子Blaze。 ";
			link.l1 = "好吧, 该死的! 真奇怪。 ";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "你说得对。 这不是最好的主意。 一个狡猾的公证人补充说, 如果继承人死后一年内没有人出示地图的两部分, 该岛将属于英国王室。 \n当时没有人预料到这一点。 现在我们正在为我们的愚蠢付出代价。 Beatrice二十年前去世了。 所有这些年过去了, 我们仍然不知道她的坟墓和她的地图部分在哪里。 Blaze Sharp不久前被谋杀了。 他的部分也消失了。 \n如果一年内没有人向当局出示完整的宝藏岛地图, 那么夏普敦将被英国认领。 他们将派一名总督和驻军到那里, 兄弟会将结束。 ";
			link.l1 = "你建议我们做什么? ";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "我们不能让这种情况发生。 我需要你, 查尔斯, 我需要你阻止这种情况。 只有在我们控制宝藏岛并选举鲨鱼.多德森为兄弟会新领袖之后, 我才能帮助你除掉勒瓦瑟。 他是我们中最有价值的。 我向你提议结盟。 \n顺便说一句, 我已经和海伦谈过了。 她同意加入你的船员。 ";
			link.l1 = "你让我别无选择, 扬。 我不能不恢复我家族的荣誉就回到法国。 为了做到这一点, 我需要不管有没有你的帮助都要除掉勒瓦瑟。 不必要的死亡不是我想要的, 我希望你能想出如何夺取托尔图加而不流太多血。 尽管如此, 我必须承认, 我自己也想弄清楚Sharp遗产的模糊过去。 ";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "很高兴听到合理的想法! 我们会找到夺取托尔图加的正确方法。 我向你保证。 那么, 我们走? ";
			link.l1 = "我们走! 我稍后再过来。 现在, 考虑一下从哪里开始解决这个问题。 ";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "两三天后再来。 到那时, 我想我的计划将达到高潮。 别忘了把海伦带上你的船。 这个可怜的女孩没有大海就憔悴了。 她会是一个忠诚的助手, 你可以放心地依靠她。 ";
			link.l1 = "好的, 扬。 我现在就去接她。 ";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//关闭出城通道
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//关闭海伦的卧室
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "首先, 你需要找到鲨鱼. 他想自己除掉勒瓦瑟, 我向你保证他有一些好主意。 当然, 我们也可以说服马库斯接受领导。 毕竟, 他是法典的守护者。 但我怀疑他会有任何帮助, 他故意限制与勒瓦瑟和托尔图加的任何接触。 一个有原则的人。 \n我不知道史蒂文和他的人藏在哪里, 但他的护卫舰'财富号'在普林西比港被看到。 也许扎卡里.马洛, 也被称为黑牧师, 可以告诉我们在哪里可以找到鲨鱼。 第二, 我们必须获得其他男爵的支持来选举多德森。 为了做到这一点, 我们需要收集他们的印第安碎片 - 选票。 新领袖必须拥有全部五块。 这是法典在前任领袖去世的情况下告诉我们要做的。 \n荒谬! 是时候改变法律了, 但只有新领袖才能做到。 我们已经有了我的选票。 我相信黑牧师不在乎谁坐在夏普敦。 我希望杰克曼没有先和他谈过。 我们还必须说服泰雷克斯和雅克.巴尔巴宗, 他们彼此憎恨。 但在我们了解鲨鱼发生了什么之前, 这一切都无关紧要。 第三, 总有一天我们必须杀死杰克曼, 用其他人代替他。 他不会和我们谈判。 \n可惜霍克死了! 人们信任他, 我们可以利用他的话。 我们找不到比马龙镇更好的男爵了。 杰克曼可能与Blaze的谋杀有关, 所以他也是找到地图第二部分的线索。 雅各布不信任任何人, 很可能把地图的一部分保存在他'百夫长号'的船舱里。 \n霍克家族曾经拥有这艘护卫舰, 但杰克曼就像霍克的男爵领地一样声称拥有它。 如果我们在杰克曼的 possession 中找到地图的第二部分, 这将是史蒂文当选的有力论据。 特别是对马库斯.泰雷克斯, 法典的守护者, 以及他对荣誉的过度谨慎。 一旦我们获得地图的两部分, 我们将把宝藏岛的权利归还给海伦。 \n不过, 我们必须小心, 杰克曼不会袖手旁观, 看着你搜索。 ";
			link.l1 = "嗯... 我正要去拜访黑牧师。 告诉我关于他的事。 ";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "天知道他在想什么。 有时他看起来像个十足的怪胎, 但尽管如此, 我相信这只是聪明的表演。 此外, 他的人准备为他们敬爱的牧师与魔鬼战斗。 \n他们在古巴建立了某种新教教派, 接近西班牙宗教裁判所。 所以不要在那里开始谈论神学问题, 他们不会赞成的。 ";
			link.l1 = "我会记住的... ";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "还有, " +pchar.name+ ": 不要浪费你的时间。 我是认真的。 还记得遗嘱中的下标吗? 上面写着, 如果继承人在一年内没有认领该岛, 那么宝藏岛将归英国王室所有, 对吗? 嗯, 现在时间不在我们这边。 当你和我上次见面时, 只剩下大约十一个月的时间了。 ";
			link.l1 = "我记得, 扬。 你说得对, 时间就是金钱。 我正在处理! ";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // 联盟杀手已激活
		break;
		
		case "shark_hunt_2":
			dialog.text = "嗯... 扎卡里告诉你什么了? ";
			link.l1 = "在他失踪之前, 鲨鱼来看过他, 并把他的护卫舰作为抵押品留给扎卡里, 换了一艘载有一些食物的双桅船, 然后航行到古巴西北部的某个地方。 ";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "这真的很可疑。 继续。 ";
			link.l1 = "一个月后, 多德森没有回来, 牧师根据协议条款, 把护卫舰据为己有, 并以好价钱卖给了一个叫帕特森的人。 就我们的事务而言, 扎卡里提到鲨鱼可能已经前往某个传说中的正义岛, 据说位于古巴西北部不远处。 ";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "我听说过正义岛。 他们说有一个岛, 白人和黑人和平共处, 平等相待。 这是各种梦想家散布的胡说八道。 但有可能在西北部存在某种走私者基地。 他们的三桅帆船十年前经常在公海被看到。 他们把不同种类的货物带到古巴换取食物。 ";
			link.l1 = "用宝藏换食物? 牧师还告诉我关于运送牛肉的海盗。 这几乎是一个行走的矛盾。 ";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "这些流言一定有来源, 那些走私者或海盗的三桅帆船出于某种原因航行到那个地区。 我记得鲨鱼告诉我他年轻时的故事, 他在海中央的某个由沉船组成的奇怪编队中是某种奴隶。 \n也许那是我们的地方? 不知道。 无论如何, 牧师有道理, 那里有东西, 要么是秘密基地, 要么是鲨鱼可能去的岛屿。 听着, 航行到圣多明各, 找到一个名叫何塞.迪奥斯的科学家。 \n他是西班牙制图师。 我曾经把他从肮脏的败类手中救出来, 我尊重有学问的人。 他会帮助你, 只要告诉他我的名字。 去伊斯帕尼奥拉岛, 找到迪奥斯并和他谈谈。 \n他非常了解我们地区的地理, 如果他不能帮助你 - 没有人会。 ";
			link.l1 = "好的, 扬。 听起来像个计划。 我走了! ";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "太糟糕了。 我确实希望何塞能帮我们一把。 ";
			link.l1 = "我也指望那个, 但唉。 好吧, 我们不要沉浸在自怜中。 我会再花些时间思考这个问题。 是的, 扬, 告诉我, 霍克是怎么死的? ";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "没有人目睹他的死亡, 就像没有人见过他的尸体一样。 他只是在几个月前消失了。 从那以后, 情况和鲨鱼一样, 无影无踪。 但与史蒂文不同, 纳撒尼尔没有理由躲起来。 正因为如此, 每个人都认为他在丛林中去世了。 如果不是这样, 他们就不会同意选举杰克曼代替他。 ";
			link.l1 = "霍克到底在丛林里做什么? ";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "这是我的错, 我是个老傻瓜! 我说服他去处理新到的土匪。 我不知道他们是谁, 也不知道他们的老板是谁。 通常我不会在意, 但他们开始绑架友好的米斯基托人。 他们的战争首领库姆瓦纳威胁要宣布战争之路, 并请求我的帮助。 我别无选择, 只能干预。 \n霍克带着一小队人在蚊子海岸登陆, 陷入了一场组织良好的伏击, 然后被击败。 看起来他和他的人预计会在那里登陆。 在丛林中的其他人中没有找到霍克的尸体。 ";
			link.l1 = "你眼皮底下发生了各种各样的恶作剧! 霍克的人没有尝试处理这些土匪吗? ";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "杰克曼抢先一步。 他在兄弟会委员会上自称要解决这个问题, 并做出了决定。 米斯基托人不再失踪, 但土匪留在那里, 相对低调。 \n杰克曼说, 他们没有扣押任何攻击他们的人作为人质, 兄弟会没有理由向他们宣战。 每个人都同意。 除了... ";
			link.l1 = "除了谁? ";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "纳撒尼尔有一个妻子。 她的名字是丹妮尔.霍克, 是个厉害的女人! 我怀疑她从未忘记失去她的船长, 更不用说她从一开始就怀疑什么, 并试图劝阻霍克。 我记得他们为此发生了激烈的争执, 但这对他们来说并不罕见。 ";
			link.l1 = "丹妮尔现在在哪里? ";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "谁知道呢! 杰克曼确保她离开了马龙镇。 她不来看我。 我们从来没有喜欢过对方, 这些年来她变得更加刻薄, 现在她一定真的恨我, 因为她可能认为我是她不幸的原因。 \n也许她自己在寻找霍克, 但一个女人能做什么, 即使她穿着裤子和佩刀! 顺便说一句, 她已经掌握了佩刀。 我不建议你如果遇到她就测试她。 是的, 和土匪谈话也没有意义。 他们在那里建立了一个非常令人印象深刻的营地, 并且武装到了牙齿。 \n看起来他们是前军人, 知道自己的业务。 他们不允许任何人进入他们的领土。 他们说西班牙人曾经在那里开采黄金。 但黄金已经耗尽, 他们放弃了矿井。 我不知道那些混蛋在那里做什么。 ";
			link.l1 = "好吧, 既然没有人见过霍克的尸体, 找到他还活着的希望仍然存在。 天知道, 我们甚至可以让他重新成为男爵。 ";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "是啊, 怎么样。 给, 拿着这封信。 当你见到史蒂夫.多德森时, 马上把它交给他。 这封信的内容将保证你的安全。 好吧, 以防万一。 ";
			link.l1 = "谢谢, 扬。 我会确保做到! ";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "好吧, 为什么拉长脸。 你累了? 也许给你一杯朗姆酒? ";
			link.l1 = "我不介意... ";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "给, 喝一杯。 现在说吧。 ";
			link.l1 = "(喝酒) 啊, 好多了... 好吧, 扬, 你和黑牧师都是对的。 正义岛确实存在。 我去过那里。 ";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "我告诉过你那里应该有一个走私基地! ";
			link.l1 = "实际上那里没有任何基地。 加勒比海的传言没有撒谎。 黑人和白人确实在那里生活在一起, 当然不一定和平, 但更像是猫和狗。 而这个岛本身由无数的沉船组成。 ";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "我不敢相信! 何塞.迪奥斯肯定会对你的故事感兴趣。 顺便说一句, 找一天去看看他。 ";
			link.l1 = "我以后会去看他。 现在不是最好的时机。 我现在有更紧迫的事情要处理。 我在岛上找到了纳撒尼尔.霍克。 ";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "你找到纳撒尼尔了? 那太了不起了! 他怎么样? ";
			link.l1 = "嗯... 他病了, 经常喝醉, 而且极度抑郁。 ";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "该死的, 这令人沮丧。 他在哪里? 在你的船上? ";
			link.l1 = "不, 他在自己的船上。 在岛上。 ";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "什么, 你没有把他带到这里? 为什么? ";
			link.l1 = "因为没有什么可以带他来的。 我没有船就去了岛上。 ";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "该死的, " +pchar.name+ ", 你几乎没喝一杯朗姆酒, 就像喝得酩酊大醉一样胡说八道。 什么, 你游过加勒比海? 还是你在脚上绑了一些海龟? ";
			link.l1 = "不, 我没有游泳。 扬, 我直接从梅因的丛林来到岛上, 就像纳撒尼尔一样, 通过一个神奇的印第安偶像。 我已经把这个故事告诉了很多人, 我厌倦了证明我没有发疯, 所以我只能说: 相信我, 好吗! ? ";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "印第安偶像? ";
			link.l1 = "加勒比海至少有三个被称为库库尔坎雕像的偶像: 一个在西梅因的米斯基托村附近, 一个在正义岛的浅水区底部, 另一个在多米尼加的加勒比村。 这些偶像在印第安魔法的帮助下, 能够瞬间在时间和空间中转移人类。 ";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "我绕了三个雕像一圈, 然后在我开始旅程的米斯基托村出来了。 如果你不相信我, 我可以叫丹妮尔过来。 她亲眼看到了一切! ";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "丹妮尔? 霍克的妻子? 她和你在一起? ";
			link.l1 = "在某种程度上, 是的。 她自己在布鲁维尔德村找到我, 把我带到米斯基托村, 到一个派我去魔法雕像的萨满那里。 现在她暂时担任我的军官。 ";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "我完全惊呆了, " +pchar.name+ "! 就像英国人说的。 你是含着银汤匙出生的。 你真是个幸运的狗娘养的! 好吧, 我就相信你, 虽然很难。 但纳撒尼尔的事情仍然一样, 他需要帮助。 ";
			link.l1 = "这就是我要做的。 我正在准备一次前往正义岛的探险。 现在我有了所有需要的东西: 岛屿的坐标和航行方向。 ";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "太棒了。 我能帮你什么吗? ";
			link.l1 = "不, 谢谢。 但我遗漏了一个小细节。 除了纳撒尼尔, 我还在岛上找到了鲨鱼.多德森。 ";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "所以, 他真的去了那里! 好吧, " +pchar.name+ ", 你做得很好。 多德森在那里怎么样? 你当然和他谈过了, 不是吗? ";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "我不仅和他谈过。 我们也成了朋友。 是他给了我返回岛上需要的航行方向。 史蒂文同意用他的战船舱室换取夏普敦的住所。 ";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "我们谈过, 是的, 但最后结果是无用的。 我在岛上停留时, 史蒂文在他的水手长查德.卡珀组织的阴谋中被杀。 ";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "哈! 鲨鱼是如何成为战船船长的? ";
			link.l1 = "这艘船已经在'平静'中航行了半个多世纪。 他和他的人被困在岛上。 这就是为什么他这么长时间没有出现在加勒比海。 无论如何, 我很快就会把他带到这里, 他会亲自告诉你他的冒险经历。 ";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "我等不及了! 现在事情开始好转了。 我们刚刚变得更强大了, " +pchar.name+ "。 你计划什么时候返回岛上? ";
			link.l1 = "现在。 我只是来这里一分钟告诉你这个消息, 而丹妮尔正在为探险做准备。 她渴望见到她的纳撒尼尔。 你知道吗, 扬, 她不是那么坏。 ";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "是吗? 好吧, 也许我对她不太对。 好吧, " +pchar.name+ ", 我不会再耽误你了。 去吧, 祝你好运! 我期待你的归来。 ";
			link.l1 = "再见, 扬。 ";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "查德.卡珀? 靠, 我认识那个家伙。 他杀了史蒂文? 那个混蛋... ";
			link.l1 = "卡珀死了。 但我们不能让史蒂文回来, 所以我们必须考虑继续组织我们政治的方法。 ";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "哈! 太糟糕了... 还有什么可考虑的? 我们只能说服泰雷克斯领导兄弟会。 此外, 在Blaze之后, 作为法典守护者的泰雷克斯是我们最受尊敬的人物。 但首先我们需要带回霍克, 至少得到一张王牌。 你什么时候出发去岛上? ";
			link.l1 = "现在。 我只是来这里一分钟告诉你这个消息, 而丹妮尔正在为探险做准备。 她渴望见到她的纳撒尼尔。 你知道吗, 扬, 她不是那么坏。 ";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC等待它的英雄! 
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // 检查船只类型
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // 杰克曼雇佣兵的攻击
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // 返回的主要功能
		break;
		
		case "nathaniel":
			dialog.text = "他怎么样? 你说他感觉不舒服。 ";
			link.l1 = "是的, 完全正确。 我要带他和我一起去米斯基托村由蛇眼萨满治疗。 ";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "那就不要浪费时间! 快点, " +pchar.name+ "! 你一把纳撒尼尔送到你的萨满那里, 就马上回来见我。 ";
			link.l1 = "好的, 扬。 听起来像个计划。 ";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // 鲨鱼活着
			{
				if (CheckAttribute(npchar, "quest.shark")) //并且在位置
				{
					dialog.text = "很好。 史蒂文已经顺便来看过我了。 现在我们终于可以继续讨论我们的计划了。 ";
					link.l1 = "我洗耳恭听, 扬。 ";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "当然很好, 但为什么多德森还没有来看我? 什么, 你把他留在岛上了? ";
					link.l1 = "嗯... 我急着把纳撒尼尔送到蛇眼那里... ";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "很好。 我为鲨鱼哭泣。 但这就是生活, 所以泰雷克斯将取代他的位置。 好吧, 现在我们终于可以继续讨论我们的计划了。 ";
				link.l1 = "我洗耳恭听, 扬。 ";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... 你忘了带鲨鱼? 我不敢相信, " +pchar.name+ "! 现在把史蒂文送到布鲁维尔德村! 你听到了吗? 走! ";
			link.l1 = "冷静点, 扬。 我会处理好一切。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "史蒂文顺便来看过我了。 现在我们终于可以继续讨论我们的计划了。 ";
				link.l1 = "我洗耳恭听, 扬。 ";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "哦, " +pchar.name+ "... 我觉得你最近喝了太多朗姆酒。 你看, 这从来没有好结果。 首先你的手开始颤抖, 然后你开始失去记忆, 然后你得到一个黑点... ";
				link.l1 = "我明白了, 扬。 我现在就去接史蒂文! ";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "黑牧师已经很清楚, 他只对那本神学书感兴趣。 我已经派我的人去寻找它, 也许有人会找到它。 马库斯.泰雷克斯不是问题, 我们说服他不会有问题。 你拜访杰克曼后, 他很快就离开了马龙镇。 他乘坐霍克家族的护卫舰'百夫长号'航行到某个地方。 \n只剩下巴尔巴宗了 - 他也被称为仁慈的雅克。 我们必须找到让他与我们合作的方法。 我目前不确定如何做到这一点。 但有一件事是显而易见的 - 你应该拜访他。 ";
			link.l1 = "告诉我关于巴尔巴宗的事。 "; // Addon 2016-1 Jason 海盗线补丁 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "神秘类型。 假装贫穷, 但他可能是加勒比海最富有的人。 他控制着东部的所有走私活动。 如果不是马库斯反对他, 他会统治向风群岛的所有走私运输。 泰雷克斯就像他喉咙里的一根刺。 \n他们在委员会总是争吵, 但巴尔巴宗没有胆量宣布公开战争。 也许他真的像他声称的那样曾经是敦刻尔克的海盗, 但现在他更让我想起一个放贷人。 ";
			link.l1 = "他到底是如何当选男爵的? ";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "黄金, 我的朋友, 黄金到处都能统治, 谁有黄金谁就制定规则。 此外, 巴尔巴宗真的很擅长提出各种有利可图的非法行动。 他自己不参与其中, 但他总是分得一份。 所以他周围总是有很多勇敢的暴徒, 他们大多头脑简单。 没有他, 他们都会饿死或最终上绞刑架。 ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "他让我想起马库斯... 扬, 事情是... 我不知道如何接近巴尔巴宗。 有一个你不知道的问题。 ";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "我如何接触巴尔巴宗? ";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "简单地假装是那些需要小费来做肥差的傻瓜之一。 甚至不要考虑试图欺骗他的份额。 仁慈的巴尔巴宗不原谅。 ";
			link.l1 = "这是不言而喻的。 我不是为了自己的利益而和他打交道。 无论如何, 是时候去拜访他了。 ";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// 这里清除LSC的任务垃圾
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason 海盗线补丁 17/1
		case "barbazon_5":
			dialog.text = "真的吗? 说吧。 ";
			link.l1 = "听说过查理.普林斯吗? "; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "是的, 我听说过谣言。 这家伙不久前还在为马库斯.泰雷克斯工作。 在很短的时间内做了很多事情, 通过掠夺卡塔赫纳而出名。 那么? ";
			link.l1 = "这个人就是我。 我是查理.普林斯。 曾经是。 现在明白了吗? "; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "靠! 你是查理.普林斯? 真是个转折! " +pchar.name+ ", 我印象深刻! 现在我明白你的能力是从哪里来的... 但这和巴尔巴宗有什么关系? ";
			link.l1 = "普林斯去拜访巴尔巴宗怎么样, 扬? .."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "嗯... 我明白了。 你以前和他打过交道? ";
			link.l1 = "不完全是。 他的一个名叫伊格纳西奥.马可的喽啰按照巴尔巴宗的直接命令试图搞砸我。 这是他们小战争的一部分。 "; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "他看到你的脸了吗? 你向他做自我介绍了吗? ";
			link.l1 = "没有。 "; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "那么这里没有问题。 我也听说过海盗查理.普林斯, 但在你告诉我之前, 我不知道他就是你。 ";
			link.l1 = "你认为巴尔巴宗不会看穿我吗? "; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "如果他从未见过你的脸, 他怎么会呢? 他所做的只是下令除掉马库斯的一个雇员。 ";
			link.l1 = "嗯... 你可能是对的。 "; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "没有巴尔巴宗, 我们不可能成功。 去见他, 但要小心。 如果他认出你就跑, 在那种情况下我们会想另一种方法接近他。 ";
			link.l1 = "好的。 我现在该走了。 一直期待见到那个混蛋。 "; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "不要装傻, 不要试图欺骗雅克。 他从不原谅。 表现得像个渴望轻松赚钱的白痴。 ";
			link.l1 = "这似乎是我最喜欢的角色... 再见, 扬! "; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "是的。 印第安萨满尽了全力, 霍克恢复健康了。 他应该已经和丹妮在马龙镇了, 所以如果你想, 就去打个招呼。 他们会很高兴见到你。 ";
			link.l1 = "我一定会顺道去看看他们怎么样... 扬, 我设法找到了Sharp地图的第二部分! 它在杰克曼的船舱里。 现在我们可以毫无问题地证明海伦对宝藏岛的权利了。 ";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "太好了, 给我看看。 \n我们是对的, 雅各布就是杀Blaze的人。 现在鲨鱼的名声上的污点终于可以彻底洗清了。 至于证据, 这是一个更微妙的问题。 必须经过非常彻底的考虑才能处理。 ";
			link.l1 = "另一件事, 扬。 看看这个笔记。 它也在杰克曼的东西里。 ";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // 删除便条
			dialog.text = "好吧, 让我看看... 哈, 所以这就是为什么土匪听杰克曼的话, 停止绑架米斯基托人! 不可能有其他结果! 那个混蛋策划了这一切, 并且领先了几步。 ";
			link.l1 = "是的, 我也明白为什么霍克的人被屠杀了。 但有两件事我不明白: 第一, 杰克曼的同伙在矿井里做什么, 第二, 为什么你对整个混乱发生在你的领土上反应如此平静? ";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "我很惭愧... 你是对的。 杰克曼真的失控了。 他的手下在我的地盘上没有业务。 看来是时候提醒加勒比海他们在和谁打交道了。 ";
			link.l1 = "你有什么想法, 扬? ";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "重温过去... 我打算组织一次惩罚性远征, 消灭矿井里的每一个土匪。 现在我们有证据证明他们是杰克曼的人, 我有义务清除我的领土上的这些败类。 \n" +pchar.name+ ", 你做得很好。 现在是我行动的时候了。 你现在休息一下。 去拜访霍克一家。 十天后回来! ";
			link.l1 = "好的, 扬。 会的。 我会在你说的时间回来! ";
			link.l1.go = "saga_31";
			link.l2 = "哈! 我也想参加这次远征。 为什么你决定让我休息? ";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "原谅我, 老伙计。 我只是认为现在终于到了我做些工作, 而你休息一下的时候了。 但如果这是你的愿望, 我会非常高兴! 让我们一起出击! 我们在矿井里找到的一切都将按照兄弟会的法律在我们的船员之间平均分配。 ";
			link.l1 = "成交, 扬! 我们什么时候出发? ";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "三天后带着你的人到蚊子海岸来。 到那时我会召集我的小队, 已经准备好等你了。 不要迟到! ";
			link.l1 = "好的, 森林恶魔。 我正渴望和你并肩作战! 回头见! ";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // 定时器
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // 定时器
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // 大概不需要
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // 打开霍克的官邸
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "太好了。 我查出了关于矿山神秘主人劳伦斯.贝尔特罗普的一些事情。 ";
			link.l1 = "那么, 这只鸟是谁? ";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "我在矿山打败了杰克曼的走狗。 他们结果是硬骨头, 但我的人也不是昨天才出生的。 此外, 在告诉他们你找到的便条上的密码后, 我们得以放下他们的警惕。 我们渗透了矿山, 给了他们一个华丽的送别。 ";
			link.l1 = "你占领了矿山? 太棒了! ";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "这应该给任何认为森林恶魔生锈了的人一个教训。 过去几年我真的太懈怠了, 看看发生了什么? 杰克曼就在我眼皮底下展开他的邪恶计划! ";
			link.l1 = "你在那个矿山看到了什么? 告诉我! ";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "矿山确实被西班牙人遗弃了, 然而来自皇家港的劳伦斯.贝尔特罗普以花生价格买下了它, 并秘密继续开采。 显然, 西班牙人太早放弃了矿井, 因为尽管我们自己没有在那里找到任何黄金, 但我们发现了几个奴隶, 他们声称直到最近还能找到黄金。 ";
			link.l1 = "劳伦斯.贝尔特罗普? 从没听说过。 他是谁? ";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "他是当地人, 托马斯.贝尔特罗普的儿子, 很久以前是Nicholas Sharp的 sworn brother 和普罗维登斯岛公司的私掠者。 我自己非常了解托马斯。 一年前, 劳伦斯再次来到加勒比海。 事实证明, 杰克曼在为他工作。 记住这一点, 睁大眼睛! ";
			link.l1 = "所以杰克曼的神秘‘老板’, 在那封信中提到的, 是劳伦斯.贝尔特罗普... 好吧, 我会记住这个名字。 ";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "还有一件事。 我记得一件奇怪的事。 Blaze曾经提到过某个废弃的西班牙金矿, 他打算把金矿的黄金投资到夏普敦。 但在他妹妹和屠夫船长私奔后, 矿山的地图消失了。 也许他说的是我们的矿山? \n不管怎样, 那是太久以前的事了, 没什么变化... 你和我应该处理委员会的事。 你拿到所有五块碎片了吗? ";
			link.l1 = "是的。 这四个: 纳撒尼尔。 泰雷克斯。 马洛和巴尔巴宗。 他们都已经同意了。 ";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "太好了。 我相信选举"+sTemp+"为海岸兄弟会的领袖不会有任何问题。 我会立即着手召集委员会会议。 ";
			link.l1 = "那么扬, 我们现在可以认为所有问题都在控制之中了吗? 纳撒尼尔在马龙镇, 杰克曼死了, 兄弟会现在有了新的领袖... 也许是时候回到我们开始的地方, 也就是夺取托尔图加? ";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "我记得, "+pchar.name+", 但我们需要稍微等待时机。 此外, 解决Sharp遗产的时间不多了, 正如你所知, 这个问题急需处理。 ";
			link.l1 = "遗产有什么问题? 我有地图的两部分。 我们真正需要做的就是展示它们, 就这样... ";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", 我向你保证, 如今他们不会简单地把岛屿交给人们。 即使是合法继承人, 履行了遗嘱的每一个段落。 英国当局非常想要这个岛, 我很清楚这一点。 \n我认为 Doyle 上校不会坐视我们夺走他已经视为英国财产的岛屿。 此外, 你和我应该保持在阴影中。 ";
			link.l1 = "你建议怎么做? ";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "前往皇家港, 在那里找到一个名叫阿尔伯特.洛克斯利的人。 他是整个加勒比海最好的律师。 他在各种阴暗事务中变得相当熟练, 所以如果给他一笔高昂的费用, 他会接受任何工作。 他的胃口很大, 但他值得。 ";
			link.l1 = "你认为Sharp的遗嘱可能有一些陷阱? ";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "我不只是这么认为, 我确信如此。 你曾经和官员打过交道吗? 要知道, 如果他们想从你那里得到什么, 他们会掏出你的灵魂, 指着一个放错位置的逗号, 以他们需要的方式解释一切, 让你像一只瞎小猫一样赤身裸体。 \n这就是为什么会有律师。 他们用自己的武器与官员战斗 —花言巧语。 笔墨和诡计。 因此, 你应该拜访洛克斯利, 雇佣他来保护我们的利益, 而我处理选举。 ";
			link.l1 = "好吧。 我去皇家港。 委员会开会和举行选举需要多长时间? ";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "十天。 所以不要早于这个时间在布鲁维尔德村找我。 ";
			link.l1 = "知道了。 那么, 扬。 那样的话, 一会儿见! ";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // 更新标志
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // 关闭斯文森的书房
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // 定时器
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" 向你致以最热烈的问候。 他将永远很高兴在宝藏岛的住所见到你。 如果有机会, 去拜访他。 ";
			link.l1 = "为了确保"+sTemp+"不会离开他的新住所, 你和我, 扬, 还有一些工作要做。 ";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "我想你已经拜访过洛克斯利了... ";
			link.l1 = "是的, 拜访过了。 他接了我们的案子, 但他要求一大笔黄金作为服务费用。 "+sTemp+" 杜布隆预付款。 预付款! 而且我们还得根据海伦的权利证明进行得如何再付给他更多。 正如他所说, 金额会翻倍或三倍。 ";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "哈! 好吧, 我对像他这样的老油条并不意外。 他像鬣狗一样从远处闻到猎物的味道。 当然, 我们谈论的是一整个岛屿。 认为阿尔伯特不会要几百块是荒谬的。 所以, 总金额可能在大约一千五百金左右... ";
			link.l1 = "扬, 那是一大笔钱! ";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "我知道你的意思。 我同意你不是一个支付所有费用的愚蠢大猩猩。 但不幸的是, 目前我没有藏匿那么多黄金。 我曾计划过这样的开支, 然而一个无赖的干预毁了一切。 ";
			link.l1 = "你在说什么? ";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "听着。 也许你已经知道我们的定居点只有一半合法。 英国人在这里驻扎了一个 garrison, 我们以好价格向他们提供桃花心木。 但有一种非常沉重和耐用的木材 - 愈创木, 你应该知道它是铁木。 \n它很稀有, 即使使用硬化钢也很难加工。 据说很久以前, 马雅-伊察人用它制作可怕的棍棒。 你不能在公开市场上买到铁木, 走私的价格等于它的银重量。 \nDoyle 的人偶尔会来, 以低价购买我们加工的全部数量。 但我总是设法为自己的需要节省一些。 ";
			link.l1 = "我听说过这种树。 他们说火枪子弹像焦油一样沉入它的油性木材中! 它的坚固程度足以用它制造钢铁机械的齿轮。 ";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "他们关于齿轮的说法有点夸张, 但其余的都很准确。 所以, 预测到开支, 我准备了一大批铁木, 但几天前某个混蛋清空了我的仓库。 是我们中的某个人, 我知道。 我有一个怀疑, 但不能肯定地说。 ";
			link.l1 = "老鼠要被踩死! 你怀疑是谁? ";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "保罗.莫利根。 他的东印度‘牡蛎号’昨天驶往巴巴多斯。 我没有机会检查她的货舱。 但无论如何, 他不会把铁木带到布里奇敦, 威洛比勋爵在那里有严肃的海关官员, 而铁木是英国海军的战略重要原材料。 \n如果他真的有我的铁木, 那么他会在到达布里奇敦之前卖掉它。 要是你能拦截莫利根并检查他的货舱就好了! ..";
			link.l1 = "你说他昨天出发去布里奇敦了? 还没有完全失去希望。 我会尝试追上他。 ";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "如果莫利根是老鼠, 你知道该怎么做。 但首先尝试了解他的客户的名字。 然后你可以自己把货物交给客户, 或者归还给我。 \n也把‘牡蛎号’带到布鲁维尔德村, 那是一艘好船, 我想自己拿过来并为自己的需要重新装备她。 你也可以拿走任何你想要的作为战利品... 如果莫利根不是罪魁祸首... 不, 我确信他是偷我铁木的老鼠。 ";
			link.l1 = "我会好好利用我的时间! ";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "如果你自己卖铁木, 为洛克斯利留出一千五百金杜布隆, 剩下的我们平分。 我可以信任你, 对吗? ";
			link.l1 = "当然。 我不是老鼠。 ";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "我毫不怀疑。 祝你好运, "+pchar.name+"! 我希望这次幸运会降临到你身上。 ";
			link.l1 = "谢谢你。 回头见! ";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // 更新标志
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("探索模式: 定时器未禁用。 遵守最后期限! ");
			Saga_CreateMolliganInWorld(); // 将莫利根的船放在地图上
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "我就知道。 他的货舱里有多少? ";
			link.l1 = "我在‘牡蛎号’上找到了"+FindRussianQtyString(sti(npchar.quest.bakaut))+"。 ";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "哇! 我的仓库里从来没有那么多。 看看谁自己拿到了一笔财富。 谢谢你, "+pchar.name+", 你从未让我失望。 我会立即出售产品, 我们已经有买家了。 明天我会把钱给你。 ";
				link.l1 = "好的。 那我就不再打扰你了。 明天见。 ";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "是的, 我差不多有那么多。 小老鼠! 谢谢你, "+pchar.name+", 你从未让我失望。 我会立即出售产品, 我们已经有买家了。 明天我会把钱给你。 ";
				link.l1 = "好的。 那我就不再打扰你了。 明天见。 ";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "他可能已经设法将一部分货物卖给了某人, 因为应该有更多。 但这不是大问题, 我们拿回了大部分。 谢谢你, "+pchar.name+", 我会立即出售产品, 我们已经有买家了。 明天我会把钱给你。 ";
				link.l1 = "好的。 那我就不再打扰你了。 明天见。 ";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "该死的, 那个混蛋已经能够卖掉相当一部分货物了... 啊, 太糟糕了。 好吧。 我会卖掉我有的, 我已经找到买家了。 明天我会拿到钱。 ";
				link.l1 = "好的。 那我就不再打扰你了。 明天见。 ";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "该死的, 太遗憾了! 那个混蛋已经能够卖掉一半以上的货物了... 啊, 太糟糕了。 好吧。 我会卖掉我有的, 我已经找到买家了。 明天我会拿到钱。 ";
				link.l1 = "好的。 那我就不再打扰你了。 明天见。 ";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "伙计, 我真倒霉。 他几乎把所有东西都卖了... 这里把这个铁木留给你, "+pchar.name+", 你想怎么处理就怎么处理。 你现在是我赚钱的唯一希望。 ";
			link.l1 = "知道了。 好吧, 我会自己看看。 这不是我第一次参加竞技表演... 再见, 扬。 ";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // 我们有牡蛎号吗
			dialog.text = "等等! 你捕获了‘牡蛎号’吗? ";
			if (iUst == 1)
			{
				link.l1 = "是的。 她现在在港口。 我按照你的要求为你锚定了她。 ";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "没有。 这艘船在战斗中受损严重, 我不得不把她击沉。 ";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "真遗憾。 但事情就是这样。 回头见, "+pchar.name+"! ";
			link.l1 = "再见, 扬。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "了不起! 我会按照她应得的方式装备这个美人。 以后你可以随时像我们约定的那样借用她。 我想大约两个月后她就会准备好。 ";
			link.l1 = "好的。 这样的船有时真的很有用... 回头见, 扬! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // 两个月后
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // 扬每1个巴考特给30杜布隆
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // 邦萨的份额 :)
				dialog.text = "我为此收到了"+iTemp+"枚硬币。 一千五百给律师, 加上你那份杜布隆 - "+idlt+"。 给你。 ";
				link.l1 = "值得称赞! 现在我可以轻松前往洛克斯利那里了。 ";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "我为此收到了一千五百杜布隆。 刚好够给律师。 给你。 ";
				link.l1 = "太棒了。 现在我可以出发去洛克斯利那里了。 ";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "我为此收到了"+iTemp+"杜布隆。 给你。 剩下的你得自己挖了。 ";
			link.l1 = "好吧, 如果是自己的话, 那就自己。 好的, 我这就去见洛克斯利。 ";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "那怎么样? 真有趣。 那个荷兰人愿意为它付多少钱? ";
			link.l1 = "每块四十杜布隆。 ";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "哇! 我的买家付得更少... ";
			link.l1 = "总的来说, 我为洛克斯利拿到了两千金币, 此外还有"+sti(npchar.quest.bakaut_sum)*2+"杜布隆。 ";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "很好。 那么我们将它平分。 ";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // 口袋里的杜布隆
				link.l1 = "给你。 我有"+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+"。 ";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "我把杜布隆留在船上了。 我很快跑过去, 马上回来。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "太好了。 你带来了多少? ";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // 口袋里的杜布隆
				link.l1 = "给你。 我有"+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+"。 ";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "我的记忆怎么了! 是时候停止用朗姆酒胡闹了。 我又一次把杜布隆留在我的箱子里了。 我会很快跑过去把它们带来。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // 支付
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // 全额
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // 记住剩余
			RemoveDublonsFromPCharTotal(sti(npchar.quest.bakaut_pay));
			Log_Info("你已经给了"+sti(npchar.quest.bakaut_pay)+"杜布隆");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "干得好, "+pchar.name+"! 我再次被提醒你是一个值得合作的好人。 ";
				link.l1 = "我努力了, 扬... ";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "太好了。 你以后会把剩下的"+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+"杜布隆带来吗? ";
				link.l1 = "是的。 我只是不能一次搬运这么大量的黄金。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "那么, "+pchar.name+", 我的杜布隆怎么样了? ";
			link.l1 = "我愿意给你更多的黄金。 ";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // 结算完毕
			dialog.text = "我有一个提议给你。 既然你能够找到一个有利可图的买家, 那么我可以卖给你一些铁木。 我过去每块得到三十杜布隆。 如果你愿意, 你可以以那个价格从我这里买。 我宁愿卖给你也不愿卖给别人。 ";
			link.l1 = "你能卖多少铁木? ";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "我避免储存大批货物。 莫利根的是个例外。 当局不会喜欢当地黑市的消息。 所以, 这是交易: 我将在每月的14日和24日为你节省25块铁木。 \n如果你想买, 带七百五十杜布隆来, 拿走整批。 如果你在那天不出现, 那么我会卖给另一个客户。 这样, 你每月可以有50块。 成交? ";
			link.l1 = "成交, 扬! 就这么办。 现在, 我该走了... ";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // 巴考特买卖生成器
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // 欺骗了扬 - 没有巴考特生成器, 损失更多
			dialog.text = "啊, 所以要么不是他, 要么他已经在之前卖掉了铁木... 真遗憾。 好吧, 你现在是我为律师拿到钱的唯一希望。 ";
			link.l1 = "我愿意承担那个责任。 这不是我第一次参加竞技表演。 ";
			link.l1.go = "exit";
			// 扬很失望, 忘记了牡蛎号 - 所以也不会有牡蛎号
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "是这样吗? 真有趣。 继续, 问吧。 你想谈论谁? ";
			link.l1 = "关于一个女孩。 她的名字是... 杰西卡.罗斯。 ";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "嗯。 我们兄弟会的新领袖告诉你关于她的事了吗? ";
			link.l1 = "他也说了。 但我是从贝克那里知道她的, 圣约翰的老刽子手。 就是那个把屠夫船长处死的人。 ";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "好的。 嗯。 好吧, 我最后一次见到杰西卡已经超过二十年了。 你对她了解多少? ";
			link.l1 = "嗯, 我知道她是如何和屠夫船长在一起的, 以及他们如何一起海盗。 我知道他为了Beatrice离开了她。 后来, 她在某个约书亚.利德比特的帮助下为他报了仇, 也被称为面具... ";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "我还知道你, 扬, 请原谅我的坦率, 对杰西卡感兴趣。 这就是我来找你的原因。 杰西卡是我搜索中的重要人物。 据我了解, 是她出于嫉妒谋杀了Beatrice Sharp。 ";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "好吧, 你知道很多。 是的, 我确实一直在追求杰丝, 但这并不奇怪, 当时宝藏岛的所有海盗都分成两个不同的群体: 那些想和Beatrice上床的人和那些想要杰西卡的人。 \n我清楚地记得她... 她很漂亮, 非常漂亮! ..";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "她很特别... 杰丝很可能杀了Beatrice。 在屠夫把她从‘Neptune’踢出去后, 她可能除了满足对他和Beatrice的报复之外, 什么也没想。 顺便说一句, 你知道屠夫是如何摆脱杰西卡的吗? ";
			link.l1 = "不知道。 要么他只是让她在巴巴多斯下船, 要么把她当人质。 ";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "第二种。 他对她的侮辱难以置信。 他只是把她锁在船舱里, 把她带到巴巴多斯, 开始和她的父亲奥利弗.罗斯谈判, 实际上把她卖了一大笔杜布隆... 在她为他所做的一切之后。 ";
			link.l1 = "嗯。 我以为当海盗从约书亚.利德比特手中夺取‘Neptune’时, 屠夫保护了她的荣誉... ";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "那也是真的。 但她也为此付出了高昂的代价。 杰西卡多次拯救了那个人渣的可怜生命, 把他从他经常为自己的狂欢和暴躁脾气而设置的钉子床上救出来。 实际上, 只是因为她, 他才获得了成功海盗的荣耀。 ";
			link.l1 = "是的, 是的, 他的‘红色护身符’。 我听说过。 他们说, 一旦屠夫踢开了杰丝, 他的运气也随之而去... ";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "当然。 没有杰西卡, 他只是另一个普通的海上袭击者, 尽管是一个鲁莽勇敢的人。 但杰西卡不在他身边, 她是那个帮助他计划所有危险行动的人, 他总是可以依靠她的刀刃。 \n当然, Beatrice也不是好女孩, 但她无法与杰丝相比, 比阿的魅力完全不同... 她犯了惹屠夫的错误。 ";
			link.l1 = "我在某处已经听过... ";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "所有海盗都这么认为, 包括她的兄弟Blaze Sharp。 他无法忍受屠夫... 但让我们回到杰西卡。 当她在‘Neptune’上时, 我甚至不敢想她, 她永远不会离开她心爱的船长。 但当屠夫以如此卑鄙的方式摆脱她时... \n我到达巴巴多斯, 和她成为了朋友。 这对她来说并不容易, 她热爱大海和危险的冒险。 那种枯燥的殖民地生活正在杀死她。 此外, 她在加勒比海服役于‘Neptune’时已经成为一个非常臭名昭著的人, 布里奇敦的人有理由认为她是屠夫的共犯... ";
			link.l1 = "但他们无法证明狗屁... ";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "是的。 但也没有人想和她有任何关系。 她被认为是被诅咒的, 尽管她在布里奇敦的地位。 我想我是那里唯一和杰西卡相处超过半小时的男人。 \n我邀请她和我一起去西梅因, 在那里开始新的生活。 她一直想要的生活 - 大海。 船只。 航行。 冒险。 那时我已经在布鲁维尔德村建立了一个大型行动, 我能够给她提供比那个人渣屠夫多一百倍的东西。 但杰丝非常受伤。 她没有原谅屠夫的背叛和他后来对她的待遇。 我相信即使在那时, 她仍然对他有感情... 尽管我尽了最大努力, 我无法让她忘记过去, 她沉迷于复仇的想法。 ";
			link.l1 = "是的, 我不羡慕她。 可怜的女孩... ";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "我对她也有同样的感觉。 后来她开始喜欢古老的印第安邪教和仪式。 这发生在某个印第安法师被俘虏并从尤卡坦丛林深处带到当地种植园之后。 杰西卡买下了他, 并在她的种植园给他一所房子。 \n她花了大量时间和法师在一起。 她说这都是因为她对神奇的印第安仪式的历史兴趣。 布里奇敦的人担心了, 尤其是当地的牧师。 实际上, 他是少数对杰西卡好的人之一。 \n牧师经常和她交谈, 说服她摆脱法师, 用危险和宗教裁判所威胁她, 但试图吓唬杰西卡是徒劳的。 一天晚上, 一些陌生人闯入法师的房子并谋杀了他。 \n同一天晚上, 两名男子在她自己的卧室袭击了杰西卡, 但结果对他们不利 - 布里奇敦没有人知道杰丝挥舞她的火焰 blade 剑有多好。 她 literally 把他们切成了薄片。 ";
			link.l1 = "是的, 当然... 那个鲁莽的泼妇! ";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "在那之后, 整个城镇都害怕她。 然后面具出现了。 他们很快就找到了彼此。 ";
			link.l1 = "根据著作, 面具是约书亚.利德比特, ‘Neptune’的前船长... ";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "我后来才知道这么多。 面具到达一周后, 杰丝拿起她的东西, 和我道别, 乘坐一艘军用护卫舰驶向未知的方向。 她再也没有回来... 就像Beatrice再也没有回到宝藏岛一样。 \n不久之后, 他们在圣约翰绞死了屠夫, 他是被面具自己送到那里的。 但他只比屠夫多活了一天。 ";
			link.l1 = "是的... 我们的史蒂文.多德森表现出了风度... ";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "是的, 我是这么被告知的。 他为Beatrice报了仇... 杰西卡的故事就这样结束了, 她在某个无人居住的岛屿上与屠夫的海盗发生小冲突时去世了。 没有人知道这个地方在哪里。 屠夫死了, 杰克曼和刽子手也死了。 ";
			link.l1 = "扬, 你错了。 屠夫还活着。 ";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = "什么! ? 不可能! 他被绞死了! ";
			link.l1 = "阅读雷蒙德.贝克的证词。 这比任何故事都好。 ";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "给我看那个... (阅读) 嗯。 难以置信! 事实证明他的处决是假的! ";
			link.l1 = "狡猾吧? 不过, 这还不是全部。 你了解屠夫。 你只是不知道他现在是谁。 ";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "是吗? 他是谁? ";
			link.l1 = "来自皇家港的劳伦斯.贝尔特罗普。 矿山的主人, 杰克曼背后的那个神秘影子。 我通过贝克发现了这一点, 贝克从面具那里知道了。 ";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = " holy fuck! 所以结果是他策划了这一切? 好吧, 好吧... 我们也会去找屠夫。 我会思考如何打倒这个坏便士。 虽然这并不容易, 他受到英国当局的持续保护。 ";
			link.l1 = "他的时间会到来, 扬。 很快, 他将见到他的水手长和军需官。 好吧, 谢谢你的故事。 我该走了。 ";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "你现在要去哪里? ";
			link.l1 = "去某个岛屿。 我相信这是杰丝和Beatrice去世的地方, 也是面具突袭屠夫-贝尔特罗普的地方。 我需要证明海伦属于Sharp家族, 我希望在那里挖掘出来。 ";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "好吧。 那么, "+pchar.name+", 祝你好运。 你回来后告诉我细节。 ";
			link.l1 = "当然。 回头见, 扬! ";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // 战斗后和平解决的属性
		break;
		
		case "saga_82":
			dialog.text = "干得好, "+pchar.name+"。 你完成了不可能的任务。 我们所有海岸兄弟会的男爵都欠你的债。 ";
			link.l1 = "是的, 胜利之路很狭窄。 要是我事先知道我必须承受这么多... ";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "海伦怎么样? 她打算做什么? ";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "她和我一起留在我的船上。 她不再只是一名普通军官了。 岛屿的控制权将交给兄弟会的领袖, 她只会得到租金。 海伦自己决定的。 ";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "她出发去宝藏岛, 要自己掌握男爵领地。 ";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "好吧, "+pchar.name+"... 恭喜! 许多男人都梦想处于你的位置。 我很高兴海伦选择了一个值得她的男人。 你永远是她人生伴侣的最佳人选。 ";
			link.l1 = "谢谢你, 扬! 现在我想回到我们关于托尔图加和勒瓦瑟的谈话。 ";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "谢谢你, 扬! ";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "太棒了。 她应得的。 我认为兄弟会的新领袖将帮助她处理她的事务。 她是一个有才华。 聪明的年轻女孩, 能够快速理解和学习任何东西。 谢谢你, "+pchar.name+"! 海伦就像我的女儿, 我为她刚刚开启的美好未来感到欣喜若狂。 ";
			link.l1 = "不客气, 扬... 无论如何, 我想回到我们关于托尔图加和勒瓦瑟的谈话。 ";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "不客气, 扬。 ";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "在你离开的时候, "+sTemp+"和我已经讨论过了, 并就处置勒瓦瑟达成了共识。 航行到宝藏岛, 与我们的新领袖交谈, 他会给你我们计划的细节, 并将向你提供他能提供的所有帮助。 ";
			link.l1 = "我终于闻到了火药的味道! 没有时间可以浪费了, 我要出发去宝藏岛! ";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", 等一下。 我有几件礼物要送给你, 感谢你在海伦和兄弟会方面的帮助。 第一个是来自遥远东方的撒拉逊魔法护身符。 它的魅力增强了船上的纪律, 我亲自验证过。 给你。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("你收到了‘禁卫军’护身符。 ");
			PlaySound("interface\important_item.wav");
			dialog.text = "第二个只是过去冒险的纪念品。 我说服委员会将使用石碎片的荒谬遗留物抛到风中。 它们不再需要了。 我会把它们给你。 也许你会以某种方式找到它们的用途。 ";
			link.l1 = "碎片的用途? 嗯。 我不知道... 但作为纪念品, 我非常感激! ";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("你收到了五块装饰图案碎片");
			dialog.text = "好吧, 别忘了你的朋友, "+pchar.name+"。 当你在布鲁维尔德村锚定时, 顺便来我这里。 我们会坐下来喝些朗姆酒。 我总是很高兴见到你。 ";
			link.l1 = "当然, 扬。 我们现在有东西可以回忆了, 不是吗? 哈哈! 无论如何, 我该走了。 ";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "祝你好运, "+pchar.name+"! ";
			link.l1 = "再见... ";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> 萨迦失败
		case "saga_f_1":
			dialog.text = "是的... 看来我们的计划确实崩溃了。 现在我们无法让我们想要的人成为兄弟会的领袖。 杰克曼死了, 这很好。 但唉, 我的计划现在行不通了。 我们将不得不以通常的方式选举兄弟会的领袖, 天知道会发生什么转折... ";
			link.l1 = "那很不幸。 非常不幸。 而且看来海伦将失去她的遗产。 ";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "是的, "+pchar.name+"。 我想帮助你夺取托尔图加, 我真的想, 但现在我甚至不知道如何做。 可能我无法提供任何帮助。 看来你只能依靠自己的力量和战斗能力。 ";
			link.l1 = "看来没有其他选择了... 好吧, 扬, 我会去考虑下一步该做什么。 回头见... ";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "顺便来看看, "+pchar.name+"。 我总是很高兴见到你。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // 第一次通过 - 带走海伦, 关闭进入斯文森的通道
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // 关闭斯文森的书房
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// 海伦 - 对话
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // 调用宝藏岛的重新布置
		break;
		
		case "saga_l2": // 第二次通过 - 带走海伦。 纳撒尼尔和丹妮到马龙镇, 清理任务战利品
			dialog.text = "但唉, 现在做什么都太晚了。 宝藏岛已正式移交给英国王室。 那里现在有一个 garrison。 这对兄弟会是一个沉重的打击, 恐怕我们无法恢复。 ";
			link.l1 = "多么可怕... 啊, 我应该行动更快。 那么, 你看, 一切都会好起来的。 好吧, 扬, 我会去考虑下一步该做什么。 回头见... ";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "顺便来看看, "+pchar.name+"。 我总是很高兴见到你。 ";
			link.l1 = "... ";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // 大概不需要
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // 打开霍克的官邸
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// 海伦 - 对话
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // 调用宝藏岛的重新布置
			pchar.questTemp.Saga_Late = true; // 第二个属性, 用于排除对话, 以防万一
		break;
		
		case "saga_l3":
			dialog.text = "是的... 我们真的遭受了惨败。 最糟糕的是, 我们几乎就差一步就能胜利了。 卡兰巴! 这怎么会发生呢, "+pchar.name+"? 你这么努力, 做了这么多... 却这么倒霉! ";
			link.l1 = "我是该为此负责的蠢货。 我应该更快的。 由于我, 海伦将失去她的遗产。 而托尔图加计划也永远不会实现了。 ";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // 第二个属性, 用于排除对话, 以防万一
		break;
	// < —萨迦失败
	
	//-----------------------------------巴考特贸易生成器--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "好吧, 我不介意。 我的仓库里有125单位。 价格如你所知, 每单位3150。 ";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "好的, 成交。 给你。 这是3150杜布隆。 ";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "真倒霉。 我把钱忘在船上了。 我马上回来拿。 ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "好吧, 我不介意。 我的仓库里有二十五单位。 价格如你所知, 每单位三十杜布隆。 ";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "好的, 成交。 给你。 这是七百五十杜布隆。 ";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "真倒霉。 我把钱忘在船上了。 我马上回来拿。 ";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // 增加巴考特供应量
			{
				link.l4 = "扬, 有没有可能增加铁木的供应量? ";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // 增加巴考特供应量, 如果第一次没带来
			{
				link.l4 = "扬, 我筹集了三千金币。 给, 你可以把这份礼物送给我们的寄生虫。 我想他们今天会很开心。 ";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("你已支付750杜布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "值得称赞。 我会命令我的人把铁木搬到你的船上。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "如果你想购买更多, 两周后再来。 到那时我会再准备一批。 ";
			link.l1 = "好的, 扬。 下次见! ";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // 定时器
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "老朋友";
			if (startHeroType == 2) sStr = "老朋友";
			if (startHeroType == 3) sStr = "老朋友";
			if (startHeroType == 4) sStr = "海伦";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "很高兴你喜欢铁木, " + sStr + "。 增加供应不是问题, 但如你所知, 有个陷阱。 数量越大, 越容易吸引不必要的注意, 尤其是英国当局的注意。 但如果我们增加可靠的人手。 值得信赖的耳目, 以及在官邸里帮助我们保持隐蔽的人, 一切都可以安排。 不过这并不便宜 —需要三千杜布隆来绕过城市金库和英国的需求。 这样我就可以为你提供五倍的供应量。 你觉得怎么样? ";
				link.l1 = "三千杜布隆? 扬, 这简直是抢劫! 我们能不能用更低的费用解决? 也许有办法不用花这么多钱就能解决问题? ";
				link.l1.go = "UpgradeBakaut_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "好主意, 但我必须说, 对于如此大量的贸易事务, 你需要更多的经验和技能。 着急的话, 风险大于收益。 这样吧: 积累更多经验, 当你准备好处理更大批量时再来。 那时我们再好好讨论。 ";
				link.l1 = "嗯... 好吧。 我们稍后再谈这个。 ";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "唉, "+pchar.name+", 如今和平的代价就是这样 —那些戴假发穿制服的先生们的胃口与日俱增。 没有什么比钱箱里的杜布隆更能吸引他们了。 如果你觉得安慰的话, 我保证你以后的所有供应都能享受百分之十五的折扣。 ";
			link.l1 = "该死的! 要这么多钱! 如此贪婪, 他们应该去买国王的宝藏, 而不是讨价还价求沉默! 扬, 也许我们应该... 让他们看看谁才是群岛的真正主宰, 嗯? ";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "我的朋友";
			if (startHeroType == 2) sStr = "我的朋友";
			if (startHeroType == 3) sStr = "我的朋友";
			if (startHeroType == 4) sStr = "海伦";
			dialog.text = "哈! 你真有精神, " + sStr + "! 但现在与整个英国为敌不符合我的利益, 而且我也不再年轻了。 我们就付钱给这些吸血鬼, 让他们安静地坐着 —我们有自己的生意要做。 筹集必要的金额, 我们的道路就会畅通无阻, 不会有不必要的问题! ";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "好吧, 扬, 你说服了我。 就这样吧, 因为没有其他办法。 给你三千杜布隆。 记住: 我不打算永远喂这些吝啬鬼。 ";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "该死的, 扬! 你真的认为没有其他出路吗? 好吧。 我会找到这些杜布隆。 但现在我没有那么多钱。 ";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "该死的, 扬, 你真的想让我喂这些官员和他们娇生惯养的女士们吗? 他们坐在椅子上, 什么都不做, 只知道要钱! 不, 我不喜欢这样! 我不会用我的汗水和鲜血填满他们的口袋! 我们回到之前的条款吧。 这对我来说足够了。 ";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "这就对了! 有了你的贡献, 我们的生意将顺利进行, 这些吝啬鬼也会得到应有的报酬 —并且不再关注铁木。 我向你保证, 很快我们就会百倍地收回所有投资。 ";
			link.l1 = "我希望如此, 扬, 我希望如此。 ";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "生意会照常进行, 你不必担心。 现在, 关于我们未来的交易: 我会像以前一样, 在每月14日和28日为你准备125根铁木原木。 你可以用3150杜布隆买下整批。 ";
			link.l1 = "我更喜欢这样的对话! 那么一百二十五根原木? 太好了, 扬。 好吧, 很快见, 我会等待货物! ";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "老朋友";
			if (startHeroType == 2) sStr = "老朋友";
			if (startHeroType == 3) sStr = "老朋友";
			if (startHeroType == 4) sStr = "海伦";
			dialog.text = "如你所愿, " + sStr + "。 别这么激动。 世界就是这样安排的。 ";
			link.l1 = "是的, 扬, 我知道世界是如何安排的。 但这并不意味着我必须容忍它。 好吧, 我得走了。 ";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "我会等你筹集到钱。 我知道你会有办法的。 一旦你准备好 —我会等你带钱来, 然后我们继续。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// < —巴考特生成器
		
	//-----------------------------------矿山突袭 --------------------------------------------
		case "mine_attack":
			dialog.text = "很高兴见到你, "+pchar.name+"。 我的人准备好了。 去丛林吗? ";
			link.l1 = "是的, 扬。 我的小队已准备好战斗。 ";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "那我们出发吧。 矿山在丛林深处, 沿着这条小径走。 在岔路口向右。 前进! ";
			link.l1 = "前进! ";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//打开地点
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "那么, "+pchar.name+", 是时候讨论我们将如何进行这次行动了。 我已经提前派了几个米斯基托印第安人去勘察该地区, 并根据他们的观察制定了行动计划。 ";
			link.l1 = "告诉我! ";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "矿坑代表着丛林中山脉下的矿山。 矿山入口附近有一个营地。 有几间房子和一个栅栏。 有一条小路通向栅栏。 看, 它通向离这里不远的丛林中的一小块空地。 那就是矿坑的主要入口所在\n它代表着两座陡峭山丘之间的高墙, 阻止任何人潜入。 大门由六个人守卫。 不是大问题, 但他们还在那里架起了两门大炮。 这是最大的问题。 \n两发冷弹可以击倒我们一半的小队, 这将是一场灾难, 所以正面攻击不是一个选择... ";
			link.l1 = "哈! 但我们有一张王牌, 我们知道可以进入的密码... ";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "没错。 我们会利用这一点, 但现在让我把整个计划从头到尾告诉你。 ";
			link.l1 = "当然, 扬。 我洗耳恭听。 ";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "矿坑还有另一个入口 - 通过丛林中的那条小路。 它绕过保护矿山的山丘, 通向一个可以用来进入的小而狭窄的凹地。 但强盗们建立了一个高栅栏, 并在那里设置了守卫。 栅栏有小门, 但从另一边被路障封锁。 \n现在听我们要做什么。 我们将摆脱那些守卫矿山第二个入口的人。 我们的小队一部分将留在那里, 找一些原木作为撞锤。 \n我们将返回主要入口并杀死炮手。 我们的密码可以用两次。 之后我们将从两侧攻击矿山。 我将带领第一攻击单位, 你将带领第二攻击单位。 ";
			link.l1 = "嗯, 这很合理。 我们会让他们在两条战线上与我们作战。 前进! ";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//打开地点
			LAi_LocationDisableOfficersGen("mine_01", true);//不允许军官进入
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "对, 我们到了... 这是通往强盗栅栏的小路。 现在我们需要决定如何对付他们。 如果我们派整个小队过去, 会太可疑, 他们会发出警报。 \n我们应该派一个不超过三个人的小组, 这个小组能够在不引起怀疑的情况下接近并发动突然袭击。 我不能带领这个小组, 我的脸在这里太出名了。 \n所以, "+pchar.name+", 这取决于你, 因为我只能信任你指挥而不冒整个行动的风险。 我会给你格雷戈里和一名火枪手协助... ";
			link.l1 = "栅栏处有多少守卫? ";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "四个。 两名火枪手和两名士兵。 ";
			link.l1 = "我们会拿下他们... ";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "了解你, 我对此毫不怀疑。 走向他们, 告诉他们是杰克曼派你来的。 告诉他们密码。 然后在他们都放松警惕后... 见机行事。 ";
			link.l1 = "好的。 我们会让他们保持警惕。 ";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "祝你好运, "+pchar.name+"! ";
			link.l1 = "... ";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//禁止对话
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//禁止对话
			}
			chrDisableReloadToLocation = false;//打开地点
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "干得好, "+pchar.name+"! 你一如既往地取得了胜利。 现在, 我的孩子们将准备从矿山这边发起攻击, 我们将清除主要入口。 ";
			link.l1 = "我想, 我又要走向守卫了? ";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "是的, "+pchar.name+", 再一次。 我很想自己去, 但他们肯定会认出我, 整个行动就会失败。 这会更危险, 因为敌人更多, 别忘了武器。 ";
			link.l1 = "我会带上我的军官。 ";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "是的, "+pchar.name+", 再一次。 我很想自己去, 但他们肯定会认出我, 整个行动就会失败。 这会更危险, 因为敌人更多, 别忘了武器。 你会带谁来帮助你? 你的军官, 还是像上次一样带格雷戈里和火枪手? ";
			link.l1 = "我会带上我的军官。 ";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "我会带格雷戈里和火枪手。 ";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "好的。 你自己的人是你最好的后援。 现在我们将返回主要入口。 你记得路吗? ";
			link.l1 = "当然。 按我们来的路回去, 然后向左走, 然后绕山的小路。 ";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "好的。 你已经成功完成了一次, 所以第二次应该是小菜一碟。 我们现在要返回主要入口。 你记得路吗? ";
			link.l1 = "当然。 按我们来的路回去, 然后向左走, 绕山的小路。 ";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "没时间浪费了。 我们前进! ";
			link.l1 = "前进! ";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//打开地点
			LAi_LocationDisableOfficersGen("mine_01", false);//允许军官进入
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//不允许军官进入
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "对, "+pchar.name+", 听最后这些指示。 守卫大门的这些魔鬼很强硬, 所以对你来说不会容易。 你的主要目标是杀死站在大门附近的炮手, 因为如果他们还活着, 我们就无法帮助你。 \n一旦他们两个都死了, 没有机会开炮, 我们所有人都会过来在几秒钟内杀死他们。 你明白了吗, "+pchar.name+"? 不要逞英雄, 杀死炮手, 剩下的留给我们。 ";
			link.l1 = "好的, 扬。 我会尽量按计划行事。 如果出了什么问题, 我会随机应变。 ";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "听起来不错。 愿上帝与你同在! ";
			link.l1 = "谢谢... ";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//禁止对话
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//打开地点
			LAi_LocationDisableOfficersGen("mine_01", false);//允许军官进入
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "呼! 我们割倒了那些狗娘养的... 他们是顽强的小混蛋。 我担心我们在这里弄出了噪音, 可能被听到了。 不能浪费一分钟! "+pchar.name+", 是时候攻击矿山了。 \n我将回到第二入口的小组 —他们一定已经找到并准备好撞锤来撞开栅栏。 你和你的人将穿过中央大门。 等我们半小时, 不要立即攻击... ";
			link.l1 = "扬, 如果他们在矿山听到了枪声, 我们没有这半小时。 那些强盗可能会建立防线, 或者很可能直接到中央大门, 用一切力量攻击我的小组... ";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "操! 这很有可能。 你建议我们怎么做? ";
			link.l1 = "嗯... 哈! 我有个主意! 大炮! 看看周围。 不仅有葡萄弹, 还有炸弹! 现在这些强盗完蛋了! 我之前怎么没想到! ";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "你认为我们应该怎么做? ";
			link.l1 = "我们拿一门大炮。 有了一门, 我们可以移动得更快更有效。 我们将把它滚进去, 穿过大门, 到矿山并设置好位置。 如果他们自己发动攻击, 他们会得到一个大爆炸, 如果他们退缩, 我们就轰炸他们的营地。 你能告诉我大门后面的营地具体在哪里吗? ";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "营地在山边的低地上。 大门外有一条小径向下延伸, 绕过小山。 营地就在这座小山后面。 ";
			link.l1 = "太棒了! 我们将在小径顶部设置, 向小山那边发射几颗炸弹到他们的巢穴! 哦, 我们会让他们四处逃窜! ";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "该死的, "+pchar.name+", 干得好! 全速前进! 我把伦道夫留在你手下, 他是我最好的炮手。 让他做你的炮手, 他不会让你失望的。 我现在就去我的部队。 ";
			link.l1 = "好的。 我会轰炸他们的阵地半个小时, 直到你打破大门。 ";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "我会尽量及时赶到。 营地见! ";
			link.l1 = "成交... 小队! 听我的命令! 准备将大炮转移到新位置! 带上火药。 炸弹和葡萄弹! 穿过大门到矿山。 前进! ";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//打开地点
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // 允许军官进入
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // 武器 - 战斗! 
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "呼, 我们是不是太晚了, "+pchar.name+"? ";
			link.l1 = "扬, 该死的! 你怎么花了这么长时间? 我的小队刚刚遭受了巨大的打击! ";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "那个该死的木栅栏结果非常坚固。 我们强行打破了它... 我们听到了你的隆隆声。 看起来你已经把这个地方清理得很好了! 它正在燃烧! ";
			link.l1 = "伦道夫的功劳... 我希望你能看到我们在最终进入肉搏战之前埋葬了多少混蛋! ";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "卡兰巴! 我向你致敬, "+pchar.name+"。 干得好! 嗯, 关于损失... 战争中总会有损失。 ";
			link.l1 = "现在我们需要做的是清理矿山本身。 可能有一些幸存者藏在里面。 ";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "我们就我们两个人去。 去那里勘察情况。 ";
			link.l1 = "听起来是个计划! ";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//不允许军官进入
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "我们还没有搜索整个矿山! 我保证还有更多的混蛋藏在这里! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "我认为没有剩下的混蛋了... ";
			link.l1 = "扬, 我以为我们只是来这里勘察情况... ";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "哈哈, 好吧, 我没告诉你这将是一次特殊的勘察, 一次血腥的勘察... 我已经有一段时间没有这样的热身了! 现在每个人都可以放心, 没有一个混蛋逃出这个矿山! ";
			link.l1 = "那么我们接下来要做什么, 扬? ";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "你说接下来要做什么是什么意思? 我们要寻找黄金和白银。 我不认为杰克曼在这里建立这样一个堡垒是出于无聊。 他在这里部署了整个驻军。 你看到矿山里的奴隶了吗? 你应该询问他们在哪里储存提取物。 ";
			link.l1 = "好的。 那么你去审问奴隶, 我爬上去搜索营地里的所有房子, 也许我会找到一些东西。 ";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "明白了! 该行动了! ";
			link.l1 = "... ";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//打开地点
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//关闭矿山出口
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "去吧, 伙计。 把这些可怜的棚屋翻个底朝天! ";
			link.l1 = "我这就去! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "哈哈! "+pchar.name+", 你自愿和我一起出来捣毁这个矿山, 真是太好了! 这再次表明你是天生的幸运儿。 ";
			link.l1 = "你找到黄金了吗? ";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "是的, 该死的! 不是黄金而是白银, 一大堆。 再晚一天, 他们就会把它运出营地。 这就是为什么这里有这么多暴徒 —他们是护送队。 \n多亏了你, 我们及时赶到了, 没有你, 我还在召集人。 恭喜你, 伙伴! ";
			link.l1 = "哈! 我明白... 我们有多少白银? ";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "我们有大约四千单位。 我们将把它分成两部分 —我一半, 你一半, 就像我们约定的那样。 ";
			link.l1 = "太棒了! 我们可以用这些东西赚一大笔钱! ";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "那是肯定的... 你找到什么有价值的东西了吗? ";
			link.l1 = "没有。 这些棚屋里甚至没有一个杜布隆。 不过我找到了一些文件。 我读了一下, 了解到这个矿山的主人是皇家港的某个劳伦斯.贝尔特罗普。 ";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "哦, 真的吗? 让我看看这些文件... ";
			link.l1 = "给你。 ";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(阅读)... 好的... 贝尔特罗普? 我从某个地方知道这个姓氏。 哦, 是的! 托马斯.贝尔特罗普! 这很有趣... 好吧, 我回到布鲁维尔德村后会调查这个。 如果你不介意, 我会把这些文件留给我? ";
			link.l1 = "一点也不。 我不需要它们。 ";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "很好。 现在, 剩下的最好的部分是, 我要把白银运到船上。 米斯基托人会帮助我们。 我们会组装一辆马车... 同时, 你就去休息吧, "+pchar.name+"。 你比任何人都值得休息! ";
			link.l1 = "谢谢, 扬。 我们将在那座山上扎营, 灰烬的味道太浓了。 是的, 我们需要扑灭这些棚屋的火, 谁知道呢, 也许将来我们会用得上... ";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "想认领矿山吗? 哈哈! 我已经在考虑这个想法了, 但掠夺是一回事, 把它作为财产是另一回事。 朋友, 它已经有主人了。 我们可能会与英国当局产生麻烦。 \n此外, 我谈到的那些奴隶告诉我, 这里的所有矿脉基本上都被开采完了 —之前已经有几批大量的白银被运走了。 恐怕这个矿山已经完了。 ";
			link.l1 = "嗯... 我们会看到的。 也许不是所有的都被耗尽了。 好吧, 我真的应该休息一下。 回头见, 扬";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "去吧。 别担心任何事。 我们会自己处理剩下的一切。 ";
			link.l1 = "... ";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "休息得好吗, "+pchar.name+"?";
			link.l1 = "还不错... 不过, 老实说, 我真想找个酒馆, 喝一杯, 在干净的床上睡一觉。 ";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "印第安人已经把白银运到岸边, 并在我军官的监督下装载到你的船上。 你可以已经回去了。 你对朗姆酒。 酒馆和床的愿望很快就会实现。 我希望你五天后到我家来, 我们还有很多事情要做。 ";
			link.l1 = "好的, 扬。 五天后布鲁维尔德村见! 祝你好运! ";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //打开矿山出口
			LAi_LocationDisableOfficersGen("mine_mines", false); // 允许军官进入
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以加速时间
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // 定时器
			pchar.questTemp.Saga.Mines = "true"; // 萨迦之后矿山将被开采
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// < —矿山突袭
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "扬, 别对我大喊大叫。 让我们像理智的人一样解决问题 —记住, 我们有生意要做! ";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "我现在就放我的狗来咬你, 你这只癞蛤蟆! 忘了勒瓦瑟, 滚蛋! ";
			link.l1 = "扬! 听我说... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "什么桶? 至于海伦, 我一定会好好教训她... 开玩笑的, 查尔斯, 开玩笑的! 我知道是怎么回事, 至于乔安娜 - 希望这个故事能让她想一想 - 你知道, 她最近特别暴躁... 嗯, 生活就是这样。 无论如何, 祝你在卡塔赫纳好运! ";
			link.l1 = "再见, 扬。 ";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}