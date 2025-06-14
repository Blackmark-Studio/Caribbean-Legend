void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Questa è sicuramente una stortura. Puoi far sapere a Jason quando e come è successo, per piacere?";
			link.l1 = "Sarà fatto.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Perché sei venuto nella mia capanna, uomo bianco? Tuttuathapak non ti considera un caro ospite.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Salute a te, grande sciamano Tuttuathapak. Sono venuto da te per chiedere il tuo aiuto e il tuo consiglio. Accetta questo moschetto come segno della mia buona volontà.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Salve a te, grande sciamano Tuttuathapak. Son venuto a chiederti aiuto e consiglio.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak non aiuta uomo bianco. Uomini bianchi sono malvagi. Uccidono e conquistano indiani, fanno schiavi gli indiani. Tuttuathapak non dà consigli agli uomini bianchi. Ora vattene.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "Sai cosa dare a Tuttuathapak, uomo bianco. Tuttuathapak accetta il tuo dono. Parlerà. Che consiglio cerchi da me?";
			link.l1 = "Ho sentito dire che vieni da una terra lontana, a sud. Ho un amuleto indiano, e un uomo sapiente mi ha detto che forse tu sai come possa essere usato.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Mostra l’amuleto.";
			link.l1 = "Ecco a te, grande sciamano.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(guardando l’amuleto)... Il tuo amico dice il vero, uomo bianco. Questo amuleto appartiene al mio popolo, i grandi indiani, Chavin era il loro nome. Un maledetto cane dalla faccia pallida ha profanato il santuario e l’ha portato qui. Tuttuathapak ha punito quel bastardo.";
			link.l1 = "Gli hai fatto perdere il senno, immagino?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "L’uomo bianco stupisce Tuttuathapak con la sua sapienza. Sì, ho divorato l’anima di quel cane rognoso. Lui e la sua lurida ciurma hanno avuto ciò che meritavano.";
			link.l1 = "Capisco... Dimmi, sciamano, a cosa serve questo amuleto? Forse protegge in battaglia o scaccia le magie malvagie?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Questo amuleto non serve a nulla per te, capitano bianco. Non puoi sfruttarne il potere. Solo i grandi sciamani della nostra tribù sanno come risvegliarlo.";
			link.l1 = "Hmm... Quindi, a quanto pare ho fatto tutto questo viaggio per nulla. Ma forse tu, grande sciamano, puoi risvegliare il potere di questo amuleto? Sicuro che potremmo trovare un accordo...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Anche se risveglio l’amuleto, tu non domerai il suo potere a lungo. Ma ti propongo un patto, uomo bianco.";
			link.l1 = "Che razza d’accordo?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Tre amuleti come questo sono stati rubati dal nostro santuario. Ognuno ha poteri diversi, ma se li riunisci, diventano tremendamente potenti. Trova tutti e tre gli amuleti e portameli, e ti ricompenserò. Ti darò un potere che durerà in eterno.";
			link.l1 = "Non capisco bene... Che sorta di potere intendi, di grazia?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Tutto a suo tempo saprai. Trova e portami tutti e tre gli amuleti. Sono nei Caraibi. Cerca e scova. Li riconoscerai subito – sono simili fra loro. Vai, uomo bianco. Tuttuathapak aspetta e chiede agli spiriti di aiutarti.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Va', uomo bianco. Trova altri due amuleti.";
				link.l1 = "Li ho già trovati, grande sciamano. Ecco, dai un'occhiata.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Vai, uomo bianco. Trova gli altri due amuleti.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Sei di nuovo qui, uomo bianco? Sembri uno che ha incontrato una giaguaro furioso nella giungla.";
			link.l1 = "Peggio ancora, grande sciamano. Appena misi piede in mare, una tempesta furibonda scoppiò dal nulla e fui assalito da una nave comandata da non-morti! Il loro capitano era del tutto invincibile. Prima mi strappò l’amuleto e quasi mi mandò all’altro mondo – sono sopravvissuto per un pelo. Poi hanno quasi affondato la mia nave, solo una manciata dei miei uomini si è salvata.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Cattive notizie, bianco. Il Caleuche caccia di nuovo per uccidere.";
			link.l1 = "Il Caleuche? Quel capitano dannato chiamava la sua nave Cuor Volante. Dunque, sapevi della nave fantasma e non mi hai avvisato? Se avessi saputo che quell’incubo dei mari cercava l’amuleto, mai e poi mai avrei...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak vede che il capitano bianco è turbato. Il capitano bianco deve darsi una calmata.";
			link.l1 = "Calmarsi?! Sei fuori di testa, come potrei mai sopravvivere contro una roba simile!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Sì. Calmati e non urlare. Dimmi – vuoi ancora ricevere da me un grande potere, che rimarrà con te per sempre?";
			link.l1 = "Certo che sì. Ma l’amuleto non ce l’ho più, ormai.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Ti insegno come prendere l’amuleto dal capitano della Caleuche. Non sarà cosa da poco. Ma se ci riesci, la sua nave sarà il tuo bottino, troverai tesori di gran valore, conquisterai gloria tra la tua ciurma e riceverai una ricompensa da me.";
			link.l1 = "Maledizione! Lo farei volentieri a pezzi, quel mostro rinsecchito! Ma come diamine posso sconfiggerlo, se né lama né piombo gli fanno un baffo?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Sei pronto ad ascoltarmi, capitano bianco?";
			link.l1 = "Sì, sono io, grande sciamano.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Quand’ero giovane guerriero, mio padre narrava che gli uomini bianchi giunsero alla mia terra a bordo della nave Cuore Volante. Si spinsero fin sulle montagne. La leggenda dice che là si cela un santuario degli antenati nostri, il tempio dei guerrieri giaguaro. Gli uomini bianchi trovarono il santuario, presero l’oro e profanarono cose sacre e antiche. Rubarono il più grande tesoro dei Chavins: il teschio di giada di Yum Cimil, dio della morte e protettore degli uomini giaguaro.\nGli uomini bianchi tornarono alla loro nave. Decisero di tornare ancora per altro oro, ma quando uno di loro posò piede sulla terraferma, morì tra atroci sofferenze. Yum Cimil maledisse il capitano e la sua ciurma: divennero immortali, ma incapaci di posare piede sulla terra. Navigarono per innumerevoli inverni, mezzo secolo secondo il vostro calendario. Così nacque il Caleuche.\nI loro corpi marcirono, la carne imputridì, ma non morirono mai. Se tagli una gamba o un braccio, ricrescono. Se li fai a pezzi, si ricompongono. Se la loro nave affonda, la riparano sott’acqua e salpano di nuovo.";
			link.l1 = "Proprio fantastico...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " Il Caleuche terrorizza i marinai. Attacca senza motivo e porta sventura sicura. Non si fa vedere spesso nei Caraibi. Preferisce navigare presso le coste della mia patria. Credo che voglia spezzare la maledizione. Ma non la leverà mai.";
			link.l1 = "Perché? Cosa bisogna fare per spezzare la maledizione?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Teschio di giada. Deve tornare al santuario di Yum Cimil, tempio dei guerrieri giaguaro. Ci sono diversi templi. Gli anziani della mia tribù dicono che ce n’è uno su una piccola isola nei Caraibi. Ecco perché il Caleuche ha navigato fin là. Una volta che il teschio sarà al tempio, l’incantesimo di Yum Cimil si spezzerà, e loro diventeranno mortali e non guariranno più le ferite.";
			link.l1 = "Ah! Più probabile che non restituiranno mai il teschio! Perché dovrebbero, se sono immortali e invincibili? E poi, non possono nemmeno riportarlo indietro, se non gli è concesso mettere piede a terra, giusto?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Non hanno più il teschio. Il capitano lo gettò via nella terra dei miei antenati, tornando dal santuario degli uomini giaguaro. Giada non è oro, l’uomo bianco non la voleva, non riuscì a prendere la splendida pietra verde dagli occhi del teschio. E lo buttò. Un marinaio la raccolse, e la maledizione non lo toccò.\nQuando vide ciò che era diventato l’equipaggio del Caleuche, fuggì. Arrivò al nostro villaggio. Mio padre vide quel marinaio e il teschio di Yum Cimil. Poi l’uomo bianco proseguì verso nord lungo la costa, portando con sé il teschio.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Un teschio di giada con pietre verdi nelle orbite? L’ho avuto tra le mani, riesci a crederci? L’ho dato io stesso a Solomon. Ma poi è partito per l’Europa con sua figlia, e pare che si sia portato dietro anche il teschio.";
				}
				else
				{
					link.l1 = "Un teschio di giada con gemme verdi nelle orbite? Santo diavolo... Io... Io l’ho tenuto tra le mie mani! E l’ho venduto a un portoghese... Merriman, o qualcosa del genere... Sì, così si chiamava – il teschio di Yum Cimil! Lo voleva come il demonio! Ha pagato mezzo milione di pesos per averlo!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Un teschio di giada con gemme verdi nelle orbite? È dunque questo che dovrò cercare? Ma quel marinaio potrebbe essere crepato nella selva cinquant’anni fa, e il teschio andato perso per sempre!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "So che il teschio si trova nei Caraibi. Il Caleuche non è qui per caso. Da sei lune lo si vede spesso presso l’isola. Un tempo non si faceva vedere da tanti inverni. Il capitano del Caleuche sente la presenza dell’artefatto degli uomini giaguaro. Così ha trovato te e la tua nave.";
			link.l1 = "Dunque, ho capito bene che devo di nuovo andare a caccia di quel teschio? E poi che ci dovrei fare, con quella reliquia?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Il teschio dev’esser qui, nei Caraibi. Il Caleuche non ci sta per caso. Da sei lune lo si vede spesso vicino all’isola. Prima non si faceva vedere da molti inverni. Il capitano del Caleuche sente l’artefatto degli uomini giaguaro. Così ti ha trovato, te e la tua nave.";
			link.l1 = "Dunque, ho capito bene che devo trovare di nuovo quel teschio? E poi, che dovrei farci?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Per prima cosa, devi trovare i due amuleti di cui abbiamo parlato. Senza di essi non puoi combinare nulla. Gli amuleti ti daranno la forza di affrontare gli uomini-giaguaro e qualsiasi canaglia ti si pari davanti.";
			link.l1 = "Affrontare uomini giaguaro? Ma che diavolo stai farneticando?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Il tempio dove devi portare il teschio di giada si trova su un'isola deserta nei Caraibi. È sorvegliato dagli uomini giaguaro. Tutti morti, eppure ora camminano ancora. Senza l'amuleto non passerai. Gli uomini giaguaro in vita erano guerrieri feroci, e da morti sono quasi invincibili. È lo stesso Yum Cimil che dona loro la forza.";
			link.l1 = "Non morti? Di nuovo? Che fortuna la mia...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Perché tanto stupore, capitano bianco? Yum Cimil è il dio della morte, il teschio di giada dà potere sui vivi e sui morti. I Caraibi. È custodito dagli uomini giaguaro. Senza l’amuleto non li superi. Con l’amuleto puoi entrare nel tempio e sopravvivere, lasci lì il teschio, poi trovi la Caleuche, sconfiggi il suo capitano e riprendi l’amuleto che ti ha sottratto.";
			link.l1 = "E perché mai il capitano della Caleuche avrebbe bisogno di questi amuleti?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Mi par che voglia andare al tempio degli uomini giaguaro e crede che l’amuleto gli porti fortuna. Ma potrei sbagliarmi. Comunque, la Caleuche è sempre attirata dagli artefatti della mia terra. Ha navigato vicino all’isola dove sorge il tempio degli uomini giaguaro, e ha solcato le coste della mia patria.";
			link.l1 = "E dove si trova quell'isola?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Prima trovi il teschio di Yum Cimil e gli amuleti. Poi parleremo dell’isola.";
			link.l1 = "D'accordo. Puoi darmi un indizio su dove cercare il teschio di giada?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Non lo so. Ma è qui, nei Caraibi. E anche gli amuleti. Chiedi. Cerca. Trova.";
			link.l1 = "Ehm... Va bene, ci proverò.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "E tu stai all’erta, capitano bianco. Il Caleuche sente gli oggetti degli Chavin. Quando avrai l’amuleto, lei ti darà la caccia. Se ti trova, fuggi e in fretta. Se ti prende, sei un uomo morto.";
			link.l1 = "Questa nave maledetta è dannatamente veloce! Va almeno il doppio di qualsiasi bastimento che abbia mai visto. Però ho notato che fatica quando naviga controvento.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "La Caleuche è maledetta – per questo vola sui flutti. Difficile sfuggirle. Devi procurarti una nave che possa superare la Caleuche. Altrimenti finisci all’altro mondo. Quando trovi l’amuleto, portamelo. Non tenere quell’amuleto a bordo.";
			link.l1 = "L’ho già preso. Grazie per la tua storia, grande sciamano. Ora è tempo che io prenda il largo.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Sto invocando gli spiriti perché ti aiutino e ti salvino dal Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(guardando) Sì, è questo. Il secondo amuleto dei Chavins. Sei in gamba. Devi trovare ancora un altro amuleto.";
			link.l1 = "Me ne ricordo, sciamano. Presto sarà nelle tue mani.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Vai, uomo bianco. Trova un altro amuleto.";
				link.l1 = "Ce l'ho già, grande sciamano. Ecco, dai un'occhiata.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Vai, uomo bianco. Trova un altro amuleto.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(guardando) Sì, è proprio quello. Il terzo amuleto dei Chavin. Sei in gamba. Hai trovato tutti gli amuleti per oltrepassare i guerrieri giaguaro defunti, servi di Yum Cimil.";
			link.l1 = "Ora, se ho capito bene, mi servirà il teschio di giada?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Dici il vero. Il teschio di giada di Yum Cimil. Devi portarlo al tempio dei Chavin. Così il Caleuche perderà il suo potere per sempre.";
			link.l1 = "Tuttuathapak, ti prego, dimmi dove cercare? Hai qualche idea?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "No. Pensa a dove hai visto l’ultima volta il teschio di giada. A chi l’hai dato. Comincia a cercare da lì.";
				link.l1 = "D'accordo, grande sciamano. Farò tutto ciò che posso.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Uno stregone bianco cerca il teschio di Yum Cimil. Lo desidera ardentemente. È venuto persino nel nostro villaggio. Ho sentito che vive in una casa su un'isola olandese. Cerca lo stregone su quell'isola, e potresti scoprire qualcosa.";
				link.l1 = "D'accordo, grande sciamano. Farò tutto ciò che posso.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Vai, uomo bianco. Trova il teschio di giada di Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Ce l'ho qui, gran sciamano, dàci un'occhiata.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Vai, uomo bianco. Trova il teschio di giada di Yum Cimil.";
			link.l1 = "Temo di non poterlo fare. Ho trovato lo stregone, ma all’ultimo istante è sgattaiolato via col teschio. Non ho la minima idea di dove possa essere adesso.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "Questa è una gran brutta faccenda, uomo bianco. Ora non passerai il tempio e non sconfiggerai il Caleuche. Io non ti do dono alcuno. Adesso vattene.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Te ne vai adesso, uomo bianco.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(guardando) Sì, è proprio quella. Molto bella. E terribilmente inquietante.";
			link.l1 = "Certo... Ma sai cosa mi stupisce di più? Ho attraversato tutto il maledetto mar dei Caraibi, da Cuba a Dominica, e il Caleuche non ha mai provato ad attaccarmi finché avevo questo teschio, nemmeno l’ho visto. Invece, quando portavo gli amuleti per te, quella nave maledetta mi stava sempre addosso: appena mettevo piede fuori porto, mi trovava in poche ore.";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Mi par che la Caleuche tema il teschio o forse non riesca a sentirlo. Non trovo altra ragione. Forse Yum Cimil ha reso il teschio di giada assai pericoloso per la Caleuche – oltre la maledizione. Forse per questo il capitano bramava tanto impadronirsi dei tre amuleti del mio popolo. Per ottenere la saggezza su come dominare l’incantesimo di Yum Cimil.";
			link.l1 = "Quindi, finché tengo il teschio di giada a bordo della mia nave, non dovrò temere gli assalti del Caleuche?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Esatto, faccia di cadavere. Lo vedi coi tuoi stessi occhi.";
			link.l1 = "Molto bene! Così potrò prendere il comando di una gran nave, arruolare una ciurma degna e preparare una calda accoglienza a quel morto che cammina, quando il sortilegio sarà spezzato, senza temere che mi venga a cercare prima...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...a proposito di quell’incantesimo, dove dovrei portare il teschio di giada?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Devi portarlo al tempio di Chavin e concludere il tuo viaggio. Voglio raccontarti una storia. Sei pronto ad ascoltare, uomo bianco?";
			link.l1 = "Le mie orecchie sono sempre pronte ad ascoltare la tua saggezza, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Come narrano le leggende dei miei antenati, tanto tempo fa, quando gli uomini dalla faccia pallida ancora non avevano messo piede nelle nostre terre, il grande capo dei Chavin costruì una canoa smisurata e la mandò, carica di guerrieri, verso la terra delle mille isole. A guidarli era il figlio del grande capo, e tra loro viaggiava anche uno degli alti sciamani. In quella terra di molte isole trovarono un luogo desolato e vi fondarono un insediamento, erigendo un tempio magnifico per Yum Cimil, come solo i nostri antenati potevano fare.\nI messaggeri tornarono con buone novelle, ma nessuno vide mai più né il figlio del capo, né lo sciamano, né i guerrieri. La leggenda narra che rimasero laggiù a vivere, ma il più saggio degli sciamani parlò con gli spiriti e disse che là ormai non abitava più anima viva, e che Yum Cimil regnava su quelle terre.\nLa terra delle molte isole è il Caribe, uomo bianco. Il tempio di Yum Cimil si trova su un’isola dove né bianchi né indiani hanno dimora. Solo i servitori di Yum Cimil, i Chavinavi, ancora vigilano tra i corridoi del tempio.";
			link.l1 = "E dove si trova quell’isola?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Suppongo sia piccola e a nord del villaggio, da qualche parte in quell'immensa distesa d'acqua che chiamate oceano, non troppo lontano.";
			link.l1 = "Hmm... A nord di Dominica, forse ai confini dell’oceano? Maledizione, è una dannata distesa d’acqua! Come diavolo dovrei scovare un’isoletta là, se nessun’anima ne ha mai sentito parlare?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Non posso dirlo meglio. Ma so un’altra storia ancora. Potresti averla sentita dai tuoi fratelli. Circa venti inverni fa, un uomo bianco trovò quell’isola. Insieme a una donna e a un vecchio entrò nel tempio di Yum Cimil e portò via un artefatto potente: l’orbe del sole nascente. Sulle rive dell’isola, il capitano dalla faccia pallida venne assalito dal Caleuche.\nMa il viso pallido fu furbo. Accecò il capitano e l’equipaggio del Caleuche con il sole nascente. La maledizione del Caleuche si indebolì, e il capitano lo mandò a fondo, ma l’orbe del sole nascente svanì. Se trovi quell’uomo dalla faccia pallida, lui ti dirà dov’è l’isola.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ah! Credo di conoscere quell’‘uomo dalla faccia pallida’... Le storie si somigliano troppo. Dunque, la Caleuche è affondata?";
			else link.l1 = "Hmm... Allora, la Caleuche è stata affondata?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Sì, ma una maledizione li protegge dalla morte. L'hanno sistemato e hanno continuato il loro eterno viaggio.";
			link.l1 = "D’accordo, ho capito. Ma che devo fare nel tempio? Dove metto il teschio? Come faccio a sconfiggere quei guerrieri giaguaro che lo sorvegliano? Se sono davvero i Chavinavi come quelli evocati da quel mago Merriman, sarebbe pura follia andarci da solo – ognuno di loro vale dieci soldati!";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Non lo sono. I Chavinavi chiamati dallo stregone bianco col teschio sono deboli. Molto più deboli di quelli evocati da Yum Cimil in persona. Tu non puoi ferirli, ma loro ti mandano all’altro mondo con un solo colpo delle loro armi.";
			link.l1 = "Un momento – e come ha fatto quell’uomo dalla faccia pallida a entrare nel tempio e rubare l’artefatto?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Prima che quel primo viso pallido mettesse piede nel tempio, esso era custodito dagli spiriti degli antenati defunti. Il viso pallido era un guerriero gagliardo e li sconfisse. Quando rubò la sfera del sole nascente, Yum Cimil montò su tutte le furie. Mandò fuoco e zolfo sul viso pallido e quasi rase al suolo il tempio, ma quello fuggì col manufatto. Ora Yum Cimil ha richiamato invincibili guerrieri giaguaro a vegliare sul tempio.";
			link.l1 = "Magnifico! E come diavolo farò a sgattaiolare dentro, allora?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "Io ti aiuto, uomo bianco. Ti do due amuleti Chavin se me li porti. Io parlo agli spiriti degli antenati e rendo l’amuleto potente. Quando ne avrai uno con te, potrai combattere i guerrieri giaguaro come fossero semplici soldati, sarai come uno di loro, ma più forte. L’amuleto ti proteggerà e darà alla tua arma il potere di ferire i Chavinavi del tempio.";
			link.l1 = "Sei sicuro che questi amuleti ci porteranno fortuna?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Io so. Io parlo con gli antenati. Io gran sciamano. Fidati di me. Prendi questi due amuleti. Uno ti protegge. L’altro rende l’arma potente. Un amuleto devi usare. Quale - lo scegli tu. Se non porti l’amuleto, finisci nelle fauci dei guerrieri giaguaro.\nE ricorda che a mezzanotte Yum Cimil ridarà vita a tutti i guerrieri che hai ucciso. Devi capire quando agire, così non combatterai due volte con gli stessi, oppure fallo pure, gli spiriti mi dicono che potresti.";
			link.l1 = "Capisco.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Prendi gli amuleti. Eccoli qua. Ricorda, il loro potere ha dei limiti. Si affievolisce in una luna. Ricorda cosa ti ho detto: non puoi trattenerne il potere? Solo il grande sciamano della nostra tribù può farlo.";
			link.l1 = "Ricordo. Quindi ho solo una luna? Solo un mese?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Sì. Quando giungi al tempio di Yum Cimil, devi trovare il santuario e una grande statua del Condor al suo interno. Questa è la parte più importante del tempio. Qui metterai il teschio di giada di Yum Cimil, e la maledizione sarà tolta dal Caleuche. Quando ti assalirà di nuovo, lo sconfiggerai come un uomo qualunque. Poi mi porterai l’amuleto che ti ha preso.";
			link.l1 = "Condor? Che c’è?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Il Condor è un grande uccello che vive tra le montagne della mia terra. In ricordo della patria, gli antenati hanno eretto una statua del Condor vicino al santuario.";
			link.l1 = "D'accordo, lo cercherò...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Stai in campana. Mille pericoli ti attendono nel tempio assieme ai guerrieri giaguaro.";
			link.l1 = "Quali pericoli?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Non lo so con certezza. Vedi coi tuoi occhi. Potrebbe essere una trappola, o forse... solo confusione. Entrare nel santuario è cosa ardua. L’entrata è sigillata, e tu devi trovare modo di aprirla. I miei antenati non erano solo grandi guerrieri e sciamani, ma pure abili costruttori; per aprirla ci vuole ingegno.";
			link.l1 = "Heh! Sembra spaventoso, ma che vengano pure tutti! Non perderò tempo. Salpo immediatamente!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Va', o guerriero pallido. Io chiamerò gli spiriti per aiutarti contro i guerrieri giaguaro e il Caleuche. Ricorda, se userai gli amuleti io potrò aiutarti, altrimenti sarai dannato.";
			link.l1 = "Ti ringrazio, grande sciamano... Mi metterò subito all’opera.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Io parlo con gli spiriti. Sei stato sull'isola, nel tempio di Yum Cimil. Hai trovato il  Caleuche e l'amuleto?";
				link.l1 = "Hai ragione, grande sciamano. Ho trovato l’isola, sono entrato nel tempio e ho lasciato il teschio di giada all’interno.";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "Vai, guerriero bianco.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, vedi... Non ho portato il teschio al tempio in tempo, e i tuoi amuleti hanno perso il loro potere.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Hai tolto la maledizione dal Caleuche. Ti ha cercato dopo, eh?";
			link.l1 = "Sì. Ci siamo incontrati proprio sull’isola. L’ho affrontata in duello e sono uscito vincitore. Ora ho tutti e tre gli amuleti. Tieni, prendili.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tu sei rapido e forte, guerriero dalla pelle pallida. Tuttuathapak non ama gli uomini bianchi, ma io rispetto un guerriero coraggioso e abile. Hai fatto proprio bene. Hai liberato i mari dal Caleuche. Mi hai portato tre amuleti. Io ti ricompenserò.";
			link.l1 = "Hai promesso qualcosa riguardo al 'potere che potrò tenere per sempre'?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Parli il vero. Ti concedo questo potere. Nessuno nei Caraibi conosce il segreto della pianta che conosco io. Ascoltami, volto pallido! Nella mia dimora cresce una pianta medicinale. La chiamiamo Manga Rosa. Hai mai sentito parlare di quella pianta?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Sì. L'ho tenuto tra le mani. Gli zingari ne sono assai attratti. E una di loro, la guaritrice Amelia, può persino...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Non ne ho la minima idea...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Ho sentito parlare dell'erborista Amelia. Sa poco, ma non abbastanza. Non conosce il segreto della Manga Rosa. Solo un grande sciamano della mia terra, da dove la Manga Rosa è stata portata fin qui, può sfruttarne il vero potere.";
			link.l1 = "Quale potere?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Quest’erba cresce nella mia terra natia, ma si trova anche qui nei Caraibi. È una pianta alta, verde chiaro, con foglie come una mano aperta e un profumo piacevole. La riconoscerai all’istante, non la confonderai con altro. Io conosco i suoi segreti. Posso estrarne la forza.";
			link.l1 = "Capisco, ma che sorta di potere?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Posso preparare pozioni di Manga Rosa. Pozioni potentissime, nessuno nei Caraibi può farle tranne me. Le mie pozioni rendono l’uomo più forte, più veloce, più furbo, con occhio d’aquila, più bello e baciato dalla sorte. Preparerò per te tre di queste pozioni.";
			link.l1 = "Molto interessante!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Tu, gran guerriero, prima ti serve una pozione per farti più robusto e una per renderti più svelto. La terza pozione la sceglierai tu, dopo che avrò preparato le prime due. Ma devi portarmi la Manga Rosa per farle – io non ne ho nemmeno una.";
			link.l1 = "Dove dovrei cercare la Manga Rosa?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "La Manga Rosa è un’erba rara nei Caraibi. Cresce dove la gente non mette spesso piede. Gli sciocchi la raccolgono, la seccano e la fumano. Veri idioti, quelli. NON FUMARLA! È uno spreco di magia... Va’ a cercarla nella giungla e nelle calette, nei posti segreti dove i babbei non si azzardano. Guarda con attenzione. Per ogni pozione mi servono cinque steli di Manga Rosa.";
			link.l1 = "D'accordo, grande sciamano. Tornerò da te quando avrò abbastanza Manga Rosa.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Vai, guerriero pallido. Portami la Manga Rosa. Non te ne pentirai. Le mie pozioni son le migliori. Dirò agli spiriti di guidarti nella tua ricerca.";
			link.l1 = "Grazie! Addio, stregone!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Hai portato cinque steli di Manga Rosa per la pozione?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Sì. Ecco cinque piante che ti servono.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Non ancora, grande sciamano. La mia ricerca continua...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Benissimo. Torna domani, quando il sole sarà calato. Ti preparerò degli elisir che renderanno più svelto il tuo braccio e più acuti i tuoi riflessi.";
					link.l1 = "D'accordo, sciamano. Tornerò domani al calar del sole.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Molto bene. Torna domani, quando il sole sarà calato. Ti preparerò delle pozioni che rafforzeranno la tua resistenza.";
					link.l1 = "Va bene, sciamano. Tornerò domani al calar del sole.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Molto bene. Qual è la tua pozione da scegliere? Pozione della forza, della vista acuta, dell'intelligenza, della bellezza o della fortuna?";
					link.l1 = "Pozione della forza.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Pozione della vista acuta.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Pozione d’ingegno.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Pozione di beltà.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Pozione della fortuna.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "Pozione pronta, guerriero dalla faccia pallida. Prendila."+sTemp+"";
				link.l1 = "Grazie, grande sciamano.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Non è ancora pronto, uomo bianco. Torna più tardi. Non venirmi a scocciare.";
				link.l1 = "D’accordo...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Ho preparato per te tutte le pozioni che avevo promesso. Ora sei più forte. Sei contento?";
				link.l1 = "Sì, grande sciamano. Era davvero una ricompensa degna.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Trovi altri cinque steli di Manga Rosa, li porti a me. Ti preparo un'altra pozione.";
				link.l1 = "Te ne porterò ancora. A presto!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Vieni domani, come sempre. Ti preparo una pozione che ti renderà più gagliardo, e combatterai meglio con quell'accetta grossa.";
			link.l1 = "Va bene.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Vieni domani, come sempre. Ti preparo un elisir che affilerà i tuoi occhi, così vedrai ogni bersaglio e sparerai con armi di fuoco che tuoneranno come tempesta.";
			link.l1 = "D'accordo.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Vieni domani, come al solito. Ti preparo una pozione che ti farà più furbo, e faresti meglio a startene nascosto dai nemici.";
			link.l1 = "D'accordo.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Vieni domani, come al solito. Ti preparo una pozione che ti renderà più bello, così convincerai la gente più facilmente.";
			link.l1 = "Bene.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Vieni domani, come al solito. Ti preparo un elisir che porta fortuna, e la buona sorte ti sorriderà.";
			link.l1 = "Va bene.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Son lieto che tu apprezzi la mia arte, l’arte del grande sciamano.";
			link.l1 = "Dimmi, Tuttuathapak, a che ti servivano questi tre amuleti? Solo per curiosità...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Già senti il potere di questi due amuleti. Gli spiriti mi aiuteranno a infonderli di forza, e tutti e tre gli amuleti insieme donano la grande saggezza sciamanica e l’illuminazione dei miei antenati, i maestosi Chavins.";
			link.l1 = "Capisco. Bene, ti ringrazio ancora per le tue pozioni miracolose. Sei davvero un grande sciamano. Ora devo andare. Addio, Tuttuathapak, spero che il destino ci faccia rincontrare.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Addio, guerriero pallido. Non mi cerchi più. Io vado in solitudine, a cogliere la saggezza degli avi miei. Che gli spiriti ti guidino nei tuoi viaggi!";
			link.l1 = "Ebbene... ahah... che gli spiriti illuminino anche il tuo cammino, grande sciamano. Addio...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Mi fai pena, faccia pallida. Io invoco gli spiriti per dare potere a questi amuleti, e tu lo sprechi. Mi rattristi. Ora vattene. Tuttuathapak non ha più nulla da dirti.";
			link.l1 = "Mi dispiace, la sorte mi è stata proprio avversa... Beh, addio, sciamano.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "Tutto è vano, marinaio. Non mi batterai mai. E tutti i miei uomini stesi sul ponte rimetteranno insieme le ossa e si rialzeranno prima dell’alba. Non ci puoi uccidere: la morte ci ha abbandonati per sempre.";
			link.l1 = "Maledizione! Sei vivo o morto? Più probabile che sia ancora vivo - i morti di solito stanno zitti e non brandiscono spade. Ma chi diavolo sei e perché hai assaltato la mia nave?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Io sono Balthazar de Cordes del Cuore Volante. Miserabili codardi, che nulla sanno di me, mi chiamano Van der Decken, capitano dell’Olandese Volante. Ma poco importa. Quello che conta è che tu porti con te un amuleto, e ora lo prendo io. Mi serve! Lo sento nelle ossa! Il grande amuleto dei Chavin, uno dei tre, sarà finalmente mio! Inginocchiati davanti a me, mortale! E forse la tua morte sarà senza dolore!";
			link.l1 = "Vaffanculo, carogna!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "Non ci posso credere! È passato così tanto tempo dall’ultima volta che ho visto il mio stesso sangue e sentito dolore... COME È POSSIBILE?!";
			link.l1 = "Questa volta hai perso, Balthazar de Cordes. Conosco la tua storia. Il teschio di giada è stato restituito al tempio dei Chavins, e la maledizione di Yum Cimil non grava più su di te né sui tuoi uomini. Non potrai più riportare in vita i tuoi marinai.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Ah, dunque ti credi un redentore, forse? No! Balthazar de Cordes farà pagare cara la poca vita che gli resta!";
			link.l1 = "L'ultimo viaggio del Cuore Volante finisce qui, a Khael Roa. E stavolta non strapperai la tua nave dal fondo del mare, come facesti venticinque anni fa.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Falco! Son passati venticinque anni, eppure ricordo tutto come fosse ieri. Quella sfera di fuoco che ci accecò e spaccò la mia nave in due. Fu la prima e ultima disfatta del Cuor Volante e di Balthazar de Cordes... Dunque incrociamo le spade un'ultima volta, capitano! Morire in battaglia è cosa leggera e benvenuta!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Finalmente ti sei svegliato, capitano... Come ti senti?";
			link.l1 = "Maledizione, che diavolo è successo? Mi scoppia la testa dal dolore...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quando siamo entrati nella cabina del capitano, tu giacevi sul pavimento, immobile come un pesce morto. I ragazzi ti hanno raccolto e trascinato sulla nostra nave – giusto in tempo, perché quei dannati cadaveri sparsi sul ponte hanno cominciato a rimettersi in piedi!\nSanta Vergine e tutti i Santi! Abbiamo tagliato le gomene in fretta e cercato di levarci di lì a tutta forza, ma una bordata dalla loro nave ha ridotto la nostra vecchia carretta in schegge e abbiamo perso il controllo. Poi hanno issato le vele e sono svaniti in un batter d’occhio.\nLa nostra nave si è arenata, e chi è sopravvissuto è riuscito a raggiungere la riva su una scialuppa. Molti bravi uomini sono morti oggi... Se solo fossimo rimasti a bordo... Ma eravamo certi che la tempesta avrebbe finito la nave per sempre.";
			link.l1 = "Nessuna colpa vostra, signori. Era la scelta giusta. Vi ringrazio, lo terrò a mente.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Ti abbiamo trascinato nella barca e poi portato a riva. Eri quasi morto...";
			link.l1 = "Ti devo la vita. Da quanto tempo giacevo qui, privo di sensi?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Per un giorno intero. Ti abbiamo lavato e fasciato le ferite, dato delle medicine e versato un po’ di rum in gola. Tornerai in piedi presto.";
			link.l1 = "Questa volta di certo non tirerò le cuoia. Anche se... non mi sento affatto in forma...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Questo è certo... Era forse l’Olandese Volante, capitano? Perché ci hanno attaccati? E perché prima dell’abbordaggio non ci hanno sparato, ma poi han quasi mandato a fondo la nostra nave con una sola bordata?";
			link.l1 = "Il loro capitano aveva bisogno dell’amuleto di cui avevo parlato con Tuttuathapak, uno stregone indiano. Ecco perché non ci hanno affondato subito, ma appena il loro capo ha preso l’amuleto, ci hanno sbarazzato in un batter d’occhio... Che orrore! Una nave governata dai morti! Da non crederci...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Già, adesso era il nostro turno d’incontrare l’Olandese Volante. Appena ne avrò la possibilità, andrò in chiesa, accenderò una candela per la mia miracolosa salvezza e pregherò il Signore...";
			link.l1 = "Anch'io... credo. Ma prima farò ritorno a quel villaggio. Devo raccontare tutto a Tuttuathapak. Quella maledetta nave ci ha assalito per via dell’amuleto! Son certo che quel diavolo dalla pelle rossa aveva qualche idea sul perché quei dannati non-morti potessero averne bisogno.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "D'accordo. Ma fa' attenzione, capitano, le tue ferite si sono appena rimarginate; almeno portati qualcuno dietro, non si sa mai.";
			link.l1 = "Starò attento, lo giuro. Grazie per non avermi lasciato nei guai!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Di che diavolo parli, capitano! Saremmo pronti a seguirti fino alla fine del mondo e affrontare mille dannati non-morti! È una maledetta disgrazia aver perso così tanto, ma questa storia vivrà nelle leggende.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Ehi! Non ho ancora raccolto abbastanza pelli di serpente da venderti, quindi levati dai piedi!";
			link.l1 = "Hmm... Sei tu Fergus Hooper?";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "No, il mio nome è Tuttuathapak, e ti scaglierò una maledizione se non sparisci subito. Quindi fai meglio ad affrettarti, o ti...";
			link.l1 = "...perderò il senno, darò fuoco alla mia stessa nave, e i miei marinai mi sgozzeranno per rubarmi ogni cosa. Giusto?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... Che diavolo, chi sei tu!? Come hai fatto a...";
			link.l1 = "Abbiamo un amico in comune, Fergus. Fa il guardiano del faro, e si chiama "+GetFullName(sld)+". Mi ha parlato di te e mi ha mandato a cercarti. A proposito, conosco di persona lo sciamano Tuttuathapak, quindi la tua burla non ha funzionato, mi dispiace. Senti, non cerco rogne. Voglio comprare qualcosa da te, e non si tratta di pelli di serpente.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Oh, dunque conosci il mio vecchio compagno! Come sta? Non sarà ancora morto dallo sbadiglio nel suo faro, eh? Vieni, marinaio, siediti e bevi qualcosa con me!";
			link.l1 = "Mi dispiace, Fergus, davvero non ho molto tempo. Ascolta, mi serve quell'amuleto indiano, uno di quelli che il tuo defunto capitano portò dal continente insieme a Tuttuathapak. Ti pagherò bene, e così ti sbarazzerai di quell’oggetto maledetto.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "E che c’è di tanto pericoloso? Finora non m’ha fatto alcun male. È solo una pietra inutile.";
			link.l1 = "Questo perché non solchi più i mari. Anch'io avevo un amuleto simile, fino a poco tempo fa. Una nave fantasma va a caccia di questi oggetti.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Scherzi, compare? Forse conoscere Tuttuathapak ti ha dato alla testa? Sta’ all’erta, capitano, quel diavolo dalla pelle rossa ti divorerà la mente...";
			link.l1 = "Credimi o no, ma dico la verità. Neanch'io ci avrei creduto, se non l’avessi visto coi miei occhi, posso giurare sul Libro o chiedi pure a chi era con me. Son sopravvissuto a malapena dopo quell’incontro col Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "Il Caleuche?";
			link.l1 = "Ebbene, la chiamano quasi tutti Olandese Volante, ma il suo vero nome è Cuor di Mare. Come ti pare. Vendimi quell’amuleto, va’. Tanto a te non serve a un accidente, lo so bene.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Già, proprio così. È solo un gingillo inutile, seppur di gran bellezza. Senti, te l’avrei venduto senza troppi discorsi, ma vedi... non ce l’ho più. Me l’hanno rubato dalla capanna insieme ad altra roba, mentre ero a caccia nella giungla. È successo di recente, sarà stato un mese fa. Mi dispiace, ma non posso aiutarti in alcun modo.";
			link.l1 = "E chi l’ha rubato?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Ma davvero credi che starei qui seduto se sapessi chi mi ha svaligiato la casa? Fuori da Belize c’è una masnada di ladri e briganti che scorrazza, con dei delatori in città. Beh, almeno così dice il comandante. Io sono sicuro che sono stati loro.";
			link.l1 = "Il comandante sa dei banditi e non muove un dito?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Che stia facendo qualcosa o no, non lo so. L’unica cosa che so per certo è che le mie cose sono sparite, e con loro anche il tuo prezioso amuleto. Prova a dare la caccia a quei mascalzoni – magari lo troverai nelle loro tasche. Dubito che siano già riusciti a venderlo – ai mercanti non servono simili cianfrusaglie.";
			link.l1 = "Va bene, andrò a parlare col comandante. Buona fortuna, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Ehi! Che vuoi? Non aspetto visite. Sparisci!";
			link.l1 = "Perché tanta scortesia, compare? Volevo solo chiederti una cosa...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Non hai sentito? Fuori dai piedi, dannato cane, o ti sbatto fuori a calci!";
			link.l1 = "Hmm... Forse sei davvero la persona che sto cercando. Ti vedo troppo agitato, compare...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Ti credi troppo furbo, eh? Te lo ripeto: o sparisci subito, o chiamo le guardie e ti sbattono in gattabuia!";
			link.l1 = "Mettermi in prigione, eh? Che faccenda intrigante. Ora son quasi certo d'aver trovato chi cercavo. D'accordo, accetto. Chiamiamo le guardie e poi ce ne andremo insieme, allegri come una famiglia, dritti dall’ufficio del comandante. Ci sono appena stato, ricordo bene la strada... Guardie! GUARDIE!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Al diavolo te! Ti infilzo come un pesce!";
			link.l1 = "Oh ho-ho! Beh, prova pure se osi!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Ehi, viandante! Benvenuto, benvenuto... Cena, alloggio – tutto quel che vuoi, basta che paghi. Preparati a svuotare le tasche!";
			link.l1 = "Non così in fretta, bel figliolo. Ho da sbrigare faccende con te.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Affari? Ah-ah! L’unico affare tuo è consegnarmi tutto il tuo argento e il tuo oro!";
			link.l1 = "Zitto una buona volta. Ti ho portato una lettera da Belize che aspettavi. Il messaggero non è riuscito a convincere le guardie e ha affidato la faccenda a me.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Fammi vedere!";
			link.l1 = "Ecco qua...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(leggendo) Mh... Questo è davvero strano... Come ci sei finito in mezzo?";
			link.l1 = "Te l'ho già detto, hanno catturato il tuo uomo, così ho preso il suo posto. Mi aveva promesso monete sonanti e un’accoglienza calorosa da parte tua...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "E avrò anch’io una fetta di questo bottino?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Vedrai che ci riuscirai! Se hai fegato in battaglia e resti vivo. Ma non pensare che sia una passeggiata, il mercante non è solo, ha una scorta, e pure bella grossa. Bene, è ora di muoverci – la nostra preda è vicina. Ragazzi! Preparate le armi, si salpa!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "Vedo che non sei un codardo. Ben fatto! Ti sei guadagnato la tua parte. Come la vuoi? Contanti? Mercanzia? Avevano una stiva piena di rum, vale una fortuna.";
			link.l1 = "Grana.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Mercanzia.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Ecco qua! E questa borsa è per aver consegnato la lettera.";
			link.l1 = "Grazie! Così mi piace, proprio come deve essere!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Ecco a te! Ma non bere come uno scavezzacollo, ah-ah-ah! E questa borsa è per aver recapitato la lettera.";
			link.l1 = "Grazie! Così mi garba, proprio così!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Mi sembri un tipo a modo. Che ne dici di un altro lavoretto? Riguarda quella lettera che mi hai fatto recapitare.";
			link.l1 = "Certo.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Allora vieni alla grotta. Ce ne sono due. Vai nella giungla fino al punto dove ci siamo visti l'ultima volta, poi prendi il sentiero a sinistra. Ci troviamo tra tre giorni all'ingresso della grotta, da mezzanotte all'una. Capito? Se ti comporti bene, ti accoglieremo nella nostra ciurma. Ma ricordati — se ti scappa una parola in città, sei finito. Ho il braccio lungo, io.";
			link.l1 = "Smettila di farmi tremare, d'accordo? Ho capito. Starò zitto come un pesce. Aspettami tra tre giorni, ci sarò. Adoro il denaro facile!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "D'accordo, compare. Ora sparisci prima che arrivino le guardie. Anche noi ce ne andiamo.";
			link.l1 = "Ci si rivede in giro, compare...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Cosa?! Hai deciso di mettere le mani sulla nostra roba? Non la passerai liscia, lurido verme!";
			link.l1 = "Chi hai appena chiamato verme, lurido bastardo?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Salute, collega! Cosa ti porta da queste parti?";
			link.l1 = TimeGreeting()+", mynheer Jackson. Sono lieto d’aver finalmente messo le mani su di voi.";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "‘Mynheer Jackson’, ahah! Beh, a dire il vero, presto anch’io mi chiamerò così. Lavoro per questa dannata Compagnia senza un attimo di tregua... ma pagano bene, maledettamente bene!.. Allora, che vento ti porta qui, compare?";
			link.l1 = "Il nostro comune conoscente, il guardiano del faro, mi ha raccontato che possedevi un antico amuleto indiano. Scommetto che non te ne sei mai servito, e invece a me serve come il pane. Voglio comprartelo.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Ah, parli di quel gingillo elegante che avevo chiesto a quel nostromo in pensione? Eh già, amico, hai ragione, non mi è mai servito a niente, ma fa la sua bella figura.";
			link.l1 = "Quanto vuoi per questa roba?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Vedi, c'è un piccolo intoppo... Lascia che ti spieghi. Al momento non ce l'ho con me. Non avendone mai trovato utilità, l'ho lasciato nel mio baule sulla riva, tra le mie altre cose.";
			link.l1 = "Oh, questo spiega perché sei ancora... beh, lasciamo stare. Andiamo direttamente al tuo forziere, e io ti compro l’amuleto. Tutto qui, semplice semplice. Dove lo tieni?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "Non è proprio così semplice. Il mio baule si trova a Barbados, nella torre del faro, ed è ben chiuso a chiave, così che nessun furfante possa approfittarne mentre non ci sono. Mi dispiace davvero, ma non posso accompagnarti a Barbados: secondo il mio accordo coi dannati olandesi, devo navigare tra Philipsburg e Port Royal e rispettare la rotta alla lettera. E Barbados non è affatto lungo quel tragitto.";
			link.l1 = "E che possiamo fare? Ho proprio, proprio bisogno di quell’amuleto!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Beh, c’è una possibilità. Ti do la chiave del mio forziere e te ne vai a Barbados da solo. Però dovrai risarcirmi tutto quello che c’è dentro, ma puoi anche tenerteli. Scusa la diffidenza – ma devi capire. Non ti ho mai visto prima d’ora.";
			link.l1 = "Quanto vuoi?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Cinquecento monete d’oro. Non un doblone di meno.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Eccoti qua! Prendi il tuo oro.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... Non ho così tanti dobloni con me.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Allora vieni a cercarmi di nuovo quando avrai raccolto il denaro. Se mi hai trovato una volta, mi troverai ancora. Navigherò tra Saint Martin e la Giamaica per un bel po’ d’ora in poi.";
			link.l1 = "D'accordo, affare fatto.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "Di nuovo tu, compare? Hai 500 monete?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sì. Ecco il tuo oro.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Non ancora, ma ci sto lavorando.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("You have given 500 doubloons");
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(500);
			DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
			dialog.text = "Perfetto! Ecco la tua chiave. Ma ti chiedo solo una cosa: quando avrai preso tutto ciò che c’è dentro, lascia la chiave nella serratura. Non vorrei dover ordinare una nuova serratura e una chiave.";
			link.l1 = "D'accordo.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Allora buona fortuna, compare! Buon viaggio!";
			link.l1 = "E altrettanto a voi... Buon viaggio, monsieur Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			AddQuestRecord("Caleuche", "20");
			// сундук со схроном
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Salute, capitano "+GetFullName(pchar)+". Lieto di darti il benvenuto a Willemstad.";
			link.l1 = "Salve, padre. Non mi ricordo di voi. Ci conosciamo, forse?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Ho fatto domande su di te, non appena la tua nave ha gettato l’ancora. E credo di potermi permettere di chiederti un aiuto.";
			link.l1 = "Molto interessante. E perché proprio io?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Perché hai fatto molto per la Repubblica delle Province Libere. Sei ben visto dalla Compagnia e sei amico del governatore. Ho già presentato ricorso a diverse autorità e sono stato respinto, ma spero che una persona nobile come te non rifiuterà l’umile richiesta di un servo del Nostro Signore.";
			}
			else
			{
				dialog.text = "Perché tu non sei al servizio del nostro governatore. Non lavori per la Compagnia e non hai nulla a che fare con i nostri militari – altrimenti mi avresti già scacciato come una mosca fastidiosa, visto che ho già fatto appello a diverse autorità e sono stato respinto.";
			}
			link.l1 = "D'accordo, allora. Di che richiesta si tratta, compare?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "C'è una casa dietro la banca. Una dama che ci abitava affittava una stanza a un tipo molto sospetto, né del posto, né olandese. E così il nostro reverendo padre, Padre "+sld.name+", lo aveva riconosciuto\nEra Joachim Merriman, un portoghese accusato dall’Inquisizione di stregoneria e patti con potenze infernali. Si era nascosto dal Santo Uffizio nel Nuovo Mondo. Sai, gli spagnoli spesso accusano di eresia e stregoneria chi cade in disgrazia, solo per bruciarli sul rogo, ma... Stavolta avevano ragione. Merriman è davvero uno stregone\nCosì, viveva da un po’ a Willemstad, poi è sparito così all’improvviso come era arrivato. Dopo un po’, una donna, quella che gli affittava la stanza, non fu mai più vista uscire da quella casa. Mai! E da allora non l’ha mai più vista anima viva, da nessuna parte\nE di notte, a volte, capita di vedere lampi rossoblu alle finestre del secondo piano e di sentire suoni strani, quasi come urla maledette. Padre "+sld.name+" si è rivolto al comandante. Ha mandato una pattuglia di quattro soldati, hanno perquisito la casa, ma non hanno trovato nulla: né la padrona, né anima viva, né alcunché di sospetto\nEppure queste stranezze continuano. Della locandiera nessuna traccia, e quella dannata luce si vede ancora lì di notte. Oltretutto, da poco sono spariti anche due mendicanti. Li ho sentiti chiacchierare sul sagrato – sapevano che la casa era senza padrone, così hanno deciso di passarci la notte. Da allora, nessuno li ha più visti.";
			link.l1 = "Immagino che tu voglia che entri in quella casa a scoprire cosa diavolo è successo davvero?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Proprio così, nobiluomo. Vi supplico, aiutate la Santa Chiesa. Il comandante dice che ci stiamo inventando tutto, visto che le sue pattuglie non hanno trovato nulla. Il governo la pensa allo stesso modo. Al popolino non interessa, perché non lo vede come un pericolo reale.";
			link.l1 = "Hmm... E dovrò andarci di notte?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Sì, signore. Là è tutto tranquillo di giorno, per questo i soldati non hanno trovato nulla, credo che il comandante tema per i suoi uomini, e farei lo stesso. Ma vi prego, vi scongiuro. Padre "+sld.name+" ti ringrazierà e ti ricompenserà per il tuo servizio. Quando avrai visitato quella tana durante la notte, riferiscigli ciò che scoprirai là. Ti assicuro che i nostri timori sono più che fondati.";
			link.l1 = "D'accordo. Ci penserò su.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Grazie, capitano. Spero che non rifiuterai la mia umile richiesta. Ti prego, fallo in nome del Signore, della nostra fede e di tutto ciò che è sacro. Vai con la mia benedizione.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Aspetta, compare. Meglio che tu non vada laggiù, se tieni alla pellaccia.";
			link.l1 = "E allora, qual è l’inganno?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Fidati, meglio che tu non sappia. Ma la Morte sta appostata dietro l’angolo, e giuro sul Libro che non tornerai vivo; ci sono cose che nemmeno immagini.";
			link.l1 = "Ebbene, se lo dici tu, non sfiderò la sorte. Grazie dell'avvertimento.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Di nulla. Tieniti lontano da quella rotta.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Stai lontano da quella rotta, compare.";
			link.l1 = "Sì, me lo ricordo...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Sei ben certo di volerci andare?";
			link.l1 = "Assolutamente. "+sld.name+", padre superiore della chiesa all’Avana, mi ha mandato qui. Devo scoprire che succede in questo luogo e prendere le giuste misure.";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "Cosa sta succedendo qui? Temo che ti tremerebbero le gambe dalla paura, una volta che vedrai con i tuoi stessi occhi cosa accade in questo posto.";
			link.l1 = "Intendi quei morti che camminano?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Sì.  E faresti meglio a dar retta alle mie parole.";
			link.l1 = "E io ti credo, davvero. Ho già incontrato quell’abominio a Willemstad e l’ho distrutto. Ora entrerò là dentro e spazzerò via tutta la feccia che si nasconde in questa caverna.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Vuoi andarci da solo? Sei già spacciato, compare. Non immagini nemmeno quanti di quei mostri ci siano là. Beh, va’, se proprio ci tieni, e io andrò in chiesa ad accendere una candela per la pace della tua anima.";
					link.l1 = "Non darmi già per morto. Ho visto tempeste ben peggiori.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Siete solo voi due? Temo che non andrete lontano. Non avete idea di quanti di quei diavoli ci siano là fuori. È pura follia.";
					link.l1 = "Tu non ci conosci, compare. Spostati, ché ripuliremo quest’infame covo di perdizione.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Siete solo in tre? Dovete essere canaglie di gran calibro se ve la sentite di provarci. Ma temo comunque che non ce la farete. Non avete la minima idea di quanti di quei mostri infestino la grotta.";
					link.l1 = "Non ci conosci bene, compare. Fatti da parte, e purificheremo questa lurida tana.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Vedo che non siete dei codardi, questo sì. Ma non avete proprio idea di quanti dannati ce ne siano laggiù. In una faccenda simile ogni uomo conta. Al diavolo, verrò anch’io con voi e sparerò a quella feccia col mio moschetto!";
					link.l1 = "Sei un'anima coraggiosa, amico. Non rifiuterò il tuo aiuto. Andiamo!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Andiamo! Morte a quei luridi non-morti!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Quella sì che è stata una carneficina! Chi avrebbe mai detto che così tanti morti si nascondevano qui dentro! Beh, almeno ora possiamo tirare il fiato... Vai a raccontare tutto a quel tuo padre superiore, quello che ti ha mandato fin qua. Spero proprio che l’Inquisizione si metta d’impegno dopo il tuo resoconto. Combattere i non-morti è affar loro, io non sono che un semplice cacciatore.";
			link.l1 = "Glielo dirò senz'altro. Ti ringrazio per l’aiuto, compare. Sei uno di quei rari che osano sfidare la morte in faccia! Buona fortuna!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Fermo dove sei! Questo posto è vietato ai non autorizzati!";
			link.l1 = "Ehh... E che c’è là dentro?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Là è stato trovato un negromante pericoloso. Solo i santi padri e i soldati che li scortano possono entrare.";
			link.l1 = "Capisco. Hanno catturato lo stregone?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Non sono autorizzato a rispondere a tali domande, señor. È tempo che ve ne andiate.";
			link.l1 = "D'accordo, ho capito. Buona fortuna!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Sta’ fermo, umano! Ti trovi proprio nel cuore del tempio, e ormai sei andato troppo oltre per tornare indietro.";
			link.l1 = "Chi diavolo sei?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Io sono il capo dei Chavinavi, custode e guardiano di questo luogo sacro. Non sei il primo a mettere piede in questo tempio, ma solo due uomini e una donna sono entrati e ne sono usciti vivi prima di te. È l’unica ragione per cui mi degno di parlarti adesso. Perché sei venuto qui, faccia pallida?";
			link.l1 = "Ho portato qui un antico cimelio, il teschio di giada. Cinquant’anni fa fu trafugato da un tempio indiano nel cuore della terraferma. Avevo intenzione di trovare il santuario e restituire la reliquia al tuo dio.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "È strano sentir parole simili da gente come te. Non ti credo. Voi, visi pallidi, venite sempre per prendere qualcosa e mai per restituire nulla.";
			link.l1 = "Non mento. Restituendo il teschio spezzerò la maledizione che grava sul capitano della nave fantasma che semina il terrore nei mari dei Caraibi, così tornerà mortale, e io libererò il mondo da lui una volta per tutte.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Come puoi sapere che il nostro Dio toglierà quella maledizione, faccia pallida? Il nostro Dio ti parla forse?";
			link.l1 = "No. Son venuto qui su consiglio di un grande sciamano chiamato Tuttuathapak. Diceva che il teschio è la chiave della maledizione, e questo è l’unico tempio nei Caraibi. E sai una cosa? Credo davvero che possa parlare con gli spiriti del passato. Forse persino con te, capo dei guerrieri giaguaro.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Le tue parole mi sorprendono, volto pallido, ma ancora non posso fidarmi di te del tutto. Tuttavia, se sei venuto in questo tempio per restituire la nostra reliquia, sicuramente il nostro sciamano ti avrà parlato di questo luogo, della sua creazione, della sua storia e dei suoi abitanti.\nSe è così, risponderai facilmente a tutte le mie domande. Allora ammetterò che sei stato sincero con me, ti permetterò di passare e, per di più, ti ricompenserò.";
			link.l1 = "Allora chiedi!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "I am the chieftain of the Chavinavi, and the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Prima che la vostra gente dalla faccia pallida arrivasse, tutta questa terra, dalla grande neve del nord alle vaste pianure del sud, apparteneva a noi, fratelli di una sola stirpe...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Prima che la vostra razza dal viso pallido arrivasse, tutta questa terra, dalla grande neve del nord alle vaste pianure del sud, apparteneva a noi, fratelli d’un’unica stirpe...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Quale tribù indiana ha eretto questo tempio?";
			link.l1 = "Inca.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Azteco.";
			link.l4.go = "question2_l";
			link.l5 = "Arawac.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "La nostra gente è cresciuta in saggezza, conquistando nuove foreste, pianure e isole. Coloro che edificarono questo tempio giunsero dai boschi oltre il Grande Mare...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "La nostra gente avanzò, imparando saggezza, e sottomise nuove foreste, pianure e isole. Coloro che eressero questo tempio giunsero dai boschi oltre il Grande Mare...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Chi guidava la ciurma di quei valorosi?";
			link.l1 = "Gran capo.";
			link.l1.go = "question3_l";
			link.l2 = "Gran sacerdote.";
			link.l2.go = "question3_l";
			link.l3 = "Figlio del grande capo.";
			link.l3.go = "question3_r";
			link.l4 = "Figlio del gran sacerdote.";
			link.l4.go = "question3_l";
			link.l5 = "La ciurma era senza capo.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Gli indiani, valorosi guerrieri e viandanti, hanno sempre amato e venerato la loro terra natia, anche dopo essersi stabiliti in un nuovo luogo. In segno del loro affetto per la patria, hanno eretto una statua nel tempio, a forma d’uccello – simbolo della loro casa. Si trova alle mie spalle...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Gli indiani, valorosi guerrieri e viaggiatori, hanno sempre amato e onorato la loro terra natale, anche dopo aver trovato dimora in luoghi nuovi. In segno d’affetto per la patria, hanno eretto nel tempio una statua a forma d’uccello, simbolo della loro casa. Si trova alle mie spalle...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Qual è il nome di quest’uccello?";
			link.l1 = "Albatros.";
			link.l1.go = "question4_l";
			link.l2 = "Aquila.";
			link.l2.go = "question4_l";
			link.l3 = "Avvoltoio.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Anni di prosperità sono svaniti come la fiamma d’una lanterna, e la vita ha abbandonato l’isola. Solo il tempio è rimasto in piedi, a rammentare la possanza degli antichi indiani. L’ultimo sciamano lasciò su un piedistallo un sacro globo solare, che donava forza ai valorosi e puniva i malvagi. Fu portato via dall’uomo che venne qui prima di te.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Gli anni di prosperità sono passati e svaniti, come la fiamma d’una lanterna, e la vita ha abbandonato l’isola. Solo il tempio è rimasto a vegliare, memoria della grande potenza degli antichi indiani. L’ultimo sciamano lasciò su un piedistallo un sacro globo solare, che donava forza ai coraggiosi e puniva i malvagi. Fu portato via dall’uomo che venne qui prima di te.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Qual era il nome di quell’orbe sacro?";
			link.l1 = "Globo del sole splendente.";
			link.l1.go = "question5_l";
			link.l2 = "Sfera dei raggi solari.";
			link.l2.go = "question5_l";
			link.l3 = "Sfera del sole a mezzodì.";
			link.l3.go = "question5_l";
			link.l4 = "Sfera del sole nascente.";
			link.l4.go = "question5_r";
			link.l5 = "Sfera del sole calante.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Risposte sbagliate dimostrano che mi hai mentito, uomo bianco! Sei venuto con intenzioni malvagie! Sei riuscito a eludere i guardiani del tempio e del santuario, hai capito il funzionamento del congegno della porta – ma non sfuggirai comunque a uno scontro mortale con me. Preparati a morire, faccia pallida!";
				link.l1 = "Ebbene, se insisti – vediamo un po’ che razza di guerriero sei...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "La tua conoscenza della mia gente e del mio tempio ti fa onore, faccia pallida. Ora ti credo. Vai e compi ciò per cui sei venuto. Poni la sacra reliquia sul piedistallo davanti al condor, dove un tempo riposava la sfera del sole nascente\nPoi torna da me. La tua devozione a Yum Cimil e la scelta di restituire volontariamente ciò che i tuoi fratelli rubarono meritano una ricompensa.";
				link.l1 = "Vi ringrazio per la vostra fiducia, grande capo.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Risposte sbagliate dimostrano che mi hai mentito, uomo bianco! Sei venuto qui con intenzioni malvagie! Sei riuscito a sgattaiolare oltre i guardiani del tempio e del santuario, hai capito come funzionava il meccanismo della porta – ma non sfuggirai comunque allo scontro mortale con me. Preparati a morire, faccia pallida!";
			link.l1 = "Ebbene, se insisti – vediamo un po’ quanto vali davvero come guerriero...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "Hai fatto ciò che hai promesso, volto pallido. Mi rallegra che tu non sia un bugiardo come la maggior parte dei tuoi fratelli. Manterrò anch'io la mia parola. Prendi questo dono da parte mia – il simbolo della potenza dei guerrieri giaguaro. Lo stesso Yum Cimil ha infuso questa pelle con un frammento della sua forza.";
			link.l1 = "Per tutti i diavoli! Che meraviglia!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Questa non è una semplice pelle. Indossandola, otterrai la forza d'un guerriero giaguaro. Il potere della tua arma, che sputa fuoco e piombo, crescerà dieci volte, e potrai disseminare il campo di battaglia coi cadaveri dei tuoi nemici.\nMa nessun mortale può reggere la potenza che Yum Cimil ha infuso in questa pelle. Una volta liberata, ti accompagnerà solo fino alla prossima mezzanotte, poi svanirà. Abbine cura, faccia pallida, e non sciupare il suo potere per una meschina scaramuccia.";
			link.l1 = "Grazie! Lo userò solo quando sarò sopraffatto dai nemici, parola di capitano.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Adesso vattene. E avvisa i tuoi fratelli di non violare la quiete di queste camere sacre. I guerrieri giaguaro non conoscono misericordia per i visi pallidi e non concederanno alcuna pietà.";
			link.l1 = "Addio, capitano.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
