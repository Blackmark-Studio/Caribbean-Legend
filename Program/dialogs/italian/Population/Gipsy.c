//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ah ciao, tesoro. Cosa desideri?";
			link.l1 = "Immagino nulla.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Ho una domanda per te.","Mi serve informazione.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Tesoro, saresti così gentile da condividere un po' d'oro? Ti dirò il tuo futuro.","Ehi, marinaio, non affrettarti così! Vuoi conoscere il futuro?","Dammi un po' di tabacco e qualche moneta d'argento, coraggioso giovane uomo. E darò uno sguardo al tuo futuro. (ammicca) Vuoi sentire un po' di magia segreta zingara?");
				link.l1 = "Mi dispiace, ma devo andare.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Ascolta signora fabbro, so che il tuo popolo è esperto in pozioni e veleni. Mi è stato detto che potresti essere interessata a questa pianta. Dai un'occhiata. Cosa ne pensi?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Ehi, occhi scuri, ho qualcosa per te... Questa è mangarosa. Vuoi comprarne un po'??";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Puoi leggere la fortuna per me?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Ho una domanda per te.","Ho bisogno di informazioni.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Ascolta, bruna, ho sentito dire che curi la gente, anche da malattie gravi. È vero?";
				link.l6.go = "dwh_gypsy_1";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Ehi, occhi scuri, hai qualche veleno per i ratti? Sono una maledetta seccatura sulla mia nave.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Certo, bello. Dammi qualche moneta e mostrami la tua mano destra. Ti parlerò del tuo futuro e ti aiuterò a evitare disastri. Non imbroglio mai! Garanzia di rimborso!";
			link.l1 = "Mi sembra che questo sia il momento in cui il tuo compagno mi svuota le tasche...Ho cambiato idea. Non sono dell'umore.";
			link.l1.go = "exit";
			link.l2 = "Quanti soldi vuoi?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah cara, quanto permette la tua borsa e desidera il tuo cuore. Più pezzi di otto, più posso vedere nel futuro!";
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, grazie per la tua carità, mio bel giovane falco! Ora ascolta:  "+sTemp+"";
				link.l1 = LinkRandPhrase("Ehi! È molto interessante. Lo prenderò in considerazione...","Davvero? Lo prenderò in considerazione...","Oh, davvero? Sei serio? Me lo ricorderò...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "La più brutta e inevitabile disgrazia ti sta aspettando. Maledetto il beffardo! Lascia che le nuvole oscure si radunino su di te e che la punizione ti trovi!";
				link.l1 = "Ah-ah! Davvero pensavi che ti avrei dato dei soldi, strega zingara? Levati dai piedi! Spero che l'Inquisizione ti prenda!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ah, grazie, mio bel giovane falco! Ora ascolta:"+sTemp+"";
				link.l1 = LinkRandPhrase("Ehi! È molto interessante. Ci penserò...","Davvero? Ci penserò...","Oh, davvero? Sei serio? Beh, me lo ricorderò...","Ehi, mi sento già meglio!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "La più brutta e inevitabile sventura ti sta aspettando. Maledetto il beffardo! Lascia che le nuvole oscure si radunino su di te e che la punizione ti trovi!";
				link.l1 = "Ah-ah! Davvero pensavi che ti avrei dato dei soldi, strega zingara? Togliti di mezzo! Spero che l'Inquisizione ti prenda!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, grazie per il tuo argento, mio bel giovane falcone! Ora ascolta:"+sTemp+"";
				link.l1 = LinkRandPhrase("Eh! È molto interessante. Ci penserò...","Davvero? Ci penserò...","Oh, davvero? Sei serio? Beh, me lo ricorderò...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "La più brutta e inevitabile disgrazia ti sta aspettando. Maledetto il beffardo! Lascia che le nuvole oscure si raccolgano su di te e che la punizione ti trovi!";
				link.l1 = "Ah-ah! Davvero pensavi che ti avrei dato dei soldi, strega zingara? Togliti di mezzo! Spero che l'Inquisizione ti prenda!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Grazie per la tua generosità, mio bel giovane falcone! Ora ascolta:"+sTemp+"";
				link.l1 = LinkRandPhrase("Eh! È molto interessante. Ci penserò...","Davvero? Ci penserò...","Oh, davvero? Sei serio? Beh, me lo ricorderò...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "La più brutta e inevitabile sfortuna ti sta aspettando. Maledetto il beffardo! Lascia che le nuvole oscure si radunino su di te e che la punizione ti trovi!";
				link.l1 = "Ah-ah! Davvero pensavi che ti avrei dato dei soldi, strega zingara? Fatti da parte! Spero che l'Inquisizione ti prenda!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Oh, non sono sicura, bello! C'era un tipo poco tempo fa che chiedeva aiuto per uccidere i ratti e poi qualcuno ha avvelenato i soldati nel forte. Le cose si sono fatte piuttosto calde per la mia gente sull'isola mentre le guardie ci interrogavano per due settimane fino a quando hanno trovato l'assassino. Era una spia nemica.","E come posso essere certo del tuo intento? Forse vuoi solo avvelenare un nobile che sei troppo codardo per sfidare in un duello onorevole??","Mi è stato detto che qualcuno ha avvelenato un commerciante nella taverna e ha rubato tutti i suoi averi. L'uomo ha sofferto a lungo prima di spirare. La schiuma gli usciva dalla bocca e si è trasformato in viola come una melanzana.. Sei responsabile di questo, amore mio?");
				link.l1 = "Voi zingare sicuramente amate condividere le vostre opinioni! Non preoccuparti ragazza, non ho intenzione di avvelenare la gente. Questo è un modo femminile di uccidere, non fa per me. Per gli uomini ho la mia spada, ma non riesco a gestire quei maledetti ratti.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) notification("Trustworthy", "Trustworthy");
			}
			else
			{
				dialog.text = "Stai cercando di intrappolarmi! No signore, non ho nessun veleno. Ho piante e pozioni, ma niente veleni.";
				link.l1 = "Come vuoi. Non mi portare sfortuna.";
				link.l1.go = "exit";
				notification("Perk Check Failed", "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Oh affascinante, un uomo così galante! (sussurrando) Pagami "+sti(npchar.quest.poison_price)+" dobloni.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Costoso... Questa roba è meglio che funzioni.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Impossibile! Ho comprato lo stesso a casa per cinque pistole! Potrei catturare ogni ratto io stesso per quella somma di denaro!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Prendili tu stesso allora e non disturbarmi. La prossima volta chiamerò la guardia.";
			link.l1 = "Non c'è bisogno delle guardie, strega, me ne sto andando.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Mostrami la pianta, cara... Mm... Suppongo che potrei comprartela. Trecento pezzi di otto, d'accordo?","Mostramelo, bello... Ehi... Beh, posso pagare duecento e mezzo per questo.","Vediamo... Oh! Un esempio interessante! Duecento pesos! Tratto?")"";
			link.l1 = LinkRandPhrase("Oh Signore... occhi scuri, non sono un semplice contadino. Conosco questa pianta. È mangarosa...","Oh, davvero?! Questo è un esemplare perfetto di mangarosa. Non cercare di ingannarmi, zingaro.","Aha, e supponi che ti darò questa mangarosa per una somma così misera.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Bene, bene, bello. Vedo che sai qualcosa su questa pianta. Cinquanta dobloni. Dammi.";
			link.l1 = "Attendi un momento! Voglio sapere come può essere utilizzato e per cosa. Puoi dirmelo? Tutta la tua gente è disposta a pagare un sacco d'oro per questo piccolo cespuglio!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Mh... Suppongo che non sia troppo male se ti parlo un po' di essa. Non sarai in grado di fare nulla con questa pianta senza competenze speciali.";
				link.l1 = "Sto ascoltando.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("La mia gente potrebbe pagare molto oro ma non svelerebbe mai i suoi segreti.","L'oro è oro e i segreti sono segreti, giovane...","Sì, siamo disposti a pagare ma non a raccontare.")+"Allora, intendi vendermi la tua mangarosa? Cinquanta dobloni è il nostro prezzo corrente per essa, nessuno ti pagherà di più.";
				link.l1 = "Oh, bene... Funziona per me comunque. Cinquanta dobloni. Prendilo";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Capiscimi, non voglio venderlo. Voglio sapere perché ne hai bisogno. Condividi la tua conoscenza con me e te lo darò gratuitamente.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendi le tue monete, giovane falco. E un'altra cosa, portaci più di queste piante. Ma possiamo comprarle solo una alla volta perché non portiamo grosse somme con noi. Le guardie non si fidano di noi e amano infastidirci...";
			link.l1 = "Bene. Se ne trovo di più, te lo porterò.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Assolutamente no! Se non vuoi venderlo - allora non farlo. Non ti dirò nulla.","Non svelerò i nostri segreti a un estraneo gorger! (sputa) Non vuoi venderlo? Al diavolo con te.","Amico, quello non è per le tue orecchie. Non vuoi venderlo per cinquanta dobloni? Vai e vendilo alla ragazza del commercio per duecento pesos.");
			link.l1 = LinkRandPhrase("Peccato per te allora! Un altro dei tuoi mi dirà comunque. E lei avrà questa pianta come regalo. Ci vediamo!","Perché così ostinato? Se non mi dirai tu, allora lo farà l'altro. E lei riceverà questo mangarosa come regalo. Addio.","Il tuo alito puzza d'aglio. Alla fine otterrò quello che voglio. Un altro della tua razza sarà più loquace e otterrà la pianta gratuitamente. Ci vediamo.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "E perché chiedi, falco?! Certo! Dammi quello.";
			link.l1 = "Dammi cinquanta dobloni.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Ops! Sembra che l'ho perso o dimenticato sulla mia nave. Che peccato. Addio...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Non preoccuparti, non ti ingannerò. Prendi le tue monete.";
			link.l1 = "Prendi la tua mangarosa. Ne porterò di più se ne trovo.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Maciniamo i boccioli in questo modo speciale, poi li asciughiamo, selezioniamo i semi e i gambi, poi li mescoliamo con il tabacco, pestiamo le nostre pipe e fumiamo il mix. E otteniamo un... effetto indimenticabile. Come l'intossicazione da alcol, ma senza mal di testa dopo. Una pianta è sufficiente per due dozzine di pipe.";
			link.l1 = "Capisco ora! Puoi insegnarmi questa tecnica segreta? Posso pagarti bene...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Giovane falco, credimi, non ne hai bisogno. Non ti coinvolgere, la pianta ti rovinerà. Offusca il cervello e ti ingrassa. Non chiedermelo nemmeno. Ma... vedo un uomo coraggioso di fronte a me, con una spada, un uomo di mare...forse anche un capitano?";
			link.l1 = "Hai ragione.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Ascolta qui allora. La Mangarosa può essere utilizzata per cose molto più nobili e potrebbe esserti utile. Una nostra guaritrice conosce tutti i suoi segreti. È lei quella di cui hai bisogno\nDammi la pianta e ti dirò il suo nome e dove trovarla. Convincerla a condividere i suoi segreti con te sarà però il tuo problema.";
			link.l1 = "Bene. Prendi la pianta e dimmi come trovare il tuo mago zingaro.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Si chiama Amelia. Vive da sola in una piccola casa tra le dune non lontano dal mare, da qualche parte sulla costa sud-ovest del Mare Spagnolo, come dicono i saggi.";
			link.l1 = "Oh per l'amor di Dio, potresti per favore essere più specifico?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Sei un marinaio, coraggioso falco, e io non lo sono. Cerca lei dove ho detto. La sua casa è davvero vicina alla costa. Si trova vicino a una baia proprio a sud-ovest del Mar dei Caraibi - i marinai dovrebbero conoscerla.";
			link.l1 = "Bene, cercherò di trovarlo...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Portale una Mangarosa o non ti parlerà nemmeno. E non dimenticarti di portare anche i dobloni, non pensare nemmeno che ti insegnerà gratis!";
			link.l1 = "Che avarizia. Ci penserò su. Grazie per il tuo racconto!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_gypsy_1":
			dialog.text = "Verità, "+GetSexPhrase("tesoro","bellezza")+". Ho il mio modo di affrontare ogni malattia. Ho aiutato comuni cittadini, mercanti, persino i ricchi a rimettersi in piedi. Perché, persino il governatore ha fatto ricorso alle mie pozioni quando nessun altro poteva aiutare. La malattia non teme l'oro, ma non può resistere ai miei rimedi.";
			link.l1 = "Allora perché rifiuti di curare una ragazza gravemente malata, la figlia di Thomas Morrison?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "Chi ti ha raccontato una tale sciocchezza, "+GetSexPhrase("falconetto","piccioncino")+"? Non ho rifiutato di aiutare. È stato suo padre che mi ha cacciato di casa. Avevamo concordato che l'avrei curata, e improvvisamente ha cambiato idea. Mi ha buttato fuori come se fossi un nemico giurato.";
			link.l1 = "Allora ha condannato sua figlia a soffrire con le sue stesse mani?";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "No, no, è un padre amorevole. È difficile immaginare perché abbia agito in quel modo.";
			link.l1 = "Hai provato a parlare di nuovo con lui?";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "Non mi lascia nemmeno avvicinarmi alla casa. Ascolta, "+GetSexPhrase("tesoro","bellezza")+", dal momento che ti preoccupi per il destino di una povera ragazza, forse potresti cercare di capire cosa sta succedendo? Parla con Thomas, aiutami a salvare il bambino dalla sofferenza.";
			link.l1 = "Certo che aiuterò. Dove posso trovare Thomas?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "No, moro. In ogni caso, sono sicuro che suo padre ha i suoi motivi per rifiutare il tuo aiuto. Non mi intrometterò. Lascia che decida lui, è sua figlia.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "La loro casa è vicino al muro, nella parte settentrionale della città, accanto a una grande villa con colonne. Vai avanti, "+GetSexPhrase("falconetto","piccioncino")+", parla con lui e torna da me.";
			link.l1 = "Torno presto.";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			
			AddQuestRecord("DWH", "2");
			
			sld = GetCharacter(CreateCharacterClone(npchar, -1));
			sld.id = "DWH_gypsy";
			npchar.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Tomas", "citiz_13", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Morrison";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas";
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
			sld.City = "SentJons";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ascoltami, falco coraggioso, potrei essere un zingaro, ma anche noi condanniamo la violenza aperta. Per favore, infila la tua spada.","Ascoltami, valoroso falcone, come cittadino di questa città ti chiedo di infilare la tua lama.");
			link.l1 = LinkRandPhrase("Bene.","Come desideri.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
