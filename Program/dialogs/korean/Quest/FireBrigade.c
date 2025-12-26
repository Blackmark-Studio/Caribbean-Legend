
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("","여자에... 선장이라니! 이제 별걸 다 보겠구만. 아가씨, 정말 눈부시군. 안타깝게도 그 아름다움이 프랑스 왕관에 큰 불행을 가져왔소\n")+"포인시의 명령은 항상 그렇게 끝나지. 한 명은 감옥에 가고, 다른 한 명은... 오늘 그와 함께 감옥에 가거나 전투에서 쓰러지겠지.";
			link.l1 = "여기선 분명 어울리지 않는군. 이렇게 똑똑한 장교랑 훌륭한 배를 현상금 사냥꾼의 더러운 일에 왜 보내는 거지?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "명령은 토론하는 게 아니라 실행하는 거다. 모든 선장이 명령을 따를지 말지 고른다면, 해군이 유지될 리가 없지.";
			link.l1 = "네 부하들에게 그렇게 전해라.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "넌 나를 궁지에 몰아넣고 내 충성과 맹세를 꺾으려 하고 있군. 이런 상황에서 그건 비열한 짓이지. 말이 아니라 칼로 결판내자!";
			link.l1 = "(지도력) 세 번째 길이 있지. 장교답지 않은 더러운 일은 그만둬. 나와 함께해. 그러면 전혀 다른 세상을 보여주지.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "그럼, 무장하라!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
                dialog.text = "배신자는 어디서나 똑같이 취급받지. 나도 그런 놈이 되진 않을 거다. 각오해라!";
                link.l1 = "기회는 이미 줬고, 넌 놓쳤다. 각오해라!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Skill Check Passed", SKILL_LEADERSHIP);
            dialog.text = "나는 왕관에 충성을 맹세했지, 우리를 죽으라고 보내는 잘난 척하는 빳빳한 관리들한테 맹세한 게 아니야. 하지만 너는 내 왕의 적이니, 그건 그냥 넘길 수 없어.";
			link.l1 = "내일이라도 당신 나라에 저지른 죄를 속죄할 수 있지—적당한 중개인에게 돈만 주면 되거든. 그게 나보다 당신네 윗사람들에 대해 더 많은 걸 말해주지.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "맞는 말이야. 그리고 이제 더는 참기 싫어. 프랑스인들만 건드리지 않겠다고 약속한다면, 당신 지휘 아래에서 일할 준비가 됐어.";
			link.l1 = "누구와 마주치게 될지 나도 모르겠고, 아무것도 장담할 수 없어. 하지만 합리적으로 행동하겠다고 약속하지. 승선을 환영하네, 장교. "+NPChar.name+"!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "이게 바로 지명수배자의 모습이군. 그 칭호가 자랑스러운가, 해적? 그걸 얻으려고 꽤 애썼겠지\n카사 데 콘트라타시온에 따르면, 네가 쓰러뜨린 건 "+(Statistic_AddValue(PChar,"spa_AbordShip",0)+Statistic_AddValue(PChar,"spa_KillShip",0))+" 스페인 왕관의 깃발을 단 배들. 그리고 오늘, 내 멋진 배도 그 목록에 오를 거야"+GetSexPhrase(".","\n스페인 함대에 화가 있기를! 우리는 질병, 편애, 배신까지 겪었지... 그런데 여인한테까지 당하다니?");
			link.l1 = " 네가 마지막으로 남은 놈이야. 네 선원들은 다 죽었지. 그리고 너도 마찬가지야, 아직 그 사실을 모를 뿐이지.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
            dialog.text = "알바가 이 임무를 맡지 못한 게 아쉽군. 그 녀석이 더 잘했을 텐데. 그래도 어쨌든 내가 끝까지 해보겠다.";
            link.l1 = "너는 진정한 고향의 아들이구나. 그곳의 영웅들을 만날 준비를 하라, 나리.";
            link.l1.go = "Alonso_2";
            link.l2 = "사냥꾼이 먹잇감이 되었군. 네 모든 말은 헛수고였지—이건 예나 지금이나 똑같다네.";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
            dialog.text = "숨 돌릴 시간 줘서 고맙다만, 이제부터는 내 검이 말할 차례다.";
            link.l1 = "무기를 들어라!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
            dialog.text = "숨 돌릴 시간 줘서 고맙다만, 이제부터는 내 칼이 말할 차례다.";
            link.l1 = "죽을 준비나 해라!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            MakeUnpushable(NPChar, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name+"! 보고서에 당신 이름이 너무 자주 나와서, 마치 오래전부터 알고 지낸 사이 같은 기분이 드는군","맥아더 아가씨! 후원자가 당신이 뭘 하고 다니는지 아시오? 아, 됐다. 어차피 그 사람이 내 다음 의뢰인이겠지.")+"\n운이 좋군. 내 상관들은 항상 이전 명령과 모순되는 긴급 명령을 보내는 걸 좋아하지. 내가 안티과에서 옛 선원들을 쫓아내느라 바쁘지 않았다면... 뭐, 됐다. 그만하자. 네가 진짜 일에서 나를 방해하고 있잖아.";
			link.l1 = "너도 나를 방해하고 있어.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "내 선미에 체인샷이 날아와서, 거의 못 피할 뻔했지! 내 늙은 뼈가 좀만 더 빨랐다면, 내가 직접 그 자식 놈을 바다 악마한테 보냈을 거야. 고맙다, 선장. 그리고 내 고인이 된 주인님도 고마워할 거야!";
			link.l1 = "너 누구야? 죄수냐? 내 선원들이 너를 풀어줬나?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "찰리 니펠 본인이오. 영국 해군 최고의 포수지!";
			link.l1 = "코트니가 너를 찾느라 오랜 시간을 보냈다고 하더군. 무슨 사연이야?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "수년 동안 나는 리처드 플리트우드라는 용감한 영국인 선장을 모시며 복무했소. 우리는 함께 수많은 전투를 치렀고, 진정한 열정인 영국 해군을 위해 헌신했지. 하지만 어느 날, 모든 것이 달라졌소.\n런던의 고위층은 우리를 꼭두각시로 썼소. 우리는 동족을 공격했고, 남의 뒤치다꺼리를 하느라 제복까지 더럽혔지. 그리고 이제, 우리 차례가 온 것이오...";
			link.l1 = "여기선 아무도 판단하지 않아. 인생이란 복잡하거든, 특히 네가 네 뜻대로 살지 못할 때는 더 그렇지.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "그래서, 옛 죄악의 그림자가 결국 너를 따라잡았다고 생각하나?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "나는 내 조국을 위해 복무한 걸 후회하지 않아. 그냥... 쓰라릴 뿐이야, 선장. 특히 내 후원자랑 그 불쌍한 부인 생각하면 말이야.";
			link.l1 = "이제 어쩔 거야?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "찌르는 말 할 필요 없어... 우린 이미 죄값을 다 치렀어!";
			link.l1 = "이제 어쩔 거야?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "이제 나는 이름도, 고향도 없는 사내다. 어디든 갈 수 있지만, 지금은 갈 곳이 없다. 함께 갈 사람도 없고. 포수는 어디서나 필요하지만, 모든 배에 대포가 있는 건 아니지.";
			link.l1 = "나와 함께하지. 영국 함대와의 관계가 썩 좋았다고는 할 수 없지만, 그 중 뛰어난 자들은 존경하네.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "나는 대포가 있지. 네가 정말 그렇게 실력 있다면, 내 선원들 중에 진짜 전문가 자리는 언제나 비어 있어.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "집에 가면 교수형이 기다리고 있어. 스페인 놈들이나 네덜란드 놈들도 마찬가지고, 프랑스 놈들은 딱히 신경 안 써. 하지만 너한텐 좋은 포수가 필요한 것 같군. 나 할게, 선장. 기회 되면 바로 선실로 갈게. 시간 나면 들러, 럼 한잔하면서 얘기나 하자.";
			link.l1 = "배에 온 걸 환영한다.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "말도 안 돼. 차라리 배를 빼앗아서 군도에서 가장 깊은 구멍으로 사라지겠어. 구해줘서 고마워, 선장님, 그리고 잘 있어.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            NPChar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "여기까지 올 사람은 네가 아니었어. 메이펑은 회사의 송곳니지. 내 전대는 복수의 칼날이고. 그런데 네가 둘 다 부러뜨렸어. 그런 일은... 있을 수 없어.";
			link.l1 = "놈들은 날 짐승처럼 쫓아왔지. 나도 궁지에 몰린 짐승처럼 싸웠고. 죽느냐 싸우느냐의 순간엔 머릿속이 맑아진다. 결국 남는 건 단 하나의 질문뿐이야:\n전설의 제벡 함선 선실까지 갈 수 있을까, 아니면 못 가는 걸까.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("","이상하군—여자가 지휘하는 건 드문 일이야. ")+"나를 기다리고 있었나?";
			link.l1 = "그래. 메이펑은 역사를 지닌 배야. 내가 네덜란드 놈들을 배신했을 때, 언젠가는 너 같은 자를 보낼 거란 걸 알았지. 그랬다면 명예로운 최후였을 텐데... 결국 이렇게 됐군.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "적을 알고 나 자신을 아는 것이 승리의 열쇠지. 그래서 선택을 한 거군. 내 함대를 네 방식대로 상대하겠다고. 죽을 각오도 했겠지. 하지만 네가 이겼어. 이제 내 목숨은 네 손에 달렸군. 왜 끝장을 내지 않는 거지?";
			link.l1 = "(지도력) 나는 회사의 야망 때문에 전설적인 선장을 침몰시키는 게 무의미하다고 생각하오. 나도 한때 그대와 같은 처지였소—남의 꼭두각시. 남의 이익을 위해 일하고, 남의 명령을 따랐지. 내가 한때 스스로 선택했던 것을 그대에게도 주겠소: 자유를.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "모든 선장은 마지막 한마디를 할 자격이 있으니까. 각오해라!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			dialog.text = "자유란 주어지는 게 아니야. 스스로 쟁취하는 거지. 그리고 선택을 말한다고 해서 모두가 그걸 줄 수 있는 건 아니야.\n피할 수 없는 길이 있고, 끝내지 못한 명령도 있지.\n내 길은 여기야. 내 명령은 끝까지 버티는 거다.";
			link.l1 = "그래서 죽음을 선택하겠다는 거냐?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "아니. 나는 나 자신으로 남겠어.";
			link.l1 = "그럼 싸우자!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Skill Check Passed", SKILL_LEADERSHIP);
			dialog.text = "너는 로덴부르크와 다르군. 그는 날 도구로만 봤어. 하지만 너는... 동등한 존재로 봤지. 자신을 희생하는 게 미덕은 아니야. 네 조건을 들을 준비가 됐어.";
			link.l1 = "간단해. 내 기함에서 항해사가 되어라. 아니면, 네가 원한다면 네 배를 가지고 내 깃발 아래에서 항해해도 돼. 더 이상 회사 놈들 뒷정리할 필요도 없고, 그들의 비밀을 숨길 필요도 없어. 나는 자유야—그리고 그 자유를 너에게도 주겠어.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "나는 많은 걸 봤지: 피, 금, 배신. 회사는 돈은 주지만, 존중은 없어. 배는 주지만, 족쇄는 채우지. 너는... 선택을 주는군. 네가 약속을 지킨다면—롱웨이는 더 이상 남의 뜻대로 사냥하는 사냥꾼이 아니야. 그는 한 인간이 될 거야. 선장이 될 거고. 아니면—어디로 항해할지 아는 선장 곁에 설 수도 있지.";
			link.l1 = "승무원에 온 것을 환영하네, Longway 항해사.";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
			sld = InitLongwayFP("Longway_FP", NPChar);
			NPChar.lifeday = 0;
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

			AddDialogExitQuest("pchar_back_to_player");
			PostEvent("LAi_event_boarding_EnableReload", 5000);
			DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
