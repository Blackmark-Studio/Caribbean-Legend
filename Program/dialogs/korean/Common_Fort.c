// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("간첩이군! 무기를 내려놓고 나와 함께 가라!","적의 첩자다! 잡아라 "+GetSexPhrase("그를","그녀")+"!");
				link.l1 = RandPhraseSimple("닥쳐, 겁쟁이!","꺼져!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("너는 누구고 여기서 뭐 하는 거야?","가만히 있어! 너 누구야? 왜 요새에 들어오려고 하는 거지?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "장교님, 저는 "+GetRusNameNationLicence(sti(npchar.nation))+", 그래서 나는 합법적으로 여기 있는 것이오. 자, 이것을 한번 보시오...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("해적이 요새 안에 있다고?! 잡아라"+GetSexPhrase("그를","그녀의")+"!","저건 해적이야, 우리 요새를 기웃거리고 있어! 감옥으로 끌고 가!!!");
							link.l1 = RandPhraseSimple("그래, 나 해적이다. 그래서 어쩔 건데?","헤헤, 잡을 수 있으면 잡아 봐라...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "저 깃발이 안 보이나 "+NationNameGenitive(sti(pchar.nation))+" 내 배의 돛대에?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "나는 근처에 닻을 내렸어 "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" 깃발 아래에서"+NationNameGenitive(sti(pchar.nation))+"! 또 필요한 거 있나?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
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
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "아이고, 선장님, 바다에서 당신과 함께 정말 멋진 시간을 보냈습니다! 당신의 지휘 아래 우리가 함께 침몰시킨 배가 얼마나 많은지요! 그리고 여기...";
									link.l1 = "여기서는, 친구야, 바다에서는 볼 수 없는 매혹적인 아가씨들을 실컷 구경할 수 있지.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "선장님, 우리가 뭘 잘못해서 이런 꼴을 당하는 겁니까?! 우린 땅쥐가 아니잖아요, 그렇죠?";
									link.l1 = "조용히 해, 선원! 네 자리는 아주 중요하고 명예로운 자리니까, 그만 징징거려.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "바다에서 무슨 일이 벌어지고 있습니까, 선장님? 우리가 다시 그 바다를 볼 수 있을까요?";
									link.l1 = "물론이지, 선원! 임무에서 해제되면 부두로 가서 마음껏 바다를 즐겨도 돼.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "불만이 있어요, 선장님. 우리 모두 바다가 그립습니다. 이 육상 근무에는 정말 진저리가 납니다!";
									link.l1 = "이 징징거림은 이제 지겹다! 여기 럼도 충분히 있으니까! 선장이 시킨 자리에서 일해라, 아니면 누군가 본보기로 목이 매달릴 거다.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "비밀로 말씀드리자면, 선장님, 새 총독은 뇌물을 받고 횡령도 하는 자입니다. 하지만 그건 제 알 바가 아니지요...";
									link.l1 = "정확히 그래, 코르세어. 너는 네 자리에서 질서를 지키는 게 할 일이야. 그리고 주지사를 돛대에 매다는 건 내 일이거든. 잘했어!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "우리를 잊지 않아 주셔서 감사합니다, 선장님! 불 속이든 물 속이든 선장님만 따라가겠습니다!";
									link.l1 = "너희 같은 놈들 잘 알아! 결국 금밖에 관심 없잖아. 오늘 밤 선술집에서 파티가 열리니까, 술값은 내가 낸다. 꼭 와라.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "헤헤, 선장! 생각해 봐, 해적이 정말 질서를 지키는 자가 될 수 있겠어?! 우리가 마지막으로 제대로 된 일거리를 맡은 게 언제였는지 기억도 안 나!";
									link.l1 = "쉴 틈 없어, 코르세어! 적 함대들이 우리 섬 근처 바다를 샅샅이 뒤지고 있으니, 언제든 피바람이 불어닥칠 준비를 해야 해.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "선장님, 왕실에서 또 다른 함대를 우리 쪽으로 보냈다는 소문을 들었습니다?";
									link.l1 = "물론이지, 코르세어. 우리가 살아 있는 한 평화란 없을 거야. 지옥에 가서도 악마들과 싸우게 될 테니까!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "요호호! 젠장, 어제 술 정말 독했지, 선장! 선장님이 거기 안 계셔서 아쉬웠어.";
									link.l1 = "별일 아니야, 내가 만회할게. 그리고 너희들, 부럽지도 않아.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "비밀로 말씀드리겠소, 선장님. 늘 저희를 잘 대해주셨으니 말씀드리는데, 어제 정말 예쁜 아가씨와 즐거운 시간을 보냈습니다...";
									link.l1 = "헤, 코르세어, 너한테 꼭 필요한 건 교수형 줄이지!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "선장님! 제발, 이 저주받은 임무에서 저를 좀 풀어주십시오! 더는 질서의 수호자 역할을 할 수가 없습니다.";
									link.l1 = "배에서 야간 경계 근무도 만만치 않아. 친구, 의무는 어디서든 무엇이든 의무지.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("중요한 일이 있어!","너와 볼 일이 있다.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
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
							dialog.text = "이봐, 친구! 나한테 작은 부탁 하나 들어줄 수 있겠어?";
							link.l1 = "무엇을 해야 하는지에 따라 다르지.";
							link.l1.go = "Wine_soldier";
							link.l2 = "이런 데 신경 쓸 시간 없어.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "이봐, 친구! 나한테 작은 부탁 하나 들어줄 수 있겠어?";
								link.l1 = "무엇을 해야 하는지에 따라 다르지.";
								link.l1.go = "Wine_soldier";
								link.l2 = "이런 데 신경 쓸 시간 없어.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "각하, 총독 나리! 무엇을 도와드릴까요?";
							link.l1 = "아무것도 필요하지 않아요, 감사합니다.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "이것은 제게 큰 영광입니다, 총독 나리! 무엇을 도와드릴까요?";
								link.l1 = "성실하게 임무를 수행하라 - 나는 그 이상을 바라지 않는다.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "뵙게 되어 영광입니다, 각하! 우리 식민지의 총독 나리께 이 미천한 병사가 무엇을 해드릴 수 있을까요?";
								link.l1 = "개인적으로 나는 너한테 필요한 게 없어. 계속 일해.";
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
							dialog.text = "각하, 부제독님! 보고 드리겠습니다: 제가 당직 중에...";
							link.l1 = "진정하게, 병사. 네 보고는 필요 없어. 상관에게 보고해.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "뵙게 되어 반갑습니다, 부제독님! 무엇을 도와드릴까요?";
								link.l1 = "아니, 네가 얼마나 주의 깊은지 확인해 본 것뿐이야. 나를 알아봐 줘서 기쁘군.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "부제독 나리, 저에게 이런 영광이! 무엇을 도와드릴까요?";
								link.l1 = "Serve "+NationNameGenitive(sti(npchar.nation))+", 병사야! 그게 네가 할 수 있는 최선이야.";
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
							dialog.text = "안녕하십니까, 선장님! 저에게 지시하실 일이 있으시다면, 실례를 무릅쓰고 말씀드리자면: 비록 제가 섬기고 있는 이는 "+NationNameGenitive(sti(npchar.nation))+", 나는 오직 사령관과 총독에게만 대답한다."; 
							link.l1 = "내 장교들과 선원들은 내 명령에 따르지. 임무를 다하라, 병사.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "선장님, 당신의 배에서 일할 수 있겠습니까? 같은 조건으로 "+NationNameGenitive(sti(npchar.nation))+", 하지만 나는 바다가 더 좋아."; 
								link.l1 = "네가 배정받은 곳에서 필요하니, 명예롭게 임무를 수행하라. 잠시 눈을 감으면, 그들이 그것을 바다로 가져갈 것이다.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "오, 운이 좋군. 너는 의 소속 선박의 선장이잖아\n "+NationNameGenitive(sti(npchar.nation))+"... 그리고 나는 하루 종일 여기 갇혀 있어."; 
								link.l1 = "내가 카리브에 막 도착해서 일주일 만에 선장이 됐다고 생각해? 이건 다 수년간의 고된 노력의 결과야...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "못 보겠어? 나 근무 중이야. 귀찮게 하지 마.";
							link.l1 = "알겠어, 알겠어...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "수상한 움직임에 대해 말해줄 생각이야?";
							link.l1 = "아니, 전혀 없네, 그리고 참고로 나는 선장이야. 이제 더 이상 듣지 않는 것 같군? 잘 가라.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "여기는 군사 시설이니, 너무 시끄럽게 굴지 마라.";
							link.l1 = "알겠어, 명심할게.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "이렇게 날씨도 좋은데, 나는 여기 서 있기만 하네. 마을엔 적어도 여자애들이 좀 있는데, 여기엔 뭐가 있나? 쥐밖에 없잖아.";
							link.l1 = ""+GetSexPhrase("안타깝지만 내가 도와줄 수 있는 건 없어 – 결국 그건 자네의 의무니까.","이봐! 내가 왜 어때서? 나 여자 아니야?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "말이 하고 싶으면 다른 사람을 찾아봐. 나는 여기 질서를 지켜야 해서 쓸데없는 잡담할 시간 없어.";
							link.l1 = "오, 아니야, 그냥 네가 아직 살아 있는지 확인하는 거야. 너 완전히 동상처럼 서 있었거든.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "너는 아마 주둔지 근무가 쉬운 일이라고 생각하겠지? 전혀 아니야! 이건 힘들고 중요한 일이야. 예전에 한 번은... ";
							link.l1 = "그 이야기는 나중에 들려주게. 지금은 내가 좀 바빠.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "여기 조심해, 여긴 요새야! 쥐처럼 조용히 해!";
							link.l1 = "말씀대로 하겠습니다, 병사.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "이봐! 혹시 물 좀 있어? 목이 타 죽겠어.";
							link.l1 = "아니야, 이봐, 좀 참아...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "주둔지 생활이 얼마나 지루한지, 너 같은 촌놈들만 있잖아! 이제, 도시 주둔군은 분명 더 재밌게 지내겠지...";
							link.l1 = "이게 근무 중이라는 거냐? 이러다간 분명히 스파이 하나쯤은 놓치고 말 거다!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("힘 좀 써 보이는데, 안 그래? 요새 주둔군에 들어올 생각 있나? 우리 숙소 넓고, 하루 두 끼에 술도 공짜로 준다네.","오, 아가씨, 이런 외진 곳에서 이렇게 아름다운 숙녀를 만나게 되어 얼마나 기쁜지 모릅니다!")+"";
							link.l1 = ""+GetSexPhrase("그거 정말 솔깃하지만, 그래도 거절해야겠어. 그 군대식 훈련은 내 체질이 아니거든.","칭찬해 줘서 고맙네, 병사.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "이 빌어먹을 더위... 유럽으로 돌아갈 수만 있다면 내 목숨의 반쯤은 기꺼이 내놓겠어.";
							link.l1 = "그래, 당신 건강이 이곳 기후에 맞지 않는 것 같군.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "흠... 알겠네. 자, 여기 있소 "+GetSexPhrase("원했다","원했다")+" 물어보다...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "있지, 나 정말 와인이 마시고 싶어... 하지만 썩은 과일로 만든 이 동네 싸구려 술 말고, 한 통에 두 페소 하는 그런 거 말고, 진짜 유럽산 와인 한 병이 필요해. 그건 마을 상인들에게서 구할 수 있어. 꽤 비싸지만, 내가 전액 지불하고 거기에 삼백 페소도 더 얹어 줄게. 그러니, 나한테 좀 가져다줄 수 있겠어?";
			link.l1 = "그걸 왜 직접 가지러 못 가는 거지? 돈 더 낼 필요도 없고, 그냥 네 임무 끝나면 가서 가져오면 되잖아. 뭐가 함정이야?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "속셈은 없어. 나는 휴가를 받기 전까지는 요새를 떠나 마을에 갈 수가 없어, 그리고 그게 당장 일어날 일도 아니지. 게다가 우리 지휘관이 요새에서 술 마시는 걸 엄격히 금지했거든, 제기랄!\n그러니, 병사 하나 좀 도와줄 수 있겠나?";
			link.l1 = "글쎄, 왜 안 되겠어? 그 포도주 가져다줄게, 어차피 시간도 좀 남으니까.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "미안하다, 친구야, 하지만 그건 못 해주겠어. 다른 사람한테 부탁해봐.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "좋아! 정말 고마워! 오늘은 내가 보초를 서고 있으니 내일 와. 요새 꼭대기에서 날 찾을 수 있을 거야. 거기서 아무도 눈치채지 않게 병을 건네줘...";
			link.l1 = "알겠어. 기다려, 내일 보러 갈게.";
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
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("이건 뭔가 속임수 같은데. 사령관한테 가서 얘기해 보자, "+GetSexPhrase("동료","여보")+", 그리고 전부 알아내...","흠... 네가 말하는 사람이 아닌 것 같은데... 무기를 내놔라 "+GetAddress_Form(npchar)+", 그리고 추가 조사를 위해 나를 따라오시오!");
			link.l1 = RandPhraseSimple("꺼져!","한 주에 일요일이 두 번 오는 날이면...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("아, 그렇군... 모든 게 이상 없는 것 같으니, 가도 된다, "+GetAddress_Form(pchar)+".","망을 서다가 좀 피곤해졌나 봐... 모든 게 괜찮아 보이네, "+GetAddress_Form(pchar)+", 미안하오.");
			link.l1 = "문제없어!";
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
				dialog.text = "생각 좀 해 봐라! 이런 무례가 어디 있냐! 상인 행세를 하며 여기까지 오다니! 네 얼굴은 모든 병영에 붙어 있다, 이 자식아! 이번엔 절대 못 빠져나간다! 잡아라!";
				link.l1 = RandPhraseSimple("아르!..","그래, 네가 원한 거잖아...");
				link.l1.go = "fight";	
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "여기서 거래하러 온 건가? 어떻게 왔는지 물어봐도 되겠나? 네 배는 어디 있지? 있잖아, 이 모든 게 아주 수상해 보여서, 우리가 다 알아낼 때까지 널 억류할 수밖에 없겠군. 무기를 넘기고 따라오도록!";
				link.l1 = RandPhraseSimple("꺼져!","한 주에 일요일이 두 번 오는 날에나...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "면허가 만료되어 무효이므로 취소해야 하오. 무기를 넘기고 추가 조사를 위해 나를 따라오시오!";
				link.l1 = RandPhraseSimple("꺼져!","한 주에 일요일이 두 번 오는 날이면...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "흠... 모든 게 제대로인 것 같군. 그래도 네 면허가 오늘로 만료된다는 점은 짚고 넘어가야겠어. 이번엔 그냥 통과시켜주겠지만, 새 면허는 반드시 다시 받아야 해.";
				link.l1 = "감사합니다, 가능한 한 빨리 처리하겠습니다.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "흠... 모든 게 괜찮아 보이네. 그래도 네 면허가 곧 만료된다는 점은 말해둬야겠어. 유효 기간은 오직 "+FindRussianDaysString(iTemp)+". 그러니 그것을 명심해, "+GetAddress_Form(npchar)+".";
				link.l1 = "감사합니다. 가능한 한 빨리 새것으로 구하겠습니다.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("음, 모든 게 괜찮아 보여. 네 면허는 유효해. "+FindRussianDaysString(iTemp)+". 지나가도 된다.","모든 것이 분명하군, "+GetAddress_Form(npchar)+". 당신은 마을을 자유롭게 드나들 수 있습니다, 허가증은 다음 기간 동안 유효합니다  "+FindRussianDaysString(iTemp)+". 귀찮게 해서 미안하오.","모든 게 괜찮아 보여, "+GetAddress_Form(npchar)+", 이제 더 이상 당신을 붙잡지 않겠소.");
				link.l1 = RandPhraseSimple("훌륭하군. 안부 전하오.","감사합니다, 장교님.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "선장님, 무기를 거두어 주시기 바랍니다. 우리 도시에서는 무기를 뽑는 것이 금지되어 있습니다.";
				link.l1 = LinkRandPhrase("알겠어, 내가 치워둘게...","이미 끝났어.","말씀대로...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("꺼져!","내가 이걸 써야겠군!","때가 되면 치워 두겠다.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("대체 왜 칼을 뽑고 돌아다니는 거야? 당장 무기 집어넣어!","당장 무기를 집어넣으라고 명령한다!","이봐, "+GetSexPhrase("동료","아가씨")+", 사람들 겁주지 마! 무기 집어넣어.");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로군...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("꺼져!","꿈꾸는 데 해로울 건 없지...","한 주에 일요일이 두 번 오는 날.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
