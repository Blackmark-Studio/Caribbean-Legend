// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐가 필요해?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, 나 그 사람 알아. 그치? 그자는 리바도스랑 해적들의 친구야. Adolf는 절대 그랑 같이 일하지 않아. 이봐... 화약 냄새 안 나? 그리고 벽에 피도 묻어 있어... 그가 Adolf를 죽이고 지금 우릴 속이려는 거야! 분명히 제독 밑에서 일하는 놈이야! 저놈을 죽여!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Cabin_fight");
		break;
		
		// на улице
		case "Town":
			dialog.text = "아, 미안... 나 좀 도와줄 수 있어?";
			link.l1 = "흠. 나는 언제나 멋진 아가씨를 도울 준비가 되어 있지. 무슨 문제야?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "있지, 내가 세실 갈라드한테서 쇳조각이 가득 든 상자를 샀어. 그 여자는 에바에 살지. 위르겐이 나한테 멋진 걸 만들어주겠다고 약속했거든, 그치? 내가 샀는데, 에휴, 그 사람한테 가져다줄 수가 없어. 젠장!\n네가 에바에서 에스메랄다의 나왈 블록까지 그 상자를 옮겨줄 수 있을까? 제발, 정말 고마울 거야!";
			link.l1 = "그게 다야? 알겠어, 아가씨, 도와줄게. 문제없어.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "고마워! 내가 상자까지 안내할게.";
			link.l1 = "아가씨...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "그리고 우리가 여기 있잖아... 이제 말해 봐, 이 자식아, 열쇠가 어디 있어?!";
			link.l1 = "이런 젠장! 하, 아무런 도움이 필요 없어 보이네... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "똑똑한 척이야, 그치? 말은 그만해, 젠장! 열쇠 어디 있어? 당장 내놔, 아니면 후회하게 될 거야!";
			link.l1 = "너무 무례하잖아! 이렇게 예쁜 아가씨가 말은 또 얼마나 독한지, 그치? 무슨 열쇠?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "네가 Adolf Barbier에게서 가져간 열쇠 말이야. 부정하려고 하지 마, 네가 그의 선실에서 나오는 걸 누군가 봤어. Adolf는 죽었고, 네가 그를 죽였지... 이제, 그 열쇠 내놔!";
			link.l1 = "결국 너였군... 큰 실수를 했어, 이 아가씨!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "뭐라고 했어...? 젠장, 넌 평범한 도둑이 아니잖아! 저 자식, 제독 밑에서 일하고 있어! 놈을 쓰러뜨려라, 얘들아!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, 저놈이야! 젠장, 놈이 지원을 데려왔어! 얘들아, 전부 죽여버려!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "딱 맞춰 왔네... 나 혼자선 절대 저 녀석들 못 이겼을 거야... 푸하! 솔직히, 난 진짜 끝났다고 생각했거든!";
			link.l1 = "너는 발키리처럼 싸웠어! 이렇게 아름다운 여자가 그렇게 맹렬하게 싸우는 건 처음 봤어...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "하하, 참 신사네, 검을 든 채로 칭찬까지 하다니. 도와줘서 고마워. 정말 날 구해줬어, 그치? 자기소개 좀 해봐, 나리. 전에 본 적 없는 얼굴인데. 여기 처음이야?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+", 하지만 예쁜 아가씨들은 나를 이렇게 불러도 돼 "+pchar.name+"... 내가 여기 처음이냐고? 흠... 그런 것 같아, 그치?";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "알겠어. 이렇게 잘생긴 남자가 근처에 있었으면 내가 바로 알아봤겠지, 그치? 내 이름은 Mary야, Mary Casper. 다들 나를 빨간 Mary라고 불러. 내 머리가 빨갛거든, 그치?";
			link.l1 = "널 만나서 기뻐, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "아, 두 번이나 기뻐, 그치? 너 아니었으면 난 벌써 죽었을 거야! 그 놈 Chad, 허세가 아니었어. 완전 쥐새끼지! 내가 아랫문을 열어둔 게 바보짓이었어. 그래서 네가 안으로 들어올 수 있었던 거지, 그치?";
			link.l1 = "응. 나는 섬 주변을 헤엄치면서 올라갈 만한 곳을 찾고 있었어, 그치?";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "알겠어. 저 열린 문 때문에 거의 죽을 뻔했지. 위르겐이 직접 나를 위해 자물쇠를 만들었거든, 제대로 된 열쇠 없이는 절대 못 열어. 자물쇠 따기도 소용없고. 게다가 누가 들어오려고 하면 내가 가만히 있을 리 없잖아 — 내 권총 네 개의 총구가 문이든 몸이든 네 개의 구멍을 남길 테니까, 하하!\n근데 그 빌어먹을 채드는 날 그냥 두질 않아. 자기 편 들라고 깡패들을 보내서 '설득'하려고 했다면, 진짜 작정한 거지. 네가 아니었으면 나도 어쩔 수 없이 받아들였을 거야. 이제 포위당한 채 여기 있어야겠네, 그치? "+pchar.name+", 그치! 다행히 내가 미리 준비해 뒀으니까. 식량도 넉넉하고, 위르겐은 내 이웃이야. 나랑은 아무런 다툼도 없어, 그치?";
			link.l1 = "Mary, 네 문제를 왜 제대로 설명하지 않는 거야? 내가 네가 도움이 필요한 건 알겠는데, 네 입에서 나온 말은 하나도 이해 못 했어.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "그래, 도움이 정말 필요해, 그치? 지금 나 혼자야. 도널드랑 다투고, 채드는 결국 악당이었어... 아, 미안해, 또 주절거렸네. 좋아, 내가 처한 상황에 대해 말해줄게...\n";
			link.l1 = "여기 온 지 얼마 안 돼서 아직 잘 모르는 게 많아, 그치? 그런데 그 Chad라는 놈이 널 '설득'하거나 죽이려고 한다고? 그리고 Donald는 또 누구야?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad는 Shark Dodson 제독의 선원 출신 해적으로, 타르타로스의 감옥지기야...";
			link.l1 = "잠깐! 샤크 돗슨이라고 했어? 그 사람이 여기 있어?!";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "너 오늘 밤에 도착한 게 분명하네, 그치? 그걸 아직 모르는 걸 보니까. 상어가 어디 있겠어? 내 골칫거리는 그가 몇 달 전에 여기 온 이후로 시작됐어. 인정하긴 싫지만, 이건 전부 나왈족이랑 리바도스 놈들 탓이야, 그치? 상어가 자기 선원들이랑 여기 왔을 때, 기지를 세우려고 했는데 우리 사람들이랑 리바도스가 그걸 싫어했지. 그래서 밤에 상어의 브리그를 공격해서 불을 질렀어.\n진짜 멍청한 짓이었지! 상어 선원들은 인간이 아니라 악마들이야, 그치? 먼저 우리 배들을 다 부숴버리고, 상륙해서 우리를 학살하기 시작했어. 나왈족은 도망치고 리바도스 놈들은 죽기 살기로 달아났지. 결국 해적들이 정의의 섬 식량 대부분이 있는 산 아우구스틴을 점령했고, 그 다음엔 타르타로스를 빼앗았어.\n상어는 우리 지도자인 앨런 밀로우를 감옥에 가뒀어. 그는 내... 내 소중한 친구이기도 했고, 리바도스의 마법사 치미셋도 같이 잡혔지. 둘 다 짐승처럼 타르타로스의 우리에 쳐넣었어. 여기서 타르타로스까지는 수영해서 쉽게 갈 수 있어서, 난 몇 번 앨런을 만나러 갔었어. 거기서 채드 캐퍼를 만났지. 상어가 그를 간수로 임명했거든. 난 채드한테 앨런을 풀어달라고 돈까지 약속했지만, 그는 제독이 무서워서 거절했어.\n그리고 앨런이 감옥에서 살해당했어.\n채드가 말해줬어, 상어가 그랬다고, 그치? 그래서 난 앨런 대신 뽑힌 도널드에게 가서 당장 해적들을 공격하라고 요구했지만, 그는 거절했어. 그 바다 악마들은 우리 힘으론 감당 못 한다고 했지. 그래서 난 그한테 꺼지라고 했어.\n내 사람들은 쓸모가 없었으니까, 상어 자리를 노리던 쓰레기 캐퍼랑 손을 잡았어. 계획이 있었지 — 제독을 요새에서 꾀어내서 음침한 곳에서 죽이기로. 좋은 소총을 가진 저격수도 구했어. 그가 퓨리의 돛대에서 제독을 쏠 수 있었지.\n이제 재밌는 부분이야, 그저께 밤에 난 타르타로스에 몰래 들어가서 채드한테 우리 계획에 대해 중요한 얘기를 하려고 했어. 수영해서 배에 갔는데, 채드가 나왈족 두 명이랑 얘기하는 걸 엿들었지. 알고 보니 상어가 앨런을 죽인 게 아니었어. 채드가 죽였더라고. 그리고 제독이 범인이라는 소문을 퍼뜨린 거야.\n채드는 나 때문에 앨런을 죽였어 — 첫째는 날 자기 침대 장난감으로 삼으려고, 둘째는 날 이용해서 상어를 없애려고. 채드는 내가 복수할 때까지 절대 멈추지 않을 걸 알고 있었던 거야. 상상이나 돼? 진짜 쓰레기지, 그치?";
			link.l1 = "그치, 나도 그런 놈들 만나봤지...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "개자식은 더 최악이야! 그 자식은... 그 괴물을 어떻게 표현해야 할지 말이 안 나와! 내가 헤엄쳐서 도망친 다음 날 아침, 그놈을 찾아가서 내가 생각하는 걸 전부 말해줬어. 그치? 내가 그놈한테는 제독을 상대로 한 음모에 절대 끼지 않겠다고 딱 잘라 말했지.";
			link.l1 = "그리고 그는 당연히 그걸 마음에 들어하지 않았지... 그치? 너무 성급했어, Mary. 좀 더 조심했어야 했잖아, 그치?";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "알아, 하지만 입 다물고 있을 수가 없었어. 그 자식이 Alan을 죽이고 나까지 자기 목적에 이용하려 했잖아! 쓰레기 같으니라고! 그리고, 그치? 걔가 화내면서 내가 후회하게 만들어주겠다고 했지. 그래서 내가 그 자식 불알을 잘라서 게밥으로 던져주겠다고 했어!\n내가 마음을 바꾸지 않으면 자기 친구들을 보내겠다고 협박하더라. 웃어버렸지. Narwhal 녀석이 감히 나한테 손을 대려고 할 줄은 몰랐거든.";
			link.l1 = "착각한 것 같네.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "그래, "+pchar.name+", 내가 Chad를 얕봤고 나 자신을 과대평가했어. 그는 외로운 소녀를 자기 선실에서 공격할 만큼 비열한 놈들을 찾아냈지. 이제 어쩌지? 아무도 믿을 수 없어, 내 사람들조차도 못 믿겠어; 우리가 죽인 이 둘도 나와 같은 나왈(Narwhals)이야. 둘 다 잘 알던 녀석들이었지, 그치? Chad가 살아 있는 한, 난 위험해. 분명히 더 많은 놈들을 보낼 거야.\n문 밖으로 나가는 것도 무서워; 우리가 Shark를 암살하려고 고용한 저격수가 Rivados 영토에서 날 쏘고 도망칠 수도 있잖아. Donald한테는 안 갈 거야 - 그 사람은 내 말을 듣지 않을 테니까.\n그리고 제독님은? '제발요, 나리, 제가 암살 계획에 가담한 건 알지만, 혹시 저를 용서해 주시고 옛 동료들한테서 구해주실 수 있나요?'\n그 사람은 날 타르타로스 감방에 썩게 보내거나, 아니면 내 머리에 총알을 박아버릴 거야. 젠장, 완전히 갇혔어! 난 그냥 여기서 총에 탄창 꽉 채우고 앉아 있을 거야, 음식이 다 떨어질 때까지… 그 다음엔… 나도 모르겠어!";
			link.l1 = "음, 그런 거라면 내가 도와줄 수밖에 없지, 그치? 어차피 네 상황이 내 계획이랑 맞아떨어지거든...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "나를 도와주고 싶다고? 그런데 어떻게? Chad를 죽이려고 하는 거야?";
			link.l1 = "그것도 계획의 일부야, 그치?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "들어봐, "+pchar.name+", 고맙긴 한데, 네가 감당할 수 있는 일이 아니야. Chad는 제독의 가장 가까운 친구 중 한 명이고, 네가 그에게 간다 해도 살아서 나올 수 없어. Shark의 해적들이 널 죽일 거야. 그 녀석들은 진실을 몰라, 그치?";
			link.l1 = "진정해. 어차피 Shark랑 얘기해야 해.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "그래서, 너도 해적이란 거야?! 이제 말 좀 해봐. 잘생긴 얼굴로 내 집에 쳐들어와서 내 목숨을 구해주고, 도와주겠다고 약속까지 했으면서, 난 너에 대해 아무것도 모르잖아!";
			link.l1 = "좋아... 난 해적은 아니지만, 지금은 어떤 해적 남작이랑 일하고 있어. 얀 스벤손이라는 사람이야. 여기 온 건 네이선 호크를 찾으려고 온 거고. 들어본 적 있어, 그치?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "아니, 걔가 누군데?";
			link.l1 = "또 다른 유명한 해적이네. 그 사람을 못 만난 게 아쉽다, 분명 어딘가에 있을 텐데. 나도 샤크를 찾고 있었지만, 여기서 그를 만나게 될 줄은 몰랐어.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "근데 어떻게 여기까지 온 거야? 난파선에서 살아남은 사람치고는 너무 멀쩡해 보이는데, 그치?";
			link.l1 = "내가 난파당했다고 왜 생각하는 거야?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "여기로 올 수 있는 방법은 그거뿐이야. 상어만이 여기까지 항해해 본 유일한 녀석이거든, 그치?";
			link.l1 = "봐봐, Shark만 있는 게 아니잖아, 그치?";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "그래서, 배가 생긴 거야? 멋지다, 그치?";
			link.l1 = "너무 들뜨지 마, Mary. 나는... 바크선을 타고 여기까지 왔어. 바크선을 타고 왔는데 가라앉아 버렸지, 그치?";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "아-아... 그러니까, 내가 말했잖아: 난파선 때문에 여기 갇힌 거야. 이제 우리랑 같이 갇힌 거라고, 그치?";
			link.l1 = "Mary, 내 계획을 말해줄게. 너가 Chad가 Shark를 죽일 계획이라고 했지, 그치? 나는 Shark가 살아있어야 해. 나랑 Jan은 Shark를 해적들의 우두머리로 만들 거야. 그래서 내가 그에게 경고해야 해. 네 얘기를 들어보니, 네가 돕든 안 돕든 Chad는 분명 시도할 거라고 확신하거든, 그치?";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "그래, 그치? 아마도 그럴 거야. 그 녀석은 그걸 해낼 만한 인원들이 있으니까...";
			link.l1 = "내 주된 목표는 Shark의 신뢰를 얻고 그를 구하는 거야. 그 다음엔 공식적으로 Chad에게 갈 거고. 그의 죄를 입증할 증거라도 있어?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "나는 그 바닥에 널브러진 저... 멍청이들 중 한 명이 가져온 그의 편지를 가지고 있어. 그 안에는 위협과 세부사항이 적혀 있는데, 제독이 흥미로워할 만한 내용이야. \n잠깐! 나는 어떻게 되는 거야? 상어가 내가 Chad랑 같이 일한 걸 알게 될 거라고!";
			link.l1 = "Mary, 너 여기서 권총 들고 평생 앉아 있으면서 그 예쁜 얼굴을 모두한테 숨길 거야, 그치? 정말 내가 이렇게 아름다운 아가씨가 죽는 걸 두고두고 마음에 짐 지고 싶어 할 거라고 생각해? 먼저 편지부터 보여 줘, 내가 뭘 할 수 있을지 보자...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "여기. 어떻게 생각해, 그치?";
			link.l1 = "잠깐만... (읽는 중). 그치? Chad는 이 세상에 들끓는 특별한 악당 부류 중 하나인 것 같아. 이 편지면 Shark가 직접 Chad 목에 올가미를 씌우고 싶어질 거야. 걱정 마, 아가씨. Shark가 절대 너를 의심하지 않게 할게. 어차피 Shark는 Chad 때문에 정신없을 테니까, 그치?";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "정말 이럴 거야? 약속해, 그치? 날 배신하지 않겠다고 맹세해!";
			link.l1 = "Mary, 너에게 맹세해. 절대 너를 배신하지 않을 거야. 널 구한 게 너를 죽게 하려고 그런 건 아니야, 그치?\nChad는 널 가만두지 않을 거야, 그건 확실해. 넌 너무 많은 걸 알고 있잖아. 그가 죽을 때까지 여기 있어.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "그래, 난 여기 있을게. 저격수한테 총 맞거나 뒤에서 칼 맞는 건 사양이야.";
			link.l1 = "착하지. 아래쪽 문까지 전부 닫아, 그치? 열쇠는 너만 가지고 있지?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "아니. 또 하나 있어. 갖고 싶어, 그치?";
			link.l1 = "그래. 나를 믿어, 그치?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "글쎄, 방금 내 목숨을 구해준 잘생긴 신사가 날 배신한다면, 더는 살 이유가 없지... 받아, 그치?";
			link.l1 = "겁내지 마, 이쁜이! 내가 널 실망시키지 않을 거야. 이 난장판만 정리하면 바로 볼게. 오래 걸리지 않길 바라, 그치?";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "괜찮아, 여기서 몇 주는 버틸 수 있어.";
			link.l1 = "좋아. 그럼 시간 낭비하지 않을게. 시체들부터 치우고 샤크랑 얘기할 거야. 샤크는 산 아우구스틴에 있지, 그치?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "그래, 그는 항상 거기 있어. 그리고 여기 들어온 것처럼 똑같이 나가, 그치? 내가 세레스호의 상갑판에는 절대 못 올라가게 할 거야.";
			link.l1 = "그건 왜인데?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "네가 죽으면 나를 도울 수 없으니까. 여긴 나르왈들의 영역이고, 넌 이방인이라서 그치? 그들이 널 죽일 거야.";
			link.l1 = "흠... 알겠어. 그럼, Mary, 또 보자. 안전해지면 바로 돌아올게.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "언제든 보고 싶으면 와도 돼, 난 상관없어. (키득키득)";
			link.l1 = "잘 가, 고운 이여!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "안녕, "+pchar.name+", 나한테 좋은 소식이라도 있어? 너 괜찮아, 그치?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Shark Dodson과의 갈등은 해결됐어. 이제 그는 너를 쫓는 데 관심 없어. 지금 그가 신경 쓰는 건 Chad의 배신뿐이야.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "아직 아니야, Mary. 하지만 내가 할 수 있는 건 다 해볼게.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "아, 신이시여, 감사합니다! 고마워, 절대 잊지 않을게, 그치? 적어도 이제 제독 걱정은 안 해도 되겠네. 그런데 Chad는 어때? Shark가 뭘 했어?";
			link.l1 = "우리가 리바도스 놈들을 설득해서 그를 쫓게 했어. 레이턴 덱스터가 타르타로스에서 경비들을 치우고 감옥 열쇠를 블랙 에디에게 넘겼지. 흑인들은 자기네 마법사 치미셋을 풀어줬지만 채드를 죽이는 데는 실패했어; 채드의 나왈 친구 둘은 잡았지만, 채드는 도망쳐서 어딘가에 숨어 있어.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "젠장! 이제 더 조심해야겠네, 그치?";
			link.l1 = "진정해, Mary. 그는 너보다 Shark에 더 신경 쓸 거야, 그치? Rivados를 자기한테 부딪히게 한 사람이 누군지 아마 알고 있을 거야. 그는 Shark를 죽이기 위해서라면 뭐든지 할 거야, 너를 해치려는 게 아니야.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "그렇게 기대하지 마. Chad는 그렇게 쉽게 넘어갈 사람이 아니야. 아, 그 사람 눈치 보면서 사는 것도 이제 지긋지긋해...";
			link.l1 = "흠. 넌 쉽게 겁먹는 여자가 아니라고 생각했는데, 그치?";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "하! 제대로 싸우는 건 하나도 안 무서운데, 가만히 앉아서 죽기를 기다리는 건 진짜 무섭지, 그치? "+pchar.name+", 그치!...";
			link.l1 = "날 믿어, Mary. Kapper는 지금 제독 때문에 정신이 하나도 없어. 그치? \n지금은... 네 조언이 필요해.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "내 조언? 무슨 조언 말이야?";
			link.l1 = "Eddie가 Chad가 쓴 편지 두 통을 찾았어. 읽어봐, 아마 그가 무슨 꿍꿍이인지 알 수 있을 거야. 어차피 너도 Chad랑 같이 계획에 끼어 있었잖아...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "여기로 줘... (읽는 중). Axel은 에스메랄다호의 우리 상인이네, 그치? Chad가 그에게서 위스키를 사려고 했다고? 이상하네. Chad는 럼만 마시거든, 위스키는 '촌놈들의 싸구려 술'이라고 하잖아...\n";
			link.l1 = "그럼 두 번째 편지는 어쩔 건데?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "'마르첼로'? 마르첼로 외눈박이, 전직 왕실 사냥꾼이야. 내가 이 선실을 절대 나가지 않으려는 이유가 바로 그 사람이거든.";
			link.l1 = "그가 네가 고용한 저격수야?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "그래, 그치? 한쪽 눈이 없어도 마르첼로는 사십 피트 거리에서 파리도 쏠 수 있어, 그치? 그의 임무는 산타 플로렌티나의 뱃머리나 퓨리의 갑판에서 장거리 슈투첸으로 샤크를 맞추는 거였지...\n";
			link.l1 = "그러니까 아직도 Chad의 Shark 암살 계획에 끼어 있다는 거네. 그런데... Eva? Cecille? 술 한잔?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "에바호는 중립선이고, 세실은 세실 할라르드야. 배에서 사는 재미있는 할머니지. 얼마 전에 산타 플로렌티나에서 이쪽으로 옮겨왔어. 오렐리 베르틴은 그녀의 친구야. 그 둘은 내가 태어나기 전부터 정의의 섬에 있었어, 그치?";
			link.l1 = "흠. 말도 안 돼. 건장한 녀석 둘이서 늙은 여자한테 숨어서 위스키 한 통을 같이 마신다고? 말도 안 되는 소리야... Chad가 술 마시기엔 참 이상한 시간과 장소인데, 그치?";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "그 사람이 위스키는 안 마시고 럼만 마신다고 내가 말했잖아... 뭔가 이상한데.";
			link.l1 = "좋아, 그럼 사이클롭스부터 시작하자. 어디서 그를 찾을 수 있는지 알아, 그치?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "아니. 그는 아주 폐쇄적인 사람이야. 매일 바깥쪽 고리에서 새를 쏘고, 아무도 그가 어디서 자는지 몰라. 리바도스에도 자주 들르지, 그치?";
			link.l1 = "별로 단서가 없네... 뭐, 그럼 내가 Axel한테 가서 얘기해 볼게. 혹시 이걸 이해할 수 있을지도 모르지. 또 보자, Mary! 문 꼭 잠가!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+", 제발 Chad를 빨리 찾아줘. 지난번 공격 이후로 한숨도 못 잤어.";
			link.l1 = "꽉 붙잡아, 자기야. 내가 할 수 있는 만큼 최선을 다할게.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! 어떻게 여기 온 거야? 혹시 오려고 했던 거야--?";
			link.l1 = "그래, 널 죽이려고 왔어, Mary. 그가 Jurgen의 선실을 통해 여기로 들어와서 밧줄을 타고 내려왔어.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "아! 나 진짜 바보야! 그 길을 까먹었잖아! Chad가 그 사람한테 말해줬겠지, 그치?";
			link.l1 = "아마 그럴 거야. 나도 간신히 살아남았거든, 그치?";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "그리고 나는 자고 있었어. 그는 나를 순식간에 죽였을 거야... 그런데 어떻게 그가 여기로 오고 있다는 걸 알았어?";
			link.l1 = "오... 나만의 방법이 있지, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "또 나를 구해줬네, 잘생긴이. 넌 항상 딱 맞는 타이밍에 나타나, 그치? 그 비결이 뭐야?";
			link.l1 = "글쎄, 나도 잘 모르겠네. 내 많은 재주 중 하나지, 그치? 네 포위전은 끝났어 – Chad Kapper는 죽었고, 그의 친구들도 다 끝장났어. Cyclops가 그 썩은 놈들 중 마지막이었지, 그치?";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "정말로, "+pchar.name+"? 나 놀리는 거 아니지, 그치?";
			link.l1 = "전혀 아니야. 에휴, 지난 며칠 동안 너무 힘들어서 좀 쉬어야겠어...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "이제야 숨 좀 쉴 수 있겠어! 고마워... 정말 고마워! 너는 내 영웅이야, 그치?";
			link.l1 = "그 말 참 마음에 들어, 네 영웅이 되는 거 말이야. 네가 드디어 무사해서 정말 다행이야, 그치?";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "그래서?";
			link.l1 = "무슨 일이야, 예쁜이?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "왜 거기 가만히 서 있어? 이리 와, 나리.";
			link.l1 = "그리고 뭘 하라고?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "이리 와서 안아 줘, 키스해 줘. 너도 원하고 있잖아, 그치?";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "나를 두고 가지 마...";
			link.l1 = "나 여기 있어, Mary, 자기야...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "모든 건 기다릴 수 있어. 네 제독도 기다릴 수 있고, 네 해적들도 기다릴 수 있지 – 오늘 밤은 우리 둘만을 위한 거야, 그치?";
			link.l1 = "그치.";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "그리고 그 이후의 모든 밤들도...";
			link.l1 = "그래, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! 돌아왔네... 그녀 없이. 결국 그녀도 너를 내게서 뺏지 못했지, 그치?";
				link.l1 = "Mary, 네 의심은 근거 없었어. 내겐 너뿐이야. 나는 항상 마음속에서도, 꿈속에서도 너와 함께였어.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", 왜 너는 나왈과 싸우고 있는 거야? 나는 그들의 영역에서 살고 있어—혹시 잊었으면 말인데, 나도 그들 중 한 명이야. 제발, 파지오에게 가서 화해해 줘, 부탁이야.";
				link.l1 = "그치? Mary, 네가 시키는 대로 할게.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", 뭔가 고민이 있네. 무슨 일이야?";
				link.l1 = "Mary, 너랑 얘기 좀 해야겠어.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! 모든 나르왈들이 너에 대해 이야기하고 있어!";
				link.l1 = "정말이야, 자기야?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! 이 브로드소드 정말 대단해! 고마워! 나도 너한테 선물을 주고 싶어. 물론 네 거랑은 비교도 안 되지만, 그래도 받아줬으면 해, 그치?";
				link.l1 = "Mary, 너한테 받는 선물이라면 뭐든 소중하게 간직할 거야... 고마워, 내 사랑.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "오늘 바쁜 하루가 기다리고 있네, "+pchar.name+"그치? 행운을 빌어!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, 오늘 Jurgen을 만나러 가야 해.";
					link.l3.go = "narval";
				}
				link.l1 = "고마워, Mary! 그건 전혀 의심하지 않아.";
				link.l1.go = "exit";
				link.l2 = "오늘은 안 돼, Mary. 여기서 좀 쉬고 싶어. 그치, 괜찮지?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "음, "+pchar.name+", 잘 지내? 평소처럼 섬을 뛰어다니고 있는 거야?";
				link.l1 = "그래, Mary. 해야 할 일이 정말 많아...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = ""+pchar.name+", 벌써 저녁이잖아, 무슨 얘기를 하는 거야? 여기 있어, 우리 술 마시면서 좀 쉬자, 그치? 다른 일은 아침까지 미뤄도 되잖아!";
				link.l1 = "(웃으며) 그치? 당연하지, 자기야, 더 말할 필요도 없어...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, 오늘은 선술집에 가자!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, 자기야, 나 지금 정말 바빠. 조금 있다가 돌아올게.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "저녁에 꼭 나한테 들러. 그리고 나 피하려고 하지 마, 그치?";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, 오늘은 우리가 Jurgen을 만나러 가야 해.";
					link.l3.go = "narval";
				}
				link.l1 = "그치, Mary, 내가 어떻게 안 오겠어? 당연히 너 보러 올 거야.";
				link.l1.go = "exit";
				link.l2 = "Mary, 오늘 밤 여기서 쉬고 싶어. 괜찮지, 그치?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "무슨 소리야? 벌써 밤이잖아! 너 어디도 못 가, 여기, 나랑 같이 있어야 해, 그치?";
			link.l1 = "(웃으며) 네 소원이면 뭐든지 들어줄게, 자기야...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "하지도 마...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("훌륭한 생각이야, "+pchar.name+", 그치! 나도 동의해!","그래, 가자, "+pchar.name+"산초가 훌륭한 와인 컬렉션을 가지고 있어, 고를 게 정말 많아!","오, 나야 당연히 좋지, 그치? 산초네 선술집은 항상 재미있고, 거긴 와인도 끝내주게 많거든, 그치?");
			link.l1 = "가자!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "당연하지, "+pchar.name+", 얼마나 머무를 거야?";
			link.l1 = "나는 정오까지 있을 거야...";
			link.l1.go = "rest_day";
			link.l2 = "저녁까지 있을게...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "그치, "+pchar.name+", 얼마나 머무를 거야?";
			link.l1 = "저녁까지 있을게...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! 돌아왔네... 그녀 없이. 결국 그녀도 너를 내 곁에서 데려가지 못했지, 그치?";
				link.l1 = "Mary, 네 의심은 근거 없었어. 나에겐 너 하나뿐이야. 항상 마음속에서도, 꿈속에서도 너와 함께였어, 그치?";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", 왜 너는 나르왈들과 싸우는 거야? 나는 그들의 영역에 살고 있어—혹시 잊었으면, 나도 그들 중 한 명이야. 제발, 파지오에게 가서 화해해 줘, 부탁이야.";
				link.l1 = "알겠어, Mary, 네가 시키는 대로 할게.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! 이 브로드소드 정말 대단해! 고마워! 나도 너한테 선물을 주고 싶어. 물론 네 것만큼 대단하진 않지만 받아줬으면 해, 그치?";
				link.l1 = "Mary, 네가 주는 거라면 뭐든 소중하게 간직할 거야... 고마워, 내 사랑.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "벌써 가려고, "+pchar.name+"그치? 행운을 빌고, 나 잊지 마...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, 오늘은 우리 Jurgen을 만나러 가야 해, 그치?";
					link.l3.go = "narval";
				}
				link.l1 = "고마워, Mary!";
				link.l1.go = "exit";
				link.l2 = "Mary, 나 여기서 좀 쉬고 싶은데. 괜찮지, 그치?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "너, 쿠쿨칸한테 안 갈 거야, 그치? "+pchar.name+"?";
				link.l1 = "아직 아니야, 아직 준비 중이야.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "벌써 저녁이네, "+pchar.name+". 여기 있으면 안 돼? 너랑 같이 있고 싶어.";
				link.l1 = "그치? 자기야, 나 여기 남아 있을게...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, 오늘은 선술집에 가자!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "행운을 빌고, 나 잊지 마... 시간 되면 저녁에 꼭 보러 와, 그치!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, 오늘 Jurgen을 만나야 해.";
					link.l3.go = "narval";
				}
				link.l1 = "좋아, 자기야.";
				link.l1.go = "exit";
				link.l2 = "Mary, 나 여기서 좀 쉬고 싶은데. 괜찮아, 그치?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "무슨 소리야? 지금 밤이잖아! 안 돼, 어디도 못 가, 여기 있어야 해, 그치!";
			link.l1 = "(웃으며) 그치? 나 있을게...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Captain "+pchar.name+"! 메리 캐스퍼 부관이 당신의 지휘 아래 복무할 준비가 됐어!";
				link.l1 = "잘했어, 장교! 지금 당장 배에 타라고 명령한다. 하지만 먼저... 네 선장에게 키스해!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "정말 대단했어, 자기야... 좋은 아침이야!";
				link.l1 = "좋은 아침이야, 자기! 너 정말 멋져, 그치?";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Donald이랑 얘기해 봤어? 정말로 제독이 리바도스랑 동맹을 맺고 나왈과 싸우려고 했다는 게 사실이야? 네가 그걸 말렸다는 것도 사실이야? 이제 해적들이랑 나왈 사이에 평화가 오는 거야?";
			link.l1 = "그래, Mary. 맞아.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", 말이 안 나와... 그리고 Donald도 너를 친구라고 생각한대. 너도 혹시 나르왈스의 일원이 될 수 있을지도 몰라, 그치?";
			link.l1 = "시간 될 때 도널드를 만나 봐. 그치? 그도 너랑 화해하고 싶어 해. 자기 말과 채드로부터 널 지키지 못한 걸 용서해 달라고 부탁했어.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "도널드는 지옥에나 가라! 그래도... 그 얘기를 들으니 기쁘긴 해, 그치? 그를 만나긴 할 거야. 하지만 너! 나는... 나는 네가 자랑스러워, 그치?";
			link.l1 = "세상에, Mary, 너는... 아, 너 때문에 내 심장이 두근거려, 그치?";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "이야기 좀 하자! 곤란한 일이라도 있어, 그치?";
			link.l1 = "아니. Mary... 우리 처음 만난 밤 기억나? 그 두 놈을 처리한 후에, 내가 배 타고 여기 왔다고 너한테 말했지, 그치?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "기억나, 그치? 네 바크선이 침몰해서 네가 여기까지 헤엄쳐 왔잖아... 그치?";
			link.l1 = "거짓말했어. 그때 진실을 말했다면 네가 날 미쳤다고 생각했을 거야, 그치? 바크선은 없었어. 내가 여기 오려고 스페인 본토에서 인디언 신 쿠쿨칸의 마법 우상을 썼거든, 그치?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... 무슨 소리야? 쿠쿨칸?";
			link.l1 = "Mary, 내 사랑, 날 믿어야 해. 이건 도무지 이성적으로 설명할 수 없는 일이거든. 그리고 너 말고는 아무에게도 말할 수 없어, 그치? Nathaniel Hawk는 인디언 우상을 만지다가 사라졌어. 쫓기고 있었는데, 그 우상이 그를 여기로 보낸 거야...\n";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "...";
			link.l1 = "나는 Nathaniel을 찾고 있었어. 인디언 주술사와 얘기했고, Hawk처럼 우상에 손을 댔지. 그랬더니 산 아우구스틴호의 화물칸 안으로 순간이동됐어, 선체에 난 구멍을 통해 빠져나왔고... 그리고 운명이 널 내게 데려왔지, 그치?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "이게 언젠가 우리 아이들에게 들려줄 우스운 이야기라도 된다는 거야, 아니면 네가 미친 거야?";
			link.l1 = "나 화난 거 아니야, Mary! 믿기 힘들다는 거 알아. 네가 보기엔 미친 짓처럼 보일 수도 있겠지. 하지만 제발... 날 믿어줘.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "에릭의 이야기들이 사실이었던 것 같아...";
			link.l1 = "에릭이 누구야? 무슨 이야기인데?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric은 이곳 토박이였어, 늙은 선원이었지. 지금은 오래전에 죽었고. 내가 어릴 때, 그가 인디언 우상에 대한 이야기, 이 정의의 섬에서 Rivados가 사람을 제물로 바치던 성소 이야기를 들려주곤 했어.\n그걸 만진 자들은... 사라졌지... 다시는 모습을 드러내지 않았어. 난 그저 아이들을 겁주려고 지어낸 이야기인 줄 알았어.";
			link.l1 = "맞아, Mary. Eric은 거짓말하지 않았어.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "다행히도 그 끔찍한 우상이 있던 배는 침몰했어. 나는 직접 본 적은 없어, 그치?";
			link.l1 = "바닥에 가라앉아 있는 걸 찾았어.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "거기서 잠수했어?! 그 망할 발명가 베데커가 너한테 그 잠수복을 줬다고? 거기 밑엔 게들이 기어 다닌다니까, 그치?! 저 망할 놈! 너를 그런 위험에 빠뜨리다니--!";
			link.l1 = "Mary, 나 걱정하지 마. 내가 게들은 알아서 처리할 수 있어. 사람들이 말하는 것만큼 위협적이지 않아. 이 섬에 처음 온 날부터 그 조각상을 찾아 헤맸는데, 드디어 찾아냈어.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "이제 어떻게 되는 거야?";
			link.l1 = "우상만이 여기서 나갈 수 있는 유일한 방법이야. 나는 바닷속에 있는 그 우상과 똑같은 우상을 통해 이 섬에 왔고, 다시 돌아가기 위해 또 그걸 쓸 거야... Mary! 울고 있는 거야? 아, Mary, 제발 그러지 마...";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "왜 안 돼? 울고 싶으면 우는 거지, 그치... (흐느낌) 이런 일은 항상 내 부하들에게만 일어나! 또다시 나 혼자 남게 됐잖아!\n";
			link.l1 = "나한테 무슨 일이 일어날 것 같아? 내가 정말 널 여기 그냥 두고 갈 거라고 생각해, 그치? 반드시 널 데리러 다시 올 거야, 배를 타고. 너랑 그리고\n "+sTemp+"Nathaniel이 다시 내 곁에 있어. 나랑 함께 세상 밖으로 나갈 거지?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(눈물 흘리며) 당연하지... 그치, 내가 할 거야... 넌 꼭 나를 데리러 올 거지? 도대체 어떻게 정의의 섬으로 다시 올 생각이야? 여기로 항해할 줄 아는 건 상어뿐이야—그리고 나 절대 잊지 마, 알았지? 안 그러면 널 찾아내서 혼내줄 거니까!";
			link.l1 = "Mary, 이제 그만해! 당연히 너를 데리러 올 거야! 너를 만난 이후로 내 심장을 이렇게 뛰게 만든 사람이 또 어디 있겠어? 걱정하지 마, 내 사랑. Shark가 나에게 정의의 섬의 좌표와 길을 알려줬어. 반드시 다시 널 찾을 거야.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "너는 스페인 본토의 우상이 널 여기로 보냈다고 했지, 그치? 하지만 저 아래에 있는 놈이 널 다른 데로 데려가면 어쩌지, 아프리카 같은 데로? 그럼 나는 어떻게 해야 해?!";
			link.l1 = "쿠쿨칸은 인디언 신이야. 그 신이 나를 카리브 해나 스페인 본토 어딘가로 데려다 줄 거야. 나는 정착지만 찾으면 돼. 그러면 내 배와 선원들을 찾는 건 쉬울 거야.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(울면서) 약속해 줘... 아니, 맹세해 줘, 꼭 돌아올 거라고, 그치?!";
			link.l1 = "Mary, 내 사랑, 너에게 맹세해. 반드시 돌아올 거야. 그리고 널 이 비참한 곳에서 데려갈 거야. 오래 그리워할 필요 없어. 이제 그만 울어, 그치?";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "좋아, "+pchar.name+"... ... 나한테 돌아와, 기다릴게, 그치? 언제 떠날 거야?";
			link.l1 = "아직 잘 모르겠어. 먼저 내가 준비를 해야 해, 그 다음에 잠수해서 그 조각상을 만질 거야. 사람들이 내가 익사했다고 말할 텐데, 그치? 믿지 마. 다 잘 될 거야.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "알겠어. "+pchar.name+", 자기야, 안아줘... 키스해줘...";
			link.l1 = "Mary... 내 사랑 Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "위르겐? 왜?";
			link.l1 = "곧 알게 될 거야. 기분 좋은 놀라움이 될 거니까, 그치?";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "오, 정말 흥미로운데! 기분 좋아? 그치? 자, 가자, 내가 궁금해서 죽기 전에!";
			link.l1 = "분명 마음에 들 거야, 그치? 가자!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "가자, "+pchar.name+"!";
			link.l1 = "그치...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "음, "+pchar.name+", 나한테 무슨 깜짝 선물이 있는 거야?";
			link.l1 = "Mary! Jurgen이랑 내가 너한테 둘이서 선물을 준비했어, 그치? 이건 특별한 검이야, 나르왈이라는 이름을 가진 브로드소드지. 이런 검은 세상에 딱 두 자루밖에 없어. 첫 번째는 Alan Milrow가 가졌고, 이 두 번째는 네 거야, 그치? 이 검은 특별한 철로 만들어졌고, Jurgen의 장인 솜씨로 단련돼서 절대 무뎌지거나 녹슬지 않아.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "내 사랑스러운 아가... 너의 고생을 나왈 일족 모두가 알고 있어. 이 브로드소드, 나왈 일족의 상징을 네가 가질 자격이 충분하지. 자랑스럽게 차고 다녀. 이 검은 네 적들에게 공포가 될 것이고, 전투에서 널 든든히 지켜줄 거야.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "유르겐? 이게... 나를 위한 거야?...";
			link.l1 = "그래, Mary. "+sld.name+"  너를 위해 만들어 달라고 부탁했고, 바다 밑에서 특별한 철도 가져왔지. 이 재료의 무게와 강도는 어떤 강철도 따라올 수 없어. 예전에 Alan의 검을 만들 때처럼, 이번에도 내 영혼을 이 검에 담았어.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "무슨 말을 해야 할지 모르겠어... 고마워, Jurgen, 정말 고마워! 자랑스럽게 간직할게, 그리고 그에 걸맞는 사람이 될 거야, 맹세해, 그치? 나는 브로드소드로 자주 연습하지 않았는데, 이제부터는 할 거야!";
			link.l1 = "의심 없어, 아가씨.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... 잠깐만... 너는 내가 만난 사람 중에 최고야! 진짜 대단해, 그치? 이게 나한테 무슨 의미인지 알아? 이 검은 내가 받아본 선물 중에 최고야! 너는 이미 나한테 너무 많은 걸 해줬고, 두 번이나 내 목숨을 구해줬는데, 아직도 나를 놀라게 하네! 고마워, 내 사랑!";
			link.l1 = "이건 네가 받아야 마땅해, Mary. 그리고 내 마지막 숨이 다할 때까지 매일 널 놀라게 해줄 거야! 네 미소만 봐도 기쁨이 넘치고, 선물이 마음에 들어서 정말 다행이야.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(킥킥) 고마워! 정말 멋진 검이야, 그치? 이런 건 강한 손이 다뤄야 해... 빨리 이걸로 훈련하고 싶어!";
			link.l1 = "금방 익힐 수 있을 거라 생각해. 얼른 네 선실로 가서 직접 해봐, 그치?";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "그렇게 할 거야. 다시 한 번 고마워, 나리! "+pchar.name+"... 준비되면 오늘 밤에 나한테 와, 그치? ... (낄낄)";
			link.l1 = "물론이지, 아가씨. 저녁에 보자.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "여기, 한번 봐봐. 내가 바깥쪽 고리의 배 중 하나에서, 선장 상자 안에서 찾았어. 경험 많은 선원들은 모두 이 부적이 항해사에게 엄청나게 귀중하다고 하더라. 이 부적이 있으면 가장 심한 폭풍에서도 배를 지켜줄 수 있대. 많은 사람들이 사려고 했지만, 난 팔지 않았어... 너에게 주고 싶었거든, 자기야. 이 부적으로 바다에서 꼭 안전하길 바랄게.";
			link.l1 = "고마워, Mary! 정말 사려 깊네, 사랑해!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "정말? 마음에 들어? 와, 진짜 좋다! 나 너무 기뻐, 그치?";
			link.l1 = "이건 정말 희귀하고 값진 부적이야. 당연히 마음에 들어! 고마워, 자기야!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... 돌아왔네. 매일 수평선을 바라보면서 널 기다렸어, 그치? 결국 내게 돌아왔구나...";
			link.l1 = "그래, Mary. 약속대로 왔어. 안아 줄게, 자기야!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "아, "+pchar.name+"... 너는 상상도 못 할 거야! 나왈들이 네가 익사했다고 했어. 다들 네가 죽었다고 확신했지. 나는 계속 네가 살아 있다고 말했는데... 물론 아무도 내 말을 믿지 않았어. 이런 일이 다 벌어진 후라 내가 미쳤다고 생각했거든.";
			link.l1 = "Mary... 내 사랑! 왜 그래? 떨고 있잖아... 추운 거야?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "아니, 안 추워. 그냥... 여기서는 얘기하고 싶지 않아. 나중에 내 선실로 와, 그치? 너랑 단둘이 얘기하고 싶어. 지금 제독이랑 네이선을 만나러 가는 거야?";
			link.l1 = "그래. 상어랑 얘기해야 하고, 물론 다니엘을 네이선에게 데려가야 해. 오래 걸리진 않을 거야. 곧 보자, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "나... 나 정말 네가 오는 게 기대돼. 최대한 빨리 와 줘, 그치?";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! 드디어네. 우리 얘기 좀 해야 해, 그치!";
			link.l1 = "왜 그래, Mary? 뭔가 고민이 있는 것 같은데. 무슨 일 있었어?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "그녀가 우연히... "+pchar.name+", 네 배에 있는 저 창녀는 누구야?";
			link.l1 = "창녀? 다니엘 얘기하는 거야? 근데 너 이미 알--";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "아니, Danielle이 아니야. 네 배 갑판에서 어슬렁거리는 그 반쯤 벗은 금발 여자 말이야! 망원경으로 똑똑히 봤거든, 그치?";
			link.l1 = "아-아! 저 사람은 헬렌 맥아더야. 다니엘처럼 이 이상한 사건에 휘말린 사람이야. 지금은 내 부관으로 일하고 있어, 물론 임시로지만, 그치?";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "장교라고? 쟤가 네 장교야?!";
			link.l1 = "음, 그치? 그게 뭐가 어때서? Mary... 젠장, 너 질투하는 거구나!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "놀랄 일도 아니지, 그치?!... (울먹이며) 난 내내 너만 기다렸어. 너 때문에 잠도 못 잤는데, 넌 여기 어떤 계집애랑 같이 돌아오다니--\n";
			link.l1 = "Mary! 울지 마! 왜 이래? 넌 사람도 주저 없이 베어버릴 수 있는데, 왜 항상 눈이 젖어 있지... Mary, 그치? Helen은 그냥 임시로 같이 일하는 장교일 뿐이야. 우리가 같은 목표를 이룰 때까지만 함께하는 거고, 그 이상은 아니야.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I've been training hard with the broadsword you gave me, and I've mastered it perfectly!";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I've been training hard with rapiers and I've mastered them perfectly.";
			dialog.text = "(흑흑) 장교... 나도 당신의 장교가 되고 싶어, 그치? 나 싸울 수 있어, 알잖아! "+sTemp+" 그리고 나 총도 잘 쏴! 해상 기술은 없지만 금방 배워. 나 재능 있거든, 그치?";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(동의) Mary... 내가 직접 그 자리를 제안하려고 했어. 너만큼 열정적이고 능숙한 여자는 없어, 그치? 내 곁에 있어 줬으면 해!";
			link.l1.go = "adversary_hire";
			link.l2 = "(거절) Mary! 승선 장교가 되는 건 위험해! 네가 뭘 요구하는지 모르는 거야. 네 목숨을 걸 순 없어.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "못 해? 그 금발 창녀는 장교가 될 수 있는데 나는 안 된다고? 거짓말이야, 그치? "+pchar.name+", 너 그냥 나랑 있고 싶지 않은 거잖아! (울음) 그래서 그 여자애가 나보다 낫다는 거지, 그치?";
			link.l1 = "Mary, 너는 이해하지 못하고 있어!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "나도 알아! 그녀가 너를 볼 때 눈이 반짝이는 걸 봤어! 그녀는 그냥 장교가 아니야, 그치? 나도 그건 알아. (흐느낌) 물론, 나는 그녀랑 경쟁할 수 없어 - 그녀는 배를 다루는 법을 아니까...\n";
			link.l1 = "Mary, 무슨 말을 하는 거야?";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "끝났어... (울음) 가버려! 네 창녀한테나 돌아가! 난 여기 남을 거야...! 내 열쇠 내놔!";
			link.l1 = "하지만 Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "저리 가...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "정말이야? 나를 네 장교로 정말 원했던 거야, 그치? "+pchar.name+", 젠장, 네가 상상도 못할 만큼 정말 기쁠 거야! 너의 부관이 너무 되고 싶어... 하지만 그 금발이랑 같은 배는 절대 싫어, 그치?";
				link.l1 = "Mary, 그런데 왜 그러는 거야?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "정말이야? 나를 네 장교로 정말 원했던 거야, 그치? "+pchar.name+", 젠장, 네가 상상도 못할 만큼 정말 기뻐! 맹세해, 절대 실망시키지 않을 거야, 곧 알게 될 거야!";
				link.l1 = "세상에, Mary, 자기야, 넌 정말 소중해. 방금 전까지만 해도 울고 있었는데 지금은 얼굴이 환하게 빛나고 있잖아, 그치? 그리고 Mary, 넌 내게 그냥 또 다른 장교가 아니야. 넌 그 이상이고, 네가 날 실망시킬 거라고는 전혀 생각하지 않아.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "넌 그녀를 그냥 네 부하로만 볼지 모르지만, 그녀는 널 단순히 선장으로만 보진 않는 것 같아. 내가 그녀가 너한테 보낸 눈빛을 봤거든, 그 눈빛 내가 잘 알지, 그치? 하지만 그런 눈빛은 나만 네게 보낼 수 있는 거야.";
			link.l1 = "Mary, 자기야, 내가 이미 말했잖아, 나 그 여자한테 아무 감정도 없어, 그게 다야! 우리 사이엔 아무것도 없어! 맹세해, 젠장! 해안의 형제단 문제를 해결하려면 그녀의 도움이 필요해. 내가 그녀를 돕지 않으면 Jan Svenson이 토르투가를 점령하는 걸 도와주지 않을 거고, 난 그가 꼭 필요해!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", 자기야, 안아줘... 미안해. 난 널 믿어. 하지만 내가 그 여자 옆에 붙어서 네가 그 여자랑 희롱하는 걸 지켜볼 순 없어, 그치! 결국엔 내가 칼을 뽑아서 그 여자를 반으로 쪼개버릴 거야!";
			link.l1 = "난 네가 그럴 거라고 믿었어... 성질이 꽤 있네, 그치?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "내가 그녀를 죽였다면, 너는 날 떠났겠지... 그리고 그건, 평생 나 자신을 용서하지 못할 거야.";
			link.l1 = "그래서 어떻게 하라는 거야, Mary? 내가 그녀를 어떻게 해야 하지?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "그녀가 임시 임관이라고 했지. 네가 그녀를 육지에 내려주면, 특히 사람이 없는 섬이면 더 좋고, 바로 합류할게. (낄낄) 나는 세상 끝까지라도 널 따라갈 거야, 그치?\n그러니까 말해봐, "+pchar.name+" 그 사람... 정말 나보다 더 나은 거야?";
			link.l1 = "헛소리 마! 그런 말 그만해, Mary, 너보다 나은 여자는 없어!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "그럼 증명해 봐. 나는 너를 나누지 않을 거야, 그치? "+pchar.name+"! 너를 다른 사람이랑 나누느니 차라리 널 보내줄 거야, 그치?";
			link.l1 = "좋아, Mary. 거래를 하자. 지금 Helen을 떼어낼 수는 없어 – 내 임무에 꼭 필요한 사람이거든. 그녀의 문제를 도와주고, Isla Tesoro의 여왕으로 만들어 준 다음, 그녀를 떠나보낼 거야. 그러면 우리 사이를 막을 건 아무것도 없어, 그치? 한두 달 이상은 안 걸릴 거야. 그때까지 기다려줄 수 있겠어?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "할 거야, 그치? 분명히 말할게... 네가 나한테 돌아오면, 그건 그녀 대신 나를 선택한 거야. 근데 돌아오지 않으면... 그걸로 끝이야. 난 여기 남아서 내 가문을 세울 거야 – 캐스퍼 가문을!";
			link.l1 = "또 울어? Mary, 이제 그만해. 그치? '내 무리를 찾겠다'니... 너 참 바보 같아, 내가 꼭 돌아올 거라는 거 몰라? 너를 이런 썩은 배들 사이에 두고 갈 내가 아니지! 네가 울면 정의의 섬이 눈물바다가 되겠는걸, 그치?";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "그럼 최대한 빨리 돌아와, 그치?... "+pchar.name+", 키스해 줘, 제발...";
			link.l1 = "금방 돌아올게. 약속해!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = ""+pchar.name+", 나를 다시 찾으러 온 거야?";
			link.l1 = "당연하지! 내가 너한테 거짓말한 적 있어? 너랑 떨어져 있는 건 도저히 못 참겠고, 다시는 너랑 헤어질 생각 없어... 내 사랑.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "정말이야? "+pchar.name+"! 어디든 따라갈게! 절대 너한테 거짓말 안 해, 절대 배신 안 해, 맹세해!";
			link.l1 = "난 너를 믿어, 내 사랑... 나도 절대 안 그럴 거야."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", 자기야, 안아줘... 우리 함께할 거지? 약속해, 그치?";
			link.l1 = "그래, 우리는 함께할 거야, Mary. 영원히.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Danielle이랑 Nathaniel처럼, 그치?";
			link.l1 = "(웃으며) 그래, 딱 걔네들 같지, 그치?";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... 나 너를 사랑해! 네가 청혼하면 나 진짜 결혼할 것 같아...";
			link.l1 = "메리, 그치? ... 물론이지 - 나중에 얘기하자. 이 난파선 무덤에서의 너의 삶은 끝났어. 이제 여기서 데리고 나갈게. 내 배에 온 걸 환영해... 그리고 넓은 세상에 온 것도, 내 사랑!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "이 섬에서 마지막 밤을 함께 보내자, 세레스호에서. 우리 둘만. 아침이 올 때까지 널 어디도 못 가게 할 거야, 그치?";
			link.l1 = "음, 지금은 네 배에 타고 있잖아, 내 배가 아니라... 그러니까 네 명령을 따를게, Casper 선장.";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "알겠어, 나리!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! 나한테 좋은 생각이 있어...";
			link.l1 = ""+npchar.name+"? 여기 안전하지 않아. 내가 너더러 배에 있으라고 명령했잖아--";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+"젠장, 씨발, 어디도 안전하지 않아! 이 배에 화약이 얼마나 많은데, 정의의 섬 전체를 지도에서 지워버릴 수도 있다고! 그냥 들어봐, 그치?";
			link.l1 = "듣고 있어, 근데 빨리 말해 줘.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "해적 코르벳이랑 프리깃함 말이야. 아직도 우리가 자기네 편인 줄 아는 것 같아... 그 Knave 녀석, 그치? 그러니까 화약통 몇 개랑 도화선 챙겨서 프리깃함 타고 가자고.\n옆에 붙으면 도화선에 불 붙이고 화약통 던져주고 최대한 빨리 도망치는 거야. 그놈들 엉덩이를 산산조각 내버리고, 그다음에 코르벳에 올라타는 거지.";
			link.l1 = "위험하긴 한데... 그래도... 네 계획이 통할 수도 있겠어. 하지만 우리가 충분히 가까워질 때까지 놈들을 속일 수 있어야 해, 그치?";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "나는 해보자고 말할게, 그치? "+pchar.name+"";
			link.l1 = "그치? 한번 해보자. 얘들아! 화약통 세 개 가져와! 하하, 네 머리 정말 마음에 들어, 그치? "+npchar.name+"! 나 혼자서는 절대 이런 생각 못 했을 거야.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "나중에 고마워해도 돼... (윙크)";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "명령대로 보고하러 왔어, 나리! (킥킥) 무슨 일인데, 그치?";
			link.l1 = "잭맨의 배는 사보-마틸라 만에 있어. 중형 프리깃, 센튜리온이야. 이 배는 한때 호크스의 소유였으니, 선장 선실에 중요한 물건과 문서가 있을 거야... 우리가 반드시 올라타야 해.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "젠장... 우리 작은 새로 그걸 어떻게 할 생각이야? 내가 망원경으로 다 봤거든, Centurion에 남자랑 대포가 얼마나 많은지 다 봤어, 그치?";
			link.l1 = "네 말이 맞아. 잭맨 쪽이 우리보다 인원이 최소 두 배는 많고, 전부 노련한 살인자랑 용병들이야. 먼저 숫자를 줄이지 않고 바로 배에 오르는 건 미친 짓이지, 그치? 그리고 센츄리온의 대포 위력을 생각하면 장기 해전도 답이 아니고. 어떻게 해야 할지 모르겠어...";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", 아직 우리를 적으로 알아보지 못했지, 그치? 터크스에서 만난 그 바보들처럼 말이야? 또다시 화약 속임수를 써볼 수 있겠네...";
			link.l1 = "Mary, 내가 방금 말했잖아, 우리는 프리깃에 올라타야지 침몰시키는 게 아니라고, 그치?";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "그건 나도 알고 있어, 그치? "+pchar.name+"! 우리는 그 배를 침몰시키지 않을 거야. 빈 럼통 몇 개에 화약, 산탄, 짧은 도화선을 채워 넣을 거야. 그리고 센튜리온 옆에 붙어서 그 폭탄을 갑판 위로 던질 거야.";
			link.l1 = "하! 진짜로 그게 통할 거라고 생각해, 그치?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "왜 안 돼? 저놈들 배가 우리보다 현측이 높긴 하지만, 두세 명만 있으면 도르래랑 장치 써서 꽉 찬 술통 하나쯤은 쉽게 들어 올려 던질 수 있어. \n우리가 외치자고, '여기 Knave에서 온 공짜 럼주다!'라고. 술통은 놈들이 반응하기도 전에 폭발할 거야.";
			link.l1 = "폭발성 산탄이 갑판 위에 있는 모두를 갈기갈기 찢어놓겠지... 젠장, 솔깃한데.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "통 다섯 개 써, 그치? "+pchar.name+". 우리는 기습의 이점이 있어. 놈들은 전혀 눈치채지 못할 거야! 하지만 폭탄을 던진 다음엔 우리가 먼저 도망쳐야 해, 그치? 그래야 놈들이 우리 배에 올라타지 못하거든. 폭탄이 터지면 그때 다시 접근해서 우리가 놈들 배에 올라타는 거야.";
			link.l1 = "그리고 우리가 통을 던지기 전에 절대 우리 정체를 들키면 안 돼... 젠장, 저놈들한테 가까이 다가가는 게 쉽지 않겠어. Jackman은 Ghoul처럼 멍청이가 아니거든, 그치?";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "그러니까 제일 좋은 부적을 챙기는 게 좋을 거야, 그치? "+pchar.name+". 빨간 Mary를 믿어 봐. 해볼 만한 가치가 있어, 그치?";
			link.l1 = "좋은 말이야, 우린 잃을 게 없지... 그치? \n도화선 좀 준비해 줄래?";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "알겠어, 선장! 나만 믿어, 그치?";
			link.l1 = "Mary, 너 정말 멋지다!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "고마워, "+pchar.name+"! 실망시키지 않을게!";
			link.l1 = "나는 네가 배신하지 않을 거라는 걸 알아. 우리가 네 계획을 망쳐서 널 실망시키지 않길 바랄 뿐이야... 무장하자!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "여기 있었네! 찾느라 좀 애먹었어... 정말 대단했어, 선장! 그렇게 숨 막히는 점프는 처음 봤다니까! 완전 영웅이야! 근데 솔직히, 너 때문에 심장 멎는 줄 알았어. 언젠간 네 저런 짓거리 때문에 내가 죽을지도 몰라, 그치...\n그래서, 저 여자는 또 뭐야? 내가 잠깐 한눈 판 사이에, 벌써 저런 계집을 꼬셨네.";
			link.l1 = "Mary! 이 '쓰레기'는 Sea Foxes의 사령관인 Fox 대령의 딸, Catherine Fox야. 우리가 그녀를 앤티과로 데려가야 해.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "오, 정말이야? 얼마나 기쁜 일인지, 그치? 좋아, 그녀에 대해 얘기해 줘... 오늘 밤에. 우리 선실에서. 나랑. 단둘이서. 이제 가자, 서둘러야 해!";
			link.l1 = "(한숨) 너 없으면 난 어떻게 했을까, Mary? Catherine, 어서 와!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "오, 세상에, 깨어났네! 이 망할 놈아! 다시는 그렇게 나를 놀라게 하지 마!";
			link.l1 = "Mary... 자기야, 무슨 일이야? 머리가... 으윽...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "우리가 선장실에 들어갔을 때, 너는 시체처럼 바닥에 누워 있었어. 우리가 너를 들어 올려서 우리 배로 끌고 갔지 – 정말 아슬아슬했어, 그치? 갑판에 널브러져 있던 해골들이 다시 일어나기 시작했거든.\n 신이시여, 정말 무서웠어! 우리는 그 녀석들에게 아무것도 할 수 없었어! 밧줄을 끊고 도망치려 했지만, 놈들의 포격에 배가 심하게 부서져서 조종을 잃었지. 진짜 악마들이었어, 그치? 그리고는 순식간에 돛을 올리고 수평선 너머로 사라져 버렸어.\n 우리 배는 좌초됐고, 폭풍이 배를 완전히 부수기 전에 우리는 소형정으로 이 해변까지 왔어. 오늘 많은 동료들이 죽었지만, 그래도 배는 살아남았어... 간신히.";
			link.l1 = "수고했어, Mary... 너 없었으면 어쩔 뻔했을까?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "음, 어디 보자... 아마 익사했겠지? 그 배에 갇혔거나? 죽은 자들에게 찢겨 죽었을 수도 있고? 젠장, 나도 엿 먹고 너도 엿 먹어, 그치? "+pchar.name+", 나를 이렇게 놀라게 해서 그치!";
			link.l1 = "쉿, Mary, 조용히 해. 날 구해줘서 고마워, 사랑아. 내가 얼마나 오래 정신을 잃고 있었지?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "하루야. 네 상처를 치료하고 약도 먹였고, 럼주도 좀 부어줬어. 곧 나아야 해, 내 앞에서 죽으려고 하지 마, 그치?";
			link.l1 = "절대 안 그럴게, 자기야. 하지만... 예전만큼은 아니야...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "예전보다 상태가 안 좋아 보이네... 그녀였어, 그치? "+pchar.name+"그게 '플라잉 더치맨'이었어? 이야기는 들었지만, 이렇게 될 줄은 상상도 못 했어...\n왜 우리를 쫓아왔지? 그리고 왜 승선하기 전에 포격을 안 했던 거야?";
			link.l1 = "그 선장은 부적을 원했어, 내가 투투아타팍, 그 인디언 주술사와 얘기했던 바로 그거 말이야. 그래서 우리 배에 올라탄 거지. 하지만 그 선장이 부적을 손에 넣자마자, 우린 더 이상 멀쩡할 필요가 없어졌어...\n끔찍했어! 죽은 자들이 조종하는 배라니! 믿을 수가 없어... 카리브 해에서 더한 것도 봤다고 생각했는데.";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "결국 '플라잉 더치맨'이 너 같은 사람을 잡으러 올 거란 건 뻔했지, 그치? 젠장, 그거 보고 나 교회 다시 나갈 뻔했잖아!";
			link.l1 = "네 기분 알아. 나도 그 인디언 마을로 돌아가서 투투아타팍에게 무슨 일이 있었는지 말해야 해, 그치? 그 배가 우리를 공격한 건 바로 그 부적 때문이야! 저 붉은 피부 악마가 도대체 왜 그 산 자의 죽은 놈들이 그걸 원했는지 설명 좀 해줬으면 좋겠네, 그치?";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "그치? 하지만 조심해. 너 아직 엉망이야.";
			link.l1 = "너만 있으면 난 아무 약도 필요 없어. 그리고... Mary, 사랑해...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "나도 사랑해, 자기야... 우리가 살아 있어서 정말 다행이야!";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", 네 품에 안겨 있는 것보다 더 행복한 건 없어, 그치? 가자!",""+pchar.name+", 가능하다면 깨어 있는 모든 순간을 너와 함께하고 싶어, 그치? 가자!");
			link.l1 = RandPhraseSimple("넌 최고야, 내 사랑...","넌 정말 멋져, 내 사랑...");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("음, 너 정말 대단했어... 항상 그렇지, 그치?","정말 멋졌어!");
			link.l1 = RandPhraseSimple("널 기쁘게 해줄 수 있어서 좋아, 내 사랑...","난 너를 사랑해, Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", 네 품에 안기는 것보다 더 좋은 건 없겠지, 그치... 하지만 지금은 때가 아니야 - 저 쓰레기 Thibaut가 도망치기 전에 잡아야 해.";
				link.l1 = "언제나 네 말이 맞아, 내 딸...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", 네 품에 안겨 있는 것보다 더 행복한 건 없어, 그치?\n가자!",""+pchar.name+", 가능하다면 매 순간 너와 함께하고 싶어, 그치? 가자!");
			link.l1 = RandPhraseSimple("너는 최고야, 내 여자...","넌 정말 멋져, 내 불타는 머릿결의 미녀야...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", 우리 섹스한 지 너무 오래됐잖아... 너 완전히 나 잊어버린 거지, 그치? 오늘 밤엔 방 잡고, 걱정은 내일로 미루자.",""+pchar.name+", 나를 완전히 잊은 거 아니야, 그치? 자기야, 나랑... 단둘이 있고 싶어. 오늘 밤 방 하나 잡자, 그치?",""+pchar.name+", 어디 갔었어? 너랑 밤새 같이 있고 싶어서 죽을 지경이야, 와인도 마시고 좀 쉬자. 너 그동안 바다에만 있었지, 완전히 나 잊은 거 아니야!");
			link.l1 = "Mary, 자기야, 무슨 소리야, '나를 완전히 잊었다'니? 바보 같은 녀석... 하지만 정말 너무 바빴어 – 내 손이 필요한 일이 끝이 없었거든. 용서해 줘, 내 사랑. 위층으로 가자, 오늘 밤은 온전히 너만 바라볼게. 세상일은 잠시 미뤄도 돼!\n";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("오늘은 안 돼, 그치? 할 일이 너무 많아.","Mary, 자기야, 내가 널 잊었다고 생각하다니, 그치? 우리 나중에 꼭 같이 시간 보낼 거야. 지금은 할 일이 있잖아, 그치?"),RandPhraseSimple("항상 네 생각뿐이야, Mary. 하지만 지금은 방심할 수 없어.","Mary "+npchar.lastname+", 오늘은 이럴 시간 없어."));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "(한숨) 알았어, 그럼 내 선실에서 혼자 놀아야겠네... 그치, 선장.";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "찰스...";
			link.l1 = "Mary, 자기야, 무슨 소리야, '나를 완전히 잊었다'니? 바보 같은 녀석... 하지만 정말 내가 너무 바빴어 – 내 손이 필요한 문제가 끝이 없거든. 용서해 줘, 내 사랑. 위층으로 가자, 오늘 밤은 온전히 네 거야. 세상일은 잠시 미뤄도 되잖아!\n";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "아, 저기 있네! 이제 나 안 좋아하는 거지, 그치? 말해 봐!";
			link.l1 = "뭐?! Mary, 이게 무슨 말도 안 되는 소리야? 왜 그렇게 생각하는 거야?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "그럼 왜 그 창녀들, 그 사창가 여자들한테 들락거린 거야? 나 다 알고 있어, 나한테 거짓말하지 마! 우리 사랑 나눌 때 내가 마음에 안 드는 거라도 있어, 그치? (울면서) 말해봐...";
			link.l1 = "Mary, Mary... 진정해, 제발, 내 아가씨. 그치? 내가 몇 번 사창가에 간 건 사실이야, 하지만 정말 일 때문에였어. 재미 보려고 간 게 아니야!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "위층 침실에서 무슨 '업무'를 봤다는 거야? (흐느낌) 거짓말이잖아, 그치? "+pchar.name+"!";
			link.l1 = "Mary, 제발 이러지 마, 부탁이야... 정말로 난 그 사창가 주인하고 볼일이 있었어. 그리고 그래, 위층에 몇 번 올라가긴 했지 - 마지막엔 총독 나리의 개인적인 일 때문이었어. 결혼반지를 찾아달라고 부탁하셨거든. 각하의 부탁을 어떻게 거절하겠어?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "...";
			link.l1 = "그리고 내가 어떻게 안주인에게 위층 침대 밑을 봐야 한다고 설명할 수 있었겠어? 못 했지. 그래서 어쩔 수 없이 위층에 올라가려고 하룻밤 창녀를 사야 했어...\n두 번째는, 상인이 거기서 선박 서류를 잃어버렸다고 하더라고. 또다시 방을 뒤지려고 여자를 사야 했지 - 그리고 실제로 서류를 찾아냈고, 그 대가로 꽤 많은 돈을 받았어...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "...";
			link.l1 = "그리고 세 번째로는 여기 주둔지 사령관을 도왔어. 주점 여자들에게 주둔군 장교에 대해 물어봐야 했지. 그 장교가 간첩질과 해적들과 내통한 혐의를 받았거든. 결국 우리가 그를 잡았고, 나는 두둑한 보상을 받았지...\n";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "...";
			link.l1 = "이제 알겠어? 내가 말했잖아, 다 일 때문이었다고. Mary, 내가 사랑하고 필요한 사람은 너야. 난 너한테만 충실해, 맹세해! 내가 너 같은 사람이 있는데 어떻게 더러운 항구 창녀랑 잘 수 있겠어, 그치? 그런 생각을 하다니, 어떻게 그럴 수 있어!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = "... 내 평생 들어본 것 중에 제일 말도 안 되는 헛소리 같은데. 하지만... "+pchar.name+"... 정말 진실을 말하는 거야? 내 모르게 딴 여자랑 잔 적 없지?";
			link.l1 = "Mary, 자기야, 아니야, 진짜야, 맹세해. 내가 사랑하는 여자는 너 하나뿐이야, 그치? 이리 와, 자기야. 안아줄게... 눈물 닦고, 제발, 질투하지 마! 네가 원한다면, 난 다시는 사창가 쳐다보지도 않을게!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "그래, 그게 내가 원하는 거야!... "+pchar.name+", 난 네가 좋아서 질투나는 거야... 그리고 널 잃고 싶지 않아, 그치? 어떤 계집이 너한테 웃기만 해도, 내 칼이 그년 배 속에 들어갈 거야!";
			link.l1 = "세상에, Mary, 진정해... 아무도 죽일 필요 없어! 널 잃지 않을 거야, 그치? 약속할게. 괜찮아, 진정해. 넌 내 유일한 여자야—그리고 세상에서 제일 멋진 여자지! 나를 믿어, 그치?";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", 무슨 이상한 질문이야? 나 너 사랑해. 네가 날 구해줬잖아. 내가 널 혼자 거기 보내줄 거라고 진짜 생각해? 그런 생각도 하지 마, 그치? 나도 같이 갈 거야! 언제 출발해?";
			link.l1 = "맞아, 자기야. 내가 어떻게 그걸 의심할 수 있겠어? 우리가 갈 때 말해줄게. 먼저 제대로 준비해야 해.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "준비됐어, "+pchar.name+". 지옥 끝까지라도 널 따라갈 거야!";
			link.l1 = "고마워, 내 사랑...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.MarySexBlock = "true"; // fix 22-03-20
			dialog.text = "이번엔 뭐야, 선장? 스페인 놈들? 해적들? 아니면 더 끔찍한 것들?";
			link.l1 = "더 심각해, Mary, 훨씬 더 심각해. 총독이 악명 높은 창녀를 방문할 생각이래, 그리고 나는 주목받는 인물로 그를 따라가야 해. 지루한 대화, 터무니없이 비싼 와인, 그리고 재미없는 귀족들, 그치?";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "정반대야. 귀족 부인이 주최하는 사교 모임 초대장이었어. 각하께서 나에게 동행해 달라고 하셔서 좀 놀랐지만, 솔직히 말해서 이런 기분 전환이 기대돼.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "오-호! 정말 더 심하네! 창녀라니! 강화 와인! 사교라니! 그치, 완전 고문 같잖아, "+pchar.name+", 이 망할--";
			link.l1 = "Mary, 진정해, 제발. 내가 거기 가는 게... 그치만, 그곳이 창관은 아니야! 아니... 사실 창관이긴 한데, 내가 귀족이고 약속을 지키는 남자가 아니라면 벼락 맞아도 할 말 없어. 우리가 함께 겪은 일들이 이렇게 많은데, 정말 날 못 믿겠어, 그치? 총독이 작은 부탁 하나만 들어달라고 해서, 그걸 들어주러 가는 것뿐이야!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "그래, 그런 '귀족' 몇 명에 대해 들어본 적 있어, 그치? 너랑 같이 있는 것도 봤고. 창녀질이 걔네들한텐 밥벌이지. '상류' 사회, '고상한' 오락이라니 웃기고 있네! 결혼했다고 해서 이런... 으... '여자들' 찾아오는 걸 멈추진 않더라. 난 너는 좀 다를 줄 알았는데, 그치? "+pchar.name+". 뭐, 너희 '귀족'들은 내 때 안 벗긴 엉덩이나 핥으라고 해, 그치?";
			link.l1 = "Mary, 잠깐만! 젠장...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "우리 둘 다 휴가 받을 만하지. 헤헤, 빨간 코트 입은 여자를 보면 사람들이 감당할 수 있을까? 구석구석에서 수군거릴 거 상상해 봐! 누군가는 분명 기절할 거야—그거 재밌겠지, 그치?";
			link.l1 = "Mary, 내 사랑, 여긴 여자를 데려올 만한 파티가 아니야... 적어도 너 같은 여자는 말이지. 좀 복잡한데, 설명할게--\n";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "나 같은 여자가? 솔직히 말해봐. 난 그 가발 쓴 자식들한텐 안 어울려, 그치? 너무 단순하고, 너무 천한 출신이야. 화려한 파티나 명예로운 샤를 드 모르 나리한텐 안 어울린다고, 그치?";
			link.l1 = "아니, 전혀 아니야. 너는 정말 대단하고, 우리가 주변 사람들에게 어떤 인상을 주든 난 신경 안 써. 총독은 언제나처럼 내 도움으로 자기 문제를 해결하려고 하지. 나는 그에게 귀중한 전리품 같은 존재가 될 거야. 귀족 백수들을 감동시키기 위한 흥미로운 손님 말이지.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "아니, "+pchar.name+", 괜찮아, 이해했어. 귀족들끼리만 어울리고, 잡놈들은 밖에 두라는 거지. (고개 숙임) 사교 모임 잘 즐기시길 바라, 엉덩이 나리. 겸손한 땅으로 돌아오면 그때 얘기하자, 그치?";
			link.l1 = "Mary, 잠깐만! 아, 젠장...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "진심으로 사교 모임 잘 즐기시길 바라요, 엉덩이 나리. 겸손한 땅으로 돌아오면 그때 얘기하자, 그치?";
			link.l1 = "Mary야, 아 진짜, 그치?";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "이것 좀 봐, 그치? 우리 상류사회에 빠진 선장님이시네!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "넌 하루 종일 사창가에 쳐박혀 있다가 이제 온 마을이 떠들썩해졌어. Charles, 내가 너 엉덩이에 나르왈을 쑤셔 넣지 말아야 할 이유 딱 하나만 대봐.";
			link.l1 = "Mary, 나중에 다 설명해 줄게. 지금은 결투 준비를 해야 해. 내가 살아남으면 그때 죽여도 돼, 그치? 그동안 우리 새 배 좀 잘 부탁해 줘. 어젯밤 카드 게임에서 상으로 얻은 배야, 그치?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "배는 집어치우고, 이 결투가 뭐야? 여기 사람들 말 들어보면, 네가 왕자나 교황이랑 싸우는 것처럼 굴던데. 도대체 무슨 일이 벌어지고 있는지 말해 봐!";
			link.l1 = "이 남자는 아주 영향력 있는 귀족, 드 레비 반타뒤르 백작의 사생아야. 그가 나에게 결투를 신청했지. 나는 그를 다치게 하지 않고 결투에서 이겨야 해 – 그의 아버지 분노를 피하려면, 그치?";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "내가 네가 방금 딴 그 낡은 배에서 엉덩이 깔고 앉아 있으라고? 미쳤어, Charles?";
			link.l1 = "이렇게 할 수밖에 없을 것 같아. 총독이 나한테 귀족 장교 둘을 세컨드로 붙여줬거든, 나중에 오해가 없게 하려고 말이야. 공식적인 결투의 신뢰를 위해서 너나 다른 선원들은 데려갈 수 없어. 이건 너무 심각한 일이야, 미안해.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "... 이제 내가 뭘 할지 알아? 저 빌어먹을 배에 올라가서 제대로 취할 거야. 너 하고 싶은 대로 해, 그치? 하지만 한 가지는 맞아. 그 고귀한 개자식이 널 못 죽이면 내가 직접 죽일 거야.";
			link.l1 = "Mary, 다 잘 될 거야, 나만 믿어. 이제, 잠깐만... 젠장! 또 시작이네, 그치?";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "저기 있네! 오늘 하루 종일 너한테서 한 마디도 못 들었잖아! 시장에서 소문 듣고 걱정됐어. 네가 배랑 여자 걸고 도박했다더라, 심지어 어떤 왕세자나 교황이랑 결투까지 벌였다고 하던데! 도대체 무슨 일이야, 그치?";
			link.l1 = "복잡해, Mary. 설명하려면 시간이 좀 걸릴 거야. 그래도 프리깃 한 척은 손에 넣었어, 그치? 내가 그 배의 전 주인과 문제를 해결하는 동안 네가 그 배를 돌봐야 해.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "결투가 있다는 거야?! 이전 주인은 누구야? 왜 그 사람과 싸우는 거야?";
			link.l1 = "복잡한 이야기지만, 간단히 말하면: 내가 그의 배와 그의... 여자를 땄어. 그는 공개적으로 내가 속였다고 비난하면서 결투를 신청했지. 이 남자는 아주 영향력 있는 귀족, 드 레비 반타뒤르 백작의 사생아야. 나는 그를 다치게 하지 않고 어떻게든 결투에서 이겨야 해.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "소문이 진짜였던 거야? 배를 걸고 도박하는 건 이해하겠는데... 여자를 두고 도박했다고? 정말이야?";
			link.l1 = "젠장, Mary, 전혀 그런 게 아니야! 그 남자는 총독한테서 그녀를 뺏었고, 나는 그 남자에게서 다시 그녀를 되찾아서 풀어주려고 한 거야, 그치? 그 이상 아무것도 없어, 맹세해!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "글쎄, 너희 귀족들한텐 이게 당연할지 몰라도, 난 아니야, 그치! 하고 싶은 대로 해, 하고 싶은 말 다 해... 걔 때문에 죽으러 가든 말든 네 맘대로 해! 난 말이지, 네가 따낸 그 빌어먹을 배에 가서 내 다락방을 럼으로 완전히 뒤죽박죽 만들어버리고 싶거든. 젠장, 너 정말... "+pchar.name+", 우리 사이가 진짜였고... 영원할 거라고 믿었어. 내가 너무 많은 걸 바랐던 거겠지, 그치?";
			link.l1 = "Mary, 난 그 여자 따위 신경도 안 써! 제발 잠깐만 기다려 줘... 젠장! 또 시작이네, 그치?\n";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, 나를 구하러 왔구나! 난 알았어, 한 번도 의심 안 했지, 그치? 이렇게 만나서 정말 기뻐!";
			link.l1 = "나도 그래, Mary! 이 모든 일이 나를 미치게 했어... 네가 무사해서 정말 다행이야!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "그런데, 네가 대체 뭘 한 거야? 나를 이렇게 쉽게 풀어주다니, 제대로 싸움도, 총질도 없이 말이야! 아, 그리고 내가 끌려나올 때 갑판에서 어떤 여자를 봤어. 무슨 일이 있었던 거야, Charles?";
			}
			else
			{
				dialog.text = "도대체 무슨 짓을 한 거야, 나를 이렇게 풀어주게 만들 정도로? 싸움도 없었고, 총도 안 쐈고, 아무 일도 없었잖아! 내가 끌려 나올 때 갑판에 영국 공작새들이 몇 명 있던데. 그게 다 뭐야, Charles?";
			}
			link.l1 = "중요한 건 네가 다시 내 곁에 있다는 거야. 내가 너를 지키지 못했어, Mary. 정말 미안해! 네 마음속에서 날 용서해줄 수 있길 바랄 뿐이야. 우리가 이렇게 끝난 게 너무 싫어.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "이미 했어. 나도 미안해, 그치? 네가 그 여자랑 얽힌 일에 내가 너무 감정적으로 굴었지... 그날 밤에 제대로 망을 봤어야 했는데—그랬으면 우리가 그렇게 쉽게 당하지 않았을 거야! 내가 정말 바보였어!";
			link.l1 = "과거는 과거야. 난 너를 사랑해, 그리고 다시는 그렇게 널 두고 떠나지 않을 거야. 약속해!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "의심해서 미안해, Charles. 어쩌면... 네가 뭘 했는지 정확히 모르는 게 더 나을지도 모르겠어, 그치? 우리 다시 함께 있으니까 그게 제일 중요한 거야.";
			link.l1 = "너한테 숨길 비밀은 없어. 다 말해줄게...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "이런 이야기가 다 있네... 다른 사람들은 절대 안 믿을 거야, 그치? 내가 알았어! 네 '사교' 밤이 수상쩍다는 거! 그 잘난 귀족 공작새들... 냉혈한 놈들! 그래도 너만은 다를 줄 알았어 - 네가 남들과는 다르다는 거, 내가 맞았지, 그치?";
				link.l1 = "밖에 있는 많은 사람들이 나를 훨씬 더 나쁘게 생각할 거라고 확신해. 동화 속 괴물 같은 존재로 말이야.";
			}
			else
			{
				dialog.text = "정말 대단한 이야기네... 다른 사람들은 아무도 안 믿을 거야, 그치? 내가 알았어! 네 '사교'의 밤이 뭔가 수상하다고 느꼈다니까! 정치, 스파이, 음-모-론까지—그런데도 너는 또 한 번 우리 모두를 구했어, 그치? 내 영웅이야.";
				link.l1 = "그건 잘 모르겠어... 아마 몇 주 안에 영국과 전쟁이 시작될 거야. 하지만 난 해야 할 일을 했어, Mary. 너는 내게 전부야.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "사람들이 뭐라고 생각하든 상관없어; 그렇다면 넌 내 괴물이야, Charles! 사람들이 싫어하면 내가 직접 얘기할게. 난 항상 네 곁에 있을 거야, 그치?";
			}
			else
			{
				dialog.text = "알아, Charles. 항상 알고 있었어... 그래도 네가 직접 말해주니 좋네. 그리고 나도 언제나 네 곁에 있을 거야, 그치!";
			}
			link.l1 = "난 한 번도 의심하지 않았어, Mary. 가자, 녀석들이 걱정하고 있어. 이제 출항해서 이곳을 벗어나야지. 네가 다시 내 곁에 있고, 저 수평선이 우릴 기다리고 있어...\n";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "알겠어, 선장님!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, 정말 너 맞지? 난 거의 모든 희망을 잃을 뻔했어, 그치? 세상에, 너 정말 너무 보고 싶었어! 제발, 제발 용서해 줘!";
			link.l1 = "아니, 미안해, 전혀 예상 못 했어... 정의의 섬까지 와줘서 고마워, Mary! 정말 기뻐!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "용서 얘기가 나와서 말인데... 솔직히 말하면, 너를 쏴버릴지 안아줄지 고민 중이야. 대체 무슨 일이 벌어지고 있는지 제대로 말해, 그치?";
			link.l1 = "널 사랑해, Mary. 이것만이 내가 너에게 전하고 싶었던 전부야.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "글쎄, 그게 다 설명이 되는 건 아니지만... 젠장, Charles. 나도 너를 사랑해, 그치? 아, 드디어, 이제야 너를 내 곁에 두게 됐어!";
			link.l1 = "그리고 우리에게 주어진 시간을 쓸데없는 이야기로 낭비하고 싶지 않아. 나랑 같이 가, 그치? 오늘 밤엔 절대 널 두고 가지 않을 거야. 하늘이 이 불쌍한 마을 위로 무너진다 해도 말이야. 다시는 널 떠나지 않을게. 절대로.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "아마... 네가 뭘 했는지 내가 굳이 알 필요는 없겠지, 그치? 우리가 다시 함께 있다는 것만으로 충분하니까...";
			link.l1 = "나 너한테 숨기는 거 없어. 다 말해줄게...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "이 말은... 그 마르키즈가 널 데려오는 데 도와줬다는 거야? 그리고 너, 영국이랑 프랑스 사이에 전쟁 일으킬 뻔했다고? 오해하지 마, 이거 정말 로맨틱하긴 한데, 그치? 근데 이제 어떻게 되는 거야?\n";
			link.l1 = "나도 모르겠어, Mary. 우린 다시 함께 있으니, 그거면 됐어. 위에 있는 자들이 모든 걸 덮어버리지 못한다면... 뭐, 나는 왕관을 위해 내 의무를 다할 준비가 되어 있어.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "그리고 그대의 후작부인은? 그녀도 데려왔어? 포르투갈인은 그녀를 아주 높이 평가하더라. 그대가 바스티유 성처럼 그녀의 유혹을 견뎠다고 내게 장담했어. 나도 믿고 싶어, 그치? 하지만 네 입으로 직접 듣고 싶어.";
			link.l1 = "Madame Botot랑 나 사이엔 아무 일도 없어, Mary. 내가 그녀를 도왔고, 그녀도 나를 도왔을 뿐이야, 그치?\nBartholomew 얘기가 나와서 말인데, 그는 어디 있어?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "이미 떠났지, 그치? 나를 여기 데려다주자마자 바로 돛을 올렸어. 난 그 빌어먹을 창관엔 절대 안 간다고 맹세했거든, 그치? 그래서 그 사람이 나한테 방을 빌려주고, 몇 주치 선불까지 내주고는 그냥... 떠나버렸어. 아, 맞다! 너한테 줄 편지가 있어!";
			link.l1 = "편지라고? 포르투갈인 바르톨로메오한테서 온 거야? 이거 뭔가 불길한데, 그치?...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "계속 읽어봐. 나는 선원들 좀 보고 올게. 아마 걱정하고 있을 거야. 모두 무사한 거지? 아래에서 한두 잔 마셔도 괜찮지? 내가 돌아올 때까지 또 말썽 피우지 마, 그치?";
			link.l1 = "알겠어, 하지만 제발 애들 좀 조심해 줘, Mary 그치? 오늘 밤엔 취한 놈들 배로 나르는 대신 너랑 같이 있고 싶으니까. 이런, 아직도 네가 돌아온 게 믿기지 않아!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "너랑 나, 해변, 그리고 좋은 와인이라니 - Charles, 이거 정말 낭만적이야! 우리 이런 거 더 자주 하자, 그치?";
			link.l1 = "마음에 들어서 다행이야. 이제부터는 이런 시간을 더 자주 함께 보내게 될 것 같아, 그치?";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "무슨 말이야? 배에 무슨 일이라도 생겼어? 왜 무릎 꿇고 있는 거야?";
			link.l1 = "내가 널 사랑하니까, Mary. 너도 알고, 나도 알고, 온 세상이 다 알지, 그치?\n그래서 지금 여기, 바다와 하늘을 마주한 이 자리에서, 나는 너에게 묻고 싶어, Mary Casper. 우리 사람들과 신 앞에서 내 곁에 서 줄 영광을 내게 허락해 줄 수 있겠니?\n나, Charles de Maure, Chevalier de Monper가 너에게 청하는데... 내 아내가 되어 줄래?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "나 이걸 꿈꿨어, 그치? 근데 진짜로 이렇게 되다니... 나... 내 대답 알잖아, Charles, 그치? 아, 젠장!";
				link.l1 = "하하! 신경 쓰지 마, 그냥 포도주일 뿐이야. 그리고 난 이 셔츠를 원래 좋아하지도 않았거든, 그치?";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, 물론이지! 그래, 그래, 천 번이라도 그래!!! 너도... 이곳도... 나를 더 행복하게 만들 수 있는 건 아무것도 없어!!! 세상에, 나 지금 너무 웃어서 볼이 터질 것 같아, 그치?";
				link.l1 = "넌 나를 행복하게 해, Mary. 너를 위해 건배할게, 내 불타는 카리브 해의 태양, 그치?";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "너를 위해 건배할게, 내 선장이자 미래의 남편, 그치? 내 인생에 일어난 최고의 일이 바로 너야!";
			link.l1 = "하지만 이건 시작일 뿐이야, 그치? 우리를 위해! 그리고 우리 둘의 미래를 위해! 앞으로 할 일이 정말 많아, 그치?";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "너에게 건배할게, 내 선장이자 미래의 남편, 그치? 내 인생에 일어난 일 중에 네가 제일 최고야!";
			link.l1 = "하지만 이건 시작일 뿐이야, 그치? 우리를 위해! 그리고 우리 둘의 미래를 위해! 앞으로 할 일이 정말 많아, 그치?";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, Abbot Benoit한테 가서 얘기 좀 해 줘, 그치? 근데 나 드레스는 안 입을 거야. 기분 나빠하지 않았으면 해.";
			link.l1 = "Mary, 나는 네가 어떤 옷을 입어도 사랑해... 뭐, 알지 그치? 네가 입고 싶은 건 뭐든 입어도 돼. 그게 불만인 사람 있으면 나한테 말하라고 해! 하지만 손님들이랑 의식에 대해서는 너랑 상의하고 싶어.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "있잖아, 우리 행복을 진심으로 기뻐해 줄 사람들 대부분은 이 정의의 섬 근처에도 못 오게 할 거야, 그치? 교회는 말할 것도 없고. 그러니까... 여기서 착한 시민들 앞에서 결혼식 올리고, 그다음에 Isla Tesoro로 가서 진짜 친구들이랑 제대로 축하하자! 어때, 그치?";
				link.l1 = "좋은 생각이야! 하자, 그치? 내가 Benoit 수도원장님이랑 얘기해볼게. 누가 올지 정하고, 초대장도 보내야 하고... 할 일이 정말 많네!";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "있잖아, 나는 선원 녀석들 말고는 친구가 별로 없어. 그러니까 네가 마음에 드는 애들 초대해 줘. 그러면 나는 행복할 거야, 그치?";
				link.l1 = "네 말대로 할게, 자기야. 내가 베누아 아빠스님이랑 이야기해서 모든 걸 준비할게. 너라면 정말 멋진 결혼식 받을 자격이 있지, 그치?";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "손님들은 걱정하지 마, 내가 다 알아서 할 거야, 그치? 우리 친구들에게 편지도 쓰고, 모든 걸 준비할게. 그런데 먼저 말해 봐, 우리 결혼식에 누가 오면 좋겠어?";
			link.l1 = "내 이상은 너랑 나, 그리고 우리 가장 가까운 친구들이야. 여기 마르티니크의 공식적인 얼굴들만 보고 나면, 우리도 진심이 그리워질 테니까, 그치?";
			link.l1.go = "LongHappy_10";
			link.l2 = "오늘을 잊지 못할 하루로 만들자. 모두 불러와! 누구도 빠지면 안 돼!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "있잖아, 해 질 무렵, 망루 갑판에서 선 chaplain이 주관하는 선상 결혼식이면 난 충분해, 그치? 하지만 네가 이걸 원한다면, 우리 제대로 축하하자! Charles... 나 눈물 날 것 같아. 안아줘, 그치...\n";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "그치, 나 이제 진정했어. 미안, 이게 다 처음이라 그래. 하지만 Charles, 나도 조직에 참여하고 싶어. 그리고 우리 친구들을 위해 파티도 열어야 해, 그치? 근데 선원 전부가 교회에 들어가긴 힘들 것 같아. 내가 선술집이랑 얘기해 볼게, 근데 술이랑 돈이 필요해—선원들이 얼마나 파티를 좋아하는지 알잖아, 그치?";
			link.l1 = "그치? 그렇게 하자. 내가 뭘 준비해야 해?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "내 생각엔, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" 페소면 충분하겠지, 그치? "+sti(pchar.questTemp.LongHappy.MarryRum)+" 럼 통이라니 - 술이 떨어지는 것만큼 끔찍한 건 없지! 다 모으면 선술집으로 와. 나머지는 내가 알아서 할게.";
			link.l1 = "알았어, 자기야, 거기서 보자.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "알겠어. 하지만 샤프타운에도 들러서 준비해야 해, 그치? 럼주 오십 통이랑 와인 몇십 통이면 충분할 거야, 그치? 그래도 혹시 모르니까, 삼십만 페소가 필요해.";
			link.l1 = "많긴 하지만, 그럴 만한 일이니까. 내가 어떻게든 마련할게, 걱정 마. 이제 나는 수도원장님을 뵈러 갔다가 샤프타운에 갈 거야.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "좋아, 다 같이 모으자, 그치? 하지만 샤프타운에도 가서 준비해야 해 – 갤리온 한 척 분량의 술이 필요하거든! 럼 백 통에 와인 오십 통이면 충분할 거야. 그래도 혹시 모르니까 오십만 페소도 챙길게. 술 떨어져서 파티가 끝나면 안 되잖아, 그치?";
			link.l1 = "그치, 우리 친구들이 목말라 죽게 둘 순 없지 - 내가 다 준비할게, 걱정 마! 이제 나는 수도원장님을 뵈러 갔다가 샤프타운에 갈 거야.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "모든 준비가 끝났어, Charles. 술을 내리게 하고, 그다음에 현지 선술집에 가서 남작을 만나 초대장을 건넬 거야. 여기서 기다려, 그치?";
			link.l1 = "키는 네가 잡아, 자기야! 난 그냥 어딘가에서 빈둥거릴게. 정의의 섬 정글로 원정 가는 게 결혼 준비보다 쉽다고는 상상도 못 했어, 그치?";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "여기서 할 일은 끝났어, Charles, 그치? 내가 다 준비했어. 믿어봐—정말 멋질 거야! 근데, 한 가지만... 일주일 전에 잔치하다가 여기 선술집이 불타버렸거든. 하지만 거의 다시 지어졌어, 전보다 더 크고 좋아! 우리 모두 들어갈 수 있을 거야.";
			link.l1 = "또 다시 불태우지 않길 진짜 바란다. 난 올드 우드페커 정말 좋아했거든! 그치? 아무튼, 아직 할 일이 많아. 이제 출항할 시간이야. Mary... 너 정말 최고야, 그거 알지, 그치?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "그래서... 이제 시작인 거지? 손님들도 다 왔고, 교회도 준비됐어. 우리가 보통 부부들보다 더 가까운 거 아는데, 이건 그냥 멋진 예배당에서 하는 몇 마디 큰 말일 뿐이잖아. 근데 젠장, 그 오래된 인디언 도시에서도 이 정도로 긴장하진 않았어, 그치?";
			link.l1 = "분명 완전히 정상인 거야, 자기야; 나도 긴장돼. 아마 베누아 아빠트가 기다리고 있을 거야, 내가 가서 예식이 언제 시작되는지 알아볼게.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "좋아, 잠깐 마을을 좀 돌아다닐게, 머리를 식혀야 하거든, 그치? Charles... 이제는 돌아갈 수 없다는 거, 너도 알지?";
			link.l1 = "Mary, 내 사랑, 우리가 만난 순간부터 나는 이미 돌아갈 수 없었어. 이 날을 온 마음으로 기다려왔지. 걱정하지 마, 모든 게 잘 될 거야.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "그치.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "그치.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "그치.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "나, 샤를 앙리 드 모르, 몽페르 기사, 너, Mary Casper를 내 아내로 맞이하여, 오늘부터 앞으로 좋을 때나 나쁠 때나, 부유할 때나 가난할 때나, 아플 때나 건강할 때나, 죽음이 우리를 갈라놓을 때까지 함께하겠노라. 하나님의 거룩한 법에 따라, 우리 주님 앞에서 이 맹세를 하노라.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "나, Mary Casper는 너, Charles de Maure를 내 남편으로 맞이해. 오늘부터 앞으로 좋을 때나 나쁠 때나, 부유할 때나 가난할 때나, 아플 때나 건강할 때나, 죽음이 우리를 갈라놓을 때까지 함께할 거야. 하나님의 거룩한 법에 따라, 주님의 앞에서 이 맹세를 해, 그치?";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "아멘.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "이건 믿을 수가 없어, 그치? 나... 나 울고 있어, 미안해 Charles, 나... 내 코 빨개졌지, 그치?";
			link.l1 = "Mary de Maure, 내 아내, 오늘도 여느 날처럼 아름답구나!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "고마워, Charles, 정말 고마워... 모든 게 너무 엄숙하고 멋졌어! 내 인생 최고의 날이야, 그치!!! 봐봐, 모두가 얼마나 행복해 보이는지! 그런데 이제 손님들이랑 어울리고 축하 인사도 받아야지! 다 끝나면 돌아와. 우리 선원들이 선술집에서 잘 지내는지 같이 보러 가자.";
			else dialog.text = "고마워, Charles, 정말 고마워... 모든 게 너무 엄숙하고 멋졌어! 내 인생 최고의 날이야, 그치!!! 봐봐, 모두가 얼마나 행복해 보이는지! 그런데 이제 손님들과 어울리고 축하도 받아야지! 다 끝나면 돌아와. 우리 Sharptown에서 기다리고 있으니까.";
			link.l1 = "바로 그렇게 할게, 자기야. 키스 한 번 해주면 바로 간다, 그치?";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, 내 사랑, 우리 손님들과 얘기해 봤어?";
			link.l1 = "아직 아니야, 자기야, 곧 돌아올게.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "그래, 이렇게 한꺼번에 '축하해'란 말을 많이 들어본 적은 처음이야. 그리고 있잖아? 대부분 진심이었어, 그치?";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "그래, 그래! 나도 똑같았어! 물론 내 옷차림 보고 깜짝 놀라는 사람들도 있지, 그치? 그리고 내가 너무 들떠서 사람들이 한 말의 반은 그냥 흘려들었어. Charles, 선술집에 있는 녀석들이 우리 기다리고 있어 – 우리 가야 해. 자기들 선장 축하해주려고 얼마나 신나 있겠어, 그치?";
				link.l1 = "지금 바로 가자. 그런데... 오늘 하루를 선술집 방보다 더 낭만적인 곳에서 마무리하고 싶어. 내 아내, 오늘 밤 우리 선실에서 함께 보내도 괜찮겠지? 게다가 이제 배에 당직도 없으니까...\n";
			}
			else
			{
				dialog.text = "그래, 그래! 나도 똑같았어! 물론 내 옷차림 보고 깜짝 놀라는 사람들도 있지, 그치? 그리고 내가 너무 들떠서 사람들이 한 말의 반은 그냥 흘려들었어. 근데 Charles, 우리 정의의 섬 Sharptown에서 기다리고 있잖아. 언제 출항해?";
				link.l1 = "지금 당장. 손님들이 우리 술을 다 마시게 둘 순 없지! 내 아내여, 오늘 밤 우리 선실에서 지내는 거 괜찮겠지?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "모기 득실거리는 오두막에서, 외딴 섬에서 지내더라도 네가 있으면 난 괜찮아, 그치?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "나도 똑같이 느껴, 그치? 어서 가자, 애들이 럼주 다 마시고 선술집에 불 지르기 전에.";
			else link.l1 = "나도 사랑해. 그럼... 출항하자!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "오, 내 사랑, 정말 행복해! 오늘은 정말 멋진 날이야...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "그 더러운 놈의 머리를 뜯어버려, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "나 괜찮아, 그치! Nathaniel은 어때, 살아 있어?";
			link.l1 = "피가 너무 많아... Dannie, 숨 쉬고 있어? 숨 쉬는 거 보여!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "더 빨리, 자기야, 시간 낭비하지 말고!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "우리가 이겼지, 그치? 늦어서 미안해. 위층에서 이 자식들 열두 놈이랑 엉켜서 꼼짝 못 했거든. 손이 모자랄 정도였어.";
			link.l1 = "괜찮아, 여기 일은 내가 처리했어. Jacques와의 이야기를 드디어 끝낼 수 있어서 기뻐... 마침내, 그는 마땅한 대가를 받았지.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "그럼 샤프타운으로 돌아가자, 그치? 네이선리얼을 확인해야 해. 그 미친놈이 우리 위해 목숨을 걸었잖아!";
			link.l1 = "네 말이 맞아, 내 사랑. 가, 내가 바로 뒤따라갈게.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "그치? 자기야, 우리 Marcus를 찾았어! 그는 화물칸에 묶인 채로 정신을 잃고 있었어.";
			link.l1 = "살아 있어?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "피투성이지만, 곧 나을 거야. 우리 남작은 쉽게 안 부서져, 그치? 겨우 깨어났는데 벌써 싸움이 하고 싶다니!";
			link.l1 = "좋은 마커스, 그치? 자, 이제 해안으로 가자.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "미안해, Charles, 그치? 나... 그냥 산책 좀 했어. 네가 돌아온 것도 봤고, 모두가 살아 있고 이겼다는 소문도 들었는데, 근데 나는... 내가 왜 이러는지 모르겠어, 그치?!";
				link.l1 = "다 잘 될 거야, 자기야, 다 잘 될 거야. 나도 슬퍼. 하지만 우리가 이겼고, 자크 바르바종은 자기 죄값을 치렀어.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Gino랑 Charles 일 때문에 정말 기분이 엉망이야, 그치? 그 소식 들었을 때, 믿을 수가 없었어!";
					link.l1 = "나도 믿기지 않아... 이렇게 하루가 끝날 줄은 상상도 못 했어.";
				}
				else
				{
					dialog.text = "또 이겼다, 그치? 내 남편은 해안의 형제단에서 잘난 체하는 남작들에게 폭풍 같은 존재야! 친구들은 살아 있고, 적들은 죽었어—원래 이렇게 돼야 하는 거지, 그치?";
					link.l1 = "우리가 해냈어, 내 사랑. 우리가 해냈다.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "제대로 서 있기도 힘들지, 그치? 어서 가자, Dannie가 변두리에 집을 하나 찾아냈어. 지금은 배로 돌아가고 싶지 않아. 앉아서 쓰러진 친구들을 위해 한잔하자—이 모든 건 맨정신으론 감당이 안 돼, 그치?";
			link.l1 = "그래, Mary, 가자.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Gino랑 Charles 일 때문에 정말 기분이 엉망이야, 그치? 들었을 때 믿을 수가 없었어!";
				link.l1 = "나도 믿기지 않아... 오늘이 이렇게 끝날 줄은 상상도 못 했어.";
			}
			else
			{
				dialog.text = "늦어서 미안해, 내 사랑. 산책하다가 너를 보고 최대한 빨리 달려왔어! Gino가 위험이 끝났다고 하니까 Danielle이 나를 막았거든. 네가 무사해서 정말 다행이야!";
				link.l1 = "나도 그래, 자기야. 그리고 우리가 이겼어. 바르바존은 죽었고, 남작들은 남은 선원들을 모으고 있어. 전투는 끝났어.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, 너 지금 제대로 서 있지도 못하잖아! 그리고 아무도 Tichingitu를 못 찾고 있어.";
			link.l1 = "Jan이 나한테 정보를 줬어... Sabo-Matila 만으로 같이 걸어가 보자, 그치? 몇몇 사람들이 그쪽으로 그가 가는 걸 봤대.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "자, 우리 무뚝뚝한 인디언이 여기 있네, 그치? 어서 가자, Dannie가 이 변두리에 집을 하나 찾아줬어 - 너 완전히 녹초가 됐지, Charles.";
			link.l1 = "저기 있다... 날 납치해 줘, 내 아름다운 사람. 그리고 아침이 되면 이 모든 게 나쁜 꿈이었던 것처럼 느껴지게 해 줘.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "오해하지 마, 남편. 교회는 화려했지만 여긴 분위기가 훨씬 더 마음에 와닿아, 그치?\n음... 이제 끝이야, Charles. 모든 고생은 다 지난 일이야. 이제 쉴 수 있어.";
			link.l1 = "음, '전부'는 아니지, 내 아내야 – 우리 인생은 함께 계속되는 거니까! 앞으로 무슨 일이 있을지는 알 수 없어. 그러니 가자, 우리 친구들이랑 한잔하고, 그리고 나서 – 그치, 기억하지? 선실, 와인, 그리고 우리 둘만의 시간...\n";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "내 남편... 그 말 참 달콤하게 들려, 그치? 이제 넌 내 사람이야, 영원히.";
			link.l1 = "난 이미 오래전부터 당신의 사람이었고, 이제는 영원히 그럴 거야, 내 사랑...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "나 정말 행복해, Charles! 이제부터 우리가 하는 모든 일은 함께하는 거야, 그치?";
			link.l1 = "그치? 자기야! 나란히, 영원히 함께하는 거야!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "이 병이 네 여자들에게 영향을 주고 있는 것 같아, Rodrigo. 뜨개질이라도 시켜서 바쁘게 해 둬!";
			link.l1 = "이 대화는 아무 소용도 없네. 우리 내일 교회에 가기로 했잖아 – 물론 기도하러 가는 거지, 그치?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "내 사랑, 네가 자랑스러워, 그치?";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "찰스...";
			link.l1 = "무슨 생각해, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(웃음) 나랑 Alan도, 네가 여기서 한 것처럼 정의의 섬에서 똑같은 걸 하고 싶었어, 그치?";
			link.l1 = "네... Alan이야?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "정말 대단한 몽상가였지 - 그치? 그 사람이 살아 있었다면 너희 둘은 정말 좋은 친구가 됐을 거야.";
			link.l1 = "우리 취향이 한 가지는 확실히 같네, 그치?...";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "뭐라고? 하하하! 아, 닥쳐, Charles!\n어쨌든, 이거 정말 대단하지... 우리가 이 사람들에게 이렇게 큰 기쁨을 준 거야!";
			link.l1 = "우리가 그들에게 기회를 줬어; 나머지는, 그들이 알아서 한 거지. 그러니까... 무슨 생각하고 있어, 그치?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "나중에 나를 보면 알게 될 거야...";
			link.l1 = "나야 물론이지!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "나는 어둡고 좁은 공간이 좋아. 그러면 마음이 차분해지거든. 드디어 생각을 정리할 수 있겠어\n마치 모든 걱정이... 그냥 사라진 것 같아! 이 느낌, 정말 그리웠어...";
			link.l1 = "의사를 만나봐야 해.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "마치 네가 다시 세레스호에 돌아온 것 같아, 그치?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "... 내가 혼자가 아니라서 아쉬워. 침묵 속에서, 어둠 속에서, 고독 속에서라면, 그치? 그게 완벽할 텐데.";
			link.l1 = "계속 꿈이나 꾸고 있어, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "한 번은 게가 내 침대에 기어들어왔어 - 내가 그걸 잘라서 먹어버렸지, 그치?";
			link.l1 = "계속 꿈이나 꾸고 있어, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "가면 쓴 개자식! 아야! 도와줘, 자기야 - 이 쇠창살을 부숴야 해!";
			link.l1 = "조용히 해! 뭐 해야 할지 생각 중이잖아!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "자기야, 저 가면 쓴 놈들이 사방에 있어! 선체를 뚫고 게처럼 기어들어오고 있다고! 전부 베어버려야 해, 그치?";
			link.l1 = "Mary, 여기 있어, 지휘를 맡아! 배를 전투에서 멀리 빼, 또다시 적이 올라타면 우리 못 버텨!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "어디 가려고? 너 그냥 보내줄 생각 없어, 그치?";
			link.l1 = "Hercule이랑 우리 선원들을 도와야 해! 나를 믿어, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "알겠어, 자기야!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "승리야! 이리 와, 자기야! 한두 시간쯤 널 갖고 싶어.";
			link.l1 = "아...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "가자!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "이봐, Hercule! 너를 다시 보게 되어 정말 기뻐, 회색 수염아!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary! Mary, 잠깐만! 네 보고가 필요해!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "어? 우리가 이겼지, 그치? 저 빌어먹을 배는 도망쳤어. 난 어떤 놈의 머리를 둘로 쪼개 버렸지!\n휴, 젠장 단추들!";
			link.l1 = "오, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "오, 신이시여, 나 보지 마, 자기야! 나 이제... 휴!";
			link.l1 = "버텨, 그치? 내가 왔어!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! 너랑 얘기 좀 해야겠어, 그치? 진짜로!";
				Link.l1 = "무슨 일이야, Mary? 문제라도 있어?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("듣고 있어, 내 사랑하는 선장님!","그치? "+pchar.name+", 다 듣고 있어!","나한테 시킬 일 있어, 그치? "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, 나 옛 인디언 도시 Tayasal에 가려고 해. 너한테 거짓말은 안 할게: 이 여행은 정말 위험하고, 내가 말했던 그 우상도 써야 해. 너... 나 따라올 거야?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, 전체 상황을 보고해 줘.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "우리가 정박할 때마다 특정 물품을 사줬으면 해.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, 네 조언이 필요해.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, 너에게 명령이 있어...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("자기야, 지금 너를 원해. 괜찮지, 그치?","Mary, 우리... 잠깐 같이 있을래? 우리 둘이서만, 그치?");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, 방을 빌려서 같이 있을래?","사랑하는 사람, 나 너랑 단둘이 있고 싶어... 우리 방 하나 빌려서 몇 시간만이라도 모든 걸 잊어버릴까, 그치?\n");
				Link.l2.go = "room_sex";
			}
			link.l9 = "별거 아니야, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, 정말 끝내주지, 그치? 선체 아래 구멍은 막았고, 돛도 말렸어. 뭐, 뭘 기대했어? 그렇게 쳐다보지 마, 나 회계 공부 같은 건 한 적 없으니까.";
			Link.l1 = "미안해, Mary. 정말 깊이 생각하지 못했어.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, 나 괜찮아! 이미 내 코트랑 칼 챙겼어. 그래도 물어봐줘서 고마워, 정말 친절하네, 그치?";
			link.l1 = "하지만 나는 정말... 에이, 됐어, 그치? 신경 쓰지 마, 우리 괜찮아.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "명령이야?";
            Link.l1 = "여기 서 있어!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나 따라와, 그리고 잘 따라붙어!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, 화기용 탄약을 바꿔.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "탄약 종류를 선택하세요:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "바로 할게, 내 사랑!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "바로 갈게, 내 사랑!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
