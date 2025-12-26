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
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Capitão, o dia é nosso. A vanguarda está terminando de limpar o convés inferior. Nenhum prisioneiro... Ha! Vejo que você também não pegou leve.";
			link.l1 = "Por algum motivo, achei que ele fosse fazer um grande discurso. Mas ele só avançou de uma vez.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
			if (sti(pchar.rank) <= 11) Achievment_Set("ach_CL_156");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Permissão para falar livremente?";
			link.l1 = "Concedido.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Não, terminamos aqui.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Por que atacamos eles? Aquele brigue não era uma ameaça, não carregava carga nenhuma. Claro, tinham vários boatos sobre o Grim, mas só os mercadores de escravos tinham medo dele. Muita gente morreu hoje — e pra quê?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Agora você fala pela tripulação?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "E não é a primeira vez...";
			link.l1 = "Agora você fala pela tripulação?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Não. Acredite, se a tripulação tivesse esse tipo de dúvida, isso só provaria que sou ruim no que faço e você já estaria com um pé na cova\n"+"Por sorte pra você, os rapazes lucraram bonito com essa maldita empreitada. Todo marinheiro desse navio saiu com os bolsos cheios de dobrões!\n"+"Mas nada de carga valiosa — só bugigangas indígenas e talismãs estranhos. Mesmo assim, a tripulação se deu bem. Parece que Grim pagou generosamente\n"+"Espero que você não esteja pensando em reivindicar uma parte daquele ouro, capitão?";
			link.l1 = "Não estou, Alonso. Obrigado por me manter informado.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Sou eu. Certifique-se de que minha parte seja entregue na minha cabine.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Sempre ao seu lado, capitão. Aliás, o que você pretende fazer com o Memento?";
			link.l1 = "Considere isso um prêmio — o que mais poderia ser?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Não decidi"+GetSexPhrase(""," ainda")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Sempre ao seu lado, capitão. Aliás, o que pretende fazer com o Memento?";
			link.l1 = "Considere isso um prêmio — o que mais poderia ser?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Ainda não decidi"+GetSexPhrase(""," ainda")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Melhor não. Está coberto por uns símbolos indígenas. E há boatos ruins sobre ele — dizem que já sobreviveu a uma praga monstruosa e que os conveses quase dançaram com cadáveres\n"+"Quanto ao esqueleto na popa, nem vou comentar: até que algum idiota resolva pegar o crânio só por diversão, ninguém além de mim vai se atrever a fazer a guarda ali.";
			link.l1 = "Entendi, Alonso. De volta ao trabalho.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Aye, capitão.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Capitão, desculpe incomodar você a esta hora.";
			link.l1 = "Relatório, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Capitão? O que está fazendo aqui? Estava dormindo aqui?";
				link.l1 = "Não importa.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "Minha cabine está... estranha.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "As coisas estão ruins. O moral da tripulação está no chão! Tem gente dizendo abertamente que o navio está amaldiçoado. Reclamam que estão vendo coisas à noite.";
			link.l1 = "Vendo o quê exatamente?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Pesadelos, na maioria. Mas o pior é que um dos nossos morreu de febre. Um rapaz jovem, forte como um touro, e ele se consumiu em poucas horas.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Isso é para o doutor decidir. "+sld.name+" sabe o que faz.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "Isso não é normal. Mantenha a tripulação sob controle, Alonso. Esse é o seu trabalho.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Sim, senhor!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Eu entendo. Muitos da tripulação agora dormem em grupos — com medo de ficarem sozinhos. Como se fosse possível ficar sozinho neste navio...";
			link.l1 = "Parece que não consegui. O que aconteceu?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Uma briga — José esfaqueou Marcel. Gritava que ele 'trazia a peste'.";
			link.l1 = "A situação está piorando?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" já relatei isso esta manhã. Perdemos onze almas. O que faremos?";
			}
			else
			{
				dialog.text = "Mais onze almas perdidas. O que devemos fazer?";
			}
			link.l1 = "Vou fazer a ligação.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Espero que sim, Capitão. E o José? Matar não é brincadeira.";
			link.l1 = "Enforque-o depois do sino. Mostre que estamos no comando.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Trinta chibatadas. Se ele sobreviver — então é a vontade de Deus.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Sim, senhor!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Sim senhor!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Capitão! Alarme!! Você precisa ir ao convés dos canhões imediatamente!";
			link.l1 = "O que está acontecendo?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "É melhor você ver com seus próprios olhos. Vamos, depressa!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Bom dia, capitão!";
			link.l1 = "Hã?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Você está com uma cara péssima. Noite difícil? Olha, tenho boas notícias. A epidemia acabou. Descobriram que... na verdade, nunca existiu.";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "A tripulação ficou assustada, começou a acreditar nessas histórias bobas de navio fantasma. O poder da sugestão — isso sim é assustador, te digo. Já afundou mais de um navio.";
			link.l1 = "Mas pessoas morreram!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Lutas, feridas sujas, carne salgada estragada — só a matemática comum de marinheiro. Se a gente não tivesse se inflamado tanto com histórias de navios amaldiçoados, talvez tivéssemos perdido alguns a menos\n"+"Aquele esqueleto na popa não ajudou em nada. Ainda bem que algum... engraçadinho roubou o chapéu dele durante a noite\n"+"Já que o raio não caiu sobre nossas cabeças por tanta blasfêmia, a tripulação se animou e logo começou a bolar travessuras. Como, por exemplo...";
			link.l1 = "Não toque no esqueleto!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Ah... bem, se você se apegou a ele, claro que não vamos. Tenha um bom dia, capitão\n"+"Aliás, belo chapéu! Ficou ótimo em você. Claramente não servia no dono anterior.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Saudações, Capitão. Você deveria falar com o Capitão Grim.";
				link.l1 = "Desculpe, marinheiro, mas você chama atenção aqui.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa, Capitão?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "Eu entendo o que você quer dizer, Capitão. Eu servi sob o comando de um capitão livre — muito parecido com você. Ele caçava tesouros, fazia trocas, aceitava cargas. Então resolveu assaltar alguns mercadores — não deu certo. Os sobreviventes foram condenados à forca por pirataria.";
			link.l1 = "E o Capitão Grim comprou você?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Comprou todos nós de uma vez, como se fôssemos carga. Todo navio precisa de marinheiros experientes, e Grim não recruta em tavernas... Mas ele nos alimenta e paga bem. E nós servimos — e tiramos a sorte.";
			link.l1 = "As sortes?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Desculpe, não deveríamos falar sobre isso.";
			link.l1 = "Por que simplesmente não vai embora?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "Pra onde? Pelo menos aqui ainda há uma chance. Vai que a sorte resolve sorrir. Cada navio tem seu destino. Grim tem o dele, você tem o seu. Não somos pessoas, só números no diário de bordo.";
			link.l1 = "As coisas são diferentes no meu navio.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "Como quiser, Capitão. Tenha um bom dia.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Faz muito tempo que não recebemos visitantes neste belo navio!";
				link.l1 = "Você é marinheiro? Não parece, não.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa, Capitão?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "Ha! O capitão me comprou direto da cela. Era pra eu ser enforcado em Port Royal — esfaqueei um almofadinha que não parava de recitar poesia. Mereceu, o desgraçado.";
			link.l1 = "Então você teve sorte, né?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "Pode apostar! O capitão não é mão de vaca, mas às vezes você tem que entrar nos... joguinhos dele.";
			link.l1 = "Que tipo de jogos?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Toda semana a gente tira palitos: o mais curto significa trabalho perigoso, ou às vezes pular no mar. É divertido, de verdade. Não é pra todo mundo, mas o capitão diz que é assim que ele elimina os indignos.";
			link.l1 = "Indigno de quê?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "Como é que eu vou saber? O capitão adora falar, prega feito um padre: «Só encarando a morte é que se vive de verdade!»\n"+"(Ele cospe.)";
			link.l1 = "Cuspir no convés te rende o chicote. Você está agindo como um bandido, não como um marinheiro. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Saudações, Capitão.";
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa, Capitão?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "O Capitão Grim tomou o navio negreiro em que eu estava. Eu estava doente, morrendo no porão... Não lembro de muita coisa. Quando dei por mim, acordei aqui, no Memento.";
			link.l1 = "E o que aconteceu com os outros escravizados?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "Eu não sei. O capitão disse que libertou todo mundo, mas só eu fui trazido a bordo. O resto deve ter se espalhado pelas ilhas ou morrido dos ferimentos. Aquele dia é um borrão pra mim.";
			link.l1 = "Pelo menos agora você está livre.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Livre? Ninguém é livre aqui. O capitão dá ouro, comida, roupas, mas em troca exige lealdade total — e ainda nos faz tirar aquelas malditas sortes.";
			link.l1 = "As sortes?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Toda semana, alguém tira a palha mais curta e pega um trabalho perigoso — nem todos voltam. O capitão diz que é assim que se separam os vivos dos mortos.";
			link.l1 = "E você aguenta isso?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Todo mundo espera que a sorte sorria pra si. O capitão sabe o que move cada homem: medo da forca, ganância por ouro, vontade de pagar uma dívida por uma vida salva. Nada disso importa pra mim. Não preciso de dinheiro, e que dívida eu poderia ter por algo que nem lembro?";
			link.l1 = "Você não tem medo de falar assim, tão abertamente?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "O que eles podem me fazer? Este é um navio dos mortos, Capitão, e é aqui que eu pertenço. Mas você — você não pertence.";
			link.l1 = "Se você diz. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bem-vindo a bordo do Memento, Capitão.";
				link.l1 = "Um soldado espanhol em um navio pirata? Isso não é algo que se vê todo dia.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa, Capitão?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "Sou um desertor. O Capitão Grim me comprou direto da forca na praça de San Jose. Pagou caro — um saco inteiro de dobrões pela minha pele miserável.";
			link.l1 = "Por que te enforcaram?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "O oficial Saldo nos mandou proteger os trabalhadores na selva, onde metade morre de febre em uma semana. Achei que minha vida valia mais do que isso. Agora sirvo ao homem que colocou um preço nela.";
			link.l1 = "Sem arrependimentos?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "Uma corda pode se torcer por muito tempo... O capitão é generoso com quem lhe é leal. Mas às vezes ele nos põe em provações estranhas — sorteios. Nem todo mundo tem sorte.";
			link.l1 = "Tirando a sorte?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "Você sabe. Alguns são mandados para o alto durante a tempestade, outros para a linha de frente. O capitão diz que é assim que ele testa se você está pronto. Pronto para quê, não sei dizer, mas espero que a sorte esteja do meu lado.";
			link.l1 = "Boa sorte... eu acho.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "Obrigado, Capitão. A morte chega para todos nós, mais cedo ou mais tarde.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa, capitão?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bem-vindo a bordo do Memento, colega. Meu nome é Mortimer Grim.";
				link.l1 = "Capitão "+GetFullName(pchar)+". Obrigado por me receber...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Sobre o que mais podemos conversar?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Essa é uma lâmina impressionante que você tem, Capitão.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Seu telescópio fica ótimo ao lado do esqueleto.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Tenho que dizer, sua tripulação é bem variada.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Nada... colega. Bons ventos pra você.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "O Caribe é generoso com aqueles que correm para a forca, disso eu sei.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "Sim? Queria me perguntar alguma coisa?";
			link.l1 = "Tem um esqueleto pendurado atrás de você.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Belo vento hoje, não acha? E o tempo está ótimo.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "Que esqueleto? Atrás de mim só tem o mar azul do Caribe.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "Concordo, colega. Não me importaria se todo dia fosse assim!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "Ha-ha-ha! Essa piada nunca envelhece! Não se assuste: o velho Yorick, assim como este navio, é uma lembrança da minha vida passada. Literalmente, posso garantir.";
			link.l1 = "'Literalmente?'";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "Colega, você tem medo da morte? Sem ameaça, é só curiosidade mesmo.";
			link.l1 = "Claro. Quem disser o contrário é mentiroso.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Não. Todos nós vamos acabar lá.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "E você?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Oh! A morte é a mãe de todos os medos. Solidão, escuridão, castigo — são apenas máscaras dela.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Oh! A morte é a mãe de todos os medos. Solidão, escuridão, castigo — tudo isso são só máscaras dela.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Oh! A morte é a mãe de todos os medos. Solidão, escuridão, castigo — são apenas máscaras dela.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "Não precisa procurar longe. Veja o velho Yorick: um monte de ossos com uma lanterna entre as costelas — e mesmo assim, até um capitão temido como você ficou abalado!";
			if (startHeroType == 4)
			{
				dialog.text = "Não precisa ir longe. Veja o velho Yorick: um monte de ossos com uma lanterna nas costelas — até a destemida Ellen, filha do grande Sean MacArthur, ficou assustada!";
			}
			link.l1 = "Você fala bem, mas ainda não disse o que fazer com tudo isso.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "Eu sei o que fazer, mas minha cura não serve para todos. Você pode tentar, mas antes, me diga o que acha.";
			link.l1 = "A Bíblia diz que não existe morte.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Se eu começar a ter medo, o navio está perdido.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "A resposta se afogou no fundo de uma garrafa de rum.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "É verdade. A única coisa com que eu concordo naquele livro.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "Admirável. Mas você se preocupa à toa: não existe morte.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "Yo-ho-ho! Um cínico. Mas mesmo sem rum, eu digo: não existe morte.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "É simples: a vida de verdade só começa quando você vence a morte. Eu já estive lá, além do véu, e acredite, só comecei a viver de verdade depois disso.";
			link.l1 = "Como é?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Deixa pra lá, colega.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Que bom que percebeu, colega! Não sou de me exibir, mas que tipo de pirata eu seria sem um sabre assustador?";
			link.l1 = "Isso realmente importa?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Exatamente! A única vez que realmente esvaziei o tesouro do navio por motivos pessoais foi por causa desta lâmina aqui. Duas mil dobrões de ouro, colega! Ora, se eu pudesse voltar do túmulo mais uma vez, voltaria só pelo valor dela!\n"+"A arma em si é excelente. Mas, de algum jeito... parece que falta alguma coisa.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Um presente de alguém. Um conversador brilhante, que entende a morte como ninguém — e com uma imaginação selvagem, como você pode ver.";
			link.l1 = "Parece sombrio.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, colega.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Minha tripulação tem mais em comum entre si do que a sua, por exemplo... Todos foram libertados por mim das cordas e correntes. Cada um já sentiu o sopro da morte. Isso une as pessoas mais do que sangue ou bandeira.";
			link.l1 = "Então, você não contrata pessoas em tavernas, imagino?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Você se surpreenderia com a facilidade com que ex-escravos e condenados se alistam: trocar o porão de um negreiro ou a forca pelo convés do Memento? Agora tenho 178 tripulantes — e cada um deles me deve algo.";
			link.l1 = "Mas você ainda precisa pagar a eles e manter o navio. Só gratidão não basta.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Sou um pirata de sucesso, colega. Um verdadeiro hostis humanitatis. É assim que os verdadeiros inimigos da humanidade — os escravizadores e os reis coroados — me chamariam. A única diferença entre eles é o título.\n"+"Por sorte, eles têm ouro de sobra. Uso as moedas dos baús dos mercadores de escravos para salvar os condenados pela coroa. O resto vai para minha tripulação — não preciso de nada. Para que serve ouro a um homem morto? Logo eles vão entender...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "É essa a merda de situação em que estamos, capitão.";
			link.l1 = "O que é isso?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Você é o único que restou. A doença pegou todos nós. Você nos decepcionou.";
			link.l1 = "Isso não pode ser!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Você nos trouxe para bordo de um navio amaldiçoado.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "Você condenou todos nós!";
			link.l1 = "Alonso, o que está acontecendo com você?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Por que parou, colega? Mudou de ideia? Então por que atacou logo de início?";
			link.l1 = "Grim? Mas você está morto!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha! O que está morto talvez nunca morra. E além disso, você está se adiantando: talvez tenha vencido o abordo, mas será que vai sobreviver... bem, vamos descobrir!";
			link.l1 = "Aquela luta acabou semanas atrás! Você está morto!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Agora está feito. Parabéns pela sua vitória.";
			link.l1 = "Grim?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Sabe, eu fico feliz. De verdade, feliz que você me matou. De verdade mesmo.";
			link.l1 = "Do que você está falando?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Sou um covarde, colega. Apenas um covarde lamentável que teve medo da morte — como milhares antes de mim. Quando a tripulação morreu de peste... e a culpa foi minha, enlouqueci de medo. Fiquei à deriva por um mês, sozinho, em um navio de mortos.";
			link.l1 = "O que realmente aconteceu?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Eu falhei na prova da morte. Em vez de aceitar, sobreviver e aprender algo, fiquei ainda mais assustado. E para abafar esse medo... comecei a forçar outros a passar pelo que eu passei.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Obrigado, colega. Por me libertar desta... existência. Agora eu sei de verdade que não existe morte. E não tenho mais medo. Não sobrou ninguém para culpar ou escravizar.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Não separe o Memento do seu capitão. Mortimer... O Capitão Mortimer era um bom homem. Encontre-o em Dominica. E o navio... o navio vai aceitar você.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, colega. Os mortos ensinam os vivos. Adeus.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 