// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "원하는 게 있소?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "너도... 결국... 죽게 될 거야. 그가 올 거고... 널 죽일 거야... 우리 모두를 죽였듯이... 여기 있는 모두를 죽였듯이...";
			link.l1 = "뭐? 너 누구야? 누구 얘기하는 거지?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "그는 거대해... 그는 무적이야... 그는 죽여... 그는 널 죽일 거야. 내가 널 죽여야 해... 내가 널 죽이면, 넌 우리처럼 되지 않을 거야... 넌 이해하지 못해... 넌 그의 칼에 죽을 거야... 넌 우리처럼 변하게 될 거야... 산타 키테리아에 있던 모두처럼...\n";
			link.l1 = "말도 안 돼!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "너를 정말 오래 기다렸어!..";
			link.l1 = "음!.. 놀랍군!... 뼈다귀가 정말 대단하네!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "보이네... 느껴지네... 네가 내게 가져다줬구나... 내 자유를...";
			link.l1 = "무슨 소리를 하는 거야? 넌 대체 뭐냐?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "나는 크소체아템의 수호자요, 쿠쿨칸의 가면을 지키는 자다... 그리고 네 앞에 닥친 죽음이기도 하지!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "멈춰...";
			link.l1 = "그걸 내가 왜 해야 하지, 어? 숨이라도 찼냐, 뼈다귀 주제에?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "아니. 너는 결코 나를 죽일 수 없을 것이다. 그 마법 단검으로도 말이다. 우리의 결투는 아주, 아주 오랫동안 계속될 테니, 네가 완전히 지쳐 죽을 때까지 말이다.";
			link.l1 = "그런가? 그런데 왜 나를 때릴 수 없는 거지?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "그대는 용감하고 강인한 전사이며 족장의 발톱을 지니고 있군. 나는 그대를 살려둘 수밖에 없지. 이 단도를 가진 자, 나와 맞서 싸울 용기를 가진 자는 자신이 찾아온 것을 얻게 되니.";
			link.l1 = "너는 누구지? 너의 진짜 정체는 뭐냐, 수호자?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "예전에는 나를 알베르토 카스코라고 불렀지. 나는 알론소 데 말도나도의 부대에서 군인이었어. 우리는 고대 타야살을 발견했지만, 붙잡혀 희생제물로 바쳐졌지. 내 키와 힘 때문에, 이교도 카넥이 나를 크소체아템의 수호자, 쿠쿨칸의 가면을 지키는 자로 만들었어. 크소체아템에 발을 디딘 자는 모두 내 손에 발견되어, 내 손에 죽임을 당하고, 언데드로 변했지.\n족장 발톱 단검으로 내 살을 도려 이곳의 지도를 새겼다. 나는 영원히 가면의 안전을 지킬 것이며, 내 손에 그 단검을 쥘 때까지 결코 편히 쉬지 못하리라.";
			link.l1 = "족장의 발톱이 필요하오?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "그래. 네가 가면이 필요하니, 단도를 내게 줘라. 나는 오랫동안 기다려온 평안을 찾고, 너는 가면을 얻게 될 거다. 네가 그 가면을 가지고 Ksocheatem에서 무사히 나갈 수 있다고 맹세하마.";
			link.l1 = "제안을 받아들이겠소, 수호자. 세례당 분수 뒤에 있는 받침대 위에서 그 가면을 봤소. 그게 맞소?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "그렇소. 이것이 바로 날아다니는 뱀, 쿠쿨칸 신의 위대한 유물이지. 우리가 이 대화를 마치면, 저쪽으로 가서 가져가도 되오.";
			link.l1 = "좋아, 네가 한 말을 꼭 지키길 바란다, 수호자...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "나는 맹세했어...";
			link.l1 = "그럼 족장의 발톱을 가져가시오. 그 물건이 그대의 영혼에 평온을 가져다주길 바라오.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "아, 이 순간을 얼마나 오래 기다렸던가! 이제야 드디어 떠날 수 있겠군... 하지만 작별의 선물로 내 힘의 일부를 너에게 전하고 싶다. 이것이 알베르토 카스코가 주는 마지막 선물이 될 것이다.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "이제 나는 떠날 시간이오. 시간 낭비하지 마시오; 수호자와 쿠쿨칸의 가면이 없으면, 그 섬은 곧 영원히 사라질 것이오.";
			link.l1 = "그건 후회할 일도 아니지. 세상에 지옥 같은 곳이 하나 줄었을 뿐이야... 그런데 잠깐, 수호자! 자네, 타야살에 다녀왔지! 제발, 그곳이 어떤 곳인지 말해 줘.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "고대 마야 도시야. 사람들이 아직 그곳에 살던 시절의 모습이 그대로 남아 있지. 웅장한 신전들, 우뚝 솟은 피라미드들... 지금은 이차 부족이 그곳에 살고 있는데, 자신들이 마야의 직계 후손이라고 주장하지. 그들은 종교, 문화, 삶의 방식까지 모든 면에서 마야를 흉내 내려 해.";
			link.l1 = "거기까지 어떻게 가나요?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "우리 지휘관은 알론소 데 말도나도였어. 우리는 그냥 그를 따라 정글을 헤쳐 나갔지. 내가 기억하는 건 모스키토 만, 페를라스 곶 북쪽에 상륙해서 서쪽으로 셀바 깊숙이 들어갔다는 것뿐이야.";
			link.l1 = "타야살에서 주목할 만한 게 뭐지?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "거기서는 모든 것이 주목할 만하지. 정말 모든 것이. 하지만 우리는 마야의 보물에만 관심이 있었어. 그리고 결국 찾아냈지. 그 대가를 혹독하게 치렀어, 특히 나 말이야. 하지만 이제, 나는 드디어 자유야!";
			link.l1 = "테야살로 가기 전에 무엇을 알아야 하지?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "이차족은 강인한 힘과 지혜를 지녔다네. 그들은 국적을 불문하고 백인들을 증오하며, 자신들의 영토를 침범하는 외부인은 모조리 파괴하지. 평범한 이차 전사들은 어떤 대화도 시도하지 않지만, 카넥이나 그의 아들 우라칸이라면... 그들이 그 가면을 본다면, 혹시 모른다네. 만약 자네가 살아서 타야살에 도달한다면, 직접 확인하게 될 걸세. 하지만 과연 그곳을 빠져나올 수 있을지는...\n";
			link.l1 = "카넥이 테야살에 오는 모든 백인들을 제물로 바치는 것이오?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "그럴 것 같소. 하지만 쿠쿨칸 가면을 쓴 자는 포함되지 않을지도 모르오.";
			link.l1 = "좋아. 그걸 기대하고 있겠어.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "안녕히 가시오, 병사. 그대가 가면의 힘을 올바른 목적에 쓰길 바라오.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
