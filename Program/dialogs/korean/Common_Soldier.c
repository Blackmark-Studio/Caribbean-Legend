// boal 25/04/04 общий диалог солдат
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
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
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
				// заглушка на пирата
				if (false)
				{
    				dialog.text = RandPhraseSimple("마을에 해적들이?! 믿을 수가 없어... 잡아라 "+GetSexPhrase("그를","그녀")+"!!","저건 해적이다! 잡아라 "+GetSexPhrase("그를","그녀")+"!!!");
					link.l1 = RandPhraseSimple("나는 해적이다, 그래서 뭐?","헤, 한번 해보시지...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("너 누구야, 여기서 뭐 하고 있는 거야?","거기서 멈춰! 너 누구냐, 무슨 권리로 이 마을에 들어오려는 거지?");
						link.l2 = "나는 근처에 닻을 내렸어 "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" 깃발 아래 "+NationNameGenitive(sti(npchar.nation))+". 뭐가 이해가 안 돼? (속임수일 확률 "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("간첩이다! 무기 내려놓고 따라와!","적의 첩자다! 붙잡아라 "+GetSexPhrase("그를","그녀의")+"!");
						link.l1 = RandPhraseSimple("닥쳐, 약골!","꺼져!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (false)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("너 누구야, 여기서 뭐 하고 있는 거지?","거기서 멈춰! 너 누구야, 무슨 권리로 이 마을에 들어오려는 거지?");
						link.l1 = "이 문서를 보시오, 병사. 나는 종교재판관 비첸초 신부님의 허가를 받고 여기 왔소.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("너 누구야, 여기서 뭐 하는 거지?","거기서 멈춰! 너 누구야, 무슨 권리로 이 마을에 들어오려는 거지?");
						link.l1 = "이 문서를 보시오, 병사. 나는 종교재판관 빈첸토 신부님의 허가를 받고 여기 왔소.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("행동 똑바로 하고 노예들 귀찮게 하지 마.","어서 가!","아, 그대였군. 들어가시오, 이미 당신에 대해 들었소.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("너 누구야, 여기서 뭐 하고 있는 거지?","거기서 멈춰! 너 누구야, 무슨 권리로 이 마을에 들어오려는 거지?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "장교, 나에게는 "+GetRusNameNationLicence(HOLLAND)+", 그래서 나는 합법적으로 여기 있는 것이오. 자, 여기 이것을 보시오...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "저 깃발이 안 보이나 "+NationNameGenitive(sti(pchar.nation))+"내 배의 돛대에?! (속임수일 확률 "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "나는 근처에 닻을 내렸어 "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" 깃발 아래에서 "+NationNameGenitive(sti(pchar.nation))+". 뭐가 이해가 안 돼? (속일 확률 "+DeceptionChance+"%%)";
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
						//==> по флагу
						// заглушка на пирата
						if (false)
						{
    						dialog.text = RandPhraseSimple("도시에 해적들이?! 믿을 수가 없어... 저놈을 잡아라!","저건 해적이다! 잡아라!");
							link.l1 = RandPhraseSimple("그래, 나 해적이야 - 그래서 어쩔 건데?","헤헷, 잡을 수 있으면 잡아봐라...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "저 깃발이 안 보이나 "+NationNameGenitive(sti(pchar.nation))+" 내 배에서?! (속일 확률 "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "나는 근처에 닻을 내렸어 "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" 깃발 아래에서 "+NationNameGenitive(sti(pchar.nation))+". 뭐가 이해가 안 돼? (속일 확률 "+DeceptionChance+"%%)";
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
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "아이고, 선장님, 바다에서 선장님과 함께 정말 멋진 시간을 보냈습니다! 선장님 지휘 아래 우리가 함께 침몰시킨 배가 얼마나 많았던가요! 그리고 여기...";
									link.l1 = "그리고 여기서는, 친구야, 바다에서는 볼 수 없는 매혹적인 아가씨들을 실컷 구경할 수 있지.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "선장님, 우리가 뭘 잘못해서 이런 일을 겪는 겁니까?! 우린 땅쥐가 아니잖아요, 그렇죠?";
									link.l1 = "조용히 해, 선원! 네 임무는 아주 중요하고 명예로운 자리니까, 그만 징징거려.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "바다에서 무슨 일이 벌어지고 있나요, 선장님? 우리가 다시 그 바다를 볼 수 있을까요?";
									link.l1 = "당연하지, 선원! 임무에서 해제되면 부두로 가서 마음껏 바다를 즐기면 돼.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "불만이 있어요, 선장님. 우리 모두 바다가 그립습니다. 이 육상 근무에는 정말 진절머리가 납니다!";
									link.l1 = "이 징징거림은 이제 지겹다! 여기 럼도 충분히 있잖아! 선장이 시킨 자리에서 일해, 아니면 본보기를 위해 누군가 목이 매달릴 거다.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "비밀로 말씀드리자면, 선장님, 새 총독은 뇌물이나 받고 횡령이나 하는 자입니다. 하지만 그건 제 알 바가 아니지요...";
									link.l1 = "정확히 그렇다, 코르세어. 네 일은 네 자리에서 질서를 지키는 거지. 그리고 주지사를 돛대에 매다는 건 내 일이야. 잘했어!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "우리를 잊지 않아 주셔서 감사합니다, 선장님! 불 속이든 물 속이든 선장님만 따라가겠습니다!";
									link.l1 = "너희 같은 놈들 잘 알지! 결국 금밖에 관심 없잖아. 오늘 밤 선술집에서 파티가 열리니까, 술값은 내가 낸다. 꼭 와라.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "헤헤, 선장! 생각해 봐, 해적이 정말로 질서를 지키는 사람이 될 수 있겠어?! 우리가 진짜 일거리를 맡은 게 얼마나 오래된 줄 알아?!";
									link.l1 = "쉴 틈 없어, 해적놈! 적의 함대들이 우리 섬 근처 바다를 샅샅이 뒤지고 있으니, 언제든 피바람이 불 준비를 해야 해.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "선장님, 왕실에서 또 다른 함대를 이쪽으로 보냈다는 소문을 들었습니다?";
									link.l1 = "물론이지, 코르세어. 우리가 살아 있는 한 평화란 없어. 지옥에 가서도 악마들과 싸우게 될 거야!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "요호호! 젠장, 어제 술 진짜 독했지, 선장! 선장님이 거기 없어서 아쉬웠어.";
									link.l1 = "별일 아니야, 내가 만회할게. 그리고 난 너희들이 부럽지도 않아.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "비밀로 말씀드리겠소, 선장님, 항상 저희를 잘 대해주셨으니. 어제 정말 예쁜 아가씨와 즐거운 시간을 보냈지요...";
									link.l1 = "헤, 코르세어, 너한텐 딱 밧줄 목매달이가 어울리지!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "선장님! 제발, 이 저주받은 임무에서 저를 좀 벗어나게 해주십시오! 더 이상 질서를 지키는 역할을 할 수가 없습니다.";
									link.l1 = "배에서 야간 경계 근무도 만만치 않아. 친구야, 의무는 어디서든, 무엇이든 의무지.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("중요한 일이 있어!","너와 볼 일이 있다.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("경보! 무장한 미치광이가 여기에 있다!","무기를 들어라, 무기를 들어! 미친 놈이 여기 왔다!");
								link.l1 = RandPhraseSimple("어? 뭐라고?","어, 왜 이러는 거야?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("나에게 볼일이라도 있소, 선장?","나는 그냥 일 때문에 여기 온 거야. 필요한 게 있으면 망설이지 말고 물어봐."),RandPhraseSimple("선장님, 지금 매우 바쁘니 다른 사람을 찾아가 보시오.","무슨 문제라도 있습니까, 선장님? 질문이 없으시면, 물러나도 되겠습니까?"),"길 비켜요, 선장님, 급하니까.");
							link.l1 = LinkRandPhrase("미안하다, 친구, 나 "+GetSexPhrase("착각했군","사람을 잘못 봤어")+" ","좋아, 네 일이나 계속해.","아니, 아무것도 없어.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("당신에게 물어볼 게 몇 가지 있어.","너와 볼 일이 있다."),RandPhraseSimple("급한 것 같군. 질문 하나만 하고 보내주지.","Я "+GetSexPhrase("원했다","원했다")+" 뭔가 물어봐."),"네 일은 나중에 해도 돼. 내가 물어볼 게 있어. "+GetSexPhrase("원했다","원했다")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("뭐야? 지나가.","길 막지 말고, 비켜.");
					            link.l1 = RandPhraseSimple("알겠어? 소리 지르지 마!","흥분 좀 가라앉혀. 내가 금방 식혀줄 생각 없으니까!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("당신에게 몇 가지 물어볼 것이 있어.","너와 볼 일이 있다."),RandPhraseSimple("서두르는 것 같군. 질문 하나만 하고 보내주지.","Я "+GetSexPhrase("원했다","원했어")+" 뭔가 물어봐."),"네 일은 나중에 해도 돼. 내가 물어볼 게 있어. "+GetSexPhrase("원했다","원했다")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("그냥 봐  "+GetSexPhrase("저 악당을 봐! 감히 얼굴을 드러내다니","저 악당을 봐! 감히 얼굴을 드러내다니\n")+" 안에서 "+XI_ConvertString("Colony"+npchar.city)+". 붙잡아 "+GetSexPhrase("그를","그녀")+"!!!","하, 너를 알아보겠군, "+GetSexPhrase("악당","놈")+"! 붙잡아라 "+GetSexPhrase("그를","그녀")+"!!!");
							link.l1 = RandPhraseSimple("아르!..","좋아, 네가 원한 거니까...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "오, 이게 누구야! 숙녀분 "+pchar.GenQuest.EncGirl.name+" 직접 오시다니 영광이군! 어떻게 감히 나타날 수 있었지? 우리가 널 찾고 있었거든! 자, 지하 감옥으로 가라 - 네 감방이 준비되어 기다리고 있다. ";
							link.l1 = "무슨 말도 안 되는 소리를 하는 거야!? 나랑 내 선원들은 "+GetSexPhrase("기사 나리","동료")+" 정글에서 산책하며 꽃을 따고 있었어. 나 좀 내버려 둬! 이 깐깐한 녀석들은 예의도 없나?! 예쁜 여자만 보면 달려들어서 귀찮게 굴잖아! "+GetSexPhrase("내 사랑, 저 멍청이들한테 꺼지라고 해서 이 정직한 여자를 좀 내버려 두라고 해줘!","여보, 저 멍청이들에게 좀 전해 줘...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "아, 여기 있었구나, 예쁜이! 네 아버지가 널 찾으려고 주둔군 전부를 동원해서 집으로 데려가려 했어.";
							link.l1 = "꺼져! 내가 어디 가는지 알아, 네 도움 따위 필요 없어! 선장님, 저놈들한테 나한테서 손 떼라고 말씀해 주십시오.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "군인의 삶은 정해져 있지 - 보초 서고, 순찰 돌고... 뭐 원하는 거야, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "이봐, 최근에 여기서 그 주정뱅이랑 싸운 게 너였지? 뭐, 보아하니, 그래, 너였더군...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "각하, 총독 나리! 어떻게 봉사할까요?";
							link.l1 = "아무것도 필요 없어, 고마워.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "이것은 저에게 큰 영광입니다, 총독 나리! 무엇을 도와드릴까요?";
								link.l1 = "성실하게 임무를 수행하시오 - 나는 그 이상을 바라지 않소.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "뵙게 되어 영광입니다, 각하! 우리 식민지의 총독 나리께 이 미천한 병사가 무엇을 도와드릴 수 있을까요?";
								link.l1 = "개인적으로 나는 너에게 바라는 게 없어. 계속 일해.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "각하, 부제독님! 보고 드리겠습니다: 제가 근무하는 동안...";
							link.l1 = "진정하게, 병사. 네 보고는 필요 없어. 네 상관에게 보고해.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "뵙게 되어 반갑습니다, 부제독님! 무엇을 도와드릴까요?";
								link.l1 = "아니, 그냥 네가 얼마나 주의 깊은지 확인해봤을 뿐이야. 나를 알아봐 줘서 기쁘다.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "부제독 나리, 저에게는 큰 영광입니다! 무엇을 도와드릴까요?";
								link.l1 = "Serve "+NationNameGenitive(sti(npchar.nation))+", 군인! 그게 네가 할 수 있는 최고의 일이야.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "안녕하십니까, 선장님! 제게 지시하실 일이 있으시다면, 실례를 무릅쓰고 말씀드립니다만: 비록 제가 섬기고 있는 이는 "+NationNameGenitive(sti(npchar.nation))+", 나는 지휘관과 총독에게만 대답한다."; 
							link.l1 = "내 장교들과 선원들은 내 명령에 따르지. 임무를 다하라, 병사.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "선장님, 당신 배에서 일할 수 있겠습니까? 같은 봉사로 "+NationNameGenitive(sti(npchar.nation))+", 하지만 나는 바다가 더 좋아."; 
								link.l1 = "네가 배정받은 곳에서 네 임무를 명예롭게 수행하라. \n잠시 눈을 감으면, 그들이 그것을 바다로 가져갈 것이다.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "오, 운이 좋군. 너는 의 소속 선박의 선장이잖아. "+NationNameGenitive(sti(npchar.nation))+"... 그리고 나는 하루 종일 여기 갇혀 있지."; 
								link.l1 = "내가 카리브에 막 도착해서 일주일 만에 선장이 된 줄 아나? 이건 다 수년간의 고된 노력의 결과야...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "못 봐? 나 근무 중이야. 귀찮게 하지 마.";
							link.l1 = "알겠어, 알겠어...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "수상한 움직임에 대해 말해줄 생각이야?";
							link.l1 = "아니, 전혀 없어. 그리고 참고로 나는 선장이야. 이제 더 이상 듣지 않는 것 같네? 그럼 잘 있어.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "여기는 군사 시설이니, 너무 시끄럽게 굴지 마라.";
							link.l1 = "알겠어, 명심할게.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "이렇게 날씨가 좋은데, 나는 여기 서 있기만 하네. 마을에는 그나마 아가씨들이라도 있지, 여긴 뭐가 있나? 쥐들밖에 없잖아.";
							link.l1 = ""+GetSexPhrase("안타깝지만 내가 도울 수 있는 일은 없어 - 결국 그건 네 책임이니까.","이봐! 내가 왜 뭐가 문제야? 나 여자 아니야?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "말이 하고 싶으면 다른 사람을 찾아. 나는 여기 질서를 지켜야 해서 쓸데없는 잡담할 시간 없어.";
							link.l1 = "아, 아니야, 그냥 네가 아직 살아 있는지 확인하려고 온 거야. 너 완전히 동상처럼 서 있었거든.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "너는 아마 주둔 근무가 쉬운 일이라고 생각하겠지? 전혀 아니야! 이건 힘들고 중요한 일이야. 예전에 한 번은... ";
							link.l1 = "그 이야기는 다음에 들려주게. 지금은 내가 좀 급하네.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "여기 조심해, 요새 안이야! 쥐처럼 조용히 해!";
							link.l1 = "말씀대로 하겠습니다, 병사.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "이봐! 혹시 물 좀 있어? 목말라 죽겠어.";
							link.l1 = "아니야, 친구, 좀 참아...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "주둔지 생활이 얼마나 지루한지, 너 같은 촌놈들만 있잖아! 그래도 마을 주둔군 쪽이 훨씬 낫겠지...";
							link.l1 = "이게 근무 중이라는 거냐? 이런 식이면 분명히 첩자를 놓치고 말 거다!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("힘 좀 써 보이는데, 안 그래? 요새 주둔군에 들어올 생각 있나? 넓은 막사에, 하루 두 끼 식사, 술도 공짜로 준다네.","오, 아가씨, 이런 외진 곳에서 이렇게 아름다운 숙녀를 만나게 되다니 얼마나 기쁜지 모르겠소!")+"";
							link.l1 = ""+GetSexPhrase("그거 정말 솔깃하지만, 그래도 거절해야겠어. 그런 병영 훈련 따위는 내 체질이 아니거든.","칭찬해 줘서 고맙네, 병사.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "이 지독한 더위라니... 유럽으로 돌아갈 수만 있다면 내 목숨의 반쯤은 기꺼이 내놓겠어.";
							link.l1 = "그래, 당신 건강이 이곳 기후에 맞지 않는 것 같군.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "잠깐만. 너한테 물어보고 싶은 게 있어 "+GetSexPhrase("원했다","원했다")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier") && npchar.location.group == "soldiers" && npchar.city == "Bridgetown")
			{
				dialog.text = "브리지타운에 오신 것을 환영합니다, "+GetAddress_Form(NPChar)+"...";
				link.l1 = "내 얼굴이 프랑스 식민지에서만 알려진 줄 알았는데... 내 이름은 "+GetFullName(pchar)+".";
				link.l1.go = "WildRose_Soldier_1";
				DeleteAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier");
				DelLandQuestMark(npchar);
			}
			//<-- Дикая Роза
		break;
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("나한테는 뭔가 속임수 같은데. 사령관에게 가서 얘기해 보자, "+GetSexPhrase("동료","여보")+", 그리고 모든 걸 알아내...","흠... 뭔가 수상한데, 네가 꾸미는 사람이 아닌 것 같군... 무기 내려놔 "+GetAddress_Form(npchar)+", 그리고 더 조사하려면 나를 따라오시오!");
			link.l1 = RandPhraseSimple("꺼져!","한 주에 일요일이 두 번 오는 날에나...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("아, 그렇군... 모든 게 이상 없는 것 같으니, 가도 좋소, "+GetAddress_Form(pchar)+".","내가 망을 서다가 좀 피곤해졌나 봐... 모든 게 괜찮아 보이네, "+GetAddress_Form(pchar)+", 미안하오.");
			link.l1 = "문제 없어!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("아, 그렇군... 모든 게 이상 없는 것 같으니, 가도 된다. "+GetAddress_Form(pchar)+".","자, 어디 보자... 음, 모든 게 제대로 된 것 같군, "+GetAddress_Form(pchar)+", 미안하오.");
			link.l1 = "이제 좀 알겠지!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "생각 좀 해 봐라! 이런 무례함이 어디 있냐! 상인인 척하고 여기까지 오다니! 네 얼굴이 모든 병영에 붙어 있어, 이 자식아! 이번엔 절대 못 빠져나간다! 잡아라!";
				link.l1 = RandPhraseSimple("아르르!..","좋아, 네가 원한 거니까...");
				link.l1.go = "fight";	
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "여기 거래하러 온 건가? 어떻게 왔는지 물어봐도 되겠나? 네 배는 어디 있지? 있잖아, 이 모든 게 아주 수상해 보여서, 일이 정리될 때까지 널 억류할 수밖에 없겠군. 무기를 넘기고 따라와!";
				link.l1 = RandPhraseSimple("꺼져!","한 주에 일요일이 두 번 오는 날에나...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "면허가 만료되어 무효이므로 취소해야 하오. 무기를 넘기고 추가 조사를 위해 나를 따라오시오!";
				link.l1 = RandPhraseSimple("꺼져!","한 주에 일요일이 두 번 오는 날에나...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "흠... 모든 게 제대로인 것 같군. 그래도 당신의 면허가 오늘 만료된다는 점은 짚고 넘어가야겠소. 이번에는 그냥 통과시키겠지만, 새 면허를 반드시 발급받아야 하오.";
				link.l1 = "고맙소, 가능한 한 빨리 새 것으로 구하겠소.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "흠... 모든 게 괜찮아 보이네. 그래도 네 면허가 곧 만료된다는 점은 짚고 넘어가야겠어. 이 면허는 오직 "+FindRussianDaysString(iTemp)+". 그러니 명심해, "+GetAddress_Form(npchar)+".";
				link.l1 = "감사합니다. 가능한 한 빨리 새 것으로 구하겠습니다.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("음, 모든 게 괜찮아 보여. 네 면허는 앞으로도 유효해 "+FindRussianDaysString(iTemp)+". 지나가도 된다.","모든 게 분명하군, "+GetAddress_Form(npchar)+". 당신은 마을을 자유롭게 드나들 수 있습니다, 면허는 앞으로도 유효합니다 "+FindRussianDaysString(iTemp)+". 귀찮게 해서 미안하오.","모든 게 괜찮아 보여, "+GetAddress_Form(npchar)+", 이제 더 이상 당신을 붙잡지 않겠소.");
				link.l1 = RandPhraseSimple("훌륭하군. 안부 전해 주시오.","감사합니다, 장교님.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("이봐, 친구, 등대에서 아무것도 부수지 마.","이 등대는 이 마을에서 아주 중요한 부분이야. 조심해!");
			link.l1 = RandPhraseSimple("알겠어, 걱정하지 마.","알았어, 걱정하지 마.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("대포에 너무 가까이 가지 마시오 - 여기는 군사 시설이오!","포신 근처에는 낯선 자 출입 금지다!","내가 너 대포 근처에서 어슬렁거리는 거 보면 끝장이다!");
			link.l1 = RandPhraseSimple("알겠어.","알겠어.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "그런데 당신은 누구요, 선장? 설마 이 정착지에서 가장 악명 높은 도둑의 공범은 아니겠지?";
			link.l1 = "누굴 지금 공범이라고 불렀어?! 해가 머리에 들었나?! 이봐, 그 여자한테서 손 떼!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "사실, 나는 "+GetSexPhrase("그녀를 알게 되었어","그녀를 알게 되었어")+" 최근에...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Sir","Miss")+", 우리는 그녀를 체포해서 지하 감옥으로 데려가라는 명령을 받았다네. 우리를 막을 수 있다고 생각한다면, 착각하고 있는 거야.";
			link.l1 = "그럼, 한번 볼까...";
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
			dialog.text = "오, 정말인가? 그렇다면 주머니부터 확인해보는 게 좋겠군. 저 여자는 전문가거든.";
			link.l1 = "감사합니다, 그렇게 하겠습니다. 내가 어떻게 이렇게 바보 같은 짓을 할 수 있었을까...";
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
			dialog.text = ""+GetSexPhrase("Sir","Miss")+", 우리는 그 아가씨를 찾아서 아버지께 데려오라는 명령을 받았어.";
			link.l1 = "명령은 명령이지 - 그럼, 해 봐라.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "이미 늦었어, 왜냐하면 나는 벌써 그녀의 아버지와 이야기하고 있으니까.";
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
				dialog.text = "선장님, 우리는 명령을 받았소. 우리를 막을 수 있다고 생각한다면, 착각이오.";
				link.l1 = "그럼, 한번 볼까...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "헤헷, "+GetSexPhrase("운이 좋은 놈이군","운 좋은 아가씨구나")+". 그녀의 아버지가 딸을 데려오는 사람에게 후한 보상을 약속했어.";
				link.l1 = "절망하지 마라 - 앞으로도 많은 보상이 기다리고 있다.";
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
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "그래, 내게 있다. 그 자는 감옥에 앉아 자기 행동을 곱씹게 두는 게 맞지. 그리고 네가 그 자를 대신해 날 협박하러 온 거라면, 믿어라. 나는 요새 사령관까지도 손쓸 수 있으니.";
			link.l1 = "그래, 나는 협박하러 온 게 아니라 그에 대한 당신의 주장을 철회해 달라고 부탁하러 왔소. 저 사람은 내 오랜 지인인데, 그냥 술에 취했을 뿐이오. 알다시피, 술 취한 사람에게 바다는 무릎까지밖에 안 되지 않소 ...\n";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "즉, 내가 근무 중일 때 그 자가 내 눈을 멍들게 했는데, 이제 그를 풀어줘야 한다고? 왜 그래야 하지?";
			link.l1 = "그의 행동에 대한 사과로 오백 페소는 어떤가?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "그렇게 생각하시오? 그는 내 명예를 모욕했소, 그런데 자네는 오백 페소면 용서할 수 있다고 생각하나? 내 명예가 돈으로 살 수 있는 것이라 생각하시오?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "아닙니다, 선장님, 모두 정당했습니다. 그 자는 당연히 그런 대가를 받아야 했습니다. 그리고 더 이상 제 임무를 방해하지 말아 주십시오.";
				link.l1 = "그래, 네 말이 맞아.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "천이다. 한 푼도 깎아줄 수 없어.";
				link.l1 = "아니, 멍 하나에 그렇게 큰돈을 낼 준비는 아직 안 된 것 같군.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "오... 좋아, 잠깐만. 여기 펜이랑 양피지가 있으니 바로 써. 내 친구에게 아무런 청구도 하지 않겠다고 적어.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "그러니 더 이상 내 임무를 방해하지 말아 주시오.";
			link.l1 = "안 해.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "여기 있다.";
			link.l1 = "일 잘 되길 바라요.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		//--> Дикая Роза
		case "WildRose_Soldier_1":
			if (GetHour() >= 6 && GetHour() <= 21)
			{
				dialog.text = "아, 선장이었군... 태양 때문에 졸려 죽겠네... 이 저주받을 더위!";
			}
			else
			{
				dialog.text = "그 말엔 딴지 걸 수 없지. 그래도 밤에는 다 똑같아 보여, 알지?";
			}
			link.l1 = "무슨 일이야, 병사? 평소엔 너희 같은 녀석들이 나한테 말 걸 일 없잖아.";
			link.l1.go = "WildRose_Soldier_2";
		break;
		
		case "WildRose_Soldier_2":
			dialog.text = "음, 그래, "+GetAddress_Form(NPChar)+". 하지만 윌러비 경의 명령이 있어서, 섬에 온 모든 신참들에게 며칠 전에 주교 농장에서 노예 무리가 도망쳤다는 걸 경고해야 해. 빌어먹을 감독관 놈들이 사슬을 끊는 동안 곯아떨어졌던 게 분명하지. 오늘은 내 사랑스러운 앙젤리크 품에 안겨 있었어야 했는데...";
			link.l1 = "짐작컨대, 그들은 농장주의 재산을 쫓으라고 주둔군 병사들을 보냈겠군?";
			link.l1.go = "WildRose_Soldier_3";
		break;
		
		case "WildRose_Soldier_3":
			dialog.text = "물론이지... 주교도 자기 용병 몇 무리를 정글로 보냈지만, 그것만으로는 만족하지 못했어. 노예들을 살아서 데려오는 자에게는 큰 보상을 약속했지. 평소에는 흑인들이 그를 위해 허리를 굽히지만, 얼마 전에는 해군 탈영병들을 한 무더기 데려왔어 – 돌 채석장에서는 별 쓸모가 없지만, 플랜테이션에서 빠져나갈 만큼은 영리하더군...";
			link.l1 = "그럼 그들은 백인이었나?";
			link.l1.go = "WildRose_Soldier_4";
		break;
		
		case "WildRose_Soldier_4":
			dialog.text = "새하얀 놈들이더군, 맙소사! 흑인들이었으면 그냥 도망쳤겠지만, 이놈들은 죽은 용병들한테서 머스킷이랑 세이버를 집어 들고 바로 써먹더라고. 우리 쪽 한 명이랑 비숍의 졸개 몇 놈도 당했지 – 그 덕에 남은 놈들은 미쳐 날뛰었어.\n도망자들인 줄 알고 우리 사람들까지 거의 쏴 죽일 뻔했지. 그리고 민간인 몇 명은 흔적도 없이 정글로 사라졌어.";
			link.l1 = "도시 성문이 잠겼어?";
			link.l1.go = "WildRose_Soldier_5";
		break;
		
		case "WildRose_Soldier_5":
			dialog.text = "아니, 물론 아니오 – 도시는 포위된 상태가 아니오. 원하는 곳 어디든 자유롭게 가도 되오. 하지만 도망자들을 쫓다가 총격전에 휘말려도, 괜히 징징대지 마시오. 그리고 살아남더라도, 관저에 찾아가서 영주님께 불평하려 들지 마시오 – 어차피 그분께서는 브리지타운 시민들뿐만 아니라 손님들까지도 충분히 배려해 주셨으니 말이오.";
			link.l1 = "저런... 참으로 은혜로운 분이시군. 프란시스 윌러비를 신께서 지켜주시길!";
			link.l1.go = "WildRose_Soldier_6";
			link.l2 = "아, 모든 총독이 윌러비 나리처럼 신참들에게 그렇게 신경 썼다면 얼마나 좋을까!..";
			link.l2.go = "WildRose_Soldier_7";
		break;
		
		case "WildRose_Soldier_6":
			dialog.text = "아주 웃기군. 가도 좋소, 선장.";
			link.l1 = "그럼 잘 가게, 군인.";
			link.l1.go = "WildRose_Soldier_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "WildRose_Soldier_7":
			dialog.text = "그래, 일이 훨씬 줄었을 텐데. 더 이상 붙잡지 않겠소, 선장.";
			link.l1 = "행운을 빌네, 병사.";
			link.l1.go = "WildRose_Soldier_8";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
		break;
		
		case "WildRose_Soldier_8":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves");
		break;
		//<-- Дикая Роза
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "선장님, 무기를 거두어 주시기 바랍니다. 우리 도시에서는 무기를 뽑는 것이 금지되어 있습니다.";
			link.l1 = LinkRandPhrase("알겠어, 내가 치워둘게...","이미 끝났다.","말씀대로...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("꺼져!","내가 이걸 써야겠군!","때가 되면 치워 두겠어.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("이봐, 왜 그렇게 무기를 휘두르고 난리야?! 당장 집어넣어!","당장 무기를 거두라고 명령한다!","이봐, "+GetAddress_Form(NPChar)+", 사람들 그만 놀래켜! 무기 집어넣어.");
			link.l1 = LinkRandPhrase("알겠어, 내가 치워둘게...","이미 끝났어.","말씀대로...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("꺼져!","내가 이걸 쓰겠어!","때가 되면 치워 두겠어.");
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
