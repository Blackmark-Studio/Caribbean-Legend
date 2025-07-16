void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Fermati dove sei e lascia cadere la tua arma! Il tuo denaro o la tua vita!","Fermati dove sei, "+GetSexPhrase("viaggiatore","ragazza")+"!) Non toccare la tua arma e niente movimenti improvvisi!","Fermati dove sei, "+GetSexPhrase("viaggiatore","ragazza")+"! Questa è una strada a pedaggio. Se vuoi passare devi pagare il pedaggio."),LinkRandPhrase("Ehi, "+GetSexPhrase("compagno","ragazza")+"! Non così veloce! Voglio vedere quanto è pesante la tua borsa.","Vieni più vicino, amico. Voglio sentire il tintinnio dell'oro nella tua borsa.","Attento, "+GetSexPhrase("compagno","ragazza")+". Io e i ragazzi abbiamo scommesso su quant'oro entrerà nella tua borsa. Ora dobbiamo controllarlo prima che le cose si mettano male."),"Non affrettarti, "+GetSexPhrase("viaggiatore","tesoro")+"! Facciamo una chiacchierata franca, lo faremo?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Perché dici queste sciocchezze?","Che succede?","Di cosa stai parlando?"),"Cosa intendi?","Cosa stai insinuando?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Briganti?! Perfetto, non vedevo l'ora di una lotta!","Oh, siete briganti! Vi state nascondendo dalla giustizia, presumo? Beh, sembra che la giustizia sia appena arrivata per voi...","Non ti hanno insegnato che disturbare gli estranei con le tue sciocchezze è un segno di maleducazione? Sembra che debba insegnarti io questa lezione..."),LinkRandPhrase("Oh, sei un insolente, vero?! Spero che la tua lama sia affilata quanto la tua lingua.","Vedo che sei un maestro della tua lingua, spero tu sia anche un maestro della tua spada.","Oh, briganti! Tanti dei vostri sono stati impiccati, ma non riuscite ancora a smettere di camminare dritti verso la forca."),LinkRandPhrase(RandPhraseSimple("Oh, briganti! Sai, di solito non spreco parole con la tua specie!","Che tipo insolente! Puzza come una pila fumante di merda e osa ancora rivolgersi a una persona decente "+GetSexPhrase("ragazzo","ragazza")+"."),"Non sprecherò parole con te, ma troverai la mia pistola molto eloquente!","Briganti di nuovo! Beh, non vi prometto la forca, ma posso sicuramente regalarvi un paio di buchi nella pancia!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("E sai che un gruppo di pattuglia mi sta seguendo da vicino? Posso solo dare loro un fischio e sei finito.",RandPhraseSimple("Sai, posso chiamare la pattuglia, non hai paura di questo? Sono nelle vicinanze. Immagino, ti stanno cercando.","Una squadra di pattuglia è stata recentemente inviata per cercarti, e saranno qui da un momento all'altro. Stai correndo un grande rischio."),RandPhraseSimple("Ti consiglierei di correre il più veloce possibile. Una pattuglia sta arrivando da questa parte, ho appena parlato con il loro ufficiale.","Avrei volentieri continuato la nostra conversazione, ma temo che l'unità di pattuglia che ho appena incontrato, non permetterà alla nostra conoscenza di evolvere in un'amicizia stretta."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Non fare il buffone! Soldi in contanti e forse allora ti lascerò andare!","Non hai sentito parlare del pedaggio di viaggio? Se non ti separi dal tuo oro, ti separerai da una testa!","Eh, questa semplice avventura ti costerà una borsa... se non mi arrabbio."),RandPhraseSimple("È molto semplice. Ci dai tutto il tuo oro e poi sei libero di andare, oppure resti qui, e ci prendiamo tutto il tuo oro, comunque. Ma penso che la seconda opzione non sia di tuo gradimento, he-he.","Non fingere di non capire! Dammi la tua borsa se non vuoi che la prenda dal tuo cadavere!"),"Ti spiego, se sei così tonto. Mi dai tutti i tuoi soldi, se tieni alla tua vita.");
			Link.l1 = "Maledetto, mascalzone! Ho solo "+makeint(makeint(Pchar.money)/20)*10+" pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Vuoi i miei soldi? Vieni a prenderli, e vedremo quanto vali!","Come osi, maleducato! Ti insegnerò una lezione di buone maniere!","Che sicurezza in te stesso! Beh, vediamo come ti comporti contro un vero "+GetSexPhrase("lupo di mare","Lupa dei mari")+"!"),LinkRandPhrase("Dovresti essere frustato per un tale oltraggio!","Briganti! Pregate i vostri diavoli per un posto caldo all'inferno!","Dovreste essere stati impiccati molto tempo fa, corvi della forca! Beh, sembra che dovrò macchiare la mia sciabola con il vostro sangue!"),RandPhraseSimple("E cosa ti fa pensare che ti darò i miei soldi?","E non hai notato che sono ben armato e non sono qui per una semplice passeggiata?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Maledizione! Va bene, puoi andare. Ma nemmeno pensare di fare rumore mentre sei qui!","Questa volta sei stato fortunato, ma la prossima volta ci dovrai il doppio! Non dimenticarti di ricordarcelo, eh-eh.");
				Link.l1 = RandPhraseSimple("Ma certo.","Fuggi già, mentre ancora puoi.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Ti uccideremo in silenzio, non emetterai nemmeno un gemito.","Maledizione! Dovremo ucciderti rapidamente prima che tu possa dare l'allarme.");
					Link.l1 = "Ebbene, questo è il tuo funerale. Ti ho avvertito.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("E perché dovrei preoccuparmi della tua pattuglia? Io li sto pagando. Quindi, dammi la tua borsa e smetti di parlare.","Pensi di potermi spaventare? Io sono 'la pattuglia' per gente come te in questa giungla. Nessuno è ancora partito senza pagare una tassa!");
					Link.l1 = "Maledetto, canaglia! Ho solo "+makeint(makeint(Pchar.money)/20)*10+" pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("Eh, non obbedirò agli ordini di un codardo come te.","Farò un paio di nuovi buchi nel tuo cranio per via di tale impudenza! Solo per ventilare un po' il tuo cervello.","Un tale impudenza non rimarrà impunita!"),"Non avresti dovuto farlo...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Ehi, non agitarti così, "+GetSexPhrase("compagno","ragazza")+"! Stavo solo scherzando! Puoi continuare la tua strada!","Bene, ho cambiato idea. Puoi andare, se sei così formidabile."),"Cosa, un "+GetSexPhrase("'capitano galante'","'ragazza militante'")+"? di nuovo? Va bene, vai in pace...","Rilassati, "+GetSexPhrase("compagno","ragazza")+". Vedi, ci siamo sbagliati, "+GetSexPhrase("pensavamo che tu fossi un mercante","pensavamo che tu fossi un mercante")+". Puoi andare.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Bene, fino a quando ci incontreremo di nuovo!","Dovresti smettere di derubare la gente, mentre ne hai ancora la possibilità.","Bene, ma se ti vedo di nuovo..."),RandPhraseSimple("La prossima volta fai attenzione a chi stai minacciando, canaglia.","Grazie a Dio che oggi sono di buon umore."),RandPhraseSimple("Questo commercio criminale ti ucciderà sicuramente alla fine. Addio.","È una decisione saggia. Bene, buona fortuna!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("No, compagno. Ora ti insegnerò un po' di buone maniere!","Oh, hai avuto paura? Beh, uno dovrebbe rispondere dei suoi atti, giusto?","No! Ora non mi calmerò finché non ti scuoio vivo!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("E tu potevi andare in pace! Ora puoi solo incolpare te stesso!","Non avresti dovuto iniziare, furfante! Ora morirai come un cane!","Ah beh! Ti farò a pezzi! Taglierò il fegato e lo darò da mangiare ai cani!");
				Link.l1 = RandPhraseSimple("Riempirò la tua gola con le tue stesse parole!","A chi stai minacciando, feccia?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Bene! Dammi quello e sparisci!","Non molto, ma comunque meglio di niente. È bello trattare con una persona intelligente! Sei libero di andare."),"Ecco una storia diversa! Come diceva un mio amico 'è sempre buono ascoltare qualcuno che è intelligente, ma parlare con lo sciocco è molto meglio'! He-he!","In cambio del tuo oro ti darò un consiglio, non dovresti camminare nella giungla, se tu sei "+GetSexPhrase("un tale codardo. Bevi il tuo rum alla taverna, così tu e la tua borsa rimanete al sicuro!","una ragazza. Essere derubato non è la peggior cosa che ti potesse succedere.")+".");
				Link.l1 = "Maledetto te!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Immagino, stai cercando di imbrogliarmi! Non preoccuparti, ti farò il solletico con il mio coltello, e forse qualcosa cadrà.";
				Link.l1 = "Maledizione!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Di nuovo tu? Torna a casa da tua mamma, prima che mi arrabbi con te!","Cosa? Non mi hai ancora dato tutto il tuo oro? Ah-ah!","Guarda, "+GetSexPhrase("compagno","ragazza")+", Ne ho abbastanza di te! Sparisci dalla mia vista mentre sei ancora vivo!");
			Link.l1 = "Sì, sto già andando via.";
			Link.l1.go = "Exit";
			Link.l2 = "Pensavo che non sarebbe stato giusto. Quindi ho deciso di mettere le cose in chiaro...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("Cosa altro ti serve? Abbiamo già concordato che te ne vai!","Lasciami stare, "+GetSexPhrase("compagno","ragazza")+". Mi occupo dei miei affari, e tu dei tuoi, e non dovremmo cercare di andare d'accordo!","Vattene ora, "+GetSexPhrase("compagno","ragazza")+"! Accidenti, sei davvero disposto a regalare tutti i tuoi soldi?");
			Link.l1 = "Sì, sto già partendo.";
			Link.l1.go = "Exit";
			Link.l2 = "Mi sono ricordato che non hai detto addio! Allora diciamo un addio come si deve...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Lasciami in pace! Aiutami! Voglio vivere!","Aiutami! "+GetSexPhrase("È un maniaco","Lei è una maniaca")+"! Non uccidermi!","Risparmiatemi! Sono solo un umile brigante! Sono troppo giovane per morire!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Se fossi rimasto a casa, saresti ancora vivo!","Dovresti averci pensato prima!","Dovresti aver saputo che ci sono sempre delle conseguenze!"),"Prima o poi, doveva succedere.","Troppo tardi per pentirti, ora combatti, feccia!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
