// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 당신이 물으려 한 것이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 미안하오.","지금은 아니오. 장소와 시간이 맞지 않소."),"사실 지금은 드릴 말씀이 없소, 미안하오.","나중에 물어보겠소.","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "총독 나리, 끔찍한 소식을 전해야 하겠습니다. 간단히 말씀드리죠: 나리의 부인께서 나리의 재물을 훔치려 하십니다. 부인께서 저에게 나리의 장식장 서랍 자물쇠를 따 달라고 설득하려 하셨습니다. 이 사실을 아셔야 할 것 같아 말씀드립니다.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", 나리. 저는 총독 슈발리에 드 푸앵시의 명령을 받고 이곳에 왔습니다. 저의 임무는 본국에서 식민지 시찰 명령을 받고 온 노엘 포르게라는 이름의 남작을 토르투가로 모시는 것입니다. 그의 주된 목적은 프랑스 서인도 무역회사를 설립하는 데 있습니다. 그를 소개해 드리겠습니다... 자세한 내용은 직접 설명할 것입니다.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "뭐, 뭐라고? 또? 그년! 이번엔 반드시 후회하게 해주지, 맹세한다! 캄파초가 그년 비명을 지르게 만들 거야. 아직도 왜 여기 있어? 당장 꺼져!";
			link.l1 = "나는 생각했소...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "항상 똑같군! 여기, 이것이나 가져가! 내 책상 위에 있는 전부야! 이제 나가시오!";
			link.l1 = "감사합니다, 각하. 저는 이만 물러가겠습니다.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "항상 똑같군! 자, 이거 가져가! 내 책상 위에 있는 건 이게 전부야!.. 그래도, 좋아, 너는 내 섬에 가득한 멍청이들과 패배자들과는 달라 보이는구나. 조금 더 얹어주지... 이제 나가!";
			link.l1 = "감사합니다, 각하. 저는 이만 물러가겠습니다.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "좋소, Charles de Maure 선장. 남작에게는 그에 걸맞은 대우를 할 것이며, 그가 임무를 완수할 수 있도록 내가 할 수 있는 모든 지원을 하겠소.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
