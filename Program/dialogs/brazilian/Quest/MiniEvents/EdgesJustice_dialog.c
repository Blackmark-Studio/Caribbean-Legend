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
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "Você é bom"+GetSexPhrase("","ess")+"... muito bom"+GetSexPhrase("","ess")+". Mas antes de você terminar o trabalho, me escute. Tenho certeza de que o que vou dizer vai te interessar.";
			link.l1 = "Acho que você pode dizer suas últimas palavras antes de morrer. Mas não crie esperanças. Você não vai sair desta caverna.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Chefe do porto, hein? Ele te mandou atrás da minha cabeça?";
			link.l1 = "Você continua tão esperto quanto sempre.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Ele te mandou aqui pra me matar, não foi? Não pra me encontrar, nem pra me capturar — pra me matar.";
			link.l1 = "Isso mesmo. E daí?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Ha... você é mesmo um "+GetSexPhrase("cabeça-dura","bobinho")+". Você já parou pra pensar por que era tão importante pra ele que eu morresse em vez de apodrecer numa cela? Não? Você não faz ideia de quem está tentando salvar. Aquele rato do cais teceu uma teia de mentiras por todo esse lugar, e você, "+GetSexPhrase("menino","querida")+", estão atolados até o pescoço nisso.\nAcha mesmo que ele é um oficial honesto? Ha! A única hora em que ele sonha com honestidade é quando está dormindo. Ele vende informações para piratas e holandeses. Trai quem confia nele. Um verme desses merece apodrecer debaixo da terra!";
			link.l1 = "E quem é que não pisa um pouco de terra com as botas. Você também não parece nenhum monge.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Eu não sou nenhum monge, e nem finjo ser. Minha lâmina nunca mente. Basta um olhar, e o homem já sabe que a morte veio buscá-lo. Não sorrio para minha presa, nem aperto sua mão sabendo que já está condenada. Não. Minha intenção é clara. Aquele burocrata?\nEle trai todo mundo que confia nele, fingindo ajudar enquanto isso. Ele é pior do que qualquer canalha que já enterrei.";
			link.l1 = "Supondo que esteja dizendo a verdade. Quem te contratou?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Não vou te dar um nome – nem eu sei qual é. Mas é alguém que foi prejudicado por aquele canalha. Um homem que busca justiça... ou vingança. Chame como quiser. Quinhentos dobrões pela cabeça daquele oficial podre! Me ajude, e a gente divide o dinheiro.";
			link.l1 = "Chega de conversa! Você diria qualquer coisa para salvar sua pele miserável. Eu deixei você falar, agora é hora de morrer.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Bela história. Mas não vou acreditar em você assim tão fácil. Tem algo além da sua palavra? Provas, testemunhas? Ou isso é só mais um truque pra escapar da morte?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Estes pergaminhos foram descobertos nos aposentos de um corsário, um cão-do-mar que meu patrono derrotou em combate. O canalha recebia informações diretamente do próprio Chefe do Porto. Aqui estão registradas, com precisão, as rotas dos navios, seus horários de partida e o tipo de carga que transportavam. Essas mesmas embarcações foram depois saqueadas, suas tripulações massacradas ou desaparecidas no azul sem fim\nPreste atenção – os traços de pena nestas anotações coincidem exatamente com os dos manifestos oficiais. Esta prova irá desmascarar o traidor. Meu patrono deseja que estes documentos sejam encontrados sobre seu cadáver. O banco de um magistrado não seria suficiente\nEsse patife tem influência demais, com inúmeros aliados corruptos em seu bolso. Se fosse levado ao tribunal, escaparia das garras da justiça como uma serpente. Vermes assim não merecem lugar entre as criaturas vivas de Deus. Só a morte e a infâmia eterna fazem jus a tamanha traição.";
			link.l1 = "Cão traiçoeiro! Os homens confiam a ele suas próprias fortunas, enquanto ele vende suas vidas para assassinos e bandidos! Conte comigo como seu aliado nisso. Uma criatura dessas não merece lugar sob o céu de Deus.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Consegui uma chave para a casa dele — através do carpinteiro que consertava os móveis naquela mansão imponente. Tudo correu como planejado até eu descobrir que ele divide os aposentos. Quando entrei para fazer justiça, a esposa dele estava lá\nA presença inesperada dela me fez hesitar. Não havia recompensa pelo sangue dela, e os homens da Coroa caçariam com muito mais empenho quem matasse uma mulher de posição. Então mudei meus planos e fiquei esperando por ele perto da alfândega.";
			link.l1 = "Maldição e desgraça! Agora toda a cidade está em alerta — não podemos atacar abertamente como antes. Que caminho nos resta?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "I've kept watch over the town, biding my time until the commotion subsided. After my attempt, that cowardly rat hurried to hide away his wife. With my own eyes I saw her board a vessel and leave the harbor\nNow he remains alone - the perfect time to finish what we started. Under cover of darkness, you can slip into his lair and end this business. Then leave these damning papers where they cannot be missed, so all may know the foul corruption that festered within his heart\nBut for me, the town gates are barred. You, however... you can succeed where I cannot. No guard searches for your face; you'll pass their watch with ease. His house is near the city prison. Five hundred doubloons! Half this bounty will be yours when the traitor lies dead.";
			link.l1 = "Que assim seja. Com minhas próprias mãos, enviarei esse canalha para prestar contas ao seu criador. Estes documentos ficarão em sua morada — para que todos conheçam a verdade sobre sua traição. Espere pelo meu retorno. Voltarei assim que a justiça for feita.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Por que está parado aí, feito uma estátua, como se seus pés estivessem presos em cal viva?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "Você? Mas que diabos? Como você entrou aqui?";
			link.l1 = "Como cheguei aqui não importa nem um pouco. E acho que, lá no fundo, você entende por que eu vim.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "Não, eu não entendo! Se você veio pela recompensa, então venha à administração amanhã, eu te dou tudo.";
			link.l1 = "Pare de fingir que é inocente! Eu sei de tudo. Você vendeu informações sobre os navios dos seus clientes para piratas. Uma pessoa tão desprezível não merece ocupar esses cargos. Além disso, você não merece viver entre gente honesta. Senhor, o seu lugar é entre os seus iguais – no inferno.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Ah, não-não-não! Não! Você entendeu tudo errado! E-eles me forçaram... Vieram até mim e ameaçaram fazer mal à minha família se eu não ajudasse... você não entende...";
			link.l1 = "Já cansei das suas desculpas patéticas! Tenho suas anotações aqui, onde você exige sua parte das gorjetas! Sua hipocrisia é nojenta, e não pretendo mais tolerar isso. Saque sua arma e se defenda, se tiver coragem!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "E então, quais as novidades? Nosso negócio está encerrado?";
			link.l1 = "Você duvidou de mim? O miserável se esforçou ao máximo para inventar alguma desculpa lamentável, mas foi tudo em vão. Coloquei os documentos incriminadores onde não podem deixar de ser encontrados, exatamente como combinamos.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Tais vermes covardes como ele sempre acham que podem comprar clemência da lâmina da Justiça com mentiras vis e moedas.";
			link.l1 = "Bem, os pensamentos dele já não o atormentam mais. Entregue meu pagamento e eu vou embora.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Aqui estão seus dobrões, bem merecidos. Você fez um bom trabalho, admito isso. Mas preste atenção — se minha mão tivesse empunhado um aço mais firme quando cruzamos espadas pela primeira vez, nossa sorte poderia ter sido bem diferente... para seu eterno pesar. Naqueles aposentos apertados, uma arma de verdade não pode ser usada direito, então fiquei só com esse maldito palito, achando que te derrubaria rapidinho.\nSe eu soubesse como as coisas iam se desenrolar, teria escolhido uma lâmina mais digna de um homem como eu.";
			link.l1 = "Ha! Nosso falecido amigo dizia que você era armado como o próprio Rolando antes do desfiladeiro de Roncesvales! Que paladino você se mostrou ser.";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. O medo lança sombras imensas, não é? Você viu com seus próprios olhos o pobre pedaço de ferro com que quase atravessei seu coração pulsante.";
			link.l1 = "Está sugerindo que, com uma lâmina mais pesada em mãos, talvez tivesse sido um adversário à minha altura?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "Na arte das lâminas de peso médio, ninguém supera minha habilidade — juro isso pela minha própria vida. Duvida? Muito bem. Vou lhe ensinar alguns golpes astutos que já me salvaram de inúmeros perigos. Preste atenção — isso não é conversa fiada, mas sabedoria que um dia pode livrá-lo de uma morte precoce. Conhecimento assim raramente é compartilhado, exceto com os pupilos mais dignos.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("An hour passes...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Vejo que você é realmente um mestre no que faz. Agradeço por ter me ensinado. Mas se nossos assuntos estão encerrados, preciso seguir meu caminho.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Vá com Deus, "+GetSexPhrase("Capitão","bela dama")+". Espero que não precisemos cruzar espadas de novo. Seria uma pena ter que mandar você pro outro mundo. Ha-ha.";
			link.l1 = "Você não teria a menor chance, mesmo se eu estivesse completamente bêbado e equilibrado em uma perna só! Adeus, mercenário.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			AddDialogExitQuestFunction("Naemnik_29");
			
			AddSimpleRumourCity("Word has it the Port Chief was found dead in his own home. Documents were discovered on his body proving his involvement in the disappearance of ships. Just imagine—what a disgrace for our town...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Have you heard the news? Someone snuck into the Port Chief’s house, killed the guards, and took him out. They found notes on the body with routes of missing ships—written in his own hand! A servant of the Crown, yet a traitor in truth! Got what he deserved! And where was the Governor all these years?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("The Port Master is dead! Killed right in his own home! The guards were slaughtered, and among his possessions were notes mapping routes of vanished ships. No doubt about it—he was behind the disappearances! Justice has finally caught up with the scoundrel.", "Beliz", 30, 1, "");
			break;
	}
}