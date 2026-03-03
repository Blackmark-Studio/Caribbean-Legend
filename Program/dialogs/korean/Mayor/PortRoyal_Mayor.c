// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 이따가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "각하, 이 섬에서 불법 거래 활동이 있음을 보고드리고자 합니다.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "비단 돛천 밀수와 관련된 임무에 대한 보고를 듣고 싶소.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "저는 필리프 드 푸앵시 총독을 대표하여 왔습니다. 제 임무는 네덜란드인들에게서 포획한 노예들을 인도하는 것인데, 맞습니까?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "약속대로 노예들을 데려왔소.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "저는 필리프 드 푸앵시 총독의 지시에 따라 네덜란드에 맞서 쿠라사오로 향하는 공동 원정에 참여하기 위해 도착했습니다.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "내 함대가 줄었으니, 이제 출발할 수 있소.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "흥미롭군. 말씀해 보시오.";
			link.l1 = "믿을 만한 소식통에 따르면, 영국 국기를 단 네덜란드 브리건틴 '위트레흐트'호가 포틀랜드 만에서 상당한 양의 비단 돛천을 꽤 오랫동안 하역해 왔다 하오. 그들은 1년 넘게 매달 10일부터 15일 사이, 밤에 활동해 왔소.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "당신의 정보원이 믿을 만한 사람임을 확신하십니까?";
			link.l1 = "때로는 나 자신조차도 믿지 못하오. 하지만 이 정보를 알려준 사내는 신뢰할 만한 사람이오. 게다가 거짓말을 할 이유도 없었소.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "알겠소, 선장. 이는 중대한 사안이니, 설령 그대의 정보원이 거짓을 말했거나 단순히 착오가 있었다 해도 나는 제시된 정보를 바탕으로 조치해야 하오. 지정된 시간에 해안 순찰대를 보내겠소, 그리고 그대의 정보가 확인된다면 충분한 보상을 내리겠소. 이러한 불법 행위는 엄중히 단속되어야 하오.";
			link.l1 = "뵙겠습니다 "+sTemp+" 16일에. 그때쯤이면 상황이 분명히 해결될 것이오.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "당신의 정보가 정확했소, 선장. 우리는 거래 도중 범죄자들을 매복하여 붙잡았소. '위트레흐트'는 도주하려다 저항했으나, 우리 순찰 코르벳함에 의해 침몰당했소. 구매자 네 명이 체포에 저항했는데, 한 명은 사살되었고 나머지 세 명은 정글로 도망쳤소. 비단 80필 전량은 포트 로얄의 금고로 이송되었소. 이 조직의 우두머리를 밝혀내지 못했고, 사망자는 신원이 확인되지 않았으며, 나머지는 도주했으나, 이번 작전은 완전한 성공이라 선언하오. 이 악당들이 다시는 감히 이곳에 돌아올 생각을 못 할 것이오.\n선장, 당신은 성실하게 일하며 사기꾼들을 밝혀내 우리에게 큰 공을 세웠소. 보상으로 1만 페소를 드리겠소.";
			link.l1 = "대단히 감사합니다, 각하. 모든 일이 계획대로 진행되어 밀수업자들이 마땅한 대가를 치른 것을 보니 기쁩니다. 이제 물러가겠습니다. 좋은 하루 보내시기 바랍니다.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "정확하오. 노예를 몇 명이나 데려왔소?";
				link.l1 = "아직 작업 중입니다. 곧 결과를 가지고 돌아오겠습니다.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "정확하오. 노예를 몇 명이나 데려왔소?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "흠, 슈발리에가 노예가 3,000명 이상일 것이라 약속했소\n";
			link.l1 = "그렇소. 이 모든 것은 내 잘못이오. 일부 노예들은 적함의 포격에 희생되었고, 일부는 길에서 죽었소. 내 실수를 바로잡고 곧 돌아오겠소. 모든 일은 계약대로 진행될 것이오.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "훌륭하오! 드 푸앵시 기사와는 진정으로 거래를 할 수 있지. 총독께 내 쿠라사오 공격을 위한 함대가 한 달 안에 준비될 것이라 전해 주시오.\n이 작전을 위해 분명 그분이 그대를 내게 보낼 것이니, 곧 다시 보겠소, 드 모르 나리.";
			link.l1 = "다시 뵙게 된다면 기쁘겠습니다, 대령 나리. 이제 작별 인사를 드리겠습니다.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "그대일 것이라 의심하지 않았소. 더욱 좋군! 우리 전대는 준비되어 있소. 1등급 전열함 한 척과 4등급 함선 두 척이 있소. 전대 전체의 최대 규모는 다섯 척을 넘지 않아야 하오.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "그렇다면 남는 배들은 부두에 남겨 두고 두 척만 보유하겠소. 결국 다섯 척의 배를 갖게 되는군요.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "예, 정확히 다섯 명이고, 그 이상은 없습니다. 이제 출발해야겠군요.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "완벽하오. 이제 우리가 따를 계획을 설명하겠소: 혹시 변경하거나 추가하고 싶은 점이 있다면 말씀하시오, 그 후에 함께 논의하겠소.";
			link.l1 = "말씀하십시오, 대령 나리.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "퀴라소를 점령하는 것은 의미가 없소. 그곳은 이 군도에서 네덜란드의 주요 식민지이며, 우리가 빌렘스타트 요새에서 그들의 깃발을 빼앗아 영국이나 프랑스 깃발을 올린다 해도, 섬을 지키는 것은 매우 어려울 것이오. 네덜란드인들은 되찾기 위해 모든 수단을 동원하고, 군사 함대로 집중적으로 공격할 것이오. 전반적으로, 필수적인 목표가 아니기에 점령할 필요가 없소. 우리에게 더 중요한 것은 스타이베산트를 우리에게 유리한 조건으로 조약에 서명하게 만드는 것이오. 이를 위해서는 적의 주요 방어선을 파괴하고, 네덜란드인들에게 빌렘스타트 식민지의 완전한 파괴라는 위협을 가하는 것으로 충분할 것이오.";
			link.l1 = "조약의 내용이 무엇이오?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "조약은 나와 드 푸앵시 기사에 의해 작성되었소. 이는 무역의 여러 측면, 회사와 영국 간의 '무역 전쟁' 종식, 스타이베산트의 신트마르턴 섬에 대한 주장 거부, 그리고 그대에게는 별로 흥미롭지 않은 기타 정치적 사안들을 다루고 있소.";
			link.l1 = "알겠습니다.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "계획은 이러하오: 먼저, 우리 모든 병력을 동원하여 요새를 공격해 파괴할 것이오. 네덜란드인들은 상륙 병력 투입을 예상하겠지만, 우리는 그렇게 하지 않을 것이오. 바다에서 성채를 돌격할 때 가장 큰 피해가 발생하니 말이오. 대신, 우리는 상륙 돌격대를 섬의 두 지점, 산타 마리아 곶과 블랑카 석호에 상륙시켜 육로로 빌렘스타트 시문까지 진격할 것이오. 야포는 이미 배에 실으라고 명령해 두었소. 퀴라소에는 뚫을 수 없는 덤불이 없으니, 대포를 땅 위로 쉽게 끌고 갈 수 있을 것이오. 네덜란드인들이 상황을 파악하지 못해 혼란스러워하는 동안, 우리는 정글에서 도시를 조준하고, 요새에서 육로로 오는 증원군의 진입을 차단할 것이오. 그 다음에는 대포로 도시를 포격할 것이오. 분명 요새의 수비대가 출격을 시도하겠지만, 야포와 우리의 머스킷총병 앞에서는 무력할 것이며, 요새의 대포가 남아 있더라도 정글로 끌고 들어올 수는 없을 것이오. 또한, 우리 함선들은 해상 상륙 준비를 하는 척하여 적에게 공포를 주고 사기를 꺾을 것이오. 시간이 지나 네덜란드인들이 자신의 처지가 절망적임을 완전히 깨달으면, 우리는 그들의 대표를 불러 협상을 시작할 것이오. 어떻게 생각하시오, 선장?";
			link.l1 = "훌륭한 계획이오! 그리고 이 계획의 가장 좋은 점은 우리가 성벽에서 병사들을 잃지 않는다는 것이오.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "제 생각을 마음에 들어해 주셔서 기쁩니다. 그럼 계속 진행하지요!";
			link.l1 = "가자!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
