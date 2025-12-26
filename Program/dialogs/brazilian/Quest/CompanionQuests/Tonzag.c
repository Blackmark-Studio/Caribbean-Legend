void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
		
		case "startoff":
			dialog.text = "Capitão de Mor! Bem-vindo a Tortuga!";
			link.l1 = "Bom dia, Tenente. Aproveitando a vista do mar com seus amigos?";
			link.l1.go = "startoff_joke";
			link.l2 = "Afaste-se, Tenente.";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "Capitão, sua fama te precede, e os figurões decidiram organizar um pequeno passeio pelas belezas da nossa adorável Ilha de Tortuga. Vamos começar agora mesmo—pelas celas da prisão da cidade. Seus oficiais também estão convidados.";
			link.l1 = "Tenente, eu não sou algum contrabandista de quinta que você pegou na praia. Sem piadinhas, por favor. Explique direito o que está acontecendo.";
			link.l1.go = "startoff_joke_1";
			link.l2 = "Então não vamos perder tempo! Mostre o caminho, Tenente!";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "Vejo que lidar com vocês, marinheiros, exige uma abordagem diferente. Soldados, preparem-se para a batalha! Capitão de Maure, você e seus oficiais estão presos. Entreguem suas armas!";
			link.l1 = "Posso te dar uma bala—onde você quer, tenente? Com vocês, ratos de terra, não tem outro jeito.";
			link.l1.go = "startoff_silence_1";
			link.l2 = "Por qual lei? Se quiser prender um grupo armado sem derramamento de sangue, tenente, vai ter que se esforçar mais.";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "Pra mim, vocês são todos iguais... Desculpe, mas não vai ter explicação, Capitão. Ordens de cima. Entregue suas armas, se não se importar.";
			link.l1 = "Eu não preciso de problemas... não agora. Faça o que eles mandam.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "Ah... Acho que você não entendeu direito. Capitão, você e seus oficiais estão presos! Entreguem suas armas e venham conosco!";
			link.l1 = "Não preciso de problemas... não agora. Faça o que eles mandam.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "Mais uma palavra, Capitão, e vamos te enterrar bem aqui. Armas no chão, agora mesmo!";
			link.l1 = "Não quero confusão... não agora. Faça o que eles mandam.";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "Não tenho medo de sangue, Capitão. Mesmo que você sobreviva por milagre, nunca mais vai pôr os pés em Tortuga. E nossa inteligência militar acredita que você valoriza muito o seu acesso a esta ilha.";
			link.l1 = "Não preciso de problemas... não agora. Faça o que eles mandam.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Capitão, a situação tá uma merda! O inimigo tá nos apertando forte, e acho que não vão largar até a gente morrer! Nossa gente tá em apuros de verdade agora, e a maioria das equipes dos canhões já foi derrubada!";
			link.l1 = "Eu vou ajudá-los. Assuma o comando e tire a gente daqui!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Sim, senhor!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vitória, Capitão! O grupo de desembarque foi destruído, o inimigo decidiu recuar e seguiu para o sul. O estado do navio é aceitável. Tripulação viva: "+GetCrewQuantity(pchar)+" pessoas. Relatório concluído!";
			link.l1 = "Obrigado! Rum para todos e reforcem a vigilância até chegarmos ao porto!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Viva! Sim senhor!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "E aí está o próprio! Viu a carnificina lá fora? Isso tudo é culpa sua, traidor! Mas você vai pagar por tudo: por Porto Bello, por Gruoh e por esta mina!";
			link.l1 = "Espera, o que isso quer dizer...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "Agh! Isso não é um bom sinal...";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "São Santiago, proteja-me! Que vilania! Que monstro poderia cometer um ato desses? Responda, senhor!";
			link.l1 = "Calma, señor! Primeiro, diga quem é você! Sim, aconteceu uma carnificina monstruosa aqui, mas quem fez isso já está morto. Eu mesmo 'decorei' as minas com os restos deles...";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "Eu sou "+GetFullName(npchar)+", engenheiro-chefe da mina real de Los Teques. Acabo de voltar de uma missão que durou meses e... o que vejo! O que aconteceu aqui é um crime contra Deus e a humanidade, por isso exijo que entreguem suas armas imediatamente. As autoridades de Caracas vão investigar essa vileza!";
			link.l1 = " Não posso obedecer, senhor, e juro que não tive nada a ver com esse massacre! Mas se insistir, seu corpo também vai parar nessa pilha.";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "Não temo a morte, mas sempre sei quando é hora de recuar. Vá, mas lembre-se: vou relatar tudo o que aconteceu aqui, e não vou deixar passar nenhum detalhe!";
			link.l1 = "Não posso concordar com isso, señor. Sinto muito que tenha chegado a esse ponto. À luta!";
			link.l1.go = "mine_head_fight";
			link.l2 = "Parece que você está procurando a morte, señor. Mas hoje, ninguém mais vai morrer. Nós vamos embora, e espero que esse detalhe também apareça no seu relatório!";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "O que devemos fazer com o prisioneiro, Capitão?";
			link.l1 = "Nada de especial, só não deixe ele morrer ou escapar.";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "Entendido! Imagino que hoje não vou precisar participar do interrogatório, Capitão?";
			link.l1 = "Por que não? Resolveu mudar de profissão, Alonso?";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "Ha-ha, não, Capitão. Eu adoro esse trabalho, mas parece que agora você tem um novo mestre a bordo!";
			link.l1 = "Hercule? De onde você tirou essa ideia?";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "Bem, Capitão, o velho trouxe as ferramentas dele só pra essa ocasião e já botou pra funcionar. Nem vou precisar pegar as minhas. Ha!";
			link.l1 = "Entendi... Continue!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "Ah... Charles de Maure. Permita-me pedir desculpas em nome de toda a Liga. A ordem para deixá-lo em paz chegou tarde demais. Nossa organização não tem nada contra você, Capitão. Quanto a esse animal careca... Ugh! Enquanto ele estiver sob seu comando, está seguro, mas meu conselho é que não o mantenha por perto e o deixe apodrecer na sarjeta, onde é o lugar dele!";
			link.l1 = "Obrigado pela recomendação, mas estou mais interessado em saber por que alguém está me protegendo dos seus mercenários.";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "Não posso saber, Capitão. Imagino que as ordens vieram do nosso novo patrão. Já ouviu falar dele, traidor? A Liga voltou ao topo agora!";
			link.l1 = "E quem é ele?";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "Não posso saber, Capitão, e mesmo que soubesse, esse tipo de coisa a gente não revela.";
			link.l1 = "Nesse caso, me diga outra coisa, e você pode ir para onde quiser. Dou minha palavra.";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "Assim mesmo? Tudo bem, Capitão, faça suas perguntas e me deixe ir. Prometo que não vou voltar para a Liga, mesmo que pudesse.";
			link.l1 = "Por que essa obsessão com o Hercule? Muita confusão por causa de um único desertor.";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "O que você contou pra ele, seu cachorro? Nem tudo é o que parece, Capitão! A Liga está sempre mudando, os códigos trocam, os patrões variam. Quer sair? Sem problema! A saída só é fechada pros oficiais de alto escalão, e esse verme nunca foi um deles. A esposa dele, tudo bem, mas a gente respeitava demais a Madame Tonzag pra não abrir uma exceção pra ela.";
			link.l1 = "Então por quê?";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "Aconteceu algo em Porto Bello... Foi grande. Veja, seu amigo não só foi embora, não só quebrou o contrato, não só matou o grupo que veio terminar o trabalho dele. Ele causou um verdadeiro massacre nas ruas, complicando bastante nossa relação com os castelhanos. Raramente um ataque pirata espalha tanto terror quanto o que os bons católicos sentiram naquele dia. Olha, talvez eu até tivesse ficado impressionado se tivesse sido outra pessoa.";
			link.l1 = "Outro massacre? Que interessante. Continue.";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "O então Vice-Diretor da Companhia, Rodenburg, interveio. De algum jeito, ele conseguiu abafar toda a história, mas não antes de perdermos muitos dos nossos melhores homens nas operações punitivas dos espanhóis. Depois de um tempo, porém, voltamos a fazer negócios com eles... Ah! Mas não esquecemos de nada, e assim que surgiu a chance, tentamos acertar as contas. O responsável por tudo, Tonzag, tinha que ser morto.";
			link.l1 = "Você não conseguiu nisso. E a mina?";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "We were forced to do it. Getting rid of that scum required too much expense; we needed gold. All because of him... But the attempted assassination failed, and I returned to Los Teques to tidy up a bit... How did you figure out where to look?";
			link.l1 = "Não importa. Preciso me encontrar com seu líder. Quero resolver esse mal-entendido pessoalmente, já que as garantias do seu patrono misterioso podem expirar a qualquer momento.";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "Tenho certeza de que já estão te esperando em Caracas, Capitão. Vê? Não estou escondendo nada de você.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "O comandante Arno morreu, agora quem manda é o Austin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "Respondi todas as suas perguntas, Capitão. Cumpra sua palavra.";
			link.l1 = "Estou te deixando ir. Saia do meu navio e reze para que não tenha uma emboscada me esperando em Caracas.";
			link.l1.go = "captive_spare";
			link.l2 = "Obrigado pela conversa interessante. Acusar o Hercule de ter causado um massacre depois do que vi na mina já é demais. Vai pro inferno, que é onde você merece estar.";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "Senhores, vocês estão convidados para uma reunião. Estão esperando por vocês na igreja, então a segurança está garantida.";
			link.l1 = "Isso foi rápido...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "Charles de Maure. Hercule. Você não vai sair vivo daqui.";
			link.l1 = "Sempre um jeito agradável de começar uma conversa. Você realmente precisa de tudo isso?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "Com você, Capitão, as coisas não são tão simples assim. Veja, nosso novo patrão fez questão de que deixássemos você em paz... mas ele pode enfiar esse pedido no rabo! Eu detesto gente como você, de verdade! Vocês navegam com essas velas branquinhas, achando que são santos. Mas quando o aço da minha lâmina entra em vocês, todos gritam feito mocinha. Isso é bom demais, Charles, pode acreditar! Faz tempo que não faço isso... e agora tenho você bem na minha frente, bonitão.";
			link.l1 = "Você está doente, camarada.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "Não, eu não posso deixar você ir. Já com seu amigo, é ainda mais simples – meus rapazes não têm utilidade pra ele, mas ainda restam alguns daqueles velhos camaradas da Liga que não estão totalmente convencidos da eficácia dos meus métodos... Estão acostumados demais a trabalhar limpo, por moedas limpas, pra Companhia limpa. Mas eu sei exatamente o que vai fazê-los mudar de ideia – a cabeça de um pecador ousado numa bandeja, ha-ha!";
			link.l1 = "Você escolheu o lugar errado pra isso, seu maluco. Vai mesmo começar uma briga dentro de uma igreja?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "Claro, por que não? Está com pena do pessoal? Talvez não seja tão lucrativo quanto em Los Teques, mas ainda vamos nos divertir. Vamos pintar as paredes da casa de Deus, ah-ha! Capitão, você vai providenciar muita tinta.";
			link.l1 = "Entendi. Você tem inveja da gente, não tem, seu rato louco? Inveja da nossa liberdade? Que as moças ficam felizes em nos ver e que as moedas tilintam nos nossos bolsos? Olhe pra você: de onde seus patrões te desenterraram, porco? Quem te deixou entrar na igreja?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "Come terra, seu merdinha!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 
