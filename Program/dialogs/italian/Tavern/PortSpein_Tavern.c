// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uffa, dove se ne è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "Sentivo dire che il morbo sta dilagando nel vostro forte. Pensi che l'epidemia si diffonderà in città?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Cosa puoi dirmi sul comandante del forte?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dimmi, il nome 'Juan' significa qualcosa per te?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Ascolta, nell'aprile 1654 una fregata ha attraccato al tuo porto sotto il comando del Capitano Miguel Dichoso e poi è sparito. C'è qualcosa che puoi dirmi al riguardo?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Il comandante afferma che non c'è pericolo. Quelli troppo curiosi finiscono rinchiusi nelle casematte. Non sono uno di quelli, mi dispiace.";
			link.l1 = "Davvero? Un oste che non vuole ascoltare pettegolezzi - questa è una novità! Potrebbe essere che il tintinnio dei pesos possa riportare la tua curiosità?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "L'argento è allettante, naturalmente, ma la mia pelle vale di più. Forse potrei parlarti di qualcos'altro, signore? In realtà, sono sempre felice di parlare, basta iniziare la conversazione!";
			link.l1 = "Allora così si svolge la questione... Bene, in questo borsellino ci sono tremila pezzi da otto e avremo una bella chiacchierata sul tempo, affare fatto?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Oh, sei persistente, signore. Ricorda solo, questa conversazione non è mai accaduta. (sussurrando) Ho sentito dire più volte già da un anno intero che la gente stava bruciando nelle nostre prigioni, morendo di consunzione. Puoi incolpare le autorità, puoi incolpare Dio, o il Diavolo, ma la maggior parte è attribuita alla sfortuna. Questa maledetta malattia ruba vite così velocemente. A volte mettono un uomo perfettamente sano lì dentro e in una o due settimane se ne è andato. Proprio così...";
			link.l1 = "Caspita... Un intero anno, dici? E nessuno si è preso la briga di fare qualcosa al riguardo?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Chi se ne importa, signore? Chi se ne importa dei prigionieri? La feccia della società - così dicono i grandi uomini in seta. C'era un medico che lavorava nelle segrete. Ha cercato di curare quelle povere anime. Non è durato a lungo, sembra che la malattia lo abbia fatto fuori anche lui\nIl comandante non lascia entrare la gente ora, e le nostre autorità non prestano attenzione a tali questioni, specialmente quando devono pagare meno per le razioni carcerarie.";
			link.l1 = "Interessante, ma cosa c'è in questa malattia che ti spaventa così tanto che, rinchiusi dentro mura sicure, stiamo sussurrando come suore in confessionale?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "È difficile per me dirtelo, ma c'era un tipo qui. È stato preso per contrabbando ed è stato rinchiuso per circa mezzo anno finché i suoi amici non lo hanno comprato. Beh, sai - hanno misurato l'oro per chiunque ne avesse bisogno, hanno aspettato quanto gli è stato detto, e il tipo è uscito. Ma da allora è diventato completamente pazzo.";
			link.l1 = "Più matto di un ratto di sentina?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Immagino. Da allora è diventato inutile per i suoi compagni, passando tutto il giorno qui, bevendo fino alla morte. Sembrava che volesse cancellare qualcosa dalla sua testa. Ogni volta che si ubriacava, raccontava storie sulla 'consunzione' che prende la gente in silenzio. Queste erano le sue parole esatte. Secondo lui, la 'consunzione' è la cosa peggiore che possa capitare a un uomo.";
			link.l1 = "Le divagazioni di un ubriaco. E allora?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Nulla, a parte il fatto che ha trovato un po' di coraggio liquido e ha iniziato a parlare sempre più, poi così, come niente fosse, qualcuno gli ha tagliato la gola e lo ha gettato nel fosso... e a me non importa chi l'ha fatto e perché.";
				link.l1 = "Cosa puoi dire riguardo il comandante?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Nulla, a parte il fatto che si è fatto coraggioso e ha iniziato a parlare sempre più e poi così come così qualcuno gli taglia la gola e lo getta nel fossato... e chi l'ha fatto e perché è tutto lo stesso per me. (alza la voce) Sì, le baie e le barriere coralline qui sono davvero pericolose, signore. Devi fare attenzione quando le tempeste arrivano impetuose dalle Grandi Antille, perdi il gage del tempo e sei finito! Buon riposo, signore, grazie per essere passato!";
				link.l1 = "Tempeste... giusto. Grazie anche a te.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "Cosa c'è da dire su di lui? È un colonnello, arrivato dall'Europa un paio di anni fa avendo ricevuto questo posto. Pare che sia stato degradato lì nel Vecchio Mondo per qualche sporco affare in cui era coinvolto. Non so se sia vero, ma all'inizio c'erano voci. Ma chi non ha voci su di sé, vero?";
			link.l1 = "Affari sporchi, dici... Interessante. Qualcos'altro?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Ebbene, cosa posso dire... Il colonnello sembra un uomo che tiene molto alla propria sicurezza. Certo, questi luoghi non sono sicuri a causa di pirati, banditi, indiani e altra feccia, ma il Signor Comandante non lascia mai la sua casa senza diversi bodyguard\nC'è la sua villa in questa città e l'ha trasformata in una piccola fortezza - i suoi servi sono ben armati e tengono le finestre sbarrate.";
			link.l1 = "Ma durante il giorno lui serve in prigione, vero?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Sì, ma quella villa è praticamente in attesa di un'imboscata o di un'invasione. Comunque, il Signor Comandante non torna spesso lì a quanto pare una vera fortezza è più la sua roccaforte, eh-eh.";
			link.l1 = "Grazie, sei stato di grande aiuto. Ci vediamo dopo, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Quale? Ce ne sono tanti qui, la gente di solito ha anche i cognomi... o almeno un soprannome...";
			link.l1 = "Stavo solo pensando... Forse il suo soprannome è 'Consumo', mai sentito prima?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Oh mio Dio, stai parlando di nuovo di quello! No, grazie a Dio, non ho sentito. Lo giuro! E ora cambiamo argomento. Per favore!";
			link.l1 = "Bene va bene, non farti venire un infarto...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		case "guardoftruth":
			dialog.text = "Lo ricordo. Spesso passava dalla mia taverna, ma non parlava molto. Beveva qualche bicchiere di rum, sussurrava qualcosa ad alcuni clienti e se ne andava. Molto cupo e serio come tutti su quella fregata. Mercenari dall'aspetto pericoloso che tenevano le loro lame pronte\nC'era una voce che la fregata fosse piena di tesori, ma non credo a tali storie. Il carico prezioso non viene mai trasportato su una sola nave senza una scorta. Sono rimasti qui un giorno, poi se ne sono andati. Verso l'Europa, ho sentito. Questo è tutto quello che so.";
			link.l1 = "Capisco. Beh, è almeno qualcosa...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
