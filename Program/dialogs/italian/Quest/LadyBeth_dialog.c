void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Cosa vuoi?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "La tua decisione, Capitano? Forse dovremmo lasciar perdere, giusto?";
				link.l1 = "Sei riuscito a trovare altri volontari per questa faccenda, giusto?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Capitano, una parola.";
				link.l1 = "Rapporto, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "L'equipaggio si chiede quali siano i tuoi piani per Cayman. La gente è in pensiero.";
			link.l1 = "Non ho ancora deciso. E perché gli uomini sono in ansia, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Quest’isola è il dominio del Capitano Blackwood. I marinai dicono che la sta scavando come un indemoniato, da cima a fondo. Che nelle sue ricerche ha rovinato decine di uomini... E quelli che lo abbandonano raccontano storie strane.";
			link.l1 = "Che tipo di storie, giusto?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Quel Blackwood non è più l’uomo che era una volta. Ormai è ossessionato dalla ricerca di un tesoro di qualche conquistador. È pronto a sacrificare tutto e tutti per quella follia. Sappiamo bene quanto ti piaccia ficcarti in storie avventurose, sbarcare da solo e cadere in trappole… Stavolta, però, non ci sarà scampo per te.";
			link.l1 = "Grazie per l’informazione e l’avvertimento. Se deciderò di sbarcare, prenderò la testa della spedizione e mi porterò dietro i nostri migliori combattenti.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Potrebbe essere arduo, Capitano. L'arrembaggio è una faccenda, ma sbarcare sotto le palle dei marines e le sciabole di tutta la feccia che Blackwood pare abbia arruolato da ogni bettola delle Piccole Antille è tutt'altra storia. E su Cayman corrono brutte voci... No, per un affare del genere non troverai molti volontari.";
			link.l1 = "Allora dovremo arrangiarci con chiunque troviamo. La tua partecipazione è obbligatoria, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "A mio avviso, ho già dimostrato tutto ciò che si poteva dimostrare a chiunque. Tutti i buoni spadaccini e tiratori verranno. È un ordine.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hmm... Beh, devo rifletterci su. Magari torniamo su questa domanda più tardi, giusto?";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Aye, Capitano!";
			link.l1 = "E la nave di Blackwood? Non ci darà grane, giusto?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Aye, Capitano!";
				link.l1 = "E la nave di Blackwood? Non ci porterà dei guai, giusto?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Skill Check Passed", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Level check passed", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Temo di no, Capitano.";
				}
				else
				{
					dialog.text = "Non devi dimostrare niente né a me né agli ufficiali, e andremo dove vorrai tu, agli ordini. Ma il marinaio comune la pensa diversamente. Temo che ci saranno dei guai, capitano.";
				}
				link.l1 = "Allora dovremo arrangiarci con chiunque troviamo. La tua presenza è obbligatoria, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hmm... Devo rifletterci un po'. Magari ne riparliamo più tardi, giusto?";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Skill Check Failed (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("Level 17 required", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Una neve. Dicono che sia una vera bellezza dal carattere focoso. Io non mi preoccuperei troppo di lei. Molto probabilmente tutto l’equipaggio sta sgobbando a terra, mentre la nave è ben nascosta tra le insenature della costa. Quando – e se – vinceremo, potremo prenderla come bottino direttamente dalla riva.";
			link.l1 = "Raduna gli uomini. Oggi è una buona giornata – la fortuna sarà dalla nostra parte.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Felice di vederti, Capitano. Credo che abbiamo già discusso tutto, giusto?";
				link.l1 = "Proprio così. Addio.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Capitano Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Ciao. Sei il capitano Blackwood, giusto?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Sei il capitano Albert Blackwood, giusto?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Felice di vederti, Capitano. Credo che abbiamo già discusso tutto, giusto?";
			link.l1 = "Proprio così. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Sì, sono io. E tu, giusto?";
			link.l1 = "Capitano "+GetFullName(pchar)+". Comando la nave '"+PChar.Ship.Name+".";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Capitano... Sei mai stato a Cayman?";
			link.l1 = "Passavo solo di qua, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Hai sentito qualche storia di tesori laggiù, giusto?";
			link.l1 = "No, nulla di preciso.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Tracce di spagnoli? Vecchie armi? Monete dell’epoca dei conquistatori?";
			link.l1 = "Non ho trovato niente del genere, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Leggende locali? Racconti su Cortez? Qualcosa che riguardi sepolture?";
			link.l1 = "Mi dispiace, Capitano, ma non ho queste informazioni. E poi, questa inizia già a sembrare un’interrogazione.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Perdonami... Vecchia abitudine da ufficiale. È solo che... per me questa faccenda è davvero fondamentale.";
			link.l1 = "Perché ti interessa così tanto proprio Cayman, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Non ha importanza. Ancora una volta, ti chiedo scusa.";
			link.l1 = "Capisco. Buona fortuna nelle tue ricerche.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Good night";
			else sStr = "Wishing you a good day";
			dialog.text = "Vieni a trovarmi se scopri qualcosa di interessante. Mi piacerebbe scambiare due parole con un altro capitano... qualcuno che conosce davvero il mare."+sStr+".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "In carne ed ossa. E tu... Capitano Helen MacArthur? La pupilla di Jan Svenson, giusto? Ho sentito parlare di te.";
			link.l1 = "Sei ben informato, capitano Blackwood. Ma non mi stupisce che un ufficiale inglese sappia chi sono.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Ex ufficiale. E tutti quei giubbe rosse sanno di te e delle tue... strane preferenze per la Corona. Il legno di ferro, come dicono, non ha odore. E la storia di come tuo padre Sean MacArthur ti portò per mare fin da bambino, facendoti diventare capitano, è ormai leggenda tra la flotta.";
			link.l1 = "E allora, che effetto fa incontrare questa leggenda, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Personalmente sono colpito. Anche se devo ammettere che parecchi dei miei ex colleghi trovano la cosa alquanto irritante. Ma per diventare capitano serve ben altro che una nascita nobile o una patente reale, non trovi?";
			link.l1 = "Vero. Servono conoscenza, esperienza, e una costante prontezza a dimostrare il proprio valore. Soprattutto nel mio caso.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Proprio così! In mare, come nella vita, non contano i titoli, ma i risultati. Piacere di conoscerti, Capitano MacArthur. Spero che ci rivedremo. Magari passerai a bere un bicchiere di vino quando tornerò dalla mia spedizione, giusto?";
			link.l1 = "Forse. Buona fortuna con le tue ricerche, Capitano.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Non mi interessa. Ma buona fortuna nelle tue ricerche, Capitano.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, Capitano "+pchar.lastname+"Che piacere vederti! Vuoi sederti, giusto?";
			link.l1 = "Con piacere.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Capitano... dimmi, che cosa sono per te i veri tesori?";
			link.l1 = "Un vero tesoro è l’amore. La persona giusta al tuo fianco. Non c’è niente di peggio che restare soli, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "I soldi, ovviamente. Cos'altro potrebbe mai essere un tesoro, giusto?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Equipaggiamento prezioso e unico. Una buona spada o una pistola valgono più dell’oro.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "La conoscenza, giusto? Il tesoro più prezioso è quello che hai nella testa.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Amore? Hmm... Non mi aspettavo una risposta del genere dalla figlia di un pirata. Io... io ero fidanzato. Con Elizabeth. La figlia di un piantatore delle Barbados. Ma suo padre... ha deciso che non avevo abbastanza denaro. Cosa potevo offrire a sua figlia, oltre al mio amore? Sei stato fortunato, Capitano MacArthur. Avevi un padre che apprezzava le tue capacità più della tua dote.";
				link.l1 = "Forse non si tratta di fortuna, ma del fatto che il vero amore non si misura in oro. Mio padre l'aveva capito. E la tua promessa sposa? Condivide le idee di suo padre, giusto?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Amore? Sì... Forse hai ragione. Io... ero fidanzato. A Barbados. Ci amavamo, ma... suo padre mi considerava indegno. Ah! Non ero abbastanza ricco. Ecco perché sono qui – a caccia di tesori per dimostrare che si sbagliava. Forse è tutto vano?";
				link.l1 = "Forse dovresti solo parlarle? Al diavolo quel piantatore.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Parlare... Sì, forse. Ma che dovrei dire? 'Scusa, non ho saputo darti una vita degna?' No. Devo tornare da vincitore. O non tornare affatto.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? No... lei mi ama. Ma io... non potevo lasciarla vivere nella miseria. Merita di più. E devo dimostrare di essere degno di lei.";
			link.l1 = "A volte l’orgoglio ostacola la felicità più della povertà, Capitano.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Non posso tornare a mani vuote. Semplicemente non posso. Mi scuso, ho molto da fare. È stato un piacere chiacchierare con te, Capitano MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Che risposta banale. Ma è difficile contraddirti. Davvero, quando cresci nei bassifondi di Bristol, quando devi lottare per ogni briciola... inizi a capire il vero valore del denaro. Non è il lusso. È la libertà. La possibilità di non dover mai più tornare in quella lurida fogna da cui sei uscito a fatica.";
			link.l1 = "Sono d'accordo. Il denaro risolve la maggior parte dei guai. E se non li risolve... vuol dire che non ce n'è abbastanza, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Esatto! Hai capito. Il denaro non porta felicità, ma la sua mancanza sì che rende infelici. Lo so fin troppo bene, giusto?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Interessante. Pratico. Ho un'archibugio... uno vero, dei tempi dei conquistadores. Un regalo di un certo prete. A volte penso che valga più di tutto l'oro che ho trovato. Ma... non risolverà i miei problemi.";
			link.l1 = "Buone armi risolvono un sacco di guai. E non ti tradiranno mai, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "È vero quel che dici. Ma ci sono battaglie che la forza delle armi non può vincere.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "La conoscenza... Sì, capisco. Ho studiato tutto quello che potevo sui conquistadores, sui tesori. Ho scritto un vero e proprio manuale sulla caccia al tesoro. Ho inventato un sistema di esercitazioni regolari e premi per la compagnia di fucilieri della nave. Qualunque capitano sarebbe felice di avere il mio manuale. Ma tutta questa sapienza... Non serve a nulla se non porta a risultati. A risultati veri.";
			link.l1 = "Ma è la conoscenza che porta ai risultati, giusto? Senza di essa, ogni ricerca è solo vagare nel buio.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Well, it's already late, and I have a lot of work to do";
			else sStr = "Well, I have a lot of work to do";
			dialog.text = ""+sStr+". Grazie per la chiacchierata, Capitano. È stata davvero interessante.";
			link.l1 = "Grazie anche a te, giusto?"+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+"Felice di vederti! Ho delle notizie eccellenti – finalmente ho trovato la soluzione ai miei guai. Presto salperò per una spedizione, e stavolta tornerò con un vero tesoro! Ah, e un consiglio da amica: stai lontano da Cayman. Da ora, quello è il mio territorio.";
			link.l1 = "Cayman non ti appartiene, Albert. Non hai i diritti della Corona su quell’isola. Questo è pirateria.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Mi stai minacciando, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Diritti della Corona? Dovevi nascere nei bassifondi di Bristol, "+pchar.name+", allora capiresti quanto valgono questi documenti. Quando hai fame, la legge non conta nulla. Comunque... hai ragione. Ufficialmente, non ho alcun diritto sull'isola. Ma lì ho trovato ciò che cercavo da anni. E non lascerò che nessuno me lo porti via.";
			link.l1 = "Spero tu capisca che stai seguendo una strada pericolosa, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Ho sempre saputo che la mia strada non sarebbe stata facile. Addio, "+pchar.name+"Forse ci rivedremo, giusto?";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Minaccioso? No, affatto. Solo un consiglio amichevole da capitano a capitano. Cayman è pericolosa... soprattutto per chi mette il naso nei miei affari.";
			link.l1 = "Mi ricorderò dei tuoi ‘consigli’. Buona fortuna a Cayman, giusto?";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "Buona fortuna, Capitano. Spero che non ti servirà. Addio.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Tu?! Pensi che mi arrenderò? Pensi che tornerò nella miseria? Preferisco crepare che morire di fame nei bassifondi ancora una volta! Niente pietà, niente premio, niente vittoria! Sotto la branda c’è una botte di polvere... Andremo tutti a fondo!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Chi diavolo sei per attaccarmi?! Pensavi che mi sarei arreso? Mai! Piuttosto crepo che tornare a morire di fame nei bassifondi! Niente pietà, niente ricompensa, niente vittoria! Sotto la branda c’è una botte di polvere... Affonderemo tutti insieme!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Capitano! Te l’avevo detto. Ora pagherai cara la tua curiosità.";
			}
			else
			{
				dialog.text = "Chi sei tu e con quale ardire osi calpestare il mio territorio?! Quest’isola è roba mia!";
			}
			link.l1 = "Vedremo, Blackwood. Oggi ci sarà un ossessionato in meno su questa terra.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Risolviamo la cosa senza spargimenti di sangue, Blackwood. Posso anche andarmene.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, sei un uomo ragionevole! Sei un ufficiale! Hai la bandiera reale che sventola sul tuo accampamento, per l'amor di Dio! Non possiamo trovare un accordo?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Ossessionato? Ah! Sono solo un uomo che sa ciò che vuole!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Andartene? Dopo quello che hai visto? No, no, no! Nessuno deve sapere quello che ho scoperto qui. Nessuno!";
			link.l1 = "Ti do la mia parola che non lo dirò a nessuno. Lo giuro sull’onore di un capitano.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "In questo mondo non esiste onore, Capitano. Solo sudiciume, miseria e disprezzo. Mi duole dirlo, ma qui devi trovare la tua fine.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Ho riflettuto. Tanto. E ho capito – questa è la mia unica occasione. O trovo l’oro di Cortez, oppure… niente. Capisci? NIENTE! Non tornerò mai alla mia vita di prima! Mai più miseria e sudiciume! Meglio crepare qui!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "Alla battaglia! Bullock, Fraser - pronti a sparare mitraglia se si avvicinano! Hopkins, carica!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Tutto bene, giusto?";
			link.l1 = "Sì, tutto a posto. E tu, giusto?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Vivo, sì. Ma queste battaglie a terra non fanno per me. Dammi un ponte sotto i piedi e sbranerò qualsiasi nave, ma qui... posto strano. Far sbarcare cento lupi di mare, farli brandire picconi, costruire fortificazioni... Non ci riuscirei mai.";
			link.l1 = "Blackwood sapeva come infiammare i cuori del suo equipaggio.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Ne ho sentito parlare quand'ero a Bluefield. Molti marinai inglesi ne parlavano con rispetto. Il miglior ufficiale della flotta, una carriera brillante... e poi d'un tratto ha gettato tutto alle ortiche per inseguire tesori.";
			link.l1 = "Che ne pensi di lui, giusto?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Penso che l'esempio di Blackwood dimostri bene il peso della responsabilità che noi… anzi, che tu porti sulle spalle davanti… ai tuoi uomini. Ti prego, non diventare il tipo di capitano che è diventato lui, giusto?";
			link.l1 = " Ci proverò, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Grazie, mio Capitano. So che ce la farai, giusto?";
			link.l1 = "Lo faremo.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "Lo faremo.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... che luogo orribile, questo.";
			link.l1 = "Tutto bene, Mary? Sei rimasta in piedi come una vera guerriera, giusto?";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "No, non sto affatto bene, giusto? Guarda questa gente! Hanno lavorato fino allo stremo, vissuto nella fame, sono morti di malattie... E per cosa? Per un oro che forse nemmeno esiste.";
			link.l1 = "Blackwood credeva che fosse proprio qui.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Questa giubba rossa... proprio come la mia. Un ufficiale inglese... Sai, mi sono venuti in mente i miei genitori, giusto? Le mie origini... tutto ciò che non ho mai saputo. Forse anch'io sono uno di loro?";
			link.l1 = "Uno di quelli, giusto?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Quelli che cercano qualcosa che forse nemmeno esiste. E poi si perdono nella ricerca. Io... ne vorrei parlare più tardi, giusto? Quando ce ne andremo da questo posto orribile.";
			link.l1 = "Ma certo, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Per prima cosa, diamogli una degna sepoltura, ti prego. Anche se forse non la merita. Per rispetto dell'uomo che era un tempo.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Capitano, Tichingitu vede posto maledetto qui. Posto davvero cattivo.";
			link.l1 = "Cosa vuoi dire, giusto?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "Quest’isola ormai è maledetta. La terra ha inghiottito troppo sangue e troppe lacrime. Chiunque scavi qui, respirerà questa maledizione.";
			link.l1 = "Pensi che Blackwood fosse posseduto?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Non solo posseduto. Lui è... come dire... un guscio vuoto. Qualcosa è entrato e ha cacciato via la sua anima. Io ho già visto questo. Quando lo sciamano della mia tribù offriva un sacrificio umano agli spiriti. Quello sciamano aveva lo stesso sguardo.";
			link.l1 = "Ma che cosa potrebbe mai causare una tale ossessione?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "Un uomo col vuoto dentro è facile da riempire con altri pensieri. Qualcuno trova la sua debolezza e la sfrutta. Tichingitu quasi si dispiace per quest’uomo.";
			link.l1 = "Quasi, giusto?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Sì, quasi. Ogni guerriero è responsabile delle proprie scelte. Anche se i demoni gli sussurrano nell’orecchio.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Maledizione, Capitano! Guarda qui! Proprio come ai vecchi tempi!";
			link.l1 = "Sai bene com'è la guerra sulla terraferma.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Mi ricorda la battaglia di Naseby. Il nostro fianco di cavalleria si scontrò con i cavalieri di Rupert. Combatterono con la stessa ferocia per il loro re.";
			link.l1 = "Cosa ne pensi di Blackwood, giusto?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Questo Blackwood era o un genio o un completo svitato. Anzi, secondo me entrambe le cose. Sai cosa mi sorprende? I suoi uomini. Molti di loro vengono dall’esercito. Non dei miserabili di strada, ma veri soldati. Eppure l’hanno seguito tutti in questa follia. Persino i fanti di marina di Fox. Ah! Quello sì che oggi si godrà il macello! Non ha mai perdonato loro il tradimento, giusto?";
			link.l1 = "Forse c’entra il denaro, giusto?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "No, c’è dell’altro. Quel tizio aveva un potere vero su di loro. Un potere reale. E poi ho sentito che era promesso a una ricca signorina di Barbados. Strano che non l’abbia sposata dopo aver messo le mani su tutti quei tesori. Un militare come tanti – non sapeva mai quando era ora di deporre le armi.";
			link.l1 = "Grazie, Tommy. Sei uno che ci sa fare, giusto?";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Eh?";
			link.l1 = "Niente.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Che amarezza vedere tutto questo, Capitano. Quanto in basso siamo caduti?!";
			link.l1 = "Noi?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "La flotta inglese! Guarda là: puntini di giubbe rosse mescolati a questa feccia morta!";
			link.l1 = "Un po’ di quella ‘feccia’ sono nostri uomini, Charlie. Capisco come ti senti, ma…";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Al diavolo tutto questo, capitano!";
			link.l1 = "Capisco come ti senti, ma faresti meglio a riversare la tua rabbia e la tua delusione su Blackwood. È lui che ha disertato dalla tua amata flotta inglese e li ha guidati fin qui.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "Proprio così. Andiamo, la giornata non è ancora finita, giusto?";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Obbedivano soltanto al loro capitano!";
			link.l1 = "Proprio come hai fatto con Fleetwood, giusto?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "Già. Andiamo, la giornata non è ancora finita, giusto?";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Come se ti seguissi io, giusto?";
			link.l1 = "Spero di dimostrarmi un capitano migliore di Blackwood e Fleetwood. Andiamo, la giornata non è ancora finita.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Aye, Capitano. E quando sarà finita – berrò finché non finirà la prossima, giusto?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, Capitano! State bene?";
			link.l1 = "Questo si vedrà. Quanti uomini abbiamo perso?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "Uccisi? In questa spedizione abbiamo perso "+sti(pchar.SailorDiedInBattleInfo)+" uomini. Non voglio sembrare invadente, Capitano, ma... ti avevo avvertito!";
			link.l1 = "Farò finta di non aver sentito quella battuta, perché oggi hai dimostrato il tuo valore, Alonso. Dove hai imparato così tante abilità, giusto?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Un giorno te la racconterò quella storia, Capitano – se avremo abbastanza vita, giusto?";
			link.l1 = "Altri preziosi consigli, giusto?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "Se ci fossero stati tesori qui, li avrebbero già trovati da tempo. Ma dobbiamo comunque perlustrare l'isola e cercare dei superstiti, poi decidere cosa farne. E non dimentichiamoci della nave di Blackwood: ho sentito solo lodi su quella meraviglia di snow. Sarebbe un peccato lasciarsi sfuggire un simile bottino, Capitano. Naturalmente, sto solo riportando il punto di vista dell’equipaggio su questa faccenda.";
			link.l1 = "Certo. Andiamo. Il bottino ci aspetta, giusto?";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Non sparate! Ci arrendiamo!";
			link.l1 = "Chi sei tu?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Noi... veniamo dalla 'Lady Beth'. Siamo uomini del capitano Blackwood. Lui... è ancora vivo?";
			link.l1 = "No. Il tuo capitano è morto.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Quindi è davvero finita... Grazie al cielo.";
			link.l1 = "Non sembri poi così afflitta per il tuo capitano, giusto?";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Non capisci. Blackwood era un grande uomo. Il miglior capitano che abbia mai conosciuto. Ma negli ultimi mesi... è cambiato. È diventato ossessionato, crudele. Ci faceva lavorare giorno e notte, cercando qualcosa che forse nemmeno esiste.";
			link.l1 = "Ti prendo nella mia ciurma. Abbiamo bisogno di marinai esperti.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Guai agli sconfitti, ragazzi. Ora il vostro posto è nella mia stiva. Se sarete fortunati – forse vedrete una piantagione alle Barbados.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Davvero? Tu... tu non hai paura che noi... che ci sia qualcosa che non va tra noi dopo tutto questo, giusto?";
			link.l1 = "Ognuno merita una seconda occasione.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Grazie, Capitano. Te lo giuro, non te ne pentirai. Siamo buoni marinai. E... forse adesso gli incubi finiranno.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Grazie, grazie! Almeno resteremo vivi. Portaci via da qui, ti prego. Quest’isola... è come se fosse maledetta.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Che diavolo?! Come osi attaccare la 'Signora' e ammazzare Jeremy? Non uscirete vivi da qui, mascalzoni, il capitano tornerà e...";
			link.l1 = "Il vostro capitano è morto. Jeremy ha sparato per primo, e ora la vostra 'Signora' è il mio bottino legittimo, pagato col sangue.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "Il capitano... morto? Bugiardo, cane! Non vali nemmeno un bottone della sua divisa!";
			link.l1 = "Se quella divisa aveva un senso, era solo per Blackwood, che ormai è solo polvere nei venti. Scegliete voi: volete morire per un uomo già sepolto, o preferite salvare la pelle?";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Non ti daremo la nave senza combattere!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Ascoltate, ragazzi. So che siete fedeli al vostro capitano. È una cosa che rispetto. Ma lui è morto, e voi siete ancora vivi. Ora dovete decidere come andare avanti. Vi stiamo offrendo la possibilità di ricominciare da capo.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Capitano, questi uomini non sono nemici. Stavano solo eseguendo degli ordini. Molti di loro sono ex marinai reali, ben addestrati e disciplinati. Sarebbe uno spreco non mettere a frutto le loro capacità. Ragazzi, sono stato nei vostri panni più di una volta durante il mio lungo servizio in flotta. E ho fatto la scelta giusta. Fatela anche voi.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Ebbene, marinai! La scelta è semplice: o vivete — come prigionieri nella stiva o unendovi alla nostra ciurma con razioni decenti e paga regolare, oppure... (passa il dito sulla gola) Fossi in voi, sceglierei la prima, giusto?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Diventerai parte della mia ciurma.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Guai agli sconfitti, ragazzi. Ora il vostro posto è nella mia stiva. Se vi va bene, vedrete una piantagione a Barbados.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Ci prendi davvero nella tua ciurma? Dopo tutto quello che è successo, giusto?";
			link.l1 = "I buoni marinai valgono oro. E il capitano Blackwood aveva occhio nello scegliere la sua ciurma.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Grazie, Capitano. Non vi deluderemo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Ebbene... almeno era l'unico modo in cui questa avventura poteva finire. Perdonaci, Capitano Blackwood. Non siamo riusciti a proteggerti.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Non ti daremo la nave senza combattere!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Mi scusi. Sei tu Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Sì, sono io. E tu chi saresti, giusto?";
			link.l1 = "Capitano "+GetFullName(pchar)+". Io... conoscevo Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Il mio Albert? Oh Dio... Sta bene, giusto?";
			link.l1 = "Purtroppo no. È caduto in battaglia. Ha combattuto fino all’ultimo respiro.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "Io... lo sospettavo. Tutti questi anni senza una sola parola... Sai, l'ho aspettato. L'ho aspettato a lungo. Mio padre diceva che Albert doveva solo aspettare una promozione. Il governatore aveva già deciso tutto, era solo questione di pochi mesi. Ma Albert... lui ha preso quella conversazione in tutt'altro modo. Disse che sarebbe tornato ricco, degno della mia mano. E se n'è andato. Semplicemente... se n'è andato.";
			link.l1 = "Ti ha pensato fino al suo ultimo giorno.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Che sciocchezza. Non mi servivano i suoi tesori. Io amavo lui, non il suo denaro. Ero pronta a fuggire con lui... ma era così orgoglioso. Ho aspettato una lettera, una qualsiasi parola... E invece è arrivato solo questo strano manuale. Un documento freddo, calcolato... niente a che vedere con l’Albert che conoscevo. È stato allora che ho capito di averlo perso.";
			link.l1 = "Tra le sue cose, ho trovato questo.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Una mappa per la mia casa? Ero io il suo vero tesoro? Che ironia. Ha cercato ricchezze in tutto il Caribe, e l’unica cosa che contava era qui… sempre. Aspetta. Ho qualcosa per te. Questo è il manuale di Albert. Me l’ha mandato un anno fa. Diceva che lo avrebbe aiutato a trovare tesori e poi tornare da me. Ora sarà più utile a te, giusto?";
			link.l1 = "Grazie, Elizabeth. Mi dispiace che sia andata a finire così.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "E mi sono sposata, Capitano. Con il signor Bishop. Mio padre ha preteso così. Tu non conosci quest'uomo... e credimi, non vorresti. Ogni giorno mi domando come sarebbe stata la mia vita se solo Albert fosse... tornato.";
			link.l1 = "Ora ci penserò anch’io, giusto?";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Addio, Capitano. E... abbi cura di te. Non inseguire fantasmi, giusto?";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Sì, sono proprio io.";
			link.l1 = " Capitano Helen MacArthur. Io... conoscevo Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Il mio Albert? Oh cielo... Lui... E tu chi diavolo sei, giusto?";
			link.l1 = "Capitana Helen MacArthur, l’ho appena detto. Comando la mia nave, giusto?";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Capitano? Una donna capitano? Tu... Tu stavi con Albert? In che senso... lo conoscevi?";
			link.l1 = "Solo come capitano. Mi dispiace, ma Albert è morto. Ho assistito alla sua ultima battaglia.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Capisco. Perdona la mia diffidenza. È solo che... il capitano Blackwood ha sempre attirato gli sguardi delle donne. Anche qui, a Barbados. Anzi, soprattutto qui.";
			link.l1 = "Lo amavi, giusto?";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "Con tutto il mio cuore. Padre diceva che ad Albert bastava aspettare una promozione, sarebbe stato solo questione di pochi mesi. Ma lui ha preso le parole di mio padre come un rifiuto per via della povertà. Ha detto che sarebbe tornato con dei tesori. E se n’è andato.";
			link.l1 = "Gli uomini e il loro maledetto orgoglio, giusto?";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Sei fortunato, capitano MacArthur. Sei libero. Navighi dove ti pare. Niente piantatori, niente padri a decidere il tuo destino. Niente mariti che ti trattano come una loro proprietà, giusto?";
			link.l1 = "La libertà ha un prezzo salato. E va difesa ogni singolo giorno.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Forse ho qualcosa che ti sarà utile in questa faccenda. Tieni, prendi pure. Questo è il suo manuale per la caccia ai tesori. Albert me lo mandò circa un anno fa. Diceva che era la sua opera migliore. Che lo avrebbe aiutato a far fortuna e a tornare da me. Ma, pagina dopo pagina, sembrava sempre meno l’Albert che conoscevo.";
			link.l1 = "Grazie. Lo tengo io.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Ti prego, Capitano... apprezza la tua libertà. Ho sposato il colonnello Bishop. Un uomo che perfino mio padre teme. Se fossi libera, come te... Tutto sarebbe diverso.";
			link.l1 = "Lo so.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Addio, Capitano. E che i venti ti siano propizi.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		// диалог с Диего де Ланда
		case "LadyBeth_DiegoDeLanda_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Hai visto Lady Bishop? Una storia triste, giusto?";
				link.l1 = "Chi sei, tu?";
				link.l1.go = "LadyBeth_DiegoDeLanda_First_1";
			}
			else
			{
				dialog.text = "Ciao, Capitano.";
				link.l1 = "Aspetta! Ci siamo già incontrati! Che ci fai a Barbados, giusto?";
				link.l1.go = "LadyBeth_DiegoDeLanda_Second_1";
			}
		break;
		
		case "LadyBeth_DiegoDeLanda_First_1":
			dialog.text = "\nServo la parrocchia di Santa Maria. Pochi cattolici a Barbados trovano conforto nella nostra chiesa.";
			link.l1 = "Conosci Elizabeth, giusto?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_2";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_2":
			dialog.text = "Oh, sì. Povera donna. Suo marito... non è certo un santo, giusto? Dicono che le sue piantagioni siano le più produttive di Barbados. E le più crudeli. Sai quanti schiavi ci lasciano la pelle ogni mese? Ultimamente ha massacrato a bastonate persino un vero medico inglese – un uomo d’ingegno e talento. Ma credimi, la sua sorte non è molto migliore.";
			link.l1 = "Sembri ben informato.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_3";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_3":
			dialog.text = "La gente viene da me per confessarsi, Capitano. Ascolto ciò che non osano dire neppure alle persone più care. Le loro paure, i loro peccati... il loro dolore.";
			link.l1 = "Non hai paura delle persecuzioni? Non è semplice per un prete cattolico nelle terre degli inglesi.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_4";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_4":
			dialog.text = "Dimmi... hai cercato proprio Blackwood? Curioso. Ma perché? Era pericoloso e da pazzi. Qual è la tua fiamma, Capitano? Cosa ti spinge avanti?";
			link.l1 = "Non sono affari tuoi.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_5";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_5":
			dialog.text = "Non riesco a capire. Gli altri – sì. Ma te... non ancora.";
			link.l1 = "Altri?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_6";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_6":
			dialog.text = "Uno, per esempio, si batte per la giustizia. E poi c'era un altro... ossessionato dalle acque oscure della morte. È così facile per la gente perdersi nei propri desideri. È vero, giusto?";
			link.l1 = "Sei un prete davvero strano, Santo Padre.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_7";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_7":
			dialog.text = "...";
			link.l1 = "Penso che me ne andrò adesso, giusto?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_8";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_8":
			dialog.text = "Ma certo. Il tuo compito è appena cominciato, Capitano.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_1":
			dialog.text = "Servo la parrocchia di Santa Maria. Hai visto Lady Bishop? Un destino triste. Ma, temo, ben meritato.";
			link.l1 = "L'ultima volta parlavi per enigmi. Lo farai di nuovo, giusto?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_2";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_2":
			dialog.text = "\nIl vero enigma è qui davanti a me, adesso. Hai raccolto molte reliquie... intriganti. Bibbia. Statuto. Ti piace collezionare simili cimeli? Sei forse un collezionista?";
			link.l1 = "Come fai a sapere del manuale, giusto?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_3";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_3":
			dialog.text = "Un cacciatore di trofei?";
			link.l1 = "Ripeto la mia domanda: come fai a sapere del manuale?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_4";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_4":
			dialog.text = "Un'amante del brivido, giusto?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_5";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_5":
			dialog.text = "\nAh. Certo. Naturalmente. Bene, Capitano, non vi trattengo oltre.";
			link.l1 = "Aspetta un momento, Santo Padre. Non hai ancora risposto alla mia domanda.";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_6";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_6":
			dialog.text = "Oh, Capitano. Non posso. A volte le risposte fanno più male dell’ignoranza stessa. Vai in pace. E abbi cura della tua collezione… di trofei. Potrebbero tornarti utili nel viaggio che ti aspetta.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
	}
} 