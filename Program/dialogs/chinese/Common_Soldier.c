// boal 25/04/04 普通士兵对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (false) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition 在任务中不使用, 是的, 也不需要让玩家再为了任务到处跑。 任务请写在common里
    /* // 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 按城市调用对话 < —*/
    int iTest, iTemp;
    string sTemp;
    iTest = FindColony(NPChar.City); // 城市
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (false)
			{
				// 海盗占位符
				if (false)
				{
    				dialog.text = RandPhraseSimple("镇上有海盗? ! 真不敢相信... 抓住" + GetSexPhrase("他","她") + "! ! ", "那是个海盗! 抓住" + GetSexPhrase("他","她") + "! ! ! ");
					link.l1 = RandPhraseSimple("我是海盗, 那又怎样? ", "呵, 你们可以试试... ");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("你是谁, 在这里做什么? ", "站住! 你是谁, 你有什么权利想进入城镇? ");
						link.l2 = "我在" + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + "附近下锚, 挂着" + NationNameGenitive(sti(npchar.nation)) + "的旗帜。 你有什么不明白的? (欺骗概率" + DeceptionChance + "%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("间谍! 放下武器跟我来! ", "敌特! 抓住" + GetSexPhrase("他","她") + "! ");
						link.l1 = RandPhraseSimple("闭嘴, 娘娘腔! ", "去你的! ");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy。 检查是否是敌人。 -->
				if (false)
				{
					// 文森托文书
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("你是谁, 在这里做什么? ", "站住! 你是谁, 你有什么权利想进入城镇? ");
						link.l1 = "看看这文书, 士兵。 我是受审判官文森托神父允许来这里的。 ";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("你是谁, 在这里做什么? ", "站住! 你是谁, 你有什么权利想进入城镇? ");
						link.l1 = "看看这文书, 士兵。 我是受审判官文森托神父允许来这里的。 ";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("规矩点, 别打扰奴隶。 ", "快点, 往前走! ", "啊, 是你。 去吧, 我们已经接到通知了。 ");
						link.l1 = "... ";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("你是谁, 在这里做什么? ", "站住! 你是谁, 你有什么权利想进入城镇? ");
					//==> 按许可证
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "军官, 我有" + GetRusNameNationLicence(HOLLAND) + ", 所以我来这里是合法的。 来, 请看看... ";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //如果停泊在城市
						{
							link.l2 = "你没看到我船上挂着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜吗? ! (欺骗概率" + DeceptionChance + "%%)";
						}
						else //如果停泊不在城市
						{
							link.l2 = "我在" + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + "附近下锚, 挂着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜。 你有什么不明白的? (欺骗概率" + DeceptionChance + "%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> 按旗帜
						// 海盗占位符
						if (false)
						{
    						dialog.text = RandPhraseSimple("镇上有海盗? ! 真不敢相信... 抓住他! ", "那是个海盗! 抓住他! ");
							link.l1 = RandPhraseSimple("是的, 我是海盗 —现在怎样? ", "呵, 有本事就来抓我... ");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //如果停泊在城市
						{
							link.l1 = "你没看到我船上挂着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜吗? ! (欺骗概率" + DeceptionChance + "%%)";
						}
						else //如果停泊不在城市
						{
							link.l1 = "我在" + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + "附近下锚, 挂着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜。 你有什么不明白的? (欺骗概率" + DeceptionChance + "%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// < —eddy。 检查是否是敌人。 
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // 我们的市民
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "哦, 船长, 我们在海上和你在一起真是太开心了! 在你的指挥下, 我们一起击沉了那么多船! 而在这里... ";
									link.l1 = "而在这里, 我的朋友, 你可以尽情欣赏迷人的女士们, 在海上可看不到她们。 ";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "船长, 我们做了什么才配得上这个? ! 我们不是陆地上的老鼠, 对吧? ";
									link.l1 = "安静, 水手! 你的岗位非常重要和光荣, 别再抱怨了。 ";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "海上发生了什么, 船长? 我们还能再见到它吗? ";
									link.l1 = "当然, 水手! 一旦你卸任, 就可以去码头, 尽情享受大海。 ";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "我要抱怨, 船长: 我们每个人都想念大海。 我们都受够了这种陆地职责! ";
									link.l1 = "我听腻了这种抱怨! 你们这里也有足够的朗姆酒! 在船长安排的地方服役, 否则有人会被绞死作为他人的榜样。 ";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "我私下告诉你, 船长, 新总督是个受贿者和贪污犯。 但这真的不关我的事... ";
									link.l1 = "没错, 海盗。 你的事是坚守岗位维持秩序。 而把总督吊在桅杆上是我的事。 干得好! ";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "谢谢你没有忘记我们, 船长! 我们愿意跟着你赴汤蹈火! ";
									link.l1 = "我了解你们这种人, 骗子! 你们真正爱的只是金子。 今晚酒馆有聚会, 我请客。 别忘了来。 ";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "呵, 船长! 想想看, 一个海盗真的能成为秩序的维护者吗? 我们已经很久没有做过真正的生意了! ";
									link.l1 = "没有时间放松, 海盗! 敌人的舰队正在我们岛屿附近的水域搜寻, 我们必须随时准备好血战。 ";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "船长, 我听说王室又派了一支中队来我们这里? ";
									link.l1 = "当然, 海盗。 只要我们活着, 就不会有和平。 即使在地狱里, 我们也会与魔鬼战斗! ";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "哟吼吼! 该死的, 船长, 昨天的酒真烈! 可惜你不在场。 ";
									link.l1 = "没什么大不了的, 我会弥补的。 而且我不羡慕你们, 伙计们。 ";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "我私下告诉你, 船长, 因为你一直对我们很好, 我们昨天和一个非常漂亮的小妞玩得很开心... ";
									link.l1 = "呵, 海盗, 你真的需要绞索! ";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "船长! 请把我从这个该死的职责中解脱出来! 我再也不能扮演秩序维护者的角色了。 ";
									link.l1 = "船上的夜哨也不容易。 朋友, 职责就是职责, 无论是什么, 无论在哪里。 ";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition 在任务中不使用, 是的, 也不需要让玩家再为了任务到处跑。 任务请写在common里
							/* link.l2 = RandPhraseSimple("有重要的事! ", "我找你有事。 ");
							link.l2.go = "quests";//(转发到城市文件) */
							break;
						}
						else
						{ // 海盗, 不是我们的
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("警报! 武装的病态疯子在这里! ", "拿起武器, 拿起武器! 有个疯狂的混蛋在这里! ");
								link.l1 = RandPhraseSimple("嗯? 什么? ", "呃, 你为什么要这样做? ");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("你找我有事吗, 船长? ", "我在这里闲逛, 如果有什么需要 —问吧, 别拖着。 "), RandPhraseSimple("船长, 我很忙, 所以找别人聊天吧。 ", "有什么不对劲吗, 船长? 如果没有问题, 那就让我过去。 "), "让开, 船长, 我赶时间。 ");
							link.l1 = LinkRandPhrase("对不起, 朋友, 我" + GetSexPhrase("介绍了","介绍了") + " ", "好吧, 忙你的事吧。 ", "不, 没什么。 ");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("我有几个问题要问你。 ", "我找你有事。 "), RandPhraseSimple("我看你很匆忙。 一个问题, 你就自由了。 ", "我" + GetSexPhrase("想","想") + "问点事。 "), "你的事可以等。 我就是想问" + GetSexPhrase("想","想") + "。 ");
							    link.l2.go = "quests";//(转发到城市文件) */
								
								//埃克库 Korsar - 他们对海盗来说太礼貌了...
								dialog.text = RandPhraseSimple("你想要什么? 过去。 ", "别挡路, 退后。 ");
					            link.l1 = RandPhraseSimple("你知道吗? 别叫了! ", "减少你的热情。 我不会很快冷静下来的! ");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("我有几个问题要问你。 ", "我找你有事。 "), RandPhraseSimple("我看你很匆忙。 一个问题, 你就自由了。 ", "我" + GetSexPhrase("想","想") + "问点事。 "), "你的事可以等。 我就是想问" + GetSexPhrase("想","想") + "。 ");
							link.l2.go = "quests";//(转发到城市文件) */
							}
							break;
						}
					}
					else
					{ //如果是对友好或中立国家有不良行为的人
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("看看那个无赖! 他竟敢在" + XI_ConvertString("Colony" + npchar.city) + "露面。 抓住" + GetSexPhrase("他","她") + "! ! ! ", "哈, 我认出你了, " + GetSexPhrase("无赖","流氓") + "! 抓住" + GetSexPhrase("他","她") + "! ! ! ");
							link.l1 = RandPhraseSimple("啊! ... ", "好吧, 你自找的... ");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> 丛林中的少女
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "哦, 看看谁在那里! " + pchar.GenQuest.EncGirl.name + "小姐亲自光临! 我想知道你怎么敢? 我们一直在找你! 请前往地牢 —你的牢房已经准备好了, 在等着你。 ";
							link.l1 = "你在说什么胡话! 我和我的" + GetSexPhrase("骑士","同伴") + "在丛林中散步, 采花。 别烦我! 这些严格的人礼貌在哪里? ! 他们一看到迷人的女孩, 就开始对她唠叨! " + GetSexPhrase("亲爱的, 请告诉那些笨蛋滚开, 让一个诚实的女人独处! ","亲爱的, 请告诉那些笨蛋... ") + "! ";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "哦, 你在这里, 美人! 你爸爸让整个驻军都去找你, 把你带回家。 ";
							link.l1 = "滚开! 我知道我要去哪里, 我不需要你的帮助! 船长, 告诉他们把手从我身上拿开。 ";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// < —丛林中的少女

					// --> belamour 夜间冒险者
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "士兵的生活是有计划的 —站岗, 巡逻... 你想要什么, " + GetAddress_Form(NPChar) + "? ";
						link.l1 = "听着, 最近是不是和你在这里有个醉汉打架了? 嗯, 不过, 显然是的, 和你... ";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// < —夜间冒险者
					
					//belamour legendary edition 对话, 如果英雄有军衔和对国家的贡献 -->
					
					// 夏尔.德.莫尔 法国殖民地总督将军
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "大人, 总督将军! 我能为您做什么? ";
							link.l1 = "我不需要任何东西, 谢谢。 ";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "这对我来说是一种荣誉, 总督将军先生! 我能为您做什么? ";
								link.l1 = "认真履行你的职责 —我不需要你做更多。 ";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "很高兴见到您, 大人! 一个卑微的士兵能为我们殖民地的总督将军做什么? ";
								link.l1 = "就我个人而言, 我不需要你做任何事。 继续服役。 ";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// 服役国家的海军中将 不穿制服也能认出来
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "中将大人! 请允许我报告: 在我值班期间... ";
							link.l1 = "冷静点, 士兵, 我不需要你的报告。 向你的军官报告。 ";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "很高兴见到您, 中将! 我能为您做些什么? ";
								link.l1 = "不, 我只是检查你有多专注。 我很高兴你认出了我。 ";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "中将, 这是我的荣幸! 我能为您做什么? ";
								link.l1 = "为" + NationNameGenitive(sti(npchar.nation)) + "服务, 士兵! 这是你能做的最好的事情。 ";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// 有许可证的军官
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "问候您, 船长! 如果您有任何指示给我, 那么请原谅: 虽然我为" + NationNameGenitive(sti(npchar.nation)) + "服务, 但我只听令于指挥官和总督。 "; 
							link.l1 = "我有我的军官和船员听从我的指导。 履行你的职责, 士兵。 ";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "船长, 你能带我到你的船上服役吗? 同样为" + NationNameGenitive(sti(npchar.nation)) + "服务, 但我更喜欢大海。 "; 
								link.l1 = "你需要在被分配的地方, 所以要光荣地履行你的职责。 你一闭眼, 他们就会把你带到海上。 ";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "哦, 你很幸运: 你是为" + NationNameGenitive(sti(npchar.nation)) + "服务的船长... 而我整天都被困在这里。 "; 
								link.l1 = "你认为我刚到加勒比海, 一周后就成了船长吗? 这都是多年的辛勤工作... ";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// < —legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "你没看见吗? 我在值班。 别烦我。 ";
							link.l1 = "好吧, 好吧... ";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "你要告诉我一些可疑的活动吗? ";
							link.l1 = "不, 一点也没有, 顺便说一下, 我是船长。 我看你不再听了? 再见。 ";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "这是军事设施, 所以在这里不要太吵。 ";
							link.l1 = "好的, 我会记住的。 ";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "天气这么好, 我却不得不站在这里。 在镇上, 至少有女孩, 而我们这里有什么? 周围只有老鼠。 ";
							link.l1 = "" + GetSexPhrase("我很同情, 但我帮不了你 —毕竟这是你的职责。 ","嘿! 我怎么了? 我不是女孩吗? ") + "";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "如果你喜欢说话, 去找别人。 我必须在这里维持秩序, 我没有时间闲聊。 ";
							link.l1 = "哦, 不, 我只是检查一下, 你是否还活着。 你站在那里就像一尊雕像。 ";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "你可能认为驻军工作日很轻松? 绝对不是! 这是一项艰苦而重要的工作。 我记得有一次... ";
							link.l1 = "你改天再给我讲那个故事吧。 我现在有点赶时间。 ";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "这里小心点, 你在堡垒里! 要像老鼠一样安静! ";
							link.l1 = "如你所说, 士兵。 ";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "嘿! 你碰巧有水吗? 我快渴死了。 ";
							link.l1 = "没有, 朋友, 耐心点... ";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "驻军生活多无聊啊, 周围只有像你这样的乡巴佬! 现在, 城镇驻军肯定过得更好... ";
							link.l1 = "你这也叫‘在值班’? 这样你肯定会让间谍从你身边溜走! ";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = "" + GetSexPhrase("你看起来像个强壮的家伙, 不是吗? 你想报名参加堡垒驻军的值班吗? 我们有宽敞的营房, 一天两餐, 还有免费的酒。 ","哦, 年轻的女士, 你不知道, 在这个穷乡僻壤遇到这么好的姑娘是多么令人愉快! ") + "";
							link.l1 = "" + GetSexPhrase("这当然很诱人, 但我还是必须拒绝。 所有的营房训练都不适合我。 ","谢谢你的夸奖, 士兵。 ") + "。 ";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "这该死的热... 我很乐意放弃我一半的生命回到欧洲。 ";
							link.l1 = "是的, 我看得出来你的健康不适合当地的气候。 ";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition 在任务中不使用, 是的, 也不需要让玩家再为了任务到处跑。 任务请写在common里
					/* link.l3 = "等一下。 我就是想问" + GetSexPhrase("想","想") + "... ";
					link.l3.go = "quests";//(转发到城市文件) */				
				}
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier") && npchar.location.group == "soldiers" && npchar.city == "Bridgetown")
			{
				dialog.text = "欢迎来到布里奇敦, "+GetAddress_Form(NPChar)+"…… ";
				link.l1 = "我还以为我的脸在法属殖民地之外也很有名呢……  我叫"+GetFullName(pchar)+"。";
				link.l1.go = "WildRose_Soldier_1";
				DeleteAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier");
				DelLandQuestMark(npchar);
			}
			//<-- Дикая Роза
		break;
		//============================== 识别时的拆解节点 =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("在我看来这是某种诡计。 我们和指挥官谈谈, " + GetSexPhrase("伙伴","亲爱的") + ", 把一切都弄清楚... ", "嗯... 我觉得你不是你假装的那个人... " + GetAddress_Form(npchar) + "放下武器, 跟我来接受进一步调查! ");
			link.l1 = RandPhraseSimple("去你的! ", "当两个星期天在一周内到来时... ");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("哦, 我明白了... 一切似乎都没问题, 你可以走了, " + GetAddress_Form(pchar) + "。 ", "我一定是站岗站得有点累了... 一切似乎都很好, " + GetAddress_Form(pchar) + ", 对不起。 ");
			link.l1 = "没问题! ";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("哦, 我明白了... 一切似乎都很正常, 你可以走了, " + GetAddress_Form(pchar) + "。 ", "现在让我看看... 嗯, 一切似乎都正常, " + GetAddress_Form(pchar) + ", 对不起。 ");
			link.l1 = "这会给你一个教训! ";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "想想看! 如此无礼! 以商人的名义来到这里! 你的照片贴在每个营房里, 你这个混蛋! 这次你逃不掉了! 抓住他! ";
				link.l1 = RandPhraseSimple("啊! ... ", "好吧, 你自找的... ");
				link.l1.go = "fight";	
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //如果停泊不在城市 300912
			{
				dialog.text = "你是来这里交易的? 我可以问问怎么交易吗? 你的船在哪里? 你知道, 这一切看起来都很可疑, 我不得不拘留你, 直到我们弄清楚。 放下武器跟我来! ";
				link.l1 = RandPhraseSimple("去你的! ", "当两个星期天在一周内到来时... ");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "你的许可证必须被吊销, 因为它已经过期了, 因此无效。 放下武器跟我来接受进一步调查! ";
				link.l1 = RandPhraseSimple("去你的! ", "当两个星期天在一周内到来时... ");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "嗯... 一切看起来都很好。 不过, 我必须注意到你的许可证今天到期。 这次我让你通过, 但你仍然必须获得新的许可证。 ";
				link.l1 = "谢谢你, 我会尽早获得新的。 ";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "嗯... 一切看起来都很好。 不过, 我必须注意到你的许可证很快就会到期。 它仍然有效只有" + FindRussianDaysString(iTemp) + "。 所以记住这一点, " + GetAddress_Form(npchar) + "。 ";
				link.l1 = "谢谢你, 我会尽早获得新的。 ";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("嗯, 一切看起来都很好。 你的许可证还有" + FindRussianDaysString(iTemp) + "有效。 你可以通过。 ", "一切都清楚了, " + GetAddress_Form(npchar) + "。 你可以自由进出城镇, 你的许可证还有" + FindRussianDaysString(iTemp) + "有效。 抱歉打扰你。 ", "一切看起来都很好, " + GetAddress_Form(npchar) + ", 我不再留你了。 ");
				link.l1 = RandPhraseSimple("太好了。 向你问好。 ", "谢谢你, 军官。 ");
				link.l1.go = "exit";
			}
		break;
		//============================== 皇家港灯塔节点 =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("嘿, 伙计, 别在灯塔里弄坏任何东西。 ", "这座灯塔是非常重要的城镇设施。 小心点! ");
			link.l1 = RandPhraseSimple("好的, 别担心。 ", "好的, 别担心。 ");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("不要靠近大炮 —这是军事设施! ", "陌生人不得靠近大炮! ", "如果我注意到你在大炮附近闲逛, 你就完了! ");
			link.l1 = RandPhraseSimple("我知道了。 ", "好的, 我知道了。 ");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> 生成器 "丛林中的少女"
		case "GirlEnc_1":
			dialog.text = "你又是谁, 船长? 你不会碰巧是这个定居点最臭名昭著的小偷的同伙吧? ";
			link.l1 = "你刚才叫谁同伙? ! 你是晒昏头了还是怎么了? ! 嘿, 把你的爪子从女孩身上拿开! ";
			link.l1.go = "GirlEnc_11";
			link.l2 = "实际上, 我最近" + GetSexPhrase("认识了她","认识了她") + "... ";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = "" + GetSexPhrase("先生","小姐") + ", 我们有命令拘留她并把她带到地牢。 如果你认为你可以阻止我们, 那你就错了。 ";
			link.l1 = "那么, 让我们看看... ";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "哦, 真的吗? 在这种情况下, 我建议你检查一下你的口袋。 那位女士是专业的, 你知道";
			link.l1 = "谢谢你, 我会的。 我怎么会犯这样的傻... ";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = "" + GetSexPhrase("先生","小姐") + ", 我们有命令找到那位女士并把她带给她的父亲。 ";
			link.l1 = "好吧, 命令就是命令 —那就去吧。 ";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "太晚了, 因为我已经在带她去见她父亲了。 ";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "船长, 我们有命令, 如果你认为你可以阻止我们, 那你就错了。 ";
				link.l1 = "那么, 让我们看看... ";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "呵, " + GetSexPhrase("你是个幸运的男人","你是个幸运的少女") + "。 她的父亲答应给把她带回给他的人一笔丰厚的奖励。 ";
				link.l1 = "不要绝望 —你前面还有很多奖励。 ";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// < —生成器 "丛林中的少女"
		// --> belamour 夜间冒险者
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "是的, 和我。 让他坐在牢里, 想想他的行为。 如果你是来为他威胁我的, 那么相信我: 我甚至可以联系到堡垒的指挥官。 ";
			link.l1 = "是的, 我不是来威胁的, 而是来请你撤回对他的指控。 你看, 他是我的老熟人, 他只是喝醉了, 但对于一个醉汉来说, 你知道, 大海只有齐膝深... ";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "也就是说, 他在我值班时给了我一个黑眼圈, 现在他应该被释放? 为什么会发生这种情况? ";
			link.l1 = "五百比索作为对他行为的道歉怎么样? ";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "你这样认为吗? 他侮辱了我的荣誉, 你认为这可以用五百比索原谅吗? 你认为我的荣誉可以被购买吗? ";
			link.l1 = "... ";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "不, 船长, 这一切都是公平的。 他罪有应得。 我请你不要再打扰我的服务了。 ";
				link.l1 = "好吧, 你是对的。 ";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "一千。 而且不能少一个比索。 ";
				link.l1 = "不, 也许我不准备为一个瘀伤付这么多钱。 ";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "哦... 好吧, 等一下。 这里马上有笔和羊皮纸。 写上你撤回对我朋友的任何指控。 ";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "那么我请你不要再打扰我的服务了。 ";
			link.l1 = "我不会的。 ";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "给你。 ";
			link.l1 = "工作顺利。 ";
			link.l1.go = "exit";
		break;
		// < —夜间冒险者
		
		//--> Дикая Роза
		case "WildRose_Soldier_1":
			if (GetHour() >= 6 && GetHour() <= 21)
			{
				dialog.text = "啊, 是您啊, 船长…… 太阳底下真让人犯困……  该死的热浪! ";
			}
			else
			{
				dialog.text = "这话不假。 不过您也知道, 到了晚上人都一个模样。";
			}
			link.l1 = "什么风把你吹来了, 士兵? 你们这些人平时可不会跟我多话。";
			link.l1.go = "WildRose_Soldier_2";
		break;
		
		case "WildRose_Soldier_2":
			dialog.text = "咳, 是的, "+GetAddress_Form(NPChar)+"。 不过我奉威洛比勋爵的命令行事: 必须提醒所有新上岛的人, 几天前有一小撮奴隶从毕肖普种植园逃跑了。 那些该死的监工大概在呼呼大睡时让他们砸开了镣铐。 本来今天我该在我亲爱的安杰莉卡怀里…… ";
			link.l1 = "让我猜猜: 派去追捕庄园主“财产”的, 是你们驻军?";
			link.l1.go = "WildRose_Soldier_3";
		break;
		
		case "WildRose_Soldier_3":
			dialog.text = "当然…… 毕肖普还派了几支雇佣兵小队进了雨林, 但他还嫌不够。 他许诺, 谁要是能把奴隶带回来——活的, 就有重赏。 平时干活的是那些黑皮肤的, 但最近送来了一批逃兵——挖矿不顶用, 但脑子倒挺灵, 居然真从种植园逃了出去…… ";
			link.l1 = "所以他们是白人? ";
			link.l1.go = "WildRose_Soldier_4";
		break;
		
		case "WildRose_Soldier_4":
			dialog.text = "白得不能再白了, 见鬼去吧! 黑人只会逃跑, 而这帮人还顺手从他们干掉的雇佣兵 身上拿了几把火枪和军刀——还真派上了用场。 他们干掉了我们一个弟兄, 还带走了毕肖普的两个走狗——搞得剩下的人都疯了。\n差点就误把自己人当逃奴给射了。 还有几个平民在雨林里神秘失踪了。";
			link.l1 = "城门上锁了吗? ";
			link.l1.go = "WildRose_Soldier_5";
		break;
		
		case "WildRose_Soldier_5":
			dialog.text = "当然没有——城又没戒严。 您想去哪儿就去哪儿。 不过要是您想猎人变成猎物, 正好撞进火力交叉点, 那就别怪我们没提醒。真要能活下来, 也别回头去总督府拍门喊冤——毕竟, 他已经表现出足够的善意, 不光照顾布里奇敦的居民, 还照顾到了客人。";
			link.l1 = "这真是…… 仁慈之举。 愿上帝保佑弗朗西斯·威洛比!";
			link.l1.go = "WildRose_Soldier_6";
			link.l2 = "唉, 要是所有总督都像威洛比爵士一样关心新来的就好了…… ";
			link.l2.go = "WildRose_Soldier_7";
		break;
		
		case "WildRose_Soldier_6":
			dialog.text = "真好笑。 您可以走了, 船长。";
			link.l1 = "那就再见了, 士兵。";
			link.l1.go = "WildRose_Soldier_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "WildRose_Soldier_7":
			dialog.text = "可不是嘛, 那我们这些人就轻松多了。 我就不多打扰您了, 船长。";
			link.l1 = "祝你好运, 士兵。";
			link.l1.go = "WildRose_Soldier_8";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
		break;
		
		case "WildRose_Soldier_8":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves");
		break;
		//<-- Дикая Роза
		
		//关于暴露武器的注释
		case "SoldierNotBlade":
			// belamour legendary edition 如果英雄是国家军官 -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "船长, 我请你收起你的武器: 在我们的城市里禁止拔出它们。 ";
			link.l1 = LinkRandPhrase("好的, 我会收起它... ", "已经完成。 ", "如你所说... ");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("去你的! ", "我想我会用它! ", "我会在合适的时候收起它。 ");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// < —legendary edition
			dialog.text = LinkRandPhrase("嘿, 挥舞所有武器是怎么回事? ! 马上把它收起来! ", "我命令你立即收起你的武器! ", "嘿, " + GetAddress_Form(NPChar) + ", 别吓唬人! 收起你的武器。 ");
			link.l1 = LinkRandPhrase("好的, 我会收起它... ", "已经完成。 ", "如你所说... ");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("去你的! ", "我想我会用它! ", "我会在合适的时候收起它。 ");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
