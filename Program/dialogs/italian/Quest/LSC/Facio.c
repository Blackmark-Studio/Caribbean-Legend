// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ciao, ciao... Sei nuovo da queste parti? Non mi pare d’aver visto la tua faccia prima. Permettimi di presentarmi – sono Giuseppe Fazio, uno che qui sull’Isola Giustizia sa come risolvere i guai.";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+"Hai ragione, sono appena arrivato qui. Perdonami la curiosità – ma che razza di guai vi tocca risolvere su quest’isola?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, ancora tu, caro "+pchar.name+"! Cosa ti porta nella mia umile dimora?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, ho un brutto dissapore con una delle famiglie. Devo trovare una soluzione a questa faccenda.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, sto cercando un uomo di nome Adolf Barbier. Mi hanno detto che hai bevuto con lui alla taverna di recente...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, dicono che tu sia immune al rum. Puoi tracannare a volontà e resti sempre in piedi come un vecchio lupo di mare.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && GetCharacterItem(pchar, "gold_dublon") >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Sono pronto a giocare al tuo gioco. Ecco la mia posta.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Voglio sapere la parola d’ordine attuale dei clan per poter entrare nei loro territori.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconterai gli ultimi pettegolezzi?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Niente di speciale, Giuseppe. Volevo solo rivederti.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Di tutto un po', caro mio, di tutto un po'. Ad esempio, faccio da paciere tra l’ammiraglio e i clan. Come avrai già sentito, i Rivados, i Narvali e l’ammiraglio sono cani e gatti. Quando l’aria si fa pesante, tocca a me rimettere le cose a posto.\nInoltre, spesso mi tocca fare da terzo incomodo quando l’ammiraglio smercia provviste ai clan. Ma questa è solo una briciola dei miei affari. Quindi se ti capita di avere grane coi Rivados o coi Narvali – non farti scrupoli a chiedere il mio aiuto, vedremo che si può fare.";
			link.l1 = "Bene. Ci rifletterò su.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Quale clan?";
			link.l1 = "Narvali.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Vuoi incontrare Donald Greenspen, dico bene?";
			link.l1 = "Esatto. Dunque, conosci la parola d’ordine?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Vuoi vedere Eddie il Nero, dico bene?";
			link.l1 = "Qualcosa del genere. Allora, conosci la parola d’ordine?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Certo! Ma lascia che ti spieghi meglio. Le parole d’ordine sono sempre di una sola parola e cambiano ogni settimana. Ogni settimo, quattordicesimo, ventunesimo e ventottesimo giorno del mese.\nTieni d’occhio la data, o rischi di sbagliare. Ah, e come avrai già capito, non è beneficenza questa: cinquanta dobloni per la parola d’ordine. Solo dobloni, bada bene.";
				link.l1 = "Cinquanta dobloni? È una cifra esorbitante!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Certo, figliolo. Conosci il prezzo. Hai cinquanta dobloni?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 50)
				{
					link.l1 = "Sì. Prendi le tue monete.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Purtroppo no. Forse più tardi...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Ehi-ehi, figliolo, calmati. Non essere avido, fidati: so bene quanto vale davvero la mia dritta. Non pensare mica che ti lascerei passeggiare impunemente tra le navi di "+pchar.questTemp.LSC.parol+" vero? Giusto. Quindi devi essere pronto a perdere qualche doblone... Allora, sei pronto a sborsare cinquanta dobloni?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "Sì. Prendi le tue monete.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Purtroppo, non possiedo tanto denaro. Forse più tardi...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveItems(pchar, "gold_dublon", 50);
			dialog.text = "Magnifico! Un piacere fare affari con te. La parola d’ordine attuale per "+pchar.questTemp.LSC.parol+" è: '"+sTotalTemp+"Ricordalo bene e non sbagliare, altrimenti non darò nemmeno uno scudo bucato per la tua pellaccia.";
			link.l1 = "Lo so, lo so... Grazie!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ah, ma certo, il mio buon vecchio Adolfo! Sì, ho parlato con lui. Vedi, caro mio, ero ben lieto di riavere i miei soldi, quei dobloni che pensavo di non rivedere mai più! Adolfo aveva preso in prestito una bella somma lasciandomi in pegno il suo fucile da vero campione, ma poi ha avuto delle noie a restituirmi il denaro.\nAvevo perso ogni speranza di rivedere un soldo e stavo già pensando di vendere quello stutzen al nostro amato Axel Yost. Ma all’improvviso, il caro Adolfo mi ha portato l’oro! Pare che sia riuscito a raccattare abbastanza monete non solo per riscattare lo stutzen, ma anche per comprarsi la cabina di Sessile Gallard in cima alla ‘Santa Florentina’!\nDi certo, molto meglio che dormire in una stiva mezza allagata.\nCosì Adolfo s’è ripreso il fucile, ha una nuova tana e io ho le mie monete. Come potevo rifiutare un bicchiere in sua compagnia, soprattutto visto che pagava lui?";
			link.l1 = "Ah, certo! Avevi mille motivi per bere. E tutto gratis... Grazie, Giuseppe, mi hai dato una gran mano. Ora so dove trovare Adolf.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "È sempre un piacere, caro. Ma non cercare Adolfo nella sua cabina prima che cali la sera, è impegnatissimo, corre qua e là per certe faccende... Eh sì, e passa più spesso da me, facciamo due chiacchiere!";
			link.l1 = "Ti inviterò quando avrò la mia cabina... Addio e buona fortuna!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Eh? Perché t'intrufoli qui come se avessi il fuoco alle calcagna? Chi diavolo credi d'essere??";
					link.l1 = "La tua giustizia... velenatore!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Risparmiami! Ti giuro, mi hanno costretto! Mi hanno puntato una pistola contro...";
					link.l1 = "Zitto. Lo so bene. Dov’è quell’ultimo bastardo? Dov’è Marcello il Ciclope?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Lo giuro, mi ci hanno costretto! Ho già raccontato tutto all’ammiraglio! Non potevo oppormi, mi avrebbero...";
					link.l1 = "Zitto. Lo so già. Dov’è l’ultimo bastardo? Dov’è Marcello Ciclope?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Cosa... cosa hai detto?";
			link.l1 = "So tutto, maledetto bastardo. Hai tramato con Chad Kapper. Hai portato una botte di rum avvelenato all’ammiraglio. Ora prega, disgraziato figlio di cane...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Aspetta! Fermati! Risparmiami! Ti giuro, mi hanno costretto! Avevano una pistola puntata contro la mia...";
			link.l1 = "Zitto. Lo so già. Dov'è l'ultimo bastardo? Dov'è Marcello il Ciclope?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Io... io... non lo so!";
			link.l1 = "Tu menti, canaglia! Lo vedo bene. Dov’è Ciclope?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Ha... ha ricevuto qualche ordine da Kapper ed è sparito. Non so dove sia!";
			link.l1 = "Bugie, ancora. Tu sai tutto. Non fare il codardo, lurido bastardo – Kapper è morto e non potrà più farti del male. Ma se non mi dici dov’è Marcello – ti sventro come un porco, qui e ora! Cosa ha ordinato Chad al Ciclope?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Lo ha mandato ad ammazzare... la Rossa Mary.";
			link.l1 = "Cosa?! Parla subito, come diavolo pensa di riuscirci? È impossibile entrare nella sua cabina! Come diavolo conta di farla fuori?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Entrerà nella cabina di Jurgen quando il fabbro sarà fuori. Poi scenderà nella stiva, la attraverserà e raggiungerà la cabina di Mary.   Dopo non gli resterà che aspettare che la ragazza si volti o si addormenti.  Così mi ha detto Chad. Non so altro, lo giuro!";
			link.l1 = "Basta così. Quando se n’è andato? Quando, ti domando, il Ciclope è andato alla ‘Fucina di Cerere’?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Sarà già nella cabina di Jurgen... o forse si sta infilando nella stiva...";
			link.l1 = "Maledizione! Non ho tempo da perdere a nuotare attorno all’Isola! Dimmi la parola d’ordine per salire sulle navi dei Narvali! Parla, e se mi menti, io troverò comunque il modo di restare in vita, ma tu ci lascerai la pelle, te lo giuro!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"...'";
			link.l1 = "Capito. Ora prega che la ragazza sopravviva.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Ti ho già detto tutto quello che sapevo! Te lo giuro!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "Lui... Lui si trova da qualche parte all'interno della 'Fleron'. Chad gli ha ordinato di nascondersi lì e aspettare i suoi prossimi ordini.";
			link.l1 = "Capisco. Spero per te che sia la verità...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Ah davvero? Suvvia, figliolo, quale clan ti dà noia?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narvali.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "I pirati dell’Ammiraglio.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Niente del genere. Scherzavo, Giuseppe, sto bene.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Beh, non è davvero un conflitto, solo un piccolo malinteso, eh eh. "+sti(npchar.quest.price)+"  dobloni e il tuo problema svanirà in un giorno.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Certo, ne ho sentito parlare. Hai combinato un bel casino, mio caro. Ma c’è una via d’uscita. "+sti(npchar.quest.price)+" dobloni e la tua grana sarà sparita in un sol giorno.";
				else dialog.text = "Tutta l'Isola Giustizia sa della carneficina che hai scatenato. Non sarà facile darti una mano, ma una speranza c'è. "+sti(npchar.quest.price)+" dobloni e cercherò di risolvere il tuo problema.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Tieni, prendi le tue monete e arrangiati.";
				link.l1.go = "pay";
			}
			link.l2 = "Purtroppo, al momento non ho abbastanza dobloni con me. Ma tornerò più tardi con la somma, e potremo riparlare allora.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Be’, in realtà non è proprio un conflitto, solo un piccolo malinteso, eh-eh. "+sti(npchar.quest.price)+"  dobloni e il tuo problema sarà risolto in un giorno.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Certo, ne ho sentito parlare. Hai combinato un bel casino, caro mio. Ma c’è una via d’uscita. "+sti(npchar.quest.price)+"  dobloni e il tuo problema sarà risolto in un giorno.";
				else dialog.text = "Tutta l’Isola Giustizia sa della carneficina che hai scatenato. Darti una mano non sarà affatto semplice, ma forse una speranza c’è ancora. "+sti(npchar.quest.price)+" dobloni e vedrò di risolvere il tuo problema.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Tieni, prendi le tue monete e arrangiati.";
				link.l1.go = "pay";
			}
			link.l2 = "Purtroppo non ho abbastanza dobloni con me al momento. Ma tornerò più tardi, e allora riparleremo.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Beh, in realtà non è proprio un conflitto, solo un piccolo malinteso, eh eh."+sti(npchar.quest.price)+" dobloni e vedrai che il tuo guaio svanirà in un batter d’occhio.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Certo, ne ho sentito parlare. Hai fatto un bel putiferio, caro mio. Ma c’è una via d’uscita. "+sti(npchar.quest.price)+" dobloni e il tuo grattacapo sparirà in un giorno.";
				else dialog.text = "Tutta l’Isola Giustizia sa del massacro che hai compiuto. Non sarà facile darti una mano, ma forse una speranza c’è. "+sti(npchar.quest.price)+" dobloni e proverò a risolvere il tuo problema.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Ecco, prendi le tue monete e arrangiati.";
				link.l1.go = "pay";
			}
			link.l2 = "Purtroppo, al momento non ho abbastanza dobloni con me. Ma tornerò più tardi, e allora riparleremo.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Splendido. Ora siediti e riposa un po'. Faresti meglio a restare nella mia cabina finché non sistemo il tuo guaio. Non vorrei che tu peggiorassi la situazione, caro mio.";
			link.l1 = "D’accordo...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Su, figliolo! Mentono, tutti mentono, ah-ah. La mia testa è solo un po' più dura della media, ma sono un uomo come te, e quindi anch'io mi ubriaco di rum. La gente beve rum per ubriacarsi, e nient'altro. Ci hai mai riflettuto sopra, caro?";
			link.l1 = "Proprio vero.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Vuoi giocare a un gioco da pazzi con me? Si chiama ‘bevi fino all’ultima goccia!’, ah-ah! Scommetto che ne hai già sentito parlare, eh?";
			link.l1 = "Sì, se ne sono sentite delle voci... Io lo chiamerei 'sbattere la faccia sul tavolo'.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ah-ah-ah, figliolo mio, hai fatto ridere questo vecchio lupo di mare, che altro vuoi che dica! 'Faccia sul tavolo!' Me lo segno... Allora, che ne dici? Giochiamo per cento dobloni?";
			link.l1 = "Cento dobloni?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Sì, e chi perde paga da bere. Affare fatto?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 100)
			{
				link.l1 = "Sì, d’accordo. Ecco la mia posta.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. Non ho poi così tanti dobloni.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Ebbene, vieni a trovarmi quando li avrai, e giocheremo!";
			link.l1 = "Va bene...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveItems(pchar, "gold_dublon", 100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eccellente, caro mio! Allora vediamoci alle nove di sera alla taverna di Sancho! Sì, la tua posta resterà con me se farai tardi, è una delle regole. Ma tu non farai tardi, vero ragazzo mio?";
			link.l1 = "Certo, Giuseppe. Preparati a una rissa a colpi di bottiglia!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "E tu, e tu, caro mio! Faccia sul tavolo! Ah-ah!";
			link.l1 = "Ci vediamo alle nove in taverna!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Ebbene, caro mio, sei pronto a baciare il tavolo, eh-eh? Il buon Sancho ci ha già portato il rum. Non credo serva spiegarti le regole, giusto? Sono piuttosto semplici: si beve dalla stessa bottiglia finché uno di noi non crolla.\nSì, possiamo parlare, anzi, dobbiamo parlare! Far quattro chiacchiere con gente rispettabile è un piacere, non trovi? E se vinci, Sancho ti darà il tuo premio. Sei pronto?";
			link.l1 = "Direi di sì. Cominciamo, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Quindici uominicci sulla... hic! Ahah! Yo-ho-ho... E... una bottiglia...";
			link.l1 = "Glorioso...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
