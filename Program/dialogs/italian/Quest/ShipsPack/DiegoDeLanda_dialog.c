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
			dialog.text = "Cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Una storia triste, non è vero?";
				link.l1 = "Chi siete?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Salve, capitano.";
				link.l1 = "Aspettate! Ci siamo già incontrati!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Uno. Due. Tre.";
				link.l1 = "Basta con questo spettacolo. Chi siete veramente?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Sai cosa c'è di speciale in questa cripta? Qui riposano due anime, legate... dal sangue. Padre e figlio de Alameda. Uno caduto per mano dei peccatori, l'altro... hm, ha trovato la sua via verso il Signore.";
				link.l1 = "Il diario di Don Fernando mi ha portato qui.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Avete visto la signora Bishop? Un destino triste, non è vero? Ma temo che fosse meritato.";
				link.l1 = "Conoscete Elizabeth?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grimm.";
				link.l1 = "Lo conoscevate, naturalmente?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nAltri tre. Al conto di sei saprete tutto.";
			link.l1 = "Se non mi date subito delle risposte chiare, allora io...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nState andando bene, capitano. Meritate di conoscere il mio nome. Mi chiamo Diego de Landa.";
			link.l1 = "Siete davvero un prete?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Prima di tutto, sono un artista. Ma non abbiate fretta...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... Il diario. Una cosa straordinaria, la parola scritta. È come... un sentiero nell'oscurità. Conduce là dove attende... la rivelazione. La nostra parrocchia visitava spesso Don Fernando. Soprattutto nell’ultimo anno.";
			link.l1 = "Servite nella parrocchia locale? Conoscevate Don Fernando?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Io... ho osservato il suo cammino. E questo libro che avete preso. Sapete cosa ha di speciale?";
			link.l1 = "Sembra vecchio.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Vecchio? Oh no. È... illuminato. La Bibbia del vecchio Don de Alameda. Ogni parola in essa è come un faro nell’oscurità. Prendetela. Aiutate i fratelli in Cristo e forse... anche voi sarete condotti a qualcosa... di più grande.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Oh, sì. Povera donna. Suo marito... non è certo un uomo gentile. Si dice che le sue piantagioni siano le più produttive di Barbados. E le più crudeli. Sapete quanti schiavi muoiono lì ogni mese? Recentemente ha picchiato a morte un vero medico inglese – un uomo di grande intelletto e talento. Ma il destino di lei non è molto migliore, credetemi.";
			link.l1 = "Sembra che siate ben informato.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "Le persone vengono da me per confessarsi, capitano. Ascolto ciò che temono dire persino ai loro cari. Le loro paure, i loro peccati... il loro dolore.";
			link.l1 = "Non temete le persecuzioni? Non è facile per un prete cattolico nei territori inglesi.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Le mie paure non sono nulla rispetto a ciò che avete lasciato dietro quella porta. E quel libretto che avete preso da quella povera donna... Se la paura avesse una forma, sarebbe proprio quella.\n"+
			"Buona giornata, capitano.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет

		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tigre, Tigre, terrore ardente\n"+
			"Bruci tra i boschi notturni\n"+
			"Quale sguardo immortale, con amore, creò te così terribile?\n"+
			"Certo che lo conoscevo, capitano. Ma voi lo conoscevate?";
			link.l1 = "Non ho mai incontrato uomo dal destino più tragico.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Lo avete incontrato, ma ancora non lo avete compreso\n"+
			"Allora non conoscevate Grim. Anche se tenete in mano il suo teschio.";
			link.l1 = "Cosa?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "Non è cristiano trattare così un defunto. Ecco, prendete un piccolo manuale post mortem. È un mio dono per voi.\n"+
			"Buona giornata, capitano.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Ditemi... Perché? Era pericoloso e sciocco. Qual è il vostro fuoco, capitano? Cosa vi muove?";
				link.l1 = "Non sono affari vostri.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Secondo.";
				link.l1 = "La scorsa volta parlavate per enigmi. Lo farete anche ora?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Aspettate, de Landa. Non posso semplicemente lasciarvi andare.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;

		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Non riesco a capire. Gli altri sì. Ma voi... ancora no.";
			link.l1 = "Gli altri?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Uno, ad esempio, cerca giustizia. Poi c’era un altro... ossessionato dalle oscure acque della morte. È così facile per le persone perdersi nei propri desideri. Non è vero?";
			link.l1 = "Siete uno strano prete, padre.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Credo che andrò.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Certo. Il vostro lavoro è appena cominciato, capitano.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nUn vero enigma mi sta davanti ora. Avete già raccolto due... reliquie. Vi piace collezionare queste cose? Siete un collezionista?";
			link.l1 = "Come lo sapete?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Un cacciatore di trofei?";
			link.l1 = "Ripeto la mia domanda: come lo sapete?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;

		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Amante del brivido?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Ma certo. Naturalmente. Allora, capitano, non vi trattengo oltre.";
			link.l1 = "Aspettate, padre. Non avete ancora risposto alla mia domanda.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, capitano. Non posso. A volte le risposte feriscono più dell'ignoranza. Andate in pace. E custodite bene la vostra collezione... di trofei. Potrebbero servirvi nel viaggio che vi attende.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Forza, capitano. Non siete curioso? Non vi state divertendo? Vi bastano i trofei?\n"+
			"È questo il vostro fuoco, capitano. Volete sapere cosa accadrà dopo. Amate le belle navi e gli oggetti curiosi\n"+
			"Semplicemente non potete fare a meno di raccoglierli tutti.\n"+
			"\n"+
			"Potete spararmi subito.";
			link.l1 = "Cosa?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Fate pure. Ma allora non saprete tutto e non avrete la collezione completa di trofei. Le navi, comunque, le avrete tutte\n"+
			"Buona giornata, capitano.";
			link.l1 = "(Lasciarlo andare)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Sparargli)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 