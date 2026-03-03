
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("","Uma mulher... e uma capitã! Agora sim, já vi de tudo. Mademoiselle, você é deslumbrante. É uma pena que sua beleza tenha trazido tanta tristeza à Coroa da França\n")+"É assim que acabam todas as ordens de Poincy. Um vai para a prisão. O outro — ou se junta a ele, ou cai em batalha hoje.";
			link.l1 = "Você claramente não pertence a este lugar. Por que mandar um oficial tão brilhante e um navio tão imponente para fazer o trabalho sujo de um caçador de recompensas?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Ordens não são para serem discutidas, são para serem cumpridas. Se cada capitão escolhesse quais ordens valem a pena—não teríamos uma Marinha.";
			link.l1 = "Diga isso aos seus homens.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Você me encurralou e está tentando quebrar minha lealdade e meu juramento. Isso é um golpe baixo, dadas as circunstâncias. Vamos resolver isso com o choque das lâminas, não com palavras!";
			link.l1 = "(Liderança) Existe uma terceira opção. Pare de fazer o trabalho sujo que não condiz com um oficial. Junte-se a mim—e eu vou te mostrar um outro mundo.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Às armas, então!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
                dialog.text = "Traidores são tratados do mesmo jeito em qualquer lugar. E eu não vou ser um deles. Em guarda!";
                link.l1 = "Você teve sua chance, e desperdiçou. Em guarda!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Skill Check Passed", SKILL_LEADERSHIP);
            dialog.text = "Jurei lealdade à coroa, não a burocratas pomposos e engomados que nos mandam morrer para encobrir suas próprias sujeiras. Mas você—você é inimigo do meu rei, e isso eu não posso ignorar.";
			link.l1 = "Eu poderia me redimir dos meus pecados contra o seu país amanhã—só preciso pagar o intermediário certo. Isso diz mais sobre seus superiores do que sobre mim.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "É verdade. E já estou cansado de aguentar isso. Estou pronto para servir sob seu comando, se você prometer deixar os franceses em paz.";
			link.l1 = "Eu não sei com quem vamos cruzar pelo caminho, e não posso garantir nada. Mas prometo agir com bom senso. Bem-vindo à tripulação, Oficial "+NPChar.name+"!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "Então é assim que se parece um inimigo público. Espero que se orgulhe desse título, pirata. Deve ter se esforçado bastante para conquistá-lo\nDe acordo com a Casa de Contratação, você já derrubou "+(Statistic_AddValue(PChar,"spa_AbordShip",0)+Statistic_AddValue(PChar,"spa_KillShip",0))+" navios que ostentam a bandeira da Coroa Espanhola. E hoje, meu belo navio vai se juntar a essa lista"+GetSexPhrase(".","\nAi da frota espanhola! Sofremos com doenças, favoritismo, traição... Mas ser derrotados por uma mulher?");
			link.l1 = " Você é o último de pé, sua tripulação está morta. E você também, só ainda não percebeu.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
            dialog.text = "É uma pena que o de Alba não tenha pegado essa tarefa. Ele teria feito melhor. Mas vou tentar terminar o trabalho mesmo assim.";
            link.l1 = "Você é um verdadeiro filho da sua terra. Prepare-se para encontrar seus heróis, señor.";
            link.l1.go = "Alonso_2";
            link.l2 = "O caçador virou caça. Todos os seus discursos não serviram pra nada—isso é tão antigo quanto o mundo.";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
            dialog.text = "Obrigado pela pausa, mas agora é minha espada que vai falar.";
            link.l1 = "Às armas!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
            dialog.text = "Obrigado pela pausa, mas agora é minha espada que vai falar.";
            link.l1 = "Prepare-se para morrer!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            MakeUnpushable(NPChar, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name+"! Seu nome aparece nos relatórios com tanta frequência que sinto como se já nos conhecêssemos há anos","Senhorita McArthur! Será que o seu protetor sabe o que você anda aprontando? Ah, deixa pra lá. Aposto que ele vai ser meu próximo serviço mesmo.")+"\nVocê tem sorte: meus chefes adoram mandar ordens urgentes que contradizem as anteriores. Se eu não estivesse ocupado me livrando da antiga tripulação de Antígua... Bem, deixa pra lá. Chega. Você está me distraindo do trabalho de verdade.";
			link.l1 = "Você também está me distraindo.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "Quase tomei um tiro de corrente na popa, nem vi chegando! Se esses meus ossos velhos fossem um pouco mais rápidos, eu mesmo teria mandado aquele desgraçado pro fundo do mar. Obrigado, capitão. E o meu antigo patrão também agradece!";
			link.l1 = "Quem é você? Um prisioneiro? Minha tripulação te libertou?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel em pessoa. O melhor artilheiro da Marinha Inglesa!";
			link.l1 = "O Courtney disse que levou muito tempo para te encontrar. Qual é a história?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Por muitos anos servi a um bravo capitão inglês chamado Richard Fleetwood. Lutamos juntos em muitas batalhas, dedicados à nossa verdadeira paixão — a Marinha Inglesa. Mas um dia, tudo mudou.\nOs figurões de Londres nos usaram como peões. Atacamos os nossos próprios. Sujamos nossos uniformes limpando a sujeira dos outros. E agora chegou a nossa vez...";
			link.l1 = "Sem julgamentos aqui. A vida é complicada, ainda mais quando você não é dono do próprio destino.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Então, diria que as sombras dos velhos pecados finalmente te alcançaram?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Não me arrependo de servir ao meu país. É só que... dói, Capitão. Principalmente por causa do meu patrão e da pobre esposa dele.";
			link.l1 = "E agora?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Não precisa das provocações... Já pagamos caro demais pelos nossos pecados!";
			link.l1 = "E agora?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Agora sou um homem sem nome e sem pátria. Eu poderia ir para qualquer lugar, mas por enquanto, não há para onde ir. E ninguém para ir junto. Artilheiros são necessários em todo lugar, mas nem todo navio tem canhões.";
			link.l1 = "Junte-se a mim. Não posso dizer que tive o melhor relacionamento com a frota inglesa, mas respeito os melhores dela.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Eu tenho canhões. Se você for realmente tão bom assim, sempre tem lugar para um verdadeiro profissional na minha tripulação.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "Tem uma forca me esperando em casa, o mesmo vale pros espanhóis e holandeses, e não faço questão dos franceses. Mas você, pelo visto, precisa de um bom artilheiro. Tô dentro, Capitão. Vou pra cabine assim que der. Apareça qualquer hora, a gente conversa tomando um rum.";
			link.l1 = "Bem-vindo a bordo.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "De jeito nenhum. Prefiro tomar um barco e sumir no buraco mais fundo do arquipélago. Obrigado por me salvar, Capitão, e adeus.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            NPChar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "Você não era quem deveria ter chegado tão longe. Meifeng é a garra da Companhia. Meu esquadrão é a lâmina vingadora. Você destruiu os dois. Isso... não acontece.";
			link.l1 = "Mandaram você atrás de mim como se eu fosse uma fera. E eu lutei—feito um animal encurralado. Quando é lutar ou morrer, a mente fica limpa. No fim, só resta uma pergunta: Será que vou chegar à cabine do lendário xebec—ou não.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("","É estranho ver uma mulher no comando. Isso não acontece com frequência. ")+"Você estava me esperando?";
			link.l1 = "Sim. O Meifeng é um navio com história. Quando enfrentei os holandeses, sabia que mais cedo ou mais tarde eles mandariam você atrás de mim. Teria sido um fim honrado... mas veja só como as coisas acabaram.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Conhecer o inimigo e a si mesmo é a chave para a vitória. Então, você fez sua escolha. Enfrentar meu esquadrão do seu jeito. Você estava pronto para morrer. Mas venceu. Agora minha vida está em suas mãos. Por que não me acaba de vez?";
			link.l1 = "(Liderança) Porque não vejo sentido em afundar um capitão lendário só para satisfazer as ambições da Companhia. Já estive no seu lugar—um peão. Servindo aos interesses dos outros, obedecendo ordens alheias. Estou te oferecendo o que um dia escolhi para mim: liberdade.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Porque todo capitão merece a última palavra. Em guarda!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			dialog.text = "A liberdade não é algo que se recebe. É algo que se conquista. E nem todo mundo que fala sobre escolha pode realmente oferecê-la. Existem caminhos dos quais não dá pra fugir. Existem ordens que não podem ficar inacabadas. Meu caminho é aqui. Minha ordem é resistir até o fim.";
			link.l1 = "Então você escolhe a morte?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Não. Eu escolho continuar sendo eu mesmo.";
			link.l1 = "Então vamos lutar!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Skill Check Passed", SKILL_LEADERSHIP);
			dialog.text = "Você não é como o Rodenburg. Ele me via como uma ferramenta. Você—como um igual. Sacrificar-se não é uma virtude. Estou pronto para ouvir suas condições.";
			link.l1 = "É simples. Seja meu navegador na minha nau capitânia. Ou, se preferir, pode ter seu próprio navio e navegar sob minha bandeira. Você não vai mais precisar limpar a sujeira da Companhia ou esconder os esqueletos deles no armário. Eu sou livre—e te ofereço essa liberdade ao meu lado.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Já vi de tudo: sangue, ouro, traição. A Companhia paga—mas não respeita. Dá um navio—mas te mantém acorrentado. Você... oferece uma escolha. Se cumprir sua palavra—Longway não será mais um caçador a serviço dos outros. Vai ser um homem. Um capitão. Ou—ficar ao lado de um capitão que sabe para onde navegar.";
			link.l1 = "Bem-vindo à tripulação, Navegador Longway.";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
			sld = InitLongwayFP("Longway_FP", NPChar);
			NPChar.lifeday = 0;
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

			AddDialogExitQuest("pchar_back_to_player");
			PostEvent("LAi_event_boarding_EnableReload", 5000);
			DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
