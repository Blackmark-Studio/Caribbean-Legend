void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa vuoi, forestiero?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, si dice che Port-au-Prince perda il suo incanto quando non sorridi. Oggi, pare, sia uno di quei giorni. Perdonate la mia schiettezza, ma avete forse qualche cruccio?";
			}
			else
			{
				link.l1 = "Mademoiselle, le storie sulla vostra bellezza e grazia sono giunte alle mie orecchie, ma devo dire—le dicerie non vi rendono giustizia. Dicono anche che Port-au-Prince perde il suo incanto quando non sorridete. Oggi, ahimè, pare proprio uno di quei giorni. Nominate il furfante che ha osato rattristarvi, e vi giuro che lo sfiderò a duello per riportare il sorriso sulle vostre labbra incantevoli.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ah, mademoiselle, la vostra premura mi commuove profondamente... Devo confessare, il vostro interessamento mi tocca il cuore. Ma, ahimè, la causa del mio cruccio non è di quelle che si scacciano con qualche parola. Nessuno è colpevole, son solo le circostanze, temo, che neppure il più fiero dei cuori potrebbe vincere.";
				link.l1 = "Le circostanze? Vi assicuro, mademoiselle, per "+GetFullName(pchar)+" nessun ostacolo è insormontabile. Raccontami cos'è successo—magari ti posso dare una mano.";
			}
			else
			{
				dialog.text = "Oh, monsieur, siete davvero un maestro nelle dolci parole. Devo ammettere, quasi mi avete strappato un sorriso. Ma, ahimè, un duello non basterà a risolvere il mio cruccio. Colui che ha offuscato la mia giornata non è un furfante, ma piuttosto le circostanze stesse – e persino un gentiluomo così valoroso come voi non potrebbe vincerle.";
				link.l1 = "Circostanze? Mia cara mademoiselle, Capitano "+GetFullName(pchar)+" posso affrontare qualsiasi tempesta! E se dovessi fallire, ti giuro che mangerò il cappello del primo passante che incontro!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Se proprio insisti, ti racconterò quel che accadde. Ma prima, voglio la tua parola che questa chiacchierata resterà solo tra noi due.";
				link.l1 = "Hai la mia parola d’onore, mademoiselle. Qualunque cosa tu mi confidi resterà tra noi, anche se dovessi portarla con me negli abissi del mare.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", sapete davvero come portare allegria perfino alla dama più afflitta. Ma vi scongiuro, abbiate pietà dei cappelli degli innocenti che passano! Se proprio insistete, vi racconterò cos’è successo. Ma promettetemi che le mie parole resteranno un segreto solo nostro.";
				link.l1 = "Avete la mia parola, mademoiselle, che tutto ciò che mi confiderete resterà segreto, anche se dovessi affrontar la forca.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Molto bene. Una collana è sparita dai miei appartamenti... ma capisci, non è un semplice gingillo. Mi fu donata da qualcuno che occupa un posto caro nel mio cuore. La sua mancanza è una ferita ben più profonda della perdita di un oggetto qualsiasi.\nHo riflettuto a lungo su chi potrebbe essere il colpevole, e giungo a una sola conclusione. Temo che debba trattarsi di uno dei miei stessi servitori. Solo loro hanno accesso alle mie stanze private e potrebbero desiderare un simile tesoro. Eppure non oso accusare nessuno apertamente...";
			link.l1 = "Una questione assai delicata, davvero, specie se la discrezione è ciò che cerchi. Ma se vuoi che ti dia una mano, devo capire che cosa ti costringe a custodire questo segreto con tanta attenzione. Ignorando i pericoli, potrei trascinarci entrambi in una tempesta. Dimmi chi dobbiamo schivare e quali minacce si celano nell’ombra.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Non puoi parlare liberamente? Allora temo, mademoiselle, che non posso offrirti altro che i miei più sinceri auguri. Né la mia indole né l’esperienza si prestano a intrighi e segreti. A mio avviso, il tuo problema si risolverebbe in fretta con l’aiuto della guarnigione cittadina. Eppure sembri aver scelto di veleggiare in acque ben più infide in questi tempi turbolenti.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Non riuscite a parlare chiaro? Allora vi chiedo perdono, mademoiselle, poiché mi trovo del tutto inerme in questa nebbia di segreti. Non ho gran simpatia per intrighi nascosti e loschi traffici. Il vostro problema mi pare assai semplice: una questione da affidare alla guardia cittadina. Eppure vi ostinate a trasformarlo in un intrigo degno delle corti reali d’Europa.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "È così che il rinomato Capitano "+GetFullName(pchar)+" affronta l’avversità? Fuggendo al primo soffio di tempesta? Forse i tuoi doni calzerebbero meglio a contar botti di rum o a scambiar insulti coi mercanti sul molo. Ti chiedo solo questo: se in te v’è anche solo un briciolo d’onore, serba segreto ciò che ti ho confidato. Buona giornata, Capitano.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "Parli con saggezza, "+GetAddress_Form(NPChar)+"  Ebbene, la verità: questa collana proviene da un uomo la cui sola esistenza fa infuriare mio zio — il governatore dei territori francesi su quest’isola. Egli ha proibito qualsiasi contatto, persino il semplice nominare il suo nome. Se mio zio dovesse scoprire da dove arriva questo dono, le conseguenze sarebbero disastrose, non solo per me ma anche per...";
			link.l1 = "Non dica altro, mademoiselle. Ho compreso perfettamente. Stia certa, recupererò la sua collana con la massima discrezione, custodendo il suo segreto gelosamente come un drago fa col suo tesoro.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Hai la mia più profonda gratitudine, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+"   La vostra galanteria e comprensione riscaldano il mio cuore in questi tempi turbolenti. Confido ciecamente che il mio segreto resti al sicuro nelle vostre mani. Che i venti della sorte gonfino le vostre vele in questa delicata impresa.";
			if (pchar.sex == "woman")
			{
				link.l1 = "La fortuna arride a chi osa, madamigella. State tranquilla—riporterò il vostro collier, sicuro come il riflusso della marea.";
			}
			else
			{
				link.l1 = "La sorte favorisce chi ha fegato, mademoiselle. Non appena rimetterò le mani sul vostro prezioso collier, tornerà subito a quelle delicate dita cui appartiene di diritto.";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, Capitano, siete tornato! Avete notizie per me? Vi supplico, ditemi che avete ritrovato la mia collana. Vi prego, ditemi che è vero.";
				link.l1 = "I tuoi guai sono finiti, Julie. La collana è stata recuperata, e mi dà gran piacere restituirla al suo vero posto—le tue mani gentili.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, Capitano, siete tornato! Avete novità per me? Vi supplico, ditemi che avete ritrovato la mia collana. Vi prego, ditemi che è vero.";
				link.l1 = "Mi rincresce deluderti, Julie. La ricerca continua. Ma fatti coraggio—non lascerò pietra inesplorata finché la tua preziosa collana non tornerà tra le tue mani.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "Salute, monsieur. Quale vento vi porta sul nostro vascello?";
			link.l1 = "I seek Captain Tristan Renier; I come bearing a proposition that would line his pockets handsomely.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Devo parlare con il Capitano Tristan Renier per una questione alquanto delicata—una faccenda personale, capisci.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "Il capitano è sbarcato, temo. Se l'affare preme, potresti cercarlo in città.";
			link.l1 = "Per caso sai dove fosse diretto? C'è forse qualche tana che predilige quando mette piede in questo porto?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "Il capitano è sbarcato, ahimè. Forse lo troverai in città, se la tua faccenda non può aspettare.";
			link.l1 = "Forse sapreste dove si dirige? C’è qualche tana che predilige quando attracca in questo porto?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Le mie scuse, "+GetAddress_Form(NPChar)+", ma il capitano tiene per sé i suoi segreti su dove va e viene. So solo che è sbarcato alcune ore fa.";
			link.l1 = "Anche questo è d’aiuto. Ti ringrazio per l’assistenza.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Chi diavolo sei tu? Con quale diritto osi mettere piede nei miei alloggi privati senza invito?";
				link.l1 = "Sono il Capitano "+GetFullName(pchar)+". E sono qui per una faccenda di una certa importanza.";
			}
			else
			{
				dialog.text = "E chi mai siete voi, mia signora? Non rammento d’aver mandato inviti questa sera. Sebbene, lo ammetto, certi ospiti inattesi sanno esser più... interessanti d’altri. Qual vento vi porta in questi miei miseri alloggi?";
				link.l1 = "Sono il Capitano "+GetFullName(pchar)+". E la mia visita riguarda affari, non piacere.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Affari, dici? Che razza d’affare giustificherebbe un’interruzione così sfacciata?";
				link.l1 = "È piuttosto semplice. Hai una collana che sono venuto a riprendere.";
			}
			else
			{
				dialog.text = "Affari, dici? Che intrigante... Quale urgente questione mercantile spingerebbe una dama del tuo fascino a cercarmi nei miei alloggi privati?";
				link.l1 = "Risparmiami le tue parole zuccherate, monsieur. Sono venuto per la collana che hai tu. E sì, so esattamente che è nelle tue mani.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ah! Un collier, dici? In verità ne ho messo le mani su uno di recente, ma che t'importa? Di certo non penserai che io lo ceda al primo sconosciuto che lo pretende, eh?";
			}
			else
			{
				dialog.text = "Una collana, dici? In effetti... Ne ho messa una nuova tra le mie cianfrusaglie di recente. E dimmi, capitano, in che modo pensi di privarmi di questo gingillo che, a tutti gli effetti, appartiene a me di diritto?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Sono disposto a offrirti cinquemila pesos per questo pezzo. Una somma generosa che ti permetterebbe di acquistare un ornamento altrettanto pregiato, forse persino più sfarzoso. Intanto, questa particolare collana tornerebbe a chi la stima più di ogni tesoro — ben oltre qualunque valore in moneta.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Ascoltami bene, signore. Le tue opzioni si sono fatte ben strette: consegna la collana di tua spontanea volontà e vivrai per navigare ancora, oppure opponi resistenza e sarò io a strapparla dal tuo cadavere. La scelta spetta a te, ma ti consiglio di deciderti in fretta.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 45)
			{
				dialog.text = "Cinquemila, dici? Ebbene, Capitano, sai proprio come strappare un affare. Ecco, prendi questo gingillo se tanto ci tieni.";
				link.l1 = "La vostra saggezza è pari alla vostra generosità, signore. Non vi pentirete di questa scelta.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Check passed", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Non ho preso questa collana per svenderla al primo pezzente che mi sventola delle monete! È un dono per mia moglie, e non voglio più sentirne parlare. Sparisci dalla mia vista prima che chiami degli uomini per buttarti fuori!";
				link.l1 = "Se rifiuti l’accordo tra gentiluomini, allora prenderò ciò che cerco con modi assai meno civili.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Insufficient skill level (45)", SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... Insolente moccioso... Pensi che le tue minacce da poppante mi facciano paura? Ah! Non hai la minima idea di con chi hai a che fare!";
				link.l1 = "Non mi importa chi tu sia. Consegnami la collana e me ne vado. O davvero vuoi crepare per un gingillo che non significa nulla per te?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Non ho comprato questa collana per contrattare con gente come te! Era un dono per mia moglie, e tu qui non hai niente da fare. Fuori dai piedi prima che ti buttiamo fuori a calci!";
				link.l1 = "Se non vuoi darmelo di buon grado, me lo prenderò con la forza.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Maledizione a te e a quella collana maledetta! Prendila. Prendila e sparisci prima che cambi idea.";
			link.l1 = "Scelta saggia! Addio.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", hai riportato la gioia nel mio cuore! Non hai solo restituito la collana, ma anche un pezzo della mia anima. La tua nobiltà è ammirevole, e giuro che racconterò a chiunque delle tue gesta valorose!";
			link.l1 = "Per favore, mademoiselle, non l’ho restituito per la fama. Il tuo sorriso è l’unica ricompensa che davvero conto.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Sei così modesto, "+pchar.name+". Ma ti prego, accetta questo forziere di dobloni. Solo sapendo che hai accettato il mio dono potrò sentirmi d'averti ringraziato come davvero meriti.";
			link.l1 = "Per favore, mademoiselle, non insista. Le vostre gentili parole valgono per me più d’un forziere di dobloni.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Se ciò vi dà sollievo, mademoiselle, accetterò il vostro dono. Ma sappiate che non l’ho fatto per una ricompensa. "+GetSexPhrase("La tua reputazione","La vostra gratitudine")+"  conta assai più per me di questi dobloni.";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "Mi son proprio scordato di chiedere—sai chi ha rubato la collana?";
			link.l1 = "Tutto ciò che so, mademoiselle, è che un mercante l’ha ricevuta da una certa Giselle. E a giudicare dalle circostanze, non credo che questa sarà l’ultima gemma che intende vendere.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "Mi son scordato del tutto di chiedere—sai chi diavolo ha rubato la collana?";
			link.l1 = "Tutto ciò che so, mademoiselle, è che un mercante l'ha ricevuto da qualcuno di nome Giselle. E a giudicare dalle circostanze, non credo sia l'ultimo gioiello che abbia intenzione di vendere.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle? Ma è la mia cameriera! Avevo i miei sospetti... ma non volevo crederci. Il peggio è che non posso nemmeno punirla come si deve. Potrebbe svelare il mio segreto—e questo non posso permetterlo.";
			link.l1 = "Allora che farai? Le lascerai passarla liscia e continuerà a rubarti sotto il naso?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Oh no, certo che no. Prima mi assicurerò che non metta più piede vicino a me. Poi troverò il modo di darle una lezione, così che sembri che la punizione venga da qualcun altro.";
			link.l1 = "L’astuzia di una donna è un’arma temibile, soprattutto se brandita da una creatura raffinata e perspicace come voi. Scommetto che la vostra domestica non si accorge nemmeno che la partita è già persa—e non certo a suo vantaggio.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, capitano... Non vorrei ricorrere a sotterfugi, ma... talvolta l’astuzia è l’unica rotta possibile.";
			link.l1 = "Già, Julie. Mi rincresce lasciarti, ma il dovere mi chiama. Chi, se non io, si prenderà cura della mia ciurma?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Fino al nostro prossimo incontro, "+pchar.name+". Tornate a farci visita più spesso al nostro porto. La nostra città ne ha davvero bisogno "+GetSexPhrase("uomini così nobili e valorosi come voi.","donzelle dal cuore nobile e dallo spirito fiero, proprio come il vostro.")+"";
			link.l1 = "Mi lusingate, mademoiselle. Prometto che non perderò occasione per tornare nella vostra splendida città. Fino alla prossima volta.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! Che sorpresa! Ancora a domare i mari?";
						link.l1 = "Felice di rivederti, mademoiselle. Mi destreggio come posso, anche se il mare resta capriccioso e crudele. E tu—riesci a goderti un po’ di pace e tranquillità?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ah, Capitano "+pchar.lastname+", che piacere rivederti! Spero che tutto vada a gonfie vele per te?";
						link.l1 = "Felice di rivederla anch’io, mademoiselle. Gli affari, come sempre, rubano tempo e fatica, ma incontri come questo illuminano ogni giornata. E le sue giornate, come scorrono?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitano "+pchar.lastname+", sei tornato di nuovo? Davvero ci sono ancora anime nella nostra umile cittadina che non hai tradito per una manciata di dobloni?";
						link.l1 = "Signorina, comprendo i vostri sentimenti, ma ho agito secondo ciò che ritenevo giusto. Talvolta la decisione corretta porta dolore e mi rincresce d’avervi ferita.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Capitano "+pchar.lastname+", di nuovo? La tua brama non ha proprio limiti, che non puoi lasciarci in pace e già cerchi la prossima preda?";
						link.l1 = "Mademoiselle, mi rincresce se le mie azioni vi hanno recato dolore, ma ho agito secondo la mia coscienza.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Ultimamente, tutto fila liscio come il mare al mattino—nulla turba la quiete. Passa più spesso al nostro porto, Capitano. Son certo che qui troverai tutto ciò che il tuo cuore brama, sia nella nostra bottega che oltre.";
			link.l1 = "Grazie, mademoiselle. Cercherò di passare più spesso. Son certo che la vostra città cela ancora molte piacevoli sorprese.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "Grazie a voi, capitano, i miei giorni ora scorrono assai più tranquilli. Spero proprio che tornerete a farci visita.";
			link.l1 = "Ma certo, mademoiselle. La vostra cittadina lascia sempre un’impressione assai gradita. Fino alla prossima volta.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Capitano "+pchar.lastname+", ci rincontriamo. Straordinario, non trovi?";
					link.l1 = "Pare che la sorte oggi ci sorrida, madamigella.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Capitano "+pchar.lastname+", pare che le nostre strade si siano incrociate ancora una volta.";
					link.l1 = "Proprio così, signorina. Mi fa piacere rivedervi.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Pare che ci incrociamo fin troppo spesso, capitano. O forse sei di quelli che non riescono a star lontano da chi han già tradito?";
					link.l1 = "Mademoiselle, i nostri incontri sono pura ventura, ma comprendo il vostro astio. Spero solo che un giorno capirete le mie ragioni.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "Cosa vuoi adesso? Non mi dirai che la tua sfortuna è così nera da farti capitare qui per caso. Oppure sei venuto solo per rinfrescarmi la memoria sulla tua vergogna?";
					link.l1 = "Mademoiselle, non era mia intenzione intromettermi né riaprire vecchie ferite. Questo incontro è davvero un caso del destino.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}