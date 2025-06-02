// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo occupato, lavoro su questioni coloniali e tu continui a infastidirmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, mi dispiace.","Non ora. Luogo e tempo sbagliati."),"È vero, non ho nulla da dire ora, mi dispiace.","Chiederò, più tardi.","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Signor Governatore, ho terribili notizie per lei. Sarò breve: sua moglie vuole rubarle. Ha cercato di convincermi a scassinare uno dei suoi bauli. Ho pensato che dovesse saperlo.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Signore. Sono qui come ordinato dal Governatore Generale Chevalier de Poincy. Il mio compito è di consegnare un barone di nome Noel Forget a Tortuga, che è arrivato dallo stato genitore con l'ordine di ispezionare le colonie. Il suo scopo principale è la fondazione di una Compagnia di commercio francese nelle Indie occidentali. Permettetemi di presentarvelo... Lui spiegherà tutti i dettagli da solo.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "C-c-cosa? Di nuovo? Quella stronza! Se ne pentirà, oh lo giuro! Kampacho la farà urlare. Perché sei ancora qui? Vattene all'inferno!";
			link.l1 = "Pensavo...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Sempre lo stesso! Prendi questo! È tutto quello che ho sul tavolo! Ora vai via!";
			link.l1 = "Grazie, vostra Eccellenza. Mi accompagnerò fuori.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Sempre lo stesso! Prendi questo! È tutto quello che ho sul tavolo!.. Anche se, va bene, non sembri come il resto degli idioti e perdenti che riempiono la mia isola. Prendi un po' di più... Ora vai via!";
			link.l1 = "Grazie, vostra Eccellenza. Mi accompagnerò fuori.";
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
			dialog.text = "Bene, capitano Charles de Maure. Il barone sarà trattato di conseguenza e farò quel che posso per aiutarlo con il suo compito.";
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
