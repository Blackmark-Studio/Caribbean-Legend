//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. Stai navigando sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+", capitano. Non ho alcun desiderio di parlare con il nemico del mio paese. Hmph!";
					link.l1 = "Ah, sì. Un vero patriota...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Cosa vuoi da me, "+GetAddress_Form(NPChar)+"? Non è appropriato per un semplice marinaio parlare con una nobile signora, ma ti sto ascoltando.","Oh, e cosa vuole da me un capitano così coraggioso?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Non prenderò molto del tuo tempo, voglio solo chiedere...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Ho bisogno di sapere cosa sta succedendo nella tua colonia.","Ho bisogno di alcune informazioni.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("L'intera città è sul chi vive - don Fernando de Alamida, l'ispettore reale, è arrivato. Sai, ho visto molto qui, ma questo... Non è la sofferenza che cambia le persone, ma come la affrontano. Dicono che sia diventato un uomo diverso dopo la morte di suo padre. Ora non troverai un servo della Corona più incorruttibile e... spietato in tutto l'Arcipelago.","Guarda solo la 'Santa Misericordia'! Dicono che sia stato il re stesso a ordinare la sua costruzione secondo progetti speciali. E nota - non un solo graffio. Come se la Vergine Maria stessa la proteggesse. Anche se ho sentito voci... forse non è la Vergine affatto.","Sai quante volte hanno cercato di uccidere don Fernando? Dodici attacchi in acque libere - e solo nell'ultimo anno! Beh, con un equipaggio così leale e addestrato, e sotto la protezione del Signore - sopravviverà anche al tredicesimo!"),LinkRandPhrase("Hai sentito? Don Fernando de Alamida è arrivato nella nostra città, e dicono che sia da qualche parte per le strade in questo momento. Mi piacerebbe vederlo con i miei stessi occhi...","Un uomo complicato, questo don Fernando. Alcuni dicono che sia un salvatore, che pulisce la Madrepatria dalla sporcizia. Altri sussurrano che qualcosa si è rotto in lui dopo la morte di suo padre e presto tutti noi piangeremo. Ma ti dirò questo: non aver paura di lui. Temi coloro che l'hanno reso quello che è.","Un uomo così affascinante, questo don Fernando! Ma sai cosa è strano? È come se non notasse nessuno. Tutto dovere e servizio. Ho sentito dire che c'era una ragazza... ma dopo aver incontrato un certo prete, ha completamente rifiutato i piaceri mondani. Come se avesse fatto un voto."),RandPhraseSimple(RandPhraseSimple("Maledetto ispettore! Mentre lui è qui - la città sembra morta. Niente commercio, niente divertimento. Anche respirare, sembra, deve essere più silenzioso. E sai cosa è più spaventoso? È la stessa cosa in ogni porto. Come un orologio. Sua Maestà Reale non avrebbe potuto inventare appositamente questa tortura per tutti noi!","Don Fernando ha visitato nuovamente l'orfanotrofio. Dona generosamente, prega per ore. Un uomo così degno dovrebbe essere preso come esempio da quei maledetti imbroglioni!"),RandPhraseSimple("Ha! 'Santo' Fernando ha chiuso tutte le case chiuse di nuovo. Beh, non importa, presto salperà e riapriranno subito.","È arrivato l'ispet... l'ispettore, ecco cosa! Don Fernando de Almeyda, o come diavolo si chiama, Alamida! Così importante che lo stesso governatore gli cammina attorno in punta di piedi. Dicono che ti guarda negli occhi e vede tutti i tuoi peccati subito. Terrificante!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Dovrei ripetermi? Non voglio essere sospettato come un amico di "+NationNameAblative(sti(pchar.nation))+"! Vattene o chiamerò le guardie! Saranno felici di parlare con te.";
					link.l1 = "Bene, bene, calmati. Me ne sto andando.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Cosa? Tu di nuovo? Cerca qualcun altro con cui parlare. Ci sono un sacco di plebei in giro, sono più il tuo tipo. Devo andare ora, ci sarà un banchetto stasera nella residenza del governatore e il mio pompadour non è ancora pronto!","No, ora stai davvero dando fastidio! Non capisci? O sei di mente lenta?","Signore, comincio a sospettare che tu non sia solo un idiota, ma un mascalzone e un volgare. Ti avverto che chiamerò mio marito se non smetti di infastidirmi con le tue stupide domande!","Un'altra parola e dirò al comandante di fare qualcosa con te!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Capisco. Addio.","Sì-sì, ricordo, ho solo dimenticato di chiedere...","Mi hai frainteso...","Calma, signora, sto già andando via...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Bene, ascoltiamo.","Oh, bene. Che cosa vuoi?","Domande? Bene, marinaio, ti sto ascoltando.");
			link.l1 = LinkRandPhrase("Potresti dirmi l'ultimo pettegolezzo di questa città?","È successo qualcosa di interessante qui di recente?","Qualche notizia dai Caraibi, mia signora?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Sei impazzito?! Mi fai paura! Infila la tua arma o dirò al comandante di impiccarti nel forte!","Sei pazzo?! Mi fai paura! Infila la tua arma o dirò al comandante di impiccarti nel forte!");
			link.l1 = LinkRandPhrase("Bene.","Come desideri.","Bene.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
