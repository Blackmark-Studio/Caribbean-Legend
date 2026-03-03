// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐 필요한 거 있어?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "너! 네가 그녀를 여기로 데려왔구나! 그녀는 그의 핏줄이야! 그녀는 그녀의 핏줄이야! 창녀의 딸이 어미의 무덤에 왔구나! 그녀는 죽을 거야! 그리고 넌 그걸 막지 못할 거다! 제시카의 길을 막지 마라! 복수는 내 몫이다!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "하! 너 따위가 나를 해칠 수는 없어!\n 공기여, 물이여, 땅이여, 불이여 - 내 명령을 들어 나를 도와라!\n 죽은 자는 일어나고, 불은 타오르며, 물은 다리를 지키고, 바람은 너를 날개에 실어 땅바닥에 내던지게 하라!\n 실컷 즐겨라!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "하! 너 따위가 나를 해칠 수는 없어!\n더 많은 죽은 자들이 일어나 공격하게 두고, 불이 돌을 태우게 하고, 바람이 너를 들어 올려 내던지게 하며, 대지가 네 힘을 빨아들이게 하라!\n즐겨라!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "하! 너 따위가 나를 해칠 수는 없어!\n독이 내 불꽃 칼날에 스며들게 하고, 바람이 너를 감싸게 하고, 물이 네 민첩함을 씻어가게 하겠다!\n죽어라! 하하하!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "그만... 이제 지쳤어. 난 패배했어... 불쌍한 제시카의 운명을 불쌍히 여겨 줘!";
			link.l1 = "그래... 이 시체의 짐은 네 불쌍한 영혼에게 지우지 않겠다!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "네 사연을 알고 있어, 제시카. 그리고 네 인생이 그렇게 슬펐고, 그런 식으로 끝나서 유감이야. 나와 이야기하고 싶지? 좋아, 네가 최근에 나를 죽이려고 했던 건 잊어보려고 할 테니, 네 말을 들어줄게. 물론 내겐 쉽지 않겠지만...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "고마워... 이미 비트리스 샤프와 로렌스에 대해 알고 있겠지... 내 로렌스. 나는 망설임 없이 그녀를 죽였지만, 그를 죽일 수는 없었어. 나는 할 수 없었지만, 그는 할 수 있었지. 제시카가 죽었어...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... 그러나 끔찍한 맹세로 맺어진 피의 서약은 아직 이루어지지 않았다. 이 서약의 힘은 인디언의 마법에서 비롯된 것이다. 그 힘이 시체를 무덤에서 일으켜 세웠지.\n증오로 내 영혼은 사막이 되었다. 이 암초에 온 자들은 모두 내 손에 죽었고, 그 시체들은 내 꼭두각시가 되었다. 나를 쓰러뜨린 자 외에는 누구에게도 도움을 청할 수 없다...";
			link.l1 = "내가 너에게 해줄 수 있는 게 뭐지? 내가 할 수 있는 건 네 고통을 덜어주는 것뿐이야...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "도와줘... 그에게 데려가 줘.";
			link.l1 = "로렌스 벨트로프에게 가라고? 그걸 내가 어떻게 하란 말이오? 내 선원들은 자네만 보면 도망치거나, 아니면 아무 생각 없이 자네를 불태워 죽일 거요. 그런데도 자네는 아직도 내 부하들을 도륙하고 '지배'할 수 있다니...\n";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "그들은 나를 보지 못해. 하지만 너는 볼 수 있지. 너도 이미 눈치챘겠지만, 나는 살아 있는 자들이 가질 수 없는 힘을 가지고 있어. 하지만 네 허락 없이는 네 배에 오를 수 없어. 나를 그에게 데려가 줘.\n너와 오래 함께 있지는 않을 거야. 네 사람들에게도 해를 끼치지 않아. 자정에 자메이카의 포틀랜드 만에 나를 내려줘. 다음 밤에 다시 만나게 될 거고, 네가 찾으러 온 것을 받게 될 거야.";
			link.l1 = "내가 왜 여기 있는지 어떻게 아는 거지?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "나는 많은 것을 알고 있지. 살아 있는 자들보다 더 많이. 나는 그녀를 봤어... 그녀를 위해 서류가 필요하지, 그걸 얻게 될 거야. 더 많은 것도 얻게 될 거다; 내가 특별히 더 줄 것이 있어. 나를 그에게 데려가...";
			link.l1 = "흠. 너의 헬렌에 대한 피에 굶주린 속셈이 마음에 안 들어. 그녀에게 손끝 하나라도 대지 마라. 결국 그녀는 어머니의 행동에 책임이 없으니까.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "네가 나를 이겼다. 그녀는 해치지 않겠다... 약속하지.";
			link.l1 = "아직 끝나지 않았어. 내게 걸린 그 수많은 저주를 풀어줄 생각이오? 인정하겠소, 평생 그 저주들과 함께 사는 건 내키지 않으니...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "그렇게 간단하지 않아... 내가 포틀랜드 코브에서 너를 다시 만나면... 그때 네가 스스로 치유하는 방법을 알려주지.";
			link.l1 = "내 뒤에 뭐?.. 무슨 뜻이야?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "그와 만난 후에.";
			link.l1 = "오, 그 자가 좋아할 리 없지. 상상 가는군. 좋아, 정리하자면: 첫째, 아무도 너를 보지 못하게 할 것, 둘째, 내 선원들에게 해를 끼치지 않을 것, 셋째, 헬렌에 대해 생각조차 하지 않을 것, 넷째, 내가 찾는 것을 내게 줄 것, 다섯째, 네 저주에서 나를 풀어줄 것. 맞나?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "거의 다 왔어. 내가 직접 치료해주진 않겠지만, 방법은 알려주지. 네가 직접 해야 해.";
			link.l1 = "좋아. 거래하지. 내 배에 타는 것을 허락하겠다.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "이봐! 어디 있냐? 그냥 사라져 버렸잖아...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "약속을 지켰군. 우리 지금 자메이카에 와 있네. 내일 밤 이곳으로 오게. 그러면 내 약속을 지키겠네. 잘 가게.";
			link.l1 = "작별이오...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "끝났어, "+pchar.name+"...";
			link.l1 = "무슨 뜻이오?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "끝났어... 자, 가져가. 네가 찾던 거야. 이게 내 라이벌의 편지인데, 그녀와 함께 묻혀 있었지. 아주 잘 보존되어 있어. 나는 그녀를 용서했고, 내 마음엔 더 이상 증오가 없어.";
			link.l1 = "그 사람을... 만났어? 로렌스랑 같이?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "그래. 그가 생애 마지막으로 느낀 감정은 공포였지. 나는 그에게 아무런 연민도 느끼지 않아.";
			link.l1 = "신께서 그의 죄 많은 영혼을 용서하시길... 나는 그를 다시는 만나지 못할 것 같군.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "그리 아까울 것도 없소. 그는 아주 나쁜 놈이었으니. 이제 서로 작별을 고해야겠군, 내 할 일은 여기서 끝났소. 내 맹세는 지켜졌고, 마법도 힘을 잃었소. 선물을 약속했지. 여기 있소. 이것이 내 플람베르주요. 이제 더는 필요 없으니. 이 검은 세상에 단 하나뿐인 것이오, 어디서도 이보다 나은 것은 찾을 수 없을 거요.";
			link.l1 = "고맙다...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "이제 네 얘기다. 브리지타운에 가서, 현지 교회로 가라. 내 저주를 풀기 위해서다.\n거기서 신부를 찾을 수 있을 거다. 그 신부는 나를 직접 알았지. 그와 대화하면 무엇을 해야 할지 알려줄 거다.\n양초 스무 개를 준비해라, 필요할 테니.";
			link.l1 = "정말로 그가 나를 치료해 줄 거라고 확신하시오?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "네가 직접 하게 될 것이오. 신께서 인도하실 것이니, 확신하시오. 모든 것이 잘 될 것이오.";
			link.l1 = "좋소, 바로 바베이도스로 항해하겠소. 이제 어쩌란 말이오?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "이제 마지막으로 한 가지 소원이 있소. 내 시신을 이 만의 바닷가에 묻어 주시오. 그것이 내 바람이오. 언젠가 그대가 불쌍한 제시카의 무덤을 찾아줄지도 모르겠구려. 안녕히,\n "+pchar.name+", 그리고 나를 위해 기도해 주시오...";
			link.l1 = "제스?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "나를 알아보겠소, 선장?";
			link.l1 = "그게... 정말 너야? 하지만 어떻게?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "그래, "+pchar.name+", 나야, 제시카야! 적어도 이십 년 전에는 이렇게 생겼었지.";
			link.l1 = "그래서... 내가 죽은 건가? 그런데 언제? 어떻게?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "너 아직 안 죽었구나, "+pchar.name+". 지금 브리지타운의 교회에 있어. 그냥... 자고 있는 거야.";
			link.l1 = "이게 그냥 꿈인가? 모든 게 너무 현실적으로 보여...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "가끔 그런 일이 있지, "+pchar.name+". 신께서 그대의 기도를 들으셨소. 그대의 기도가 그대만 치유한 것이 아니라 내 영혼까지 정화시켰소. 진심으로 감사하오, "+pchar.name+"! 그리고 암초에서 있었던 일에 대해 용서를 구하고 싶어. 그게... 아무튼, 그냥 용서해 줘. 네 용서를 구하지 않고는 떠날 수가 없었어.";
			link.l1 = "용서하마, 제시카. 내가 정말 살아 있는 것인가?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "너는... 걱정하지 마. 곧 깨어날 거야. 그냥 작별 인사를 하고 싶었어.";
			link.l1 = "너무... 아름다워!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "나를 좋아하나? 그래, 한때는 소앤틸리스 제도에서 제일가는 구혼자들이 나를 쫓아다녔고, 이슬라 테소로의 해적 셋 중 하나는 나를 위해 결투할 준비가 되어 있었지.";
			link.l1 = "하지만 너는 항상 하나만 필요했잖아... 에이, 생강 부적! 도대체 어떻게 이렇게 된 거야?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "내 분노 때문이오. 내 증오 때문이오. 이해하지도, 용서하지도, 잊지도 못한 내 무능함 때문이오. 새 삶을 시작할 수도 있었지만, 나는 어리석고 무의미한 복수에 내 자신을 바치기로 선택했소. 그대가 나를 해방시켰소. 고맙소, "+pchar.name+"...";
			link.l1 = "나는 정말 그대의 인생이 안쓰럽구나...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "안 돼... 아직 생강 부적이 있잖아...";
				link.l1 = "내 뭐?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "안 돼... 아직 생강 부적이 있잖아...";
				link.l1 = "내 뭐?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "...그러지 마시오... 내 슬픈 경험을 생각하고 내 실수를 반복하지 마시오. 그리고 당신이 사랑하는 이들도 같은 실수를 저지르지 않게 하시오.";
			link.l1 = "그 점을 고려하겠소. 그리고 분명히 같은 실수는 다시는 하지 않겠소...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "잠깐 생각해 봐. 그녀는 네 배에 있어.";
			link.l1 = "메리?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "그래. 그녀는 네 인생에서 만날 수 있는 최고의 여자야. 명심해라. 그녀의 사랑은 순수하고, 헌신은 끝이 없다. 용감하고, 젊지만, 절박하고 경험이 부족하지. 많은 걸 이해하지 못한다. 그녀를 잘 돌보고, 지켜주고, 너희 사이에 누구도 끼어들지 못하게 해라. 그녀는 네 부적이야...\n";
			link.l1 = "나... 나는 절대 그녀를 떠나지 않을 거야, 그리고 어떤 위험에서도 그녀를 지킬 거야.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "그 여자는 죽은 배들로 이루어진 그 이상한 섬에 있어... 거기 혼자는 아니지만, 외로워하지. 매일 아침 너를 생각하며 눈을 뜨고, 매일 너를 위해 기도하며, 매일 밤 그녀의 선실엔 불이 켜져 있고 베개는 눈물로 젖어 있지...\n";
			link.l1 = "메리...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "너희 둘 사이에는 딸이 있다. 한때 로렌스와 내 사이에 섰던 그 여자의 딸이지. 너의 부적의 운명은 네 손에 달려 있다. 그 둘은 함께 존재할 수 없어, 베아트리스와 내가 그럴 수 없었던 것처럼.";
			link.l1 = "그걸 어떻게 아는 거지?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "저편... 많은 것을 드러내지... 선택은 네 몫이야. 하지만 기억해라: 메리는 네 인생에서 만날 수 있는 최고의 여자야. 그녀의 사랑은 순수하고, 헌신은 한이 없어. 그녀는 용감하고, 젊지만, 절박하고 미숙해. 많은 것을 이해하지 못하지. 그녀에겐 네 보호와 보살핌, 그리고 사랑이 필요해. 그녀는 네 부적이야.";
			link.l1 = "생각해 보지. 꼭 그렇게 하겠어...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"가야겠어. 이제 정말로 작별을 고할 시간이야... 제시카를 잊지 말고, 가끔 그녀의 무덤에도 들러 줘... 그곳이 어디인지 아는 건 너뿐이니까.";
			link.l1 = "물론이지, 제스. 내가 거기에 들러서 너를 위해 기도할게.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "감사합니다. 안녕히 가십시오, "+pchar.name+"! 잘 가라!";
			link.l1 = "잘 가, 제시카...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
