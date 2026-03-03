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
			dialog.text = "O que você quer?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...e do Espírito Santo. Amém.";
			link.l1 = "Raramente vejo militares em igrejas.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Muitos acreditam que fé e espada não combinam. Mas um cirurgião não corta para curar? Um pai não pune para proteger?";
			link.l1 = "Parece uma desculpa.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Há sabedoria nisso. Às vezes, a crueldade é necessária.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Você está enganado. Isso não é uma justificativa – é compreensão. Quando comecei meu serviço, cada morte era... difícil. Mas então... meus olhos se abriram. 'A crueldade é a manifestação do amor supremo.'";
			link.l1 = "Vou deixar você com suas orações.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Sim... sim! Foi exatamente isso que ele disse, aquele que me guiou por este caminho. 'Misericórdia sem força é inútil, como uma espada sem mão.'";
			link.l1 = "Vou deixar você com suas orações.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Reze por todos nós. Pelo que fizemos... e pelo que ainda teremos que fazer.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Déficit de sete por cento. Da última vez, era cinco. Crescendo como ervas daninhas em um jardim abandonado...";
			link.l1 = "Tem um novo governador na cidade?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "O quê? Ah, não. Sua Excelência está ali, no canto. Eu sou dom Fernando de Alamida, inspetor real.";
			link.l1 = "Deve ser um trabalho difícil.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Sabe qual é a parte mais difícil de combater a corrupção? Os culpados nem sempre são pessoas más. Eles têm filhos, famílias. E toda vez você precisa se lembrar: veneno continua sendo veneno, mesmo servido numa taça de ouro.";
			link.l1 = "Mas será que podemos julgar tão severamente? Todos nós somos humanos...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Você é mole demais. Só a prisão vai mudar eles.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "Ter misericórdia do lobo é ser cruel com as ovelhas. Foi o que disse... um homem sábio. E a cada dia que passa, entendo cada vez mais a razão dele.";
			link.l1 = "Não vou mais te atrapalhar no seu trabalho.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hum. Sabe, eu costumava pensar do mesmo jeito. Mas a prisão é simples demais. É preciso algo mais... Purificação.";
			link.l1 = "Não vou mais te atrapalhar no seu trabalho.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Sim. Os papéis não vão esperar. Às vezes, porém, me parece que atrás de cada número aqui se esconde o destino de alguém.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Estou ouvindo com atenção, "+GetAddress_Form(NPChar)+"? O que te fez vir falar comigo assim, na rua?";
			link.l1 = "Você se destaca dos demais.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, inspetor real. Você é o primeiro curioso a aparecer hoje. Todos se escondem, todos me temem. Mas quem é honesto não tem nada a temer. O que isso nos diz?";
			link.l1 = "Que a sua reputação os assusta?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Que pessoas honestas são poucas?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Engraçado. Eu também pensava assim. Até entender que o medo purifica. Quando alguém sente medo, se torna mais honesto. Mais próximo da sua verdadeira natureza. De Deus.";
			link.l1 = "Pensamento interessante. Preciso ir. Tenha um bom dia, dom Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Interessante... Você pensa exatamente como alguém que eu conheci. Pena que nem todos conseguem aceitar essa verdade.";
			link.l1 = "Pensamento interessante. Preciso ir. Tenha um bom dia, dom Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Bom? Sim, talvez. Desde que seja justo.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_DlgExit");
		break;
		
		case "Alamida_repeat":
			dialog.text = "Mais alguma coisa, Capitão?";
			link.l1 = "Não, dom Fernando, só estou cumprimentando, nada mais.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Uma donzela com uma espada? Ora, nunca pensei que viveria para ver algo assim. E quem é você, señorita, para ousar atacar a 'Santa Misericórdia'?";
				link.l1 = "Capitã Hellen McArthur. E essa expressão de surpresa no seu rosto, eu conheço muito bem.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Como ousa?! Atacar a 'Santa Misericórdia'?! Um navio que carrega a vontade do rei e... Bem. Já que está aqui, me diga – por quê? Por que escolheu essa loucura?";
				link.l1 = "Sou um pirata. E seu galeão certamente está cheio de tesouros.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Que navio lindo... Eu preciso tê-lo.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Sou inimigo do seu país, dom Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Porque sim. Por que não?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Como você se parece com a Virgem Maria, protetora do nosso navio... Tão bela quanto. Mas Ela protege os justos, enquanto você...";
			link.l1 = "Vim pelo seu navio. E elogios não vão te ajudar aqui, dom Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Que pena. Então vou ter que te ensinar humildade. À força, já que não tem outro jeito.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ah, sim. Claro. Ouro. Sempre ouro. O veneno que corrói as almas. Por ele você vai morrer.";
			link.l1 = "Não seja tão dramático. Isso é só negócio.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Cada moeda no porão é o pagamento dos pecadores pela purificação. Quer ela? Então compartilhe o destino deles.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Muitos cobiçaram a 'Santa Misericórdia'. Sua beleza foi a perdição de muitos capitães.";
			link.l1 = "Então serei o primeiro a reivindicá-lo.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "Misericórdia sem força é inútil, como uma espada sem mão. Essa lição você vai aprender hoje.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Então é isso. Mais um invejoso da grandeza do Império.";
			link.l1 = "Que grandeza? Seu jeito rígido está atrasando este mundo.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Não se engane. O medo da Espanha te deixa mais sincero. Mais próximo do que você realmente é. Agora vai perceber isso por si mesmo.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Louco. Ou talvez você tenha sido enviado até mim como uma provação?";
			link.l1 = "Nem tudo precisa de um motivo, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Ele disse que pessoas como você são as mais perigosas. Mas isso só vai fortalecer minha determinação na batalha.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_1");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Tanta força de espírito... Tanta vontade...";
				link.l1 = "Surpreso?";
			}
			else
			{
				dialog.text = "Nada mal. Faz tempo que não encontro um oponente à altura.";
				link.l1 = "Não vou te dar tempo para descansar.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Me avisaram... sobre uma provação assim. Sobre uma beleza capaz de abalar a fé de um guerreiro.";
				link.l1 = "Você sempre complica tanto as coisas simples assim, dom Fernando?";
			}
			else
			{
				dialog.text = "O Senhor dá força àqueles que servem uma causa justa. Mas... às vezes já não sei mais o que estou servindo.";
				link.l1 = "Está com dúvidas?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Simples? Não... Deve haver um significado maior. Isso é um teste. Eu não posso estar errado.";
			}
			else
			{
				dialog.text = "Não. Ele me ensinou a nunca duvidar. Jamais.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_2");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Espere... Espere. Você venceu. Estou ferido, sangrando até a morte. Permita-me rezar antes de partir.";
			link.l1 = "Muito bem.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Senhor... perdoa meus pecados e me dá força nesta hora de provação. Abençoa as almas dos meus camaradas caídos. Marujos fiéis, morreram acreditando que carregavam a justiça\nPai, tentei viver segundo teus ensinamentos, lutar contra a injustiça. Mas teu filho manchou a honra da família Alamida. Perdoa-me\nPátria... jurei te servir com lealdade e verdade. Mas meu fervor, minha raiva... tornei-me aquilo que tentei combater\nDiego... Será que ele mentiu? Todo esse tempo... Ai de mim, se for verdade\nE abençoa esta mulher, Senhor. Talvez, em tua última misericórdia, tu a tenhas enviado a mim... para que eu visse o quanto me desviei. Amém.";
			}
			else
			{
				dialog.text = "Senhor... perdoa meus pecados e me dá força nesta hora de provação. Abençoa as almas dos meus companheiros caídos. Marinheiros leais, morreram acreditando que levavam justiça\nPai, tentei viver segundo teus ensinamentos, lutar contra a injustiça. Mas teu filho manchou a honra da família Alamida. Perdoa-me\nPátria... jurei te servir com lealdade e verdade. Mas meu fervor, minha raiva... tornei-me aquilo que lutei para destruir\nDiego... Será que ele mentiu? Todo esse tempo... Ai de mim, se for assim\nSanta Virgem Maria, roga a Deus por nós e concede-nos tua misericórdia. Amém.";
			}
			link.l1 = "Eu não reconheço você, dom Fernando. Você parece outra pessoa agora. E de quem você estava falando?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_3");
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Meu capitão, parabéns! Que batalha feroz. Aquele capitão era habilidoso, muito habilidoso. Mas você... você mostrou ser ainda melhor. Que orgulho eu sinto de você...";
			link.l1 = "Obrigada, meu amor. Você se machucou?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Não, não. Embora eu tenha achado que estávamos por um fio algumas vezes – tanto antes de embarcarmos quanto durante. E você, está bem?";
			link.l1 = "Estou bem, obrigada mais uma vez. Vá descansar na cabine, já já eu vou me juntar a você.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, você está bem? Vim assim que pude, tudo certo.";
			link.l1 = "Estou bem, obrigada, querido. Mas foi uma luta e tanto.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Fico feliz! Mas... Escuta, Charles? Por que atacamos essas pessoas? O Senhor não vai nos perdoar por isso, não. Este navio... é como um grande templo. Quando o vi, meu coração estremeceu, igual da primeira vez que entrei numa igreja de verdade, não só nos livros. E agora ele sangra!";
			link.l1 = "Mary... Você sabe que as aparências enganam. E por trás da máscara de piedade estavam aqueles que tiravam dinheiro dos fiéis mais simples – assim como você. Entende?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Eu... eu acredito em você, Charles. Tudo bem. Só... vamos doar pelo menos uma parte do ouro que encontramos aqui para quem realmente precisa? Isso aliviaria meu coração.";
			link.l1 = "Vamos fazer isso, Mary. Eu prometo. Agora respire fundo e tente se acalmar. Já passou.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ha, bem, parabéns pela sua vitória, capitão! Isso sim é que é negócio! Que pilhagem nesse galeão!..";
			link.l1 = "Seu sorriso está ainda mais largo que o normal hoje, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Pode apostar! Que pilhagem. E que luta. Me lembrou a Revolução. E também... heh.";
			link.l1 = "O que foi, Tommy? Vamos, fale logo.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Como eles enfeitaram o navio inteiro como se fosse uma catedral flutuante. E juntaram tanto ouro de todos os cantos. Verdadeiros fanáticos papistas! Uma vergonha, chega a ser ridículo.";
			link.l1 = "Este é um navio do tesouro, Tommy. Não um navio da igreja.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Não faz muita diferença no nosso caso. De qualquer jeito, fiquei feliz em dar uma boa lição nesses dons e papistas! Não suporto nenhum deles. Aproveitei demais este dia, ha-ha-ha!";
			link.l1 = "Você não muda nunca! Tudo bem, pode ir. Aqui está tudo sob controle.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Capitão Charles, vencemos a batalha. Foi uma luta difícil. Até Tichingitu achou complicado, e eu sou um dos melhores guerreiros da aldeia.";
				link.l1 = "É verdade, meu amigo. Eles foram adversários à altura, sem dúvida.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Senhor de Montoya, o navio é nosso.";
				link.l1 = "Muito bem, Tichingitu. Eu também acabei aqui agora.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Capitão Paterson, última resistência esmagada no navio.";
				link.l1 = "Você está atrasado, Tich! Da próxima vez é melhor ficar comigo. Não que eu não desse conta sozinho, veja bem...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Capitão McArthur, você está bem?";
				link.l1 = "Sim, Tichingitu, estou bem, obrigado por perguntar. E pare de duvidar do seu capitão – eu resolvi tudo muito bem sozinho.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Os espíritos me dizem isso durante a luta. E perguntam por que eu os mato. Agora eu te faço a mesma pergunta. Tichingitu vê nos olhos deles, eles não são vilões. Ainda não.";
				link.l1 = "Ah, o que posso te dizer? Não tenho uma resposta, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Quero te fazer uma pergunta, Capitão de Montoya.";
				link.l1 = "Estou ouvindo.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu quer lhe fazer uma pergunta, Capitão William, se permitir.";
				link.l1 = "Concedido.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Não duvido, só me preocupo com você, capitão.";
				link.l1 = "Certo, certo. Vejo nos seus olhos que você quer me perguntar mais alguma coisa.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hum, como quiser, capitão. Terminamos aqui?";
				link.l1 = "Sim. Vou dar mais uma olhada por aqui e depois me junto aos outros.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Essas pessoas, elas não são da mesma tribo que você? Não são espanholas? Por que você decidiu atacar?";
				link.l1 = "É verdade. Mas as tribos indígenas também não lutam entre si? Ou não existem brigas e desavenças dentro de uma mesma tribo?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Esse navio parece uma igreja. Você odeia igreja e o deus branco?";
				link.l1 = "De jeito nenhum. Mas é só decoração, entendeu? Este é um navio do tesouro. Mas você não entenderia – ouvi dizer que o seu povo nem sabe o que são impostos. Sortudos.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Sim. Seja sincero. Capitão MacArthur, por que estamos atacando essa igreja flutuante?";
				link.l1 = "Igreja flutuante, ha-ha-ha! Não, não. Este é um navio do tesouro. Hmm, vejo que você não entendeu direito. Bem, eles estavam transportando ouro. Já imagino o orgulho do Jan quando eu contar que derrotei Fernando de Alamida!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = " Hmm, você está certo, capitão. Mas com os índios isso acontece menos do que com o homem branco.";
				link.l1 = "Talvez. Bem, esse homem estava... se metendo comigo.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "É verdade, Maskogi não têm castelos nem impostos.";
				link.l1 = "Exato. Pode ir, você já está atrasado mesmo. Depois decidiremos o que fazer com esse belo galeão. Não gosto muito desses trambolhos, mas, caramba, ela é linda.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu também sente orgulho de você, capitão. E te parabeniza por vencer essa luta difícil.";
				link.l1 = "Obrigado. Agora vamos dividir o saque.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Interferindo, senhor de Montoya?";
			link.l1 = "Exatamente. Este arquipélago é pequeno demais para nós dois. E eu sou muito mais útil ao nosso estado aqui. Lembre-se da Folha de Cacau – ele fez mais mal do que bem aos seus irmãos. O mesmo acontece aqui.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Agora eu entendi. Tichingitu pode ir, capitão?";
			link.l1 = "Sim, vá. Logo me junto a vocês também.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Ei, qual é a dessa agitação toda com as armas?! Guarda isso agora mesmo!","Eu ordeno que você guarde sua arma imediatamente!","Ei, "+GetAddress_Form(NPChar)+", pare de assustar as pessoas! Guarde sua arma.");
			link.l1 = LinkRandPhrase("Certo, vou guardar isso...","Já está feito.","Como você quiser...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vai se ferrar!","Acho que vou usar isso!","Vou guardar quando chegar a hora certa.");
			link.l2.go = "fight";
		break;
		
	}
} 