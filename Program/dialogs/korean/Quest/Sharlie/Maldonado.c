// Алонсо де Мальдонадо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "무엇이 필요하십니까?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "멈추시오, 선장 "+GetFullName(pchar)+"...";
			link.l1 = "어쩐지 여기 스페인 병사들이 있는 것도 이제는 놀랍지도 않군... 누군가 항상 내 뒤를 쫓는 데 익숙해진 모양이지. 이 버려진 섬에서 뭘 찾고 있나, 카스티야 놈? 빨리 한몫 챙기고 싶어서 온 건가?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "내 이름은 알론소 데 말도나도다. 내 이름은 네게 별 의미가 없을지 모르지만, 디에고 데 몬토야라면 들어봤겠지. 그는 내 가장 친한 친구였어. 내 목숨을 구해줬고, 이제 그의 피가 네 손에 묻었구나.";
			link.l1 = "나를 따라 여기까지 온 건 복수하려는 거겠지?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "나는 단순히 복수만을 원하는 게 아니야. 내가 알기로, 너는 쿠쿨칸의 가면을 가지고 있다지?";
			link.l1 = "이런, 맙소사! 또 다른 보물 사냥꾼이군! 돈 디에고가 시작한 미완의 일 때문에 온 건가?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "나는 보물에는 관심 없어. 나는 타야살의 부를 직접 봤거든. 미겔 디초소도 한 조각 이상은 제대로 챙기지 못했지. 내가 원하는 건 그 가면이야.";
			link.l1 = "너 타야살에 다녀왔다고? 믿기 힘든데. 내가 알기로는 디초소만이 그 원정대의 유일한 생존자였어.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "나는 Dichoso가 오기 스무 해 전, 이미 Tayasal에 갔었지. 바로 그 미친 주술사 카넥이 이 섬에 가면을 숨기려고 그 끔찍한 인신공양 의식을 썼던 때와 같은 시기였어.";
			link.l1 = "내가 지금 듣고 있는 걸 믿을 수가 없어! 진리의 수호자가 만들어질 때 제물로 끌려간 그 정복자 무리의 일원이었단 말이야? 너희는 모두 죽었잖아!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "우리 모두는 아니야. 나는 살아남았지.";
			link.l1 = "잇사족이 왜 너만 살려줬지? 넌 뭐가 그렇게 특별하길래?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "넌 이해 못 할 거야. 젠장, 나도 이해 못 했으니까. 아무도 나를 봐주지 않았지. 어제 일처럼 생생히 기억나... 그 야만인이 단검으로 카스코의 등에 살점을 도려내고 죽인 다음 미친놈처럼 울부짖기 시작했을 때, 난 우상에 빨려 들어간 것 같았어. 그리고 눈을 떠 보니, 타야살에서 아주 멀리 떨어진 곳에서, 스무 해가 지난 뒤였지. 내겐 한순간 같았는데!";
			link.l1 = "시공간의 소용돌이... 젠장, 크사틀 차가 한 말이 전부 맞았잖아! 그 가면에 대해 어떻게 알게 된 거지? 그걸 어디에 쓰려고 하는 거야?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "나는 미친 인디언 주술사가 소환한 지옥의 산물을 반드시 막아야 하오. 이 흉물은 우리 세상을 불바다로 만들려 하고 있소!";
			link.l1 = "흠... 당신, 빈첸토 신부와 얘기했지? 그 종교재판관은 이쪽저쪽 눈치만 보며 행동하고 있군. 놀랍지도 않지. 그자가 나를 찾아내서 한판 붙으라고 보냈나? 잘했어! 임무를 완수했군, 알론소 나리!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "주님께서 악과의 전투에서 내 손에 힘을 더해 주신다. 나는 다시 테야살로 돌아가 가면을 사용해 영원히 문을 봉인하겠다.\n그리고 인간의 모습을 한 어떤 악마도 다시는 우리 세계로 들어오지 못할 것이다.";
			link.l1 = "네 계획에 딱 하나 문제가 있소, 돈 알론소. 그 악마는 이미 우리 중에 있소. 우리가 해야 할 일은 그가 이 문을 통해 나가지 못하게 막는 것뿐이오. 당신이 그에게서 가면만 지키고 있다면, 그는 절대 나갈 수 없을 것이오.  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "그 정도로는 부족해. 누가 옳든 한 가지는 확실하지:\n문은 영원히 닫혀야 해. 그리고 그 방법은 단 하나야:\n타야살 제단 위에 있는 가면을 파괴하는 것. 그렇게 하면, 악마는 모든 힘을 잃게 될 거야.";
			link.l1 = "흠. 나도 그게 우리가 할 수 있는 최선이라고 생각해... 그런데 타야살까지 어떻게 갈 생각이지? 거기로 가는 길은 알고 있나?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "그때 우리가 사용했던 쉬운 길은 이제 더 이상 존재하지 않는다. 길들은 돌무더기 아래에 묻혀 정글 속에서 사라졌다. 도시로 가는 다른 길이 있긴 하지만, 그 길은 멀고 위험하다. 그 길은 유카탄 최북단 만에서 시작된다.\n빈첸토 신부와 라몬 데 멘도사 돈의 도움을 받아, 나는 정예 병사들을 모아 이차 야만인들이 지키는 셀바를 뚫고 나아갈 것이다. 쉽지는 않겠지만, 신께서 우리의 신앙을 위한 싸움에 힘과 용기를 내려주실 것이다.";
			link.l1 = "알론소 나리, 제 포부가 나리의 뜻과 우연히 일치하는군요. 잠시 앙금을 접어두고 힘을 합칠 때가 되지 않았습니까? 함께라면 이 성전을 성공적으로 완수할 가능성이 훨씬 높을 것입니다.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "나는 스페인 군인이다. 나는 이단자들과 동맹을 맺지 않으며, 프랑스 놈들과 거래하지도 않는다. 게다가, 이미 돈 디에고를 위해 너에게 복수를 선언했다. 목숨에는 목숨으로 갚아주마!";
			link.l1 = "알론소 돈, 당신은 황소처럼 고집이 세군! 거기 서서 세상이 큰 악에 위협받고 있다고 설교하면서도, 그렇게 엄청난 일을 해내는 데 내 도움은 끝내 거절하는군!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "이제 내가 결정한다, 빈첸토 신부가 아니야! 기도나 하고 죽을 준비나 해라, 프랑스 선장!..";
			link.l1 = "아, 지난 몇 달 동안 그 말 정말 많이 들었지! 검을 들어라, 고집 센 카바예로!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
