// boal 25/04/04 堡垒士兵通用对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour传奇版 任务中不使用, 是的, 也不需要让玩家再为箱子奔波。 任务请写在commone中
	/* // 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("间谍! 放下武器跟我走! ", "敌方特工! 抓住他" + GetSexPhrase("他","她") + "! ");
				link.l1 = RandPhraseSimple("闭嘴, 娘娘腔! ", "去你的! ");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy。 检查是否为敌人。 -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("你是谁, 在这里做什么? ", "站住! 你是谁? 为什么试图进入堡垒? ");
					//==> 按许可证
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "军官, 我有" + GetRusNameNationLicence(sti(npchar.nation)) + ", 所以我是合法来到这里的。 请看... ";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> 按旗帜
						// 海盗占位符
						if (sti(pchar.nation) == PIRATE)
						{
							dialog.text = RandPhraseSimple("堡垒里有海盗? ! 抓住他" + GetSexPhrase("他","她") + "! ", "那是个海盗, 在我们的堡垒里窥探! 送进监狱!!! ");
							link.l1 = RandPhraseSimple("是的, 我是海盗, 现在怎样? ", "呵, 有本事就来抓我... ");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) // 如果停泊在城市
						{
							link.l1 = "你没看到我船上飘扬的" + NationNameGenitive(sti(pchar.nation)) + "旗帜吗? ! ";
						}
						else // 如果停泊在非城市区域
						{
							link.l1 = "我在" + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + "附近停泊, 船上升着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜! 还需要别的吗? ";
						}
						// belamour传奇版 值得信赖的特质让玩家有机会欺骗守卫
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							Notification_Perk(true, "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// < —eddy。 检查是否为敌人。 
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // 我们的市民
						{
							switch (rand(10))
							{
								case 0:
									dialog.text = "哦, 船长, 我们在海上和你度过了多么美好的时光! 在你的指挥下我们一起击沉了那么多船! 而在这里... ";
									link.l1 = "而在这里, 我的朋友, 你可以尽情欣赏迷人的女士, 在海上可看不到她们。 ";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "船长, 我们做了什么要受这个? ! 我们不是陆上老鼠, 对吧? ";
									link.l1 = "安静, 水手! 你的岗位非常重要和光荣, 别再抱怨了。 ";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "海上怎么样, 船长? 我们还能再见到海吗? ";
									link.l1 = "当然, 水手! 一旦你下班, 就可以去码头尽情享受大海。 ";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "我要抱怨, 船长: 我们每个人都想念大海。 我们受够了这种陆上职责! ";
									link.l1 = "我听够了抱怨! 这里也有足够的朗姆酒! 按船长的安排服役, 否则有人会被绞死以儆效尤。 ";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "我私下告诉你, 船长, 新总督是个受贿者和贪污犯。 但这真的不关我的事... ";
									link.l1 = "没错, 海盗。 你的事是站岗维持秩序。 把总督吊死在桅杆上是我的事。 干得好! ";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "谢谢你没有忘记我们, 船长! 我们愿意跟随你赴汤蹈火! ";
									link.l1 = "我了解你们这种人, 骗子! 你们真正爱的是黄金。 今晚酒馆有派对, 我请客。 别忘了来。 ";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "呵, 船长! 想想看, 海盗真的能维持秩序吗? 我们好久没做真正的生意了! ";
									link.l1 = "没有时间放松, 海盗! 敌人的舰队在我们岛屿附近巡游, 我们必须随时准备血战。 ";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "船长, 我听说王室又派了一支中队来? ";
									link.l1 = "当然, 海盗。 只要我们活着, 就不会有和平。 即使在地狱我们也会与魔鬼战斗! ";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "哟吼吼! 该死, 昨天的酒真烈, 船长! 可惜你不在场。 ";
									link.l1 = "没什么大不了, 我会补上的。 而且我不羡慕你们, 伙计们。 ";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "我私下告诉你, 船长, 因为你一直对我们很好, 我们昨天和一个非常漂亮的女孩玩得很开心... ";
									link.l1 = "呵, 海盗, 你真该被绞死! ";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "船长! 请解除我这个该死的职务! 我再也不能扮演秩序维护者了。 ";
									link.l1 = "船上的夜哨也不容易。 朋友, 职责就是职责, 无论是什么在哪里。 ";
									link.l1.go = "exit";
								break;
							}
							// belamour传奇版 任务中不使用, 是的, 也不需要让玩家再为箱子奔波。 任务请写在commone中
							/* link.l2 = RandPhraseSimple("有重要的事! ", "我找你有事。 ");
							link.l2.go = "quests";//(转发到城市文件) */
							break;
						}
					}
					
					//Jason --> 迷你任务 短缺商品
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason 海盗线
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "嘿, 伙计! 能帮我个小忙吗? ";
							link.l1 = "看是什么事。 ";
							link.l1.go = "Wine_soldier";
							link.l2 = "我没时间。 ";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "嘿, 伙计! 能帮我个小忙吗? ";
								link.l1 = "看是什么事。 ";
								link.l1.go = "Wine_soldier";
								link.l2 = "我没时间。 ";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// < —迷你任务 短缺商品
					
					//belamour传奇版 对话, 如果英雄有军衔和国家荣誉 -->
					
					// 夏尔.德.莫尔 法国殖民地总督将军
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "总督大人! 有什么可以为您效劳? ";
							link.l1 = "我不需要什么, 谢谢。 ";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "能为您效劳是我的荣幸, 总督大人! 我能帮您什么? ";
								link.l1 = "认真履行你的职责 - 我不需要你做更多。 ";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "很高兴见到您, 总督大人! 一个卑微的士兵能为我们殖民地的总督做什么? ";
								link.l1 = "我个人不需要你做什么。 继续服役。 ";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// 服役国家的舰队副司令 无需制服即可识别
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "舰队副司令, 大人! 请允许我报告: 在我值班期间... ";
							link.l1 = "冷静点, 士兵, 我不需要你的报告。 向你的上司报告。 ";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "很高兴见到您, 舰队副司令! 我能帮您什么吗? ";
								link.l1 = "不, 我只是检查你有多专注。 很高兴你认出了我。 ";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "舰队副司令, 这是我的荣幸! 我能为您做什么? ";
								link.l1 = "为" + NationNameGenitive(sti(npchar.nation)) + "服务, 士兵! 这是你能做的最好的事。 ";
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
							dialog.text = "问候您, 船长! 如果您有任何指示, 请原谅: 虽然我为" + NationNameGenitive(sti(npchar.nation)) + "服务, 但我只听令于指挥官和总督。 "; 
							link.l1 = "我有我的军官和船员听从我的指挥。 履行你的职责, 士兵。 ";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "船长, 你能带我到你的船上服役吗? 同样为" + NationNameGenitive(sti(npchar.nation)) + "服务, 但我更喜欢大海。 "; 
								link.l1 = "你需要在指定的地方服役, 所以光荣地履行你的职责。 你一闭眼, 他们就会把你带到海上。 ";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "哦, 你真幸运: 你是为" + NationNameGenitive(sti(npchar.nation)) + "服务的船长... 而我整天被困在这里。 "; 
								link.l1 = "你以为我刚到加勒比一周就成了船长吗? 这都是多年的辛勤工作... ";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// < —legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "你没看到吗? 我在值班。 别烦我。 ";
							link.l1 = "好吧, 好吧... ";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "你要告诉我一些可疑的活动吗? ";
							link.l1 = "不, 完全没有, 顺便说我是船长。 我看你已经不听了? 再见。 ";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "这是军事设施, 所以别在这里太吵。 ";
							link.l1 = "好的, 我会记住的。 ";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "天气这么好, 我却不得不站在这里。 镇上至少有女孩, 而我们这里有什么? 只有老鼠。 ";
							link.l1 = "" + GetSexPhrase("我很同情, 但我帮不了你 - 这是你的职责。 ","嘿! 我怎么了? 我不是女孩吗? ") + "";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "如果你喜欢聊天, 去找别人。 我必须在这里维持秩序, 没时间闲聊。 ";
							link.l1 = "哦, 不, 我只是看看你是否还活着。 你站得像尊雕像。 ";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "你可能认为驻军工作日很轻松? 绝对不是! 这是艰苦而重要的工作。 我记得有一次... ";
							link.l1 = "你下次再告诉我那个故事。 我现在有点赶时间。 ";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "在这里小心点, 你在堡垒里! 要像老鼠一样安静! ";
							link.l1 = "如你所说, 士兵。 ";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "嘿! 你碰巧有水吗? 我快渴死了。 ";
							link.l1 = "没有, 伙计, 忍着点... ";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "驻军生活多无聊啊, 周围只有像你这样的乡巴佬! 现在, 城镇驻军肯定过得更好... ";
							link.l1 = "你这也叫'值班'? 这样肯定会让间谍溜过去! ";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = "" + GetSexPhrase("你看起来像个强壮的家伙, 不是吗? 想报名参加堡垒驻军的值班吗? 我们有宽敞的营房, 一天两餐, 还有免费的酒。 ","哦, 年轻的女士, 你不知道在这种偏僻的地方遇到这么好的姑娘有多令人愉快! ") + "";
							link.l1 = "" + GetSexPhrase("这当然很诱人, 但我还是必须拒绝。 所有那些营房训练不适合我。 ","谢谢你的夸奖, 士兵。 ") + ".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "这该死的热... 我愿意用半生换回到欧洲。 ";
							link.l1 = "是的, 我看你的健康不适合当地气候。 ";
							link.l1.go = "exit";
						break;
					}
					// belamour传奇版 任务中不使用, 是的, 也不需要让玩家再为箱子奔波。 任务请写在commone中
					/* link.l3 = "嗯... 明白。 我只是想" + GetSexPhrase("问","问") + "... ";
					link.l3.go = "quests";//(转发到城市文件) */
				}
			}
		break;
		
		//Jason --> 迷你任务 短缺商品
		case "Wine_soldier":
			dialog.text = "你看, 我非常想要些酒... 但不是当地用烂水果做的劣酒, 那种每桶卖两比索 - 我想要一瓶真正的欧洲葡萄酒。 你可以在镇上从商人那里买到。 虽然很贵, 但我会全额支付, 甚至再多加三百比索。 那么, 你能帮我带一些吗? ";
			link.l1 = "你为什么不自己去买? 你不需要多付钱, 等到你下班再去就行。 有什么陷阱吗? ";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "没有陷阱。 我只是不能离开堡垒去镇上, 直到我休假, 而这短期内不会发生。 此外, 我们的指挥官严格禁止在堡垒内饮酒, 去他的! 那么, 你能帮一个士兵吗? ";
			link.l1 = "嗯, 为什么不呢? 我会给你带酒来, 反正我也有空闲时间。 ";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "抱歉, 伙计, 但我不能这么做。 找别人帮你吧。 ";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "太好了! 非常感谢! 今天我值班, 所以明天来。 你会在堡垒顶部找到我, 在那里你可以把瓶子递给我, 这样没人会注意到... ";
			link.l1 = "好的。 等我, 我明天来看你。 ";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// < —迷你任务 短缺商品
		
		//============================== 识别时的解析节点 =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("在我看来这是某种诡计。 我们和指挥官谈谈, " + GetSexPhrase("伙计","亲爱的") + ", 把事情弄清楚... ", "嗯... 我觉得你不是你假装的那个人... " + GetAddress_Form(npchar) + "放下武器, 跟我来接受进一步调查! ");
			link.l1 = RandPhraseSimple("去你的! ", "当两个星期天在一周内到来时... ");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("哦, 我明白了... 一切似乎都没问题, " + GetAddress_Form(pchar) + "你可以走了。 ", "我站岗太久有点累了... 一切似乎都很好, " + GetAddress_Form(pchar) + ", 对不起。 ");
			link.l1 = "没问题! ";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "想想看! 如此无礼! 以商人的身份来到这里! 每个营房都贴着你的照片, 你这个混蛋! 这次你逃不掉了! 抓住他! ";
				link.l1 = RandPhraseSimple("啊! ..", "好吧, 这是你们自找的... ");
				link.l1.go = "fight";	
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) // 如果停泊在非城市区域
			{
				dialog.text = "你是来这里交易的? 请问怎么交易? 你的船在哪里? 你知道, 这一切看起来都很可疑, 我不得不拘留你, 直到我们弄清楚。 放下武器跟我走! ";
				link.l1 = RandPhraseSimple("去你的! ", "当两个星期天在一周内到来时... ");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "你的许可证必须被吊销, 因为它已经过期, 因此无效。 放下武器跟我来接受进一步调查! ";
				link.l1 = RandPhraseSimple("去你的! ", "当两个星期天在一周内到来时... ");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "嗯... 一切看起来都没问题。 不过, 我必须指出你的许可证今天到期。 这次我让你通过, 但你仍然需要获得新的许可证。 ";
				link.l1 = "谢谢你, 我会尽快办理。 ";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "嗯... 一切看起来都没问题。 不过, 我必须指出你的许可证很快就会到期。 它还剩" + FindRussianDaysString(iTemp) + "有效期。 记住这一点, " + GetAddress_Form(npchar) + "。 ";
				link.l1 = "谢谢你, 我会尽快办理新的。 ";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("嗯, 一切都很好。 你的许可证有效期为" + FindRussianDaysString(iTemp) + "。 你可以通过。 ", "一切都清楚了, " + GetAddress_Form(npchar) + "。 你可以自由进出城镇, 你的许可证有效期为" + FindRussianDaysString(iTemp) + "。 抱歉打扰你。 ", "一切看起来都很好, " + GetAddress_Form(npchar) + ", 我不再拘留你了。 ");
				link.l1 = RandPhraseSimple("太好了。 致以最诚挚的问候。 ", "谢谢你, 军官。 ");
				link.l1.go = "exit";
			}
		break;

		// 关于暴露武器的评论
		case "SoldierNotBlade":
			// belamour传奇版 如果英雄是国家军官 -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "船长, 我请你收起武器: 在我们的城市里禁止拔出武器。 ";
				link.l1 = LinkRandPhrase("好的, 我会收起... ", "已经收好了。 ", "如你所说... ");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("去你的! ", "我想我会用它! ", "时机合适时我会收起。 ");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// < —legendary edition
			dialog.text = LinkRandPhrase("你到底为什么带着出鞘的刀到处跑? 立即收起你的武器! ", "我命令你立即收起武器! ", "嘿, " + GetSexPhrase("伙计","姑娘") + ", 别吓唬人! 收起武器。 ");
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("去你的! ", "梦想一下又没害... ", "当两个星期天在一周内到来时。 ");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}