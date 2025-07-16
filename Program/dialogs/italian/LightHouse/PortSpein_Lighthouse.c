// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Cosa ti serve, "+GetAddress_Form(NPChar)+"?","È la terza volta che provi a chiedermi...","Ne ho abbastanza di te, sparisci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi dispiace, ho cambiato idea.","Non è niente, scuse."),"Ho dimenticato, mi scuso...","La terza volta è la volta buona, eh? Scusami...","Scusa, scusa! Allora me ne vado da solo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Ascolta, una fregata sotto il comando di Miguel Dichoso era qui nel aprile 1654, poi è scomparsa. Puoi dirmi di più sulla sua nave? Forse hai visto cosa le è successo o dove è andata? Ti ricordi di qualcosa?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Sì, Signore, era uno spettacolo da vedere! Non dimentichi cose del genere, ah!";
			link.l1 = "Mi può dire cosa è successo?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "La fregata del Signor Dichoso ha gettato l'ancora nel porto di San Jose. Avevo una buona vista per vedere tutto, eh. Ti dico, era un'ottima fregata, un capolavoro, giuro sul mio cuore sanguinante! L'equipaggio si vantava della velocità, poteva accelerare fino a sedici nodi!\nHanno passato un giorno qui, poi hanno preso il largo direttamente verso l'isola di Tobago. Poi, non ci crederesti, sono cominciate a succedere cose strane con il tempo non appena erano scomparsi all'orizzonte. Il tempo era stato bello per giorni all'epoca, nemmeno una nuvola!\nEppure questa terribile tempesta è arrivata dal nulla. Sembrava che lo stesso Nettuno ci avesse fatto visita! Sono salito in cima al mio faro per accenderlo, ma poi l'ho vista... Santa Quiteria! Si stava precipitando su enormi onde accompagnata da un gigantesco tornado!\nLa fregata volava vicino al mio faro come una scintilla e poi era stata guidata dalla tempesta a Nord Ovest! Nessuno ha più visto Santa Quiteria da allora. Solo un'ora dopo il vento, la pioggia e le nuvole erano scomparsi e il sole splendeva, nessun segno della tempesta! Non ho mai visto nulla di simile! Anche se quel giorno ho raccolto così tanto ambra dalla mia baia...";
			link.l1 = "Allora la tempesta ha spinto la fregata di nuovo nel mare dei Caraibi?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "È vero! Lontano, verso la Martinica. Dubito che Dichoso sia sopravvissuto a quella tempesta, stava facendo del suo meglio! La fregata non stava affondando, ma Santa Quiteria deve essere sul fondo del mare tra i coralli adesso... A dire il vero, non sei la prima persona che mi chiede di Dichoso e della sua fregata.";
			link.l1 = "Davvero? Chi altro era interessato a Miguel?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Un audace capitano della flotta spagnola, nientemeno! Si è presentato come...oh... l'ho dimenticato... Ah! Signor Diego. Il suo nome era Diego, ma il suo cognome... de Montagna o de Montoya. Qualcosa del genere. Mi ascoltava proprio come stai facendo tu, mi ha ringraziato ed è andato via. Non l'ho più visto da allora.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "Capisco. Grazie mille per il tuo racconto, mi hai aiutato molto. Accetta la mia gratitudine in monete. Addio.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Capisco. Grazie mille per il tuo racconto, mi hai aiutato molto. Addio.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
