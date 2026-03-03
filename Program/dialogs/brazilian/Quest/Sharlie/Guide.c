// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "É um prazer recebê-lo nas colônias, senhor! Permita-me apresentar-me: "+GetFullName(npchar)+". Você está vindo da boa e velha casa?";
			link.l1 = "Bom dia, monsieur. Meu nome é "+GetFullName(pchar)+". Sim, acabei de desembarcar do navio.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Quando vi um cavalheiro, achei que devia ajudar. O Novo Mundo tem suas próprias regras, e desconhecê-las pode sair caro. Pessoas de posição devem se apoiar. Tem muito canalha por aqui que te venderia por umas poucas moedas\n"+"Posso te mostrar o lugar e te explicar o básico?";
			link.l1 = "Muito gentil da sua parte, monsieur! Ficarei feliz em ajudar.";
			link.l1.go = "guide_2";
			link.l2 = "Obrigado, monsieur, mas eu vou encontrar meu próprio caminho.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Como desejar, Monsieur. De qualquer forma, foi um prazer conhecê-lo. Cavalheiros honrados são raros por aqui. Desejo-lhe muita sorte!";
			link.l1 = "E para você também, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Excelente! As cidades do Caribe têm a mesma estrutura. Aprenda Saint-Pierre e todos os outros portos vão fazer sentido.";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "Taverna — o centro do porto. Aqui você encontra cama, rum, fofoca, e pode contratar marinheiros ou oficiais. Jogue cartas, arrume trabalho ou negocie com contrabandistas e vendedores de mapas do tesouro.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Market. Need supplies? The smith has blades, armor, and shot; the herb-woman sells tonics. Gypsies and monks trade charms, and the junk-dealer offers odds and ends for those who can craft.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Prostíbulo. Nada levanta o ânimo como passar um tempo com uma dama habilidosa. Se estiver se sentindo esgotado, passe por aqui e saia renovado.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Banco. Pegue empréstimos ou invista dinheiro, troque pesos por dobrões, e é o melhor lugar para vender joias.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Prison. Few real villains inside—mostly drifters. Want a job from them? Talk to the commandant; a small bribe opens the cells.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Palácio do Governador. Comerciantes e capitães vêm aqui para tratar de negócios importantes. Mantenha-se em bons termos com o Governador—sua palavra define como a nação dele vai te tratar.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Estou te segurando, meu amigo?";
			link.l1 = "Monsieur, estou aqui para encontrar meu irmão. Dizem que ele está em Saint-Pierre. Um homem de certa importância—com certeza o Governador deve conhecê-lo...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, entendi. Nosso governador é Jacques Dyel du Parquet. Tenho certeza de que ele vai recebê-lo em breve.";
			link.l1 = "Quem mais eu poderia perguntar? Prefiro não incomodar Sua Excelência logo de cara.";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Se seu irmão é conhecido na Martinica, pergunte ao pessoal da cidade—alguém vai saber. E o nome dele?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Já ouvi esse nome, embora nunca tenhamos nos encontrado. Pergunte por aí — ou vá direto ao Governador. Boa sorte, monsieur. Nos falamos de novo!";
			link.l1 = "Obrigado, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Ah, é você de novo! Ouvi dizer que você esteve na fortaleza dos Cavaleiros. Pelo visto, anda em círculos importantes. Conseguiu encontrar seu irmão?";
			link.l1 = "Encontrei ele... de certa forma.";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Me perdoe, mas não ouço muita alegria nessa resposta...";
			link.l1 = "É verdade. Eu esperava voltar pra casa no próximo navio, mas o destino ri de mim. Estou preso aqui—quem sabe até quando—e, pra piorar, ainda tenho que aprender a ser marinheiro.";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Não me surpreende. A notícia da sua viagem no Ulysses já se espalhou. Não desanime—ter um navio e o título de capitão não é pouca coisa. Você pretende comprar uma embarcação, não é?";
			link.l1 = "Sim — droga — eu preciso. Mas não sei onde fica o estaleiro, não sei navegar, nem como conseguir dinheiro. Nada!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Dinheiro me falta, mas no resto estou à sua disposição. Vamos continuar o passeio?";
			link.l1 = "Você tem razão—conhecimento é poder.";
			link.l1.go = "guide_25";
			link.l2 = "Obrigado, monsieur, mas daqui em diante eu me viro.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Um prazer. Para conseguir dinheiro, fale com quem movimenta a cidade—talvez o comerciante da loja\n"+"Boa sorte, "+pchar.name+"—seja ousado e você vai conseguir.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Então venha comigo! Primeiro de tudo—navios.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Estaleiro. Compre ou conserte navios aqui. Na maioria, cascos pequenos, mas de vez em quando aparece um bom. Também temos canhões e velas elegantes.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Píer—sua porta de entrada para o mar. Assim que você tiver um navio, sua embarcação ficará aqui. Por enquanto, contrate um navegador, um intendente e um artilheiro—eles vão facilitar sua vida no mar.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Capitania do Porto. Atracar seu navio aqui ou pegar trabalho honesto—frete, escolta, entregas de correspondência. Quanto mais serviços você faz, melhor é o pagamento.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Armazém. Os capitães vêm aqui buscar comida, rum, remédios, pólvora e balas. Se faltar alguma coisa, procure os contrabandistas na taverna. Sem um bom intendente, negociar é pura perda de tempo e dinheiro.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Portões para as terras selvagens. Perigosos, mas úteis para chegar a fortes, caçar tesouros ou atravessar até outro povoado.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Nem toda colônia recebe forasteiros de braços abertos. Se não quiser esperar pela noite, hasteie outra bandeira no mar e confie na discrição — ou compre uma licença de comércio.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Preste atenção, meu amigo. Que tal um pouco de diversão? Um duelo de treino além dos portões.";
			link.l1 = "Com certeza! Parece perfeito.";
			link.l1.go = "guide_47";
			link.l2 = "Obrigado, monsieur, mas daqui eu cuido.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Meu amigo, imagino que você não seja estranho à esgrima?";
			link.l1 = "Ha!   Já sobrevivi a um ataque de abordagem e até—";
			link.l1.go = "guide_50";
			if (GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "unarmed")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Excelente. Vamos?";
			link.l1 = "Vamos dançar!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Você... você é um homem que sabe manejar sua espada. Muito bem, Monsieur. Você ainda precisa de prática, mas tem potencial para se tornar um verdadeiro mestre da espada.";
			link.l1 = "Muito obrigado. E agora?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Mais prática, você diz? Está falando sério? Estou cansado desse tom condescendente desde que pus os pés nesse lugar miserável!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Much better! See, all you need is to concentrate. You need more practice; one day you will become a decent fencer.";
			link.l1 = "Muito obrigado. E agora?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "Eu venci, Monsieur. Mova-se mais rápido, aparre meus golpes, recue. Uma revanche?";
			link.l1 = "Oui! Sem piedade, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "Não, já chega. Vamos terminar a lição. E agora?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "Ganhei de novo, "+pchar.name+"! Não perca a iniciativa. Intercepte meus golpes, finja que vai bloquear. Se perceber que vou atacar com força – desvie ou aparre, não só defenda. De novo!";
			link.l1 = "Venha, Monsieur, desta vez eu vou te dar uma surra!";
			link.l1.go = "guide_56";
			link.l2 = "Não, já chega. Vamos terminar a lição. E agora?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Você ainda tem muito o que aprender, "+pchar.name+". Não se preocupe, você ainda tem bastante tempo para dominar a esgrima. Mas tome cuidado, não se arrisque antes de saber segurar uma arma.";
			link.l1 = "Vou considerar, Monsieur, mas preciso dizer que você teve muita sorte! Esse calor infernal... é a única razão de eu não ter acabado com você. Merde, vamos encerrar nossa aula de esgrima. E agora?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Agora é hora de me despedir, Monsieur. Foi um prazer. Espero que minha apresentação e treinamento tenham lhe sido úteis e que sirvam para algo no futuro. Quem sabe um dia nos encontremos de novo.\nE sobre o dinheiro que você precisa – converse com as pessoas importantes da nossa cidade. Visite todos os lugares que lhe mostrei hoje e fale com os donos. Pergunte por aí. Dê uma volta pela selva e pelo forte. Arrume um trabalho ou... bem, não sou padre nem juiz, dê uma olhada nas casas das pessoas e veja que bugigangas encontra nos baús destrancados. Só faça isso quando ninguém estiver olhando, ou os guardas vão te pegar.\nBoa sorte, "+pchar.name+", tenho uma forte sensação de que você carrega a centelha da verdadeira grandeza dentro de si. Faça o possível para transformá-la em uma chama ardente!";
			link.l1 = "Merci, Monsieur. O prazer foi meu. Boa viagem!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Controle sua língua, Monsieur! Não vou tolerar mais essa insolência. No entanto, entendo sua reação a um ambiente novo, por isso vou relevar seu descontrole desta vez. Mas preste atenção às suas palavras daqui em diante. Adeus, Monsieur de Maure.";
			link.l1 = "Sem ofensa, Monsieur Valinnie. Se estivéssemos no Louvre agora, você tomaria mais cuidado com suas palavras! Está na hora de ensinar uma última lição a um provinciano. Defenda-se!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Guide_DlgExit_64");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
