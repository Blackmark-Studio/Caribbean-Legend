// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 안녕히 가시오.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "최근에 도시 병사 중 한 명이 찰리 니펠을 체포해서 구금했소. 아직 여기 있소?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "맞다, 그런데 왜 묻는 거지?";
			link.l1 = "문제는, 찰리 녀석이 내 부하 중 하나라는 거야. 그가 무슨 죄로 잡혀온 건지 알고 싶어. 그를 데려간 군인들이 아무 말도 안 해줬거든."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "맞아. 흔히 알려진 사실이 아니지. 유감스럽게도, 너에게도 마찬가지야. 국가 기밀이야, 나리.";
			link.l1 = "그럼, 보석은 불가능하다는 말이군?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "맞소. 귀중한 선원을 잃는 일이 불쾌하다는 건 이해하오, 하지만 그대도 나도 어쩔 도리가 없지. 유감이오, 선장.";
			link.l1 = "보석은 안 되는군. 그럼... 보상은 어떤가? 넉넉하게 주지. 너랑 네 부하들 모두에게, 누구 하나 빠짐없이."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "뇌물이라고? 대담하군, 선장. 하지만 아무리 많은 돈을 줘도 우리가 찰리를 풀어줬다는 사실이 알려지면 그 분노에서 우리를 구해줄 수는 없어.";
			link.l1 = "어쩌면... 하지만 적어도 그와 이야기할 수는 있겠소?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "왜 안 되겠어? 네가 그를 구출하거나 탈출시키기 위해 할 수 있는 건 아무것도 없으니... 들어가 봐. 그는 감방 중 하나에 있어.";
			link.l1 = "하, 그놈이 자기가 무슨 죄로 잡혔는지 말하고, 자네가 그렇게 신경 쓰는 국가 기밀까지 털어놓는다면 어쩔 텐가, 경관?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "그건 걱정하지 않는다. 곧 이유를 알게 될 거다. 가서, 내가 마음 바꾸기 전에 네 예전 장교와 이야기해라.";
			link.l1 = "감사합니다."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "필요 없어, 선장. 내가 말했듯이, 넌 그 바보 찰리와 같은 감방에 처넣어졌을 거야. 하지만 우선, 총독께서는 네가 체포에 저항하지 않은 점을 높이 평가하셨고, 둘째로는 최근에 돈놀이꾼이 찾아와서 궁전 창문이 깨질 뻔할 정도로 비명을 질러댄 게 마음에 들지 않으셨지...";
			link.l1 = "내 체포를 요청했다고?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "그자는 묻지 않았소 - 요구했지. 그리고 각하께서는 어떤 요구도 싫어하시지. 그래서 그 고리대금업자는 쫓겨났소.";
			link.l1 = "우습군. 이제..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "이제 "+pchar.lastname+" 선장도 그렇게 하시지. 그리고 대답받지 못할 질문은 하지 마시오.";
			link.l1 = "나는 Charlie Knippel 없이 여기서 나가지 않을 거야."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "제발요, 나리, 찰리 니펠과 얘기하게 해주십시오. 아니면 적어도 무슨 일인지라도 알려주십시오..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "그렇다면, 그와 함께 가라. 감방이 아니라 저승에서.";
			link.l1 = "그래, 그는 죽었군..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "정말 눈치 빠르군, 선장. 하지만 누가 그랬는지, 왜 그랬는지는 절대 말해주지 않을 거라는 걸 알아둬.";
			link.l1 = "그런가?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "그래. 이제 내 인내심을 시험하지 마라 – 내가 너를 영국 병사를 죽인 죄로 감방에 처넣으라고 명령하기 전에.";
			link.l1 = "네 감옥에서 살아 나오는 자가 드물다는 걸 생각하면, 나도 거기 갇히고 싶진 않군. 좋은 하루 보내란 말은 안 하겠다."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "찰리 니펠은 아무하고도 말하지 않아. 어쩌면 창조주하고만 얘기할지도 모르지...";
			link.l1 = "죽었어?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "형이 집행되었소. 더 이상 자세한 내용은 말해줄 수 없소. 그리고 더 캐묻지 않는 게 좋을 것이오 – 자네한테도 좋지 않은 일이 생길 수 있으니. 그냥 감방에만 그치지 않을 수도 있지. 내 말 이해했나, 드 모르 선장?";
			link.l1 = "완전히 이해했소. 안녕히 가시오."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
