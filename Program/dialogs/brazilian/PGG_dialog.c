#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Cruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is coming, not 'Beware' you idiot! Ha-ha-ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "Se você encontrar um erro... por favor, reporte ao QA, para a Marinha.";
//	link.l1 = "Com certeza!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Ei, cai fora, vai! Se você estragar meu negócio, eu arranco seu coração!";
			link.l1 = RandPhraseSimple("Você ousa me ameaçar, seu cão?!","Vou fazer você engolir suas palavras, canalha!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Ah, entendi. Negócios são negócios. Boa sorte.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Boa tarde, meu nome é "+GetFullName(NPChar)+", e a sua?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "Meu nome é "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Bebida para todos! Eu sou o capitão "+GetFullName(pchar)+".","Eu sou o capitão do '"+PChar.Ship.Name+" e uns duzentos diabos de verdade! He-he! Meu nome é "+GetFullName(pchar)+"."),RandPhraseSimple("Permitam-me apresentar-me, senhores. Sou o Capitão "+GetFullName(pchar)+".","Ainda não fomos apresentados. Eu sou o capitão do '"+PChar.Ship.Name+" sob a bandeira de "+NationNameGenitive(sti(PChar.nation))+". Meu nome é "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Bem, todo mundo aqui me conhece! Eu sou "+GetFullName(NPChar)+". Prazer em conhecê-lo! Em que posso ajudar?";
		link.l1 = RandPhraseSimple("Tenho negócios com você!","Quero conversar com você...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Bem, todo mundo aqui me conhece! Eu sou "+GetFullName(NPChar)+", capitão "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "Que tal se juntar a mim? Dois navios são melhores do que um. Podemos fazer bons negócios juntos.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Você gostaria de servir como oficial no meu navio?","Acho que você se sairia bem como oficial no meu navio. O que me diz?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Missões.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-test) Duelos.";
			link.l8.go = "outraged";
		}
		link.l9 = "Nada.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Ei, cai fora, tá ouvindo! Se você estragar meu negócio, eu arranco seu coração!";
			link.l1 = RandPhraseSimple("Você ousa me ameaçar, seu cachorro?!","Vou fazer você engolir essas palavras, canalha!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Ah, entendi. Negócios são negócios. Boa sorte.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Já te contei tudo por hoje!";
			link.l1 = "Oh, sim...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("O que você precisa"+GetFullName(pchar)+"?","Quem é? Ah, é você... Cai fora, não tô com paciência...");
		link.l1 = RandPhraseSimple("E que tal um negócio?","Eu queria conversar com você...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Olha só quem apareceu! É "+GetFullName(pchar)+". Alguma novidade?","Como vai? Em que posso ajudar?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase(" Quais são as novidades?"," Quais são as novidades pelo arquipélago?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+" Quais são as novidades?",PGG_Meet_BadRep[iAns]+" Quais são as novidades pelo arquipélago?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Que tal se juntar a mim? Dois navios são melhores do que um. Podemos fazer bons negócios juntos.","Você parece um capitão experiente. Quer navegar sob minha bandeira?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Ah, que desgraça... Meu navio afundou!","Olha só quem apareceu?! O que te traz aqui? Aliás, perdi meu navio...");
				link.l3 = RandPhraseSimple("Que pena. Talvez você tenha mais sorte da próxima vez.","É mesmo... Bem, está na hora de eu ir. Até mais.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Você gostaria de servir como oficial no meu navio?","Acho que você se sairia bem como oficial no meu navio. O que me diz?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "Quais são as novidades?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Que cara feia. Dá até vontade de socar.","Oh, nosso 'amigo'. Quer ganhar uns buracos novos no peito?");
			link.l8.go = "outraged";
		}
		link.l9 = "Nada.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Já te disse que não estou interessado.","Eu pensei que já tínhamos discutido tudo.");
			link.l1 = RandPhraseSimple("Como eu poderia esquecer?","Justo. Tchau.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hum... talvez não. Não uma segunda vez.","E você achou que eu cairia nessa de novo?!");
			link.l1 = RandPhraseSimple("Bem, como quiser...","Certo. Até mais, então.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hum... Não, acho que não.","Não, eu sou capitão, e não quero servir como oficial.");
			link.l1 = RandPhraseSimple("Bem, como quiser...","Tá certo. Até mais, então.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Você já tem um conjunto completo.","Acho que você ainda não está pronto para me dar ordens.");
			link.l1 = RandPhraseSimple("Pena...","Bem, o destino quis diferente.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Era exatamente o que eu precisava! Nossas lâminas vão provar o sangue dos nossos inimigos! Mas tem um problema - ainda preciso "+NPChar.Quest.Officer.Price+" pesos para pagar minhas dívidas.","Você parece um verdadeiro lobo do mar. E se estiver disposto a pagar "+NPChar.Quest.Officer.Price+" pesos, talvez possamos trabalhar bem juntos."),LinkRandPhrase("Sua oferta é bastante lisonjeira. Aceito trabalhar para você por uma quantia bem modesta de "+NPChar.Quest.Officer.Price+" pesos.","Hum... Você parece um marinheiro experiente. Talvez eu deva aceitar sua oferta se estiver disposto a me pagar "+NPChar.Quest.Officer.Price+" pesos.","Acho que vamos trabalhar bem juntos, capitão. Só "+NPChar.Quest.Officer.Price+" pesos, e temos um acordo."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "Hmm... e quão qualificado você é?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Acho que você está com um problema de dinheiro, capitão.";
			link.l1 = "Oh... de fato.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("Excelente!","Eu nunca duvidei de você, capitão.");
		link.l1 = "Não se atrase para a partida.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Um erro, avise os desenvolvedores";
		link.l1 = "Eu vou!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Já te disse que não estou interessado.","Eu pensei que já tínhamos discutido tudo.");
			link.l1 = RandPhraseSimple("Como eu poderia esquecer?","Justo. Tchau.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Navegar com você?! Cresça um pouco primeiro!","Acho que não estou interessado nisso!");
			link.l1 = RandPhraseSimple("Bem, como quiser...","Certo. Até mais, então.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hum... Não, acho que não.","Não, obrigado. Não gosto de servir sob as ordens de ninguém.");
			link.l1 = RandPhraseSimple("Bem, como quiser...","Certo. Até mais, então.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Gostei de você! Negócio fechado! Já consigo ouvir o tilintar dos pesos nos nossos bolsos!","Você é esperto "+GetSexPhrase("cara","moça")+"... Acho que vamos trabalhar bem juntos!"),LinkRandPhrase("Gostei da sua proposta. Aceito.","Isso é interessante. Sabe, acho que juntos podemos conquistar ainda mais!","Isso vai ser divertido. Fechado!"));
			link.l1 = RandPhraseSimple("Ótimo! Vou te esperar no mar!","Fechado! Vamos formar uma ótima tripulação.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Acho que você já tem companheiros suficientes.","Você já tem navios suficientes – por que precisaria de mais?");
			link.l1 = "É... Talvez você esteja certo.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Estou cansado de você!!! Estou saindo do seu esquadrão!","Minha paciência acabou! Estou indo embora."),RandPhraseSimple("Estou cansado das suas escapadas, 'almirante'... Permita-me retirar-me.","Estou farto do seu comando e estou deixando o seu esquadrão."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Tá bom, então cai fora.","Certo, vá para onde quiser."),RandPhraseSimple("Tudo bem. Não vou te segurar.","Essa é a sua escolha. Que os ventos estejam a seu favor."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... que tal um extra?","Caramba! Ora, talvez você pudesse ficar? Posso até pagar um extra pros seus homens!"),RandPhraseSimple("Eu odiaria me separar de você... Talvez uma pequena compensação possa resolver nossa disputa?","Que tal aumentar seu salário?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Uma vez já foi suficiente para mim. Não vou mais confiar nas suas promessas!","Você não vai me seduzir com dinheiro! Minha decisão é final!");
			link.l1 = RandPhraseSimple("Está certo, boa sorte pra você.","Então suma daqui e trate de nunca mais aparecer na minha frente!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Um prêmio? Tudo bem! Uma quantia de "+NPChar.Quest.Companion.Price+" pesos vão me servir muito bem.","Bem, talvez, se você estiver disposto a pagar à minha tripulação "+NPChar.Quest.Companion.Price+" pesos, talvez eu consiga convencê-los a ficar."),RandPhraseSimple("Certo! Posso ficar por uma pequena taxa de "+NPChar.Quest.Companion.Price+" pesos!",NPChar.Quest.Companion.Price+" vai satisfazer a mim e à minha tripulação por um bom tempo."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Tá rindo de mim ou o quê?! Cai fora, agora!","Ha! Eu prefiro gastar esse dinheiro com algo mais útil!"),RandPhraseSimple("Ah não. Eu não sou tão rico assim!","Adeus. Vou pagar essa quantia."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Excelente! Aqui está a sua recompensa!","Eu nunca duvidei que tudo se resumia a dinheiro!"),RandPhraseSimple("Excelente! Fico feliz que você vai ficar.","Aqui está o que eu prometi."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Selecione um modelo!";
		link.l1 = "Modelo de missão 1 - mar.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "SELECIONADO! Modelo de missão 1 - terra.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Modelo de Missão 1 - mar.";
		link.l1 = "Oh, sim...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "SELECIONADO! Modelo de Missão 1 - terra.";
		link.l1 = "Oh, sim...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Já te contei tudo o que sei!";
			link.l1 = "Ah, sim...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Que assunto?.. Hic! Não tá vendo que eu e os rapazes estamos nos divertindo?.. Hic...","Ehh... Sem negócios hoje!");
		link.l1 = "Entendi...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "Que conversa? Mas, veja só, você chegou na hora certa. Quando se trata de negócios, estou sempre pronto!";
					link.l1 = "Hum. Do que você está falando?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...só o diabo e eu conhecemos esse lugar, e quem for o último a ficar vivo leva tudo!..","...e Meinard respondeu: 'Não espero misericórdia de você, e também não vou lhe dar nenhuma'","...e assim que estávamos em alto-mar, quando ele já estava meio bêbado, sugeriu: 'Vamos causar o diabo lá e ver quem fica de pé até o fim'.")+PCharRepPhrase(LinkRandPhrase("Lá vem outro pirata!","Senhores, será que temos um cavalheiro de fortuna à nossa mesa, hein?","Sinto cheiro de pólvora e sangue! Um filibusteiro a estibordo!"),LinkRandPhrase("Capitães decentes são uma raridade nessas águas.","A nobreza está fora de moda hoje em dia.","Ah, agora sim, um verdadeiro capitão, não como vocês, bando de assassinos! He-he!"));
						link.l1 = "Eu não estou gritando, estou te dizendo – tem um negócio lucrativo!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "Cuidado, cuidado! Oh! Eu te conheço. Você é "+GetFullName(PChar)+". Já ouvi falar muito sobre você.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Eu sou o capitão "+GetFullName(pchar)+".","Eu sou o capitão do '"+PChar.Ship.Name+" e uns duzentos verdadeiros demônios! He-he! Meu nome é "+GetFullName(pchar)+".")+" Mas eu não me lembro de você.",RandPhraseSimple("Permitam-me apresentar-me, senhores. Sou o Capitão "+GetFullName(pchar)+".","Ainda não fomos apresentados. Eu sou o capitão do '"+PChar.Ship.Name+" sob a bandeira de "+NationNameGenitive(sti(PChar.nation))+". Meu nome é "+GetFullName(pchar)+".")+" Mas eu não me lembro de você.");
//			link.l1 = "Hum... e quem é você? Não me lembro de você.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Oi, "+GetFullName(NPChar)+". Como vai a vida?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Eu sou "+GetFullName(NPChar)+", capitão "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". O corsário mais notório de todo o Caribe espanhol.",". Só um marinheiro.");
		link.l1 = "Sim, agora vou me lembrar de você.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Tenho assuntos a tratar com você, "+GetSexPhrase("companheiro","moça")+". Eu sei que posso confiar em você, mas simplesmente não posso falar sobre isso na taverna – tem ouvidos demais nos lugares errados. Vou te esperar a bordo do meu navio. O nome do meu velho barco é '"+NPChar.Ship.Name+"'.";
//			link.l1 = "Fale logo, não tenho tempo para visitas.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Tenho um trabalho interessante para você e seus brutamontes.","Se unirmos forças, podemos conquistar um prêmio realmente grandioso! Claro, vamos ter que matar alguém no caminho. He-he."),RandPhraseSimple("Tenho uma proposta de negócio para você, capitão.","Capitão, sua reputação é incomparável, e por isso o convido a participar de um empreendimento muito tentador."))+RandPhraseSimple("Só entre nós dois. Vamos conversar sobre isso na sala de oficiais do '"+NPChar.Ship.Name+"   sobre o barril da melhor cerveja. Hoje.","Não devemos discutir isso aqui, vamos negociar os detalhes em '"+NPChar.Ship.Name+" em paz e tranquilidade. E, por favor, não demore muito.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Que se dane essa demora! Se for coisa boa, quero saber na hora, e se for ruim, mais ainda!","Não faz sentido conversar assim, tão às pressas! Tem um quarto apropriado na taverna – vamos até lá!"),RandPhraseSimple("E por que não podemos discutir sua proposta agora, no quarto da taverna?","Receio que não tenho muita vontade de visitar seu navio. Se precisa de algo, diga logo aqui e agora!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... Não devíamos falar de negócios na taverna – tem ouvidos demais por aqui. Estou te esperando no meu navio '"+NPChar.Ship.Name+". Vamos conversar lá.";
			link.l1 = "Não tenho tempo e não gosto de fazer visitas.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Eu vou. Mas se você estiver só perdendo meu tempo, eu arranco sua língua fora!",RandSwear()+"Certo, me espere. Espero que sua oferta valha a pena. E nem pense em tentar me enganar!"),RandPhraseSimple("Eu aceitarei seu convite com prazer, capitão.","Você me deixou curioso. Claro, eu vou."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Ah, está enjoado, é? Vai correr e se esconder debaixo da saia da sua mãe!","Tá com medo?! Cai fora!"),RandPhraseSimple("Não vai rolar. Se ouro não te interessa, é problema seu.","É assim e não tem outro jeito. Se não quiser - tudo bem, há muitos outros."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha! Você é corajoso, não é? Tudo bem, eu vou!","Vejo que você sabe se manter firme, capitão. Tudo bem, me espere."),RandPhraseSimple("Certo, eu concordo.","Você fala bastante. Estou pronto para discutir negócios no seu navio."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha! Você achou que ia me atrair para o seu navio e me matar lá? Isso não vai acontecer!","Suas palavras não valem um tostão! Não quero fazer negócio com você!"),"Oferta duvidosa. Preciso recusar.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Rum pra mim! E você, suma da minha frente!","Já não discutimos tudo?"),RandPhraseSimple("Cuide da sua vida. Eu tenho coisas para fazer.","Não acho que temos algo para discutir."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Eu disse que estaria esperando por você no meu navio!";
		link.l1 = "Oh... claro...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Ah, não, isso não vai dar certo... Não são navios demais pra você? "+GetSexPhrase("companheiro","moça")+"?","Ha! Com tanta gente por perto, não tem como esconder nada. Cai fora.");
			link.l1 = RandPhraseSimple("Como quiser!","Tá bom. Não que eu me importe.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Ótimo. Agora tenho certeza de que não há ouvidos indesejados por perto, e meus marinheiros já foram avisados. Então, minha proposta é adquirir algumas mercadorias sem dono.";
//			link.l1 = "E o que tem de tão difícil nisso? Por que você precisaria de mim pra isso, afinal?";
			Dialog.Text = RandPhraseSimple("Bem-vindo a bordo, capitão!","Ótimo. Agora tenho certeza de que não há ouvidos indesejados por perto, e meus marinheiros já foram avisados. Então, minha proposta é adquirir algumas mercadorias sem dono.")+" Então minha proposta é adquirir algumas mercadorias sem dono.";
			link.l1 = RandPhraseSimple("E o que tem de tão difícil nisso? Por que você precisaria de mim pra isso, afinal?","Sem dono?! Você só pode estar brincando!");
		}
		else
		{
			Dialog.Text = "Agora tenho certeza de que não há ouvidos indesejados por perto - pode falar logo!";
			link.l1 = "Então minha proposta é adquirir algumas mercadorias sem dono.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Bem, há pessoas que acham que aquilo lhes pertence, e elas precisam ser convencidas do contrário.","Claro, alguém vai ter que ser morto – mas com certeza isso não vai ser um problema, né?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Vamos ao que interessa!","Isso cheira a massacre! E onde eles estão?"),RandPhraseSimple("Gostaria de saber mais detalhes sobre a sua proposta.","O que exatamente você está me oferecendo?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Você está tentando me enganar. Eu não vou participar disso!","Isso parece fácil, mas eu não confio em você! Quer que eu faça o trabalho sujo por você? Pois eu não concordo!"),RandPhraseSimple("Parece interessante, mas vou deixar passar.","Não, eu não roubo, prefiro quando me dão presentes em vez disso."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "E o que tem de tão difícil nisso? Por que você precisaria de mim pra isso, afinal?";
			link.l1 = "Bem, há pessoas que acham que isso lhes pertence, e elas precisam ser convencidas do contrário.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetIslandNameByID(PChar.GenQuest.PGG_Quest.Island);
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) +
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Não enrola, fala logo!","Eu estava certo sobre você, o que mais você sabe?"),RandPhraseSimple("Isso é muito interessante, por favor, continue!","Eu sou "+GetSexPhrase("todos","tudo")+" ouvidos!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Isso parece uma proposta tentadora, mas ainda assim recuso. Não preciso arranjar confusão com "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","Uma caravana? Sem dono?! Deveria ter mil soldados protegendo ela! Não, assim não dá. Estou indo embora."),RandPhraseSimple("Não, eu não estou em guerra com "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", então não estou interessado.","Minha resposta é não! Não vou estragar minha relação com "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "Isso cheira a massacre! E os detalhes?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Só temos "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" para interceptá-los.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" a caravana vai se afastar demais, e não vamos conseguir alcançá-la.","Temos exatamente "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" dias para matar todos eles e pegar o saque!"),RandPhraseSimple("Só temos "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" dias para toda a operação à nossa disposição.","É melhor a gente se apressar, "+PChar.Name+". Só temos "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("Vamos conseguir a tempo! Vamos zarpar hoje.","Então não vamos perder tempo. Dê a ordem para zarpar hoje.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "Isso é muito interessante, por favor, continue.";
			link.l1 = "Só temos "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" para interceptá-los.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Não vamos perder tempo! Vamos nessa!";
		link.l1 = "Lá vamos nós!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"Você me decepcionou, capitão. Achou que eu ia te convidar para "+RandPhraseSimple("Missa de domingo?!!","uma peça infantil!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Isso é problema seu. E cabe a mim decidir.","Eu não vou acabar na forca por uns poucos pesos."),RandPhraseSimple("Minha decisão é final, capitão.","Não temos mais nada para discutir."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("Ah, vamos lá! Vai dar tudo certo, ninguém vai saber de nada. Vamos matar todo mundo."),RandPhraseSimple("Onde você vai, capitão? Vai procurar as autoridades, talvez?","Não é nada sensato entrar na toca de um tigre achando que vai sair dela facilmente."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Vai beijar o diabo do mar! Eu sou o capitão "+GetFullName(PChar)+" e eu não me importo com você! Eu vou embora!","Juro pelo diabo, você está realmente me tirando do sério!"),RandPhraseSimple("Sua proposta não me interessa, e não temos mais nada para discutir. Adeus.","Acho que não há mais nada para discutirmos. Desculpe, estou ocupado e preciso ir."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Tomar "+GetSexPhrase("ele","ela")+"! Empate "+GetSexPhrase("ele","ela")+" ao canhão! Vamos ver que cor "+GetSexPhrase("dele","ela")+" suas tripas são!!!","Ei! Johnny! Henderson! Pega aquilo "+GetSexPhrase("canalha","moça")+"! Não deixe "+GetSexPhrase("ele","ela")+" para chegar ao bote salva-vidas!!!"),RandPhraseSimple("Que pena, capitão! Espero que goste do nosso porão, pelo menos. Depois decidiremos o que fazer com você.","Escravos brancos não costumam viver muito, capitão, então escolha: ou Hends te dá um tiro na cabeça, ou você passa o resto da vida numa pedreira."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Vou fazer você engolir suas tripas imundas, "+GetFullName(NPChar)+"!!!"," Abram caminho! Canalhas! Eu mato vocês onde estiverem! "),RandPhraseSimple("Sua oferta é inaceitável... E muito imprudente!!!","Vejo que você não é muito hospitaleiro... Saia da frente!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "Então, "+GetFullName(PChar)+", vejo que cometi um erro ao me envolver com você. Agora não teremos nenhum saque. Adeus!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Maldição! Chegamos atrasados – e tudo por causa daqueles preguiçosos imbecis! Agora não tem butim pra dividir com você, "+GetFullName(PChar)+". Iça a vela de estai! Vamos sair daqui! ","Então, "+GetFullName(PChar)+", vejo que cometi um erro ao me envolver com você. Agora não teremos nenhum saque. Adeus!"),RandPhraseSimple("Eles desapareceram – e tudo por causa da sua demora! Agora cada um segue seu caminho, "+GetFullName(PChar)+".","Não tem como a gente alcançar a caravana agora. Foi um erro me envolver com você. Adeus!"))link.l1 = PCharRepPhrase(RandPhraseSimple("Que se dane essa caravana! Os mergulhadores de pérolas são ainda melhores, e não tem risco nenhum!","A sorte está do nosso lado e amanhã é um novo dia! Tem muitos mercadores tolos pelos mares só esperando a gente pegar o dinheiro deles!"),RandPhraseSimple("Uma pena, de fato, que uma operação tão brilhante tenha acabado sendo um fracasso total! Adeus!","O homem propõe e Deus dispõe... Adeus!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Ah, por que diabos eu fui me meter com você. Você acabou com tudo. Agora, vai ter que me pagar uma indenização de "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Sanguinário "+GetSexPhrase("canalha","imundície")+"! Tudo foi direto para o diabo do mar!"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos na hora, e suma da minha frente!","Se acha que é o Almirante Nelson? Afundou todo o tesouro, "+GetSexPhrase("idiota","mulher tola")+"Me dá isso agora "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos e suma daqui!"),RandPhraseSimple("Você decidiu começar uma guerra aqui! Isso é totalmente inaceitável! Mas, suponho que podemos esquecer isso se você nos pagar "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos.","Seus métodos são totalmente inaceitáveis! Você arruinou tudo! Pague nossa parte imediatamente, no valor de "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos e vá para onde quiser!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Se não fosse por mim, você já estaria servindo de comida pros caranguejos agora, seu desgraçado ganancioso!","Ah, é mesmo, eu devia ter deixado a nau capitânia deles te abordar – assim você não estaria mais envenenando o ar, balançando no mastro!"),RandPhraseSimple("Suas exigências são descabidas, e suas insinuações são insultuosas!","Não combinamos a penalidade, então não vou te pagar nada!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Eu não posso lutar com você agora, e você sabe disso! Engasgue com seus pesos!"," pesos?!! Bom, a sorte definitivamente não está do meu lado hoje. Concordo."),RandPhraseSimple("Suas exigências são absurdas, mas acho que não tenho escolha.","Seus apetites são exagerados, mas tenho que concordar!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Ah, por que diabos eu fui me meter com você. Você estragou tudo.";
			link.l1 = "Ah, qual é! Você mesmo viu que não tinha outro jeito.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Então, nosso saque soma "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Vamos nos separar.";
			Dialog.Text = PCharRepPhrase("Isso foi um ótimo negócio! Então, nosso saque totaliza "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Excelente trabalho, capitão! Nosso saque compensa "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" Minha parte é "," A minha parte do navio - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" Sua parte é ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Está tudo certo! Os barcos já estão sendo carregados!","Sim, está tudo certo. Um acordo é um acordo."),RandPhraseSimple("Seus cálculos estão corretos. Concordo.","Quando se trata de dividir, você é impecável."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Você ousa exigir a sua parte? Você deveria ser enforcado no mastro agora mesmo!","Sua parte? Aqui, cada um por si. Se não sobrou nada pra você, o problema é seu!"),RandPhraseSimple("Acho que você não pode esperar nenhuma parte.","Minha resposta é não! Não vou dividir nada com canalhas como você!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Tá bom então, não vou discutir! Adeus!","Vamos evitar derramamento de sangue e não piorar as coisas! Da próxima vez, teremos mais sorte!"),RandPhraseSimple("Bem, adeus, capitão, não estou em posição de fazer exigências...","As perdas e os danos ao meu navio não me permitem insistir numa decisão justa. Vou deixar isso à sua consciência, capitão!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ventos favoráveis para você!","Sete pés abaixo da quilha!"),RandPhraseSimple("Até logo! Espero que o ar fresco do mar lhe faça bem!","Espero que nossos infortúnios não te deixem ainda mais insuportável, capitão! Adeus!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Você não entendeu! Você podia ter comprado sua vida! Peguem esse desgraçado!","Ou você acha que estamos brincando com você? Bem, depois que te arrastarmos sob o casco, aposto que vai ficar mais obediente!"),RandPhraseSimple("Então teremos que encurtar sua vida, capitão! Se não vai sair numa boa, logo vai conhecer São Martinho!","Você não me deixa escolha, "+GetFullName(PChar)+"! Eu vou pegar o que é meu, goste você ou não!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Juro pelo diabo, você vai pagar por isso!!!","Então vá e traga pra mim, Capitão "+GetFullName(PChar)+"! "),RandPhraseSimple("O corte vai ser longo e profundo!","Você prefere morrer rápido ou sentir um pouco de sofrimento?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "Não quero mais lidar com você!";
		link.l1 = "Sem problema algum.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Foi um prazer fazer negócios com você. Boa sorte.";
		link.l1 = "E o mesmo pra você.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("Isso sim foi um massacre de verdade! Pena que não tinha nenhuma mulher com eles! Pelo menos o saque compensa  "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Nada mal, capitão! O saque compensa "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" Minha parte é ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" Sua parte é ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Justíssimo, caramba!","Está tudo perfeitamente bem, caramba!"),RandPhraseSimple("Seus cálculos estão corretos. Concordo.","Quando se trata de dividir, você é impecável."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
