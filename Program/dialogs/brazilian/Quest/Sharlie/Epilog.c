void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Queria alguma coisa?";
			link.l1 = "Não, nada não.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Que surpresa! Você mesmo "+GetTitle(NPChar,true)+" "+pchar.lastname+" em pessoa!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Essa eu não esperava ver... Na verdade, nem achei que você ainda estivesse vivo!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Não acredito no que vejo... Bonitão? Mas... como?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ha-ha! Pois é, você se enganou. Como pode ver – estou mais vivo do que nunca. Olha só, resolvi comprar um navio 'novinho'. E você... conta aí: como foi que chegou nesse ponto, hein, camarada?";
			  }
			  else 
			  {
				dialog.text = "Ha-ha! Pois é, você se enganou. Como vê – estou mais vivo do que nunca. Olha só, resolvi comprar um navio 'novinho'. E você... conta aí: o que te trouxe aqui, hein, camarada?";
			  }
			link.l1 = "Não aqui. Vamos para a taverna – os assuntos podem esperar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Psiu... Não grite assim. Bonitão ficou no passado, assim como, imagino, o Príncipe. Não é?";
			link.l1 = "Mas eu vi com meus próprios olhos...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Como me mataram? Melhor se tivesse sido assim mesmo, amigo. Pode acreditar.";
			link.l1 = "Vamos para a taverna. Você vai me contar tudo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Então, você é o novo dono do pinas '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Eu. "+GetFullName(npchar)+", já que você está tão curioso. E você, quem é?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", e eu gostaria de comprar este navio de você.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Claro, claro, já ouvi falar. E eu achando que já tinha me livrado de todos que querem pôr as mãos nesse barco. Vou ter que te decepcionar, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' agora é meu, e muito em breve vou partir para Bordeaux nele. Não entrei no comércio para desfazer o primeiro negócio logo de cara. Dá azar, sabe como é.";
			link.l1 = "Bordeaux, você disse? Interessante... Talvez eu tenha uma proposta vantajosa para você. Que tal conversarmos sobre isso tomando um rum?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Não costumo recusar nem rum, nem boas propostas. Vamos.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Bem, à sua saúde, "+GetTitle(npchar,false)+" "+pchar.lastname+"Eu sabia que um cara como você não ia ficar muito tempo correndo atrás dos recados do Tirax. Mas que você se tornaria alguém tão importante assim... você realmente sabe surpreender, caramba.";
				link.l1 = "Ha-ha. Quem diria. Então, resolveu virar comerciante?";
			  }
			  else 
			  {
				dialog.text = "Um brinde ao nosso encontro! Eu sentia lá no fundo que ainda iríamos nos ver de novo.";
				link.l1 = "Ha-ha. Por ela! Então quer dizer que você resolveu virar comerciante?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "Não vou passar a vida arriscando o pescoço por uns trocados. Dei uma moeda pra quem precisava, calei a boca de quem não devia falar – e pronto: não sou mais ladrão nem pirata, agora sou um negociante respeitável.";
			link.l1 = "Essa é uma surpresa e tanto. Agora nem sei mais como te oferecer aquilo que eu ia propor ao recém-nomeado capitão do pinasse '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Ah, fala logo como é. A gente se conhece faz séculos.";
			link.l1 = "Veja... eu vim aqui para o Caribe naquele pinasse que você comprou. Quando soube que ele estava indo a leilão, quis negociá-lo — e voltar para casa nele, para a França.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ha-ha-ha-ha! Espera... ah-ha-ha-ha-ha!..";
			link.l1 = "E então, o que é tão engraçado?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "Mal ganhei o leilão, já veio até mim um dândi — jovem, todo arrumadinho: pediu, com toda gentileza, que eu o levasse, junto com seus pertences, até Bordeaux, por uma bela quantia. E não era só uma moeda — era um maldito saco cheio delas.";
			link.l1 = "É mesmo? Ha-ha. Que engraçado. E então? Você aceitou?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", eu não sou idiota de recusar um monte de ouro só por uma travessia comum do Atlântico. Né, vou ter que passar uns meses comendo bolacha dura e carne salgada. Mas olha, já arrisquei meu pescoço por bem menos. Então, é claro que eu topo.";
			link.l1 = "Nesse caso, posso te oferecer o mesmo. Leve-me até Bordeaux – e vai receber a mesma pilha de moedas.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Você está pronto para ser passageiro? Você sabe como são as nossas regras – só existe um capitão a bordo. E no meu navio, esse capitão sou eu.";
			link.l1 = "Por que não? Vou respirar um pouco, pensar na vida. Talvez eu deva mesmo sossegar, criar raízes. Agora é difícil até imaginar isso, mas quem sabe faça sentido. Até você resolveu se afastar das batalhas.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ah, se eu tivesse uma esposa bonita como a sua, talvez até largasse o mar e fosse viver num canto qualquer: construiria uma casa e venderia um vinhozinho. Ainda bem que agora tenho do que viver – depois que você me tirou das garras dos espanhóis, não perdi tempo.";
			}
			else
			{
				dialog.text = "Ah, se eu tivesse uma esposa linda como a sua, talvez até largasse o mar e fosse viver num canto qualquer: construía uma casa, vendia um vinhozinho. Ainda mais que dá pra viver bem – a viúva do fazendeiro tinha uma herança e tanto.";
			}
			link.l1 = "Esposa! Diabo, "+npchar.name+", ainda não falei com ela sobre isso.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Você ainda tem tempo de sobra pra isso. Eu preciso equipar meu barco direito. Quando resolver todos os seus assuntos, traz essa sua bunda pra cá. Vamos fazer uma festa antes de zarpar.";
			link.l1 = "Isso sim é do meu jeito! Não se preocupe, não vai demorar muito pra esperar.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ah, se eu tivesse uma esposa, talvez até largasse o mar, me estabelecesse em algum canto esquecido: construiria uma casa, venderia um pouco de vinho. Mas por enquanto... o mar é meu lar.";
			link.l1 = "Com vinho das minhas plantações, haha! Em Bordeaux, "+npchar.name+", aquelas moças são de encher os olhos! Quem sabe você também não encontra alguém por lá – dizem que elas são bem habilidosas nos assuntos do amor. Sabe, fiquei pensando: nos próximos meses, tudo o que vamos ver são as caras dos seus marinheiros. Antes de zarpar, a gente devia fazer uma bela farra no bordel da cidade.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "E você, monsieur, sabe bem o que oferecer. Quando terminar todos os seus assuntos, traga essa sua bunda pra cá. Depois a gente pode até passar num bordel, pode apostar.";
			link.l1 = "Então, não vou perder tempo. Vamos ao trabalho!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "Pela liberdade!";
			link.l1 = "E por você, Jean! Pela sua ressurreição! Ainda não consigo acreditar. Como?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Me arrastaram do campo de batalha – quase morto, coberto de sangue dos pés à cabeça. Jogaram-me num barracão e me deixaram lá pra morrer feito um animal. Entre os escravos havia um sujeito bem habilidoso – Moko. Foi ele quem salvou minha pele: amarrou meu ferimento com um pedaço da minha própria camisa e me deu água pra beber.";
			link.l1 = "Quer dizer que os espanhóis te deixaram vivo depois de tudo isso?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Como você pode ver. Mas não foi por bondade, não. Eles queriam vingança — interrogatório pesado, tortura. Queimavam, batiam, cortavam. Ameaçaram até arrancar meus olhos — tudo isso só por tanto amor que sentiam por mim. Mas aí alguém espalhou um boato de que os piratas estavam prontos pra se vingar por mim e já afiavam as facas. O dono da plantação até ficou com um tique no olho. Ele não quis esperar a visita dos nossos camaradas e correu para suas terras em Campeche. Levou eu, Moko e o resto junto, pra não deixar testemunhas. Pros outros, disseram que eu tinha morrido — e fim de papo.";
			link.l1 = "E o que aconteceu depois? Como você conseguiu sair? E como, diabos, você veio parar aqui?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "Sorte, camarada. Sorte cega, suja. Me levaram pra uma plantação – e as torturas continuaram. Aquele desgraçado decidiu saborear cada segundo do meu sofrimento, mas a cada dia ele ficava mais fraco... até morrer de febre. Depois disso, ninguém mais ligava pra mim. Me jogaram no campo, feito um animal, sem esquecer de me presentear com boas chicotadas.";
			link.l1 = "Eu ainda não entendo como você conseguiu escapar de lá?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Já ouviu falar do Christopher Myngs?";
			link.l1 = "O Alonso mencionou alguma coisa... O ataque a Campeche! Eles acabaram mesmo com os espanhóis naquela vez. Então foram eles que te libertaram?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Não exatamente. Nós mesmos conseguimos escapar. Enquanto os guardas lutavam contra um grupo de bucaneiros ingleses, eu e Moko achamos uma brecha no telhado do barracão e começamos uma revolta. Tomamos o arsenal e o cofre da esposa do falecido canalha fazendeiro.";
			link.l1 = "O tesouro?! Essa é boa.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Não pensamos muito – pegamos nossas armas e suprimentos e fomos para a selva. Passamos dois dias abrindo caminho pela mata até encontrar uma aldeia dos índios Kan Pech. O xamã deles fingia obedecer aos espanhóis, mas não gostava deles de verdade. Moko logo se entendeu com ele – nos acolheram em troca de metade do nosso arsenal e ajuda na guerra, fosse contra quem fosse. Assim vivi lá por um ano e meio.";
			link.l1 = "Você, Jean, não é mais quem era antes. De agora em diante, você é o Sortudo.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ha-ha. Não me oponho. Depois disso, um pregador francês apareceu no nosso batabil. A gente percebeu na hora: era a chance de sair dali sem algemas. Subornamos a escolta dele – e logo já estávamos navegando para Tortuga\nE então, como você já deve ter adivinhado, decidi não brincar mais de esconde-esconde com a morte. Larguei o velho ofício... e aproveitei pra comprar um '"+GetShipName("Ulysse")+"'.\n"+"E você? Como foi parar nessa vida? Eu sabia que um sujeito tão ousado não ia ficar muito tempo correndo atrás dos recados do Tirax. Mas virar alguém tão importante assim... você realmente sabe surpreender, viu.";
			link.l1 = "Ha-ha. Quem diria. Então, resolveu virar comerciante?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "Por aqueles que estão no mar!";
			link.l1 = "E à senhora sorte!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Vamos ao que interessa. O que você queria me propor?";
			link.l1 = "Você está indo para Bordeaux... Veja, eu também estou indo pra lá.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Quer que eu te leve a bordo? Pelo que sei, você deveria ter seu próprio navio. Talvez até uma frota inteira. E mesmo assim decidiu viajar em outro navio. Estou certa?";
			link.l1 = "Exatamente. Os últimos acontecimentos me fizeram pensar: talvez tenha chegado a hora de lançar âncora, sossegar... Acho que ser apenas uma passageira no seu navio vai me ajudar a entender se consigo aceitar esse novo ritmo de vida.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hum... Então, cansou de arriscar o pescoço à toa? Sei bem como é. Eu mesmo já... Enfim, não importa. Tem lugar pra você no navio, e pra toda sua comitiva também. A viagem já foi paga por um jovem francês — e ele também pagou pela pressa, então não vou encher os porões. Quanto ao pagamento...";
			link.l1 = "Não se preocupe, capitão. Não sou menos generoso que seu contratante e estou disposto a pagar a mesma quantia.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Excelente! Então, combinado?";
			link.l1 = "Fechado! Isso merece um brinde!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Sim, esse rum está no ponto... Vou precisar de duas semanas — para deixar o navio em ordem e abastecer tudo o que for preciso. Depois disso, podemos zarpar.";
			link.l1 = "Então nos encontramos aqui mesmo em duas semanas. Bem, até logo, capitão.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "E aí, camarada, resolveu seus assuntos? Vamos mostrar pra esse galinheiro como é que se faz festa?";
				link.l1 = "Ainda não é hora, "+npchar.name+", ainda tenho algumas coisas para resolver.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Capitão, você já está pronto para embarcar no navio?";
				link.l1 = "Infelizmente, colega, ainda tenho coisas a fazer.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Ei, estalajadeiro! Bebida para todos por minha conta! E não qualquer coisa, traga o melhor que você tem!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "Por nós, camarada. Pelo vento salgado, pelo mar sem fim e pelo horizonte – sempre chamando, sempre inalcançável...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", querida, quero conversar com você sobre meu pai.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "O que aconteceu, querido? Espero que esteja tudo bem com ele, né?";
			link.l1 = "Bem, não tão bem quanto gostaríamos. Há motivos para acreditar que ele não vai durar muito, e o que mais o preocupa é a ideia de talvez não me ver antes de partir para o outro lado.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Eu sei, minha querida, eu sei... Mas é assim que a vida é. Eu gostaria que você o conhecesse. Que ele veja como minha esposa é incrível e nos dê sua bênção.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "E se eu não agradar a ele, né? Eu não sou de sangue nobre...";
			link.l1 = "Bobagem, "+npchar.name+", como é que ele não vai gostar de você? Você é um encanto! Se conseguiu conquistar meu coração – vai conquistar o dele também.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Você acha mesmo isso, querido? Então precisamos ir até ele o quanto antes.";
			link.l1 = "É exatamente isso que eu vou fazer. Já até arrumei um navio pra nós. Partimos em duas semanas.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "O navio? Nós não vamos no nosso próprio barco?";
			link.l1 = "Não, querida. Vamos partir na pinasse '"+GetShipName("Ulysse")+"'. Foi nele que cheguei ao Caribe — e é nele que vou embora.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "E você não vai ser o capitão?";
			link.l1 = "Cedo ou tarde eu teria que abrir mão desse papel de qualquer jeito. Espero que seja só por um tempo. Mas, de qualquer forma, não faz mal sentir o que me espera no futuro.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "E os nossos oficiais? Não vamos conseguir levar todos com a gente. E duvido que eles vão ficar aqui esperando por você.";
			link.l1 = "Hum... Sim, você tem razão. Vou ter que conversar com cada um deles e, provavelmente, me despedir para sempre. Mesmo que não seja fácil – considerando tudo o que passamos juntos.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Talvez devêssemos fazer uma pequena festa de despedida na taverna?";
			link.l1 = "Eu também pensei nisso, querida. Sabe... acho que você tem razão. É realmente uma boa ideia.";
			link.l1.go = "exit";
			link.l2 = "Não acho que seja uma boa ideia. Vamos evitar despedidas barulhentas... Assim, provavelmente, será melhor para todos. Talvez só devêssemos chamar os amigos mais próximos...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Querida, eu queria conversar com você sobre meu pai.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Claro, "+pchar.name+". Espero que ele esteja bem?";
			link.l1 = "Não exatamente. Ele já está doente faz tempo e, receio que logo a doença vai vencer... Meu pai está lidando com tudo isso com muita coragem. A única coisa que realmente o preocupa é que talvez nunca mais me veja. Eu quero visitá-lo... e te apresentar a ele. Receber a bênção dele para o nosso casamento.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Vou ficar feliz em conhecê-lo, meu amor. Quando partimos?";
			link.l1 = "Daqui a duas semanas. Mas isso não é tudo. Não vamos no nosso navio. Para o Velho Mundo, vamos de pinasse '"+GetShipName("Ulysse")+"' - aquele mesmo que um dia me trouxe até aqui.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", mas trocar de navio antes de uma longa viagem dá azar.";
			link.l1 = "Não vamos trocar de navio, querida. Seremos passageiros.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Mas... meu amor, eu não entendo...";
			link.l1 = "É preciso, "+npchar.name+"Mais cedo ou mais tarde vou ter que deixar o posto de capitã. E quero saber de antemão quais sentimentos vou ter que enfrentar.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Se é isso que você decidiu... Mas e os nossos oficiais? Não vamos conseguir levar todos com a gente. E é bem provável que eles não queiram ficar aqui te esperando.";
			link.l1 = "Hum... Sim, você tem razão. Vou ter que conversar com cada um deles e, provavelmente, me despedir para sempre. Embora isso não seja fácil, considerando tudo o que passamos juntos.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Talvez devêssemos fazer uma pequena festa de despedida na taverna?";
			link.l1 = "Eu também pensei nisso, querida. Sabe... acho que é isso mesmo que vamos fazer. É realmente uma boa ideia.";
			link.l1.go = "exit";
			link.l2 = "Não acho que seja uma boa ideia. Vamos evitar despedidas barulhentas... Assim, acho que será melhor para todos. Talvez só convidemos os amigos mais fiéis...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Capitão... Já falei com o dono da taverna – ele preparou a melhor bebida que tem. Quando começamos?";
				link.l1 = "Agora mesmo! Ei, estalajadeiro! Bebida para todos por minha conta!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Capitão, você prometeu me contar como ficou sabendo do 'Ulisses'.";
				link.l1 = "Lembro, lembro. Ei, estalajadeiro! O melhor rum para esta mesa.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Cedo, "+npchar.name+". Ainda tenho assuntos urgentes para resolver.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Então, camarada, chama o resto do pessoal – vamos mostrar pra Saint-Pierre como é que os verdadeiros lobos do mar festejam!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ha-ha! Capitão, você não vai acreditar – eu já chamei eles!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "Por nós, "+npchar.name+"   À senhora sorte e ao vento que enche nossas velas!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "E a bagunça que a gente fez, capitão. Haha. Acho que só o pouco rum do taverneiro salvou a taberna da falência total.";
			link.l1 = "Nem me lembre, "+npchar.name+", só agora comecei a me sentir um pouco melhor.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Como quiser, senhor "+pchar.lastname+". Ha-ha. Mas pelo menos nos despedimos de Martinica em grande estilo. Vão lembrar da sua partida por muito tempo por lá.";
			link.l1 = "Acho que a gente exagerou um pouco quando colocamos o dono da taverna no bote e mandamos ele pra Le François buscar bebida.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ha-ha-ha. Não se preocupe com ele. Nestes dias, ele ganhou tanto ouro que pode comprar uma plantação e ainda levar um título de brinde.";
				}
			else
				{
					dialog.text = "Ha-ha-ha. Não se preocupe com ele. Nestes dias, ele juntou tanto ouro que pode comprar uma plantação e ainda levar um título de brinde. Pena que você não conversou com nenhum dos oficiais. Vamos sentir falta deles.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Parece que "+sld.name+" ainda está brava com você por ter sumido a noite inteira.";
			}
			else
			{
				dialog.text = "Mas com aquele comerciante... ali você, capitão, realmente passou dos limites.";
			}
			link.l1 = "Diabos, e logo a gente tinha que entrar naquela loja com o Jean…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "E como é que não te pegaram ainda? Isso ia ser engraçado, viu - "+GetTitle(PChar,true)+" pego tentando roubar algumas garrafas de vinho.";
			link.l1 = "Você acha engraçado, "+npchar.name+", e eu nem lembro da metade de tudo isso. Da última vez que bebi tanto assim... foi... foi nunca, na verdade.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Então, vamos brindar a isso, capitão. Ha-ha. Eu gostei. Faria de novo. Quando mesmo a gente volta?";
			link.l1 = "Vai dar uma olhada nas nossas coisas, vai. Pegamos tudo mesmo? Eu desço depois – o ar do porão não vai me fazer bem agora, com certeza.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Só olha pra isso... o navio balançou bonito, hein.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Aqui tem uma porção de ouro do diabo, capitão!";
			link.l1 = "Eu vejo, "+npchar.name+". Precisamos esconder tudo isso nos baús o quanto antes, antes que a tripulação veja. Eles não precisam dessas tentações.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "Não, não vou resistir...";
			link.l1 = "O quê?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Ei, o que foi isso?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Levanta aí. Achou uma boa hora...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Junte-se a nós, capitão.";
			link.l1 = "Levanta, chega de fazer besteira.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Relaxe. Você precisa sentir isso.";
			link.l1 = "Tá bom, que se dane. Vai, dá licença.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Sempre sonhei em fazer isso...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "É uma sensação maravilhosa, não é, capitão?";
			link.l1 = "Ha-ha-ha. Então foi assim que visitei o Caribe – só pra saber como estava meu irmão. Meu pai com certeza não esperava por esse desfecho. Ha-ha!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Senhor "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ha-ha! Você se lembra de como chegou ao arquipélago?";
			link.l1 = "Claro que me lembro. Ha-ha. Nem dá pra acreditar que eu já fui tão vaidoso quanto aquele ali que agora desfila pelo convés. Tanta coisa aconteceu nesses malditos Caribes… Intrigas, mortos-vivos, o irmão Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Você é mesmo sortudo pra caramba, capitão. Juntar tanta grana e ainda sair vivo disso... nem todo mundo consegue.";
			link.l1 = "Pois é. Tá bom, chega de ficar à toa. Vai que alguém realmente percebe.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Olha, camarada, não gosto do freio do cabrestante deste navio. Ele é confiável demais não, viu. Vai que alguém esbarra nele sem querer.";
			}
			else
			{
				link.l1 = "Olha, capitão, não gosto do freio do cabrestante deste navio. Ele é instável demais. Alguém pode acabar soltando ele sem querer.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ah, deixa disso, "+pchar.name+",   no navio todo mundo sabe que...";
			}
			else
			{
				dialog.text = "Ah, deixa disso, capitão. Quem é que pensaria nisso...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Ei, você, cabeça-dura... Que diabos você está fazendo? Nunca te ensinaram a não enfiar esses seus cambitos tortos onde não deve?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Calma aí, não se esqueça com quem está falando! Eu sou um nobre, e não vou tolerar...";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "No meu navio, você não é ninguém. Meus marinheiros têm mais direitos aqui do que você. Então, ou você fica quieto e não atrapalha ninguém, ou eu mesma vou te jogar no mar.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ha-ha-ha. Foi como se eu tivesse me visto de fora.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Do que você está falando?";
				link.l1 = "Não, não importa, "+npchar.name+". Não seja tão duro com o nosso passageiro. Tudo isso ainda é novidade pra ele. No fim das contas, nós também não viramos lobos do mar de um dia pro outro.";
			}
			else
			{
				dialog.text = "Sobre o quê?";
				link.l1 = "Não dê importância, "+npchar.name+". E não julgue seu passageiro com tanta severidade. Tudo isso é novidade pra ele. No fim das contas, nós também não nascemos lobos do mar, não é mesmo?";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Com o talento dele, é mais fácil ele se enroscar no cabrestante do que virar marinheiro. Precisa ser muito cabeça de vento pra isso...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Quem sabe, quem sabe. Cheguei ao arquipélago tão despreocupado, curioso e arrogante quanto um jovem.";
			}
			else
			{
				link.l1 = "Quem sabe. Quando cheguei ao arquipélago, eu era tão despreocupado, curioso e arrogante quanto você, um jovem cheio de si.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Até parece, né.\n"+"Espera\n"+"Então você se vê nele? Ha-ha-ha. Então leve ele sob sua responsabilidade. Eu não vou ficar cuidando dele.";
				link.l1 = "Eu vou ficar de olho nele. Até você arrancar o couro dele. Mas pelo menos pelo âncora ele vai pagar direitinho.";
			}
			else
			{
				dialog.text = "Então você se viu nele? Ha-ha. Pois bem, capitão, então fique responsável por ele. Eu não vou ficar cuidando dele.";
				link.l1 = "Eu vou cuidar dele. Até vocês arrancarem o couro dele. Mas pelo âncora – ele que pague como deve ser.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Escolher a âncora. Esperar o vento. Manter o mesmo rumo.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Levantar âncora. Pegamos o vento. Rumo ao nordeste.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Ergam a âncora! Baixem o estai - vamos pegar o vento. Ao trabalho...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "O que você está fazendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "O que você está fazendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "Não, o que você está fazendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... O que você está fazendo? O marinheiro sênior repete as ordens do capitão.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "Então o marinheiro mais velho só repete o que eles dizem.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Deixa disso, Alonso. Somos só passageiros aqui. Esqueceu?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Hum... Desculpe, capitão. Não consegui me segurar\nMas valeu a pena. Foi como voltar ao passado.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... O que deseja?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "E aí, amigo, como você está se sentindo?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Admita, "+npchar.name+", você já tinha decidido virar comerciante quando resolveu se separar do Tirax, não foi?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Admita, "+npchar.name+", você já pensava em virar comerciante naquela época, lá na plantação?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Eu me lembro claramente de que um mensageiro tentou falar comigo. Mas, por mais que eu tente, não consigo lembrar sobre o quê. Você sabe de alguma coisa sobre isso?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Você já esteve em Bordeaux, capitão?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Capitão, pra falar a verdade, eu mal me lembro de como saímos da Martinica. Eu deveria receber uma correspondência importante de uma pessoa, mas parece que nunca chegou até mim. Ninguém procurou você sobre isso?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Parece que começou a soprar uma brisa leve. Hora de içar as velas. (Zarpar)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Ainda nada. Eu vou indo.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ha-ha... Como nunca antes! Cheio de energia e saúde.";
			link.l1 = "Sério? Mas você tá com uma cara de quem foi mastigado por um tubarão.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Olha quem fala. Você mesmo tá parecendo um cachorro surrado.";
			link.l1 = "E me sinto do mesmo jeito. Haha. Diabo, nem lembro como e quando zarpamos.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Ah, foi uma bela festa. Só que saiu cara pra diabo. Meus idiotas quase botaram fogo no bordel – tive que pagar um saco de moedas pra abafar o escândalo. Agora esses patetas vão me dever até o fim da vida\nE aí, como está sendo a vida de passageiro? Já começou a uivar de tédio?";
			link.l1 = "Tenho a sensação de que já não controlo mais o meu próprio destino. Mas, ao mesmo tempo, sinto um alívio estranho. Como se tivesse tirado dos ombros uma caixa cheia de balas de canhão.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ha-ha. Tudo bem, se a saudade apertar — estou pronto pra te aceitar como oficial no meu navio.";
			link.l1 = "Muito generoso da sua parte, mas vou ter que recusar. Não há rum suficiente em todo o Caribe pra bancar as nossas farras.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Não exatamente, camarada. Essa ideia já me passou pela cabeça de vez em quando, mas nunca dei muita atenção. Ela voltou pra mim de novo quando ouvi um boato — diziam que toda a turma fiel do Tirax sumiu sem deixar rastro. Todos eles — Facão, Careca, até aquele velho fedorento do Leprechaun.\nE quando fiquei sabendo do sucesso que você teve — aí decidi de vez que já deu pra mim. Não dá pra arriscar a cabeça por moedas pra sempre.\nTenho ouro suficiente pra nunca mais me curvar diante de nenhum canalha de peruca. Mas largar o mar... pra isso eu não estava pronto. Então resolvi mudar de vida.";
			} 
			else 
			{
				dialog.text = "Não exatamente, camarada. Essa ideia já me passou pela cabeça de vez em quando, mas nunca dei muita atenção. Ela voltou de vez quando ouvi um boato — diziam que toda a turma dos cães fiéis do Tirax sumiu sem deixar rastro. Todos eles — Facão, Careca, até aquele velho fedorento Leprechaun.\nE quando as balas inimigas quase arrancaram meus miolos duas vezes na mesma batalha, decidi de vez: chega pra mim. Não dá pra ficar arriscando a cabeça por moedas pra sempre.\nTenho ouro suficiente pra nunca me curvar diante de nenhum canalha de peruca. Mas deixar o mar... pra isso eu não estava pronto. Então resolvi mudar de vida.";
			}
			link.l1 = "Cutelo, Careca, Duende... Você sabe para onde eles foram?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "Não, não sei. E pra falar a verdade – não tô nem aí pra onde essas criaturas foram. Podiam muito bem ter sumido do mapa.";
			link.l1 = "Foi mais ou menos pra lá que eu os mandei.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "Então foi você quem acabou com toda a turma deles? Nossa! E o Marcus te perdoou por isso?";
			link.l1 = "Ele não sabe disso. E, provavelmente, nunca vai saber.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Então, diabos, eu saí deles na hora certa, haha. Vai ver, você também não teria poupado a minha cabeça\nSó tem uma coisa que eu não entendo – pra que diabos você precisava disso?";
			link.l1 = "Você estava certo – por um mísero pedaço de ouro, esses canalhas fariam qualquer coisa, trairiam, matariam quem fosse. Fomos atraídos para uma das masmorras no Sul do Main, com uma história inventada sobre tesouros incalculáveis. Era uma armadilha muito bem planejada, e aqueles malditos brutamontes caíram feito patos. Em vez de dividir o saque igualmente, decidiram que era melhor não compartilhar nada, me matar e ficar com tudo para eles.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "E não conseguiram nada, haha! Espera aí, mas quem foi que armou essa armadilha?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Um tal de Zorro, um justiceiro espanhol do povo – vingança por Cartagena. Quem tivesse sobrevivido àquele massacre deveria ficar nas masmorras para sempre – todas as saídas estavam trancadas. Mas o desgraçado não teve sorte – meu oficial enganou ele.";
			}
			else
			{
				link.l1 = "Um tal de Zorro, justiceiro popular espanhol – vingança por Cartagena. Quem conseguisse sobreviver àquele massacre infernal deveria ficar para sempre nas masmorras – todas as saídas estavam trancadas. Eu consegui escapar de lá. Mas a um preço altíssimo.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "Pelo menos você sobreviveu. E, imagino eu, pegou todo o ouro pelo qual quase pagou com a própria pele?";
			link.l1 = "Não havia ouro nenhum lá. Era só chumbo dourado...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Depois de tudo isso, decidi deixar o Tirax. Você é o primeiro a quem conto isso. Tirando meus oficiais.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "Não gosto de dizer 'eu avisei', mas... eu avisei.";
			link.l1 = "Parar na hora certa não é o meu forte. Então você vai ter que me dar umas aulas.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Você me conhece – por umas canecas de rum bom, eu até conto onde escondi meu ouro, hehe.";
			link.l1 = "Mas de mim, não espere tanta generosidade, ha-ha-ha. Já basta pra você o que tem nos seus estoques.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Está certo. Ele tentou te empurrar umas cartas — de um tal de Ben ou Benedito, sei lá. Só que você logo gritou que não conhecia nenhum Ben e ameaçou jogar ele pra fora da taverna se continuasse estragando nossa diversão.";
			link.l1 = "Diabo... Parece que eram cartas do abade Benoît. Cartas importantes.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Então, ainda bem que fui eu quem pegou. Hehe.  Senti no fundo que aquele garoto não errou de pessoa. Toma.";
			link.l1 = "Você me ajudou muito, "+npchar.name+", obrigado.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Um 'obrigado' só não basta, camarada. Você me deve uma bebida — e não qualquer uma, mas a melhor que se encontra em Bordeaux.";
			link.l1 = "Vai ter bebida pra você, mendigo. Nosso rum, claro, não se compara ao do Caribe, mas o vinho... Esse você com certeza nunca provou.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Não tive oportunidade...";
			link.l1 = "Invejo você. Gostaria de ver Bordeaux de novo, como da primeira vez. Provavelmente você prefere rum, mas ainda assim recomendo dar uma passada na feira de vinhos perto da prefeitura. Pelo nosso clarete, os conhecedores aqui no Caribe pagariam uma fortuna.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Obrigado pelo conselho. Posso fazer uma pergunta?";
			link.l1 = "Claro.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Como é ser passageira depois de tantos anos ao leme? Já se acostumou com essa nova situação?";
			link.l1 = "Hum... Não consigo me livrar da sensação de que já não controlo mais o meu próprio destino. Mas, ao mesmo tempo, sinto um alívio estranho. Como se tivesse tirado um baú de balas de canhão das costas. Acho que ainda é cedo pra tirar conclusões.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Considerando essa calmaria dos infernos em que a gente caiu tão convenientemente, vocês vão ter tempo de sobra.";
			link.l1 = "Com boa companhia, até a calmaria não pesa. E com a companhia, capitão, tenho que admitir, tive sorte.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Sim, veio um mensageiro de um tal abade. Sempre esqueço de lhe entregar essas cartas. Aqui, pegue.";
			link.l1 = "Excelente. Você me ajudou muito, capitão. Agradeço a você.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Você tem razão.";}
			else {dialog.text = "Você tem razão.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Vento pela amurada de estibordo! Iça tudo, da vela de proa à vela de popa! Avante toda!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Excelente lâmina, "+GetTitle(NPChar,true)+". Posso dar uma olhada?";
			link.l1 = "Talvez, em outra ocasião.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Quando vão tocar essas ampulhetas? Daqui a pouco eu engulo a língua.";
			link.l1 = "Paciência, marinheiro.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Viu o tamanho do rato que passou agora? Juro, nunca vi um tão grande na vida!";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "O que eu faço agora, monsieur? Bebi tanto que nem lembro como vim parar neste navio. Eu nem sou marinheiro... E em casa tenho esposa, dois filhos.";
			link.l1 = "Devia ter bebido menos. Agora já era – vai ter que virar marinheiro.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". É uma honra para nós tê-lo a bordo do nosso navio.";
			link.l1 = "Você é muito cortês, monsieur imediato. Cortesia não é a qualidade mais comum entre marinheiros experientes. Mas não vamos deixar a tripulação constrangida — não estamos na corte de Sua Majestade. Pode me chamar simplesmente de capitã.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Bem, eu só virei marinheiro há pouco tempo. Antes, eu era escrivão do senhor Levasseur. Mas quando ele foi... hã... eliminado, chegou um novo governador. Logo ficou famoso, entre os mais próximos, que o senhor de René de Baudoufle de Lestre era um canalha. Aí eu percebi: não ia mais conseguir trabalho decente. As pessoas iam achar que eu sabia de tudo – e fiquei calado.";
			link.l1 = "E não foi assim?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Claro que não. Nunca tive o hábito de me meter onde não sou chamada. Além disso, Levasseur punia severamente a curiosidade.";
			link.l1 = "Nisso eu acredito sem hesitar.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Então, depois que você resolveu aquele problema, eu me alistei como marinheiro no primeiro navio pirata que apareceu. E, por incrível que pareça, me adaptei rápido e mudei bastante. Até consegui conquistar o respeito dos mais perigosos canalhas. Mas o que eles faziam... Isso não era pra mim. Foi assim que vim parar aqui.";
			link.l1 = "Então, você sabia do meu envolvimento no destino do Levasseur?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Claro, capitão. E fico feliz que tenha livrado o mundo daquele monstro. De quebra, me tirou do meu quartinho abafado. Fez com que eu olhasse para minha vida de outro jeito.";
			link.l1 = "Incrível como o mundo é pequeno...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Pode parecer contraditório, mas o mundo é tão pequeno quanto é imenso.";
			link.l1 = "Engraçado. Nunca tinha pensado nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Capitão "+pchar.lastname+"... Que noite maravilhosa hoje, não acha?";
			link.l1 = "Talvez. Só um vento moderado vindo do noroeste poderia torná-lo ainda melhor.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Capitão "+pchar.lastname+"...";
				link.l1 = "Na verdade... Bem, não importa. Eu me lembro de você! Seu nome é Moko. Foi você quem secou um barril inteiro de rum de uma vez, não foi?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "O que você quer... monsieur?";
				link.l1 = "Não é todo dia que se vê um grandalhão assim. Qual é o seu nome?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Eu... E só acordei dois dias depois.";
			link.l1 = "Outro no seu lugar não teria durado nem duas horas. Se você luta tão bem quanto bebe – Jean teve uma sorte danada com o contramestre.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Assim como eu tive sorte com o capitão. Graças a ele, encontrei minha liberdade. E graças a você também. Eu teria apodrecido nas plantações se você não tivesse salvado o Jean.";
			link.l1 = "Foi uma aventura interessante. E fico feliz que tenha terminado melhor do que poderia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Eu sou o contramestre deste navio.";
			link.l1 = "Ha-ha, queria ver quem teria coragem de te desafiar. Faz tempo que serve ao capitão?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Alguns anos. Eu devo muito a ele. Se não fosse por ele, eu teria apodrecido na...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Você quis dizer - na plantação?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Deixa disso, "+npchar.name+", olha, você tem todo direito de não me contar nada, mas, caso ainda não tenha percebido, eu não sou dessas pessoas cheias de frescura e peruca. O capitão pagou o seu resgate?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Fugimos juntos. Da plantação em Maracaibo. Sem o Jean, nada teria dado certo. Desde então, faço parte da tripulação dele. Primeiro como marinheira, e agora - sou a contramestre.";
			link.l1 = "O capitão já foi escravizado? Nunca teria imaginado. Bem, eu também tenho meus próprios segredos. Fico feliz que você conseguiu escapar do jugo espanhol, "+npchar.name+". E então, como é ser marinheiro?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Parece que antes disso eu nem vivia. O mar é minha casa agora.";
			link.l1 = "Aqui eu te entendo, meu amigo. Como ninguém mais.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Capitão "+pchar.lastname+"... Como posso ajudar?";
			link.l1 = "Obrigado, "+npchar.name+", por enquanto não preciso de nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Como estou feliz por ver pelo menos um rosto sensato neste navio. Esses... marinheiros... são uns bárbaros.";
			link.l1 = "Se eu fosse você, não falaria assim no navio dos outros. Não sei como veio parar no Caribe, mas aqui, sabe, as regras são outras. Seria bom mostrar respeito pela tripulação.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Respeito? Por eles? Mas são selvagens! Eu sou um nobre, "+GetTitle(NPChar,true)+", eu estou acostumado com ordem, com serviço, com... civilização! Que só tentem me contrariar - meu pai vai...";
			link.l1 = "Seu pai vai saber que você morreu de febre no caminho. E dificilmente vai conseguir provar o contrário.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Maldito seja esse coronel Fox! Tudo por culpa dele! Por causa da filha dele atravessei o oceano, abri mão do conforto, aguentei esses olhares tortos, essa comida horrível, esse... balanço! E agora ainda estou viajando num navio de outra pessoa!";
			link.l1 = "Coronel Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Você o conhece, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Hum... Eu ouvi falar dele.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Então, quer dizer que você não perdeu muita coisa. Esse homem é a personificação da teimosia cega de soldado e dos preconceitos.";
			link.l1 = "Ele é militar...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Exatamente! E isso diz tudo. Quando fui pedir para encontrar a filha dele, sabe o que ele fez? Sabe? Me pôs pra fora! Sem dizer uma palavra!";
			link.l1 = "Mas pelo visto você não desistiu?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Claro! Passei uma semana tentando ser recebido! Me humilhei! Eu até... tentei subornar os guardas! No fim, consegui entrar até ele, sem convite. Só queria conversar!";
			link.l1 = "Não acho que ele tenha ficado feliz com isso.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Ficou feliz? Ah, ele fez um verdadeiro escândalo! Fui expulsa, proibida de chegar perto da residência, confiscaram o navio do meu pai e depois proibiram todos os capitães ingleses de me aceitarem a bordo! Tive que procurar um navio francês na Martinica... Foi um pesadelo.";
			link.l1 = "Parece que você o deixou bem irritado.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "Ele sempre foi contra mim. A frase favorita dele era: 'Filha de oficial, esposa de oficial'. Você, "+GetTitle(NPChar,true)+", ele achou uma opção muito mais adequada.";
			link.l1 = "Talvez, desta vez, ele tivesse outros motivos...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Então, você veio até aqui para ver sua amada.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Sim. Não recebi uma linha dela desde que deixou a Europa. Tenho certeza de que o pai dela simplesmente intercepta as cartas. Ela não poderia ter me esquecido! Claro, ela era reservada comigo... até fria... Mas não acredito que ela me apagou da vida dela.";
			link.l1 = "Sinto muito por você, monsieur. As feridas da alma são bem mais difíceis de curar do que as do corpo. Espere... Por que você, um inglês, está indo para Bordeaux?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Não pretendo voltar para casa envergonhado. Vou ter que ficar um tempo na casa do tio em Bordeaux, até que tudo se acalme. Aliás, a propriedade dele é bem mais espaçosa e elegante que a nossa. E os criados são mais bem treinados também.";
			link.l1 = "Bem, talvez essa não seja a pior saída. Quem sabe você até encontre outra pretendente por lá. Bordeaux está cheia de jovens encantadoras, pode acreditar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Quando vamos chegar, afinal, "+GetTitle(NPChar,true)+"? Eu sofro terrivelmente cercada por todos esses... cavalheiros. Eu simplesmente preciso urgentemente de um banho.";
			link.l1 = "Receio que, pelos próximos dois meses, só lhe resta sonhar com ela.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Maldito mar calmo, que o diabos leve esse marasmo.";
			link.l1 = "Não resmunga, "+npchar.name+", cedo ou tarde o vento vai soprar.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "E o que eu faço até lá, senhor? Nem posso fazer uma revisão dos canhões... Estamos num navio que nem é nosso.";
			link.l1 = "Tenta só relaxar um pouco. Não precisa trabalhar o tempo todo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Maldita calmaria...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Um bom navio, senhor capitão. O senhor também acha?";
			link.l1 = "Melhor até do que a Meifeng?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Para "+npchar.name+" não há navio melhor do que o Meifeng. Nenhum navio jamais vai cortar o vento tão bem quanto ele.";
			link.l1 = "Calma, "+npchar.name+", era só uma brincadeira. Claro, o Meifeng é imbatível. Mas o Ulisses também é um bom navio. Bem sólido.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" querer estar no leme. Sentir como o navio obedece à mão...";
			link.l1 = "Infelizmente, meu amigo, este navio não é nosso. Melhor sugerir àquele grandalhão ali que treinem esgrima juntos. Vai ser bom para vocês dois.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "Com que velocidade podemos ir, se o vento estiver a favor?";
			link.l1 = "Isso eu realmente não posso te dizer, "+npchar.name+". Melhor perguntar ao navegador deles.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Viu o tamanho do gigante que é o contramestre daqui? Dizem que ele consegue esmagar um coco com uma mão só.";
			link.l1 = "Ha-ha. E você, pelo visto, tem um certo receio dele, né?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Por que isso? Tamanho não é o mais importante. Já dei conta de coisas bem maiores.";
			link.l1 = "Então talvez você devesse propor uma luta justa, só vocês dois, um contra um.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "Você ficou meio pálido. Ha-ha. Bom, se não quer, tudo bem. Vamos poupar esses seus ossos que já não são tão jovens assim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "Nessas águas tem tanto peixe que dá pra pegar de balde, mas esses preguiçosos nem se deram ao trabalho de jogar a rede.";
			link.l1 = "Converse com o contramestre deles. Acho que ele vai gostar do seu comentário, hehe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "O ouro está seguro, capitão "+pchar.name+". Ensinei ao Tichingitu para protegê-lo bem.";
			link.l1 = "Obrigado, amigo. Alonso logo vai te substituir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Por todos os canhões, senhor, tem mais ratos nesse barco do que eu vi em toda a minha vida.";
			link.l1 = "O navio ficou muito tempo no porto, sem os devidos cuidados. A nova tripulação logo vai se livrar deles.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longwei ouvir barulho de corrente. Capitão jogou âncora?";
			link.l1 = "Foi o nosso passageiro que soltou o fusível. O vento ainda está bem fraco, mas espero que isso não dure muito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Sim, droga... Eu não recusaria uma caneca de rum forte agora.";
			link.l1 = "O jantar está quase pronto, tenha paciência. Alonso vai te substituir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", minha querida, como você está se sentindo?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Ah, querida, você ficou mesmo chateada comigo só porque fui até a loja comprar vinho?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "Foi comprar vinho? Você podia pelo menos ter avisado! Como eu vou saber que você não estava num bordel – com alguma… ou com todas de uma vez?!";
			link.l1 = "Querida, você acha mesmo que eu arriscaria tudo assim? Eu tenho a esposa mais bonita, inteligente e absurdamente ciumenta de todo o arquipélago. Acha mesmo que eu trocaria isso por umas garotas baratas de porto?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Você podia ao menos ter me dito alguma coisa, né! Eu fiquei lá sentada e…";
			link.l1 = "Prometo, da próxima vez não vou só te contar – vou te levar comigo. Agora… de repente fiquei curiosa, será que está tudo certo com os móveis da cabine do capitão? Principalmente com a cama. Vamos conferir?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... E se alguém entrar?\nHm... agora eu quero isso ainda mais.";
			link.l1 = "Então não vamos perder nem um segundo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", minha querida, como você está se sentindo?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Ah, querida, você ficou mesmo chateada comigo só porque fui até a loja comprar vinho?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Poderia ter me levado com você. Ou acha que eu teria feito pior do que suas parceiras?";
			link.l1 = "Acho que você ofuscaria todas elas sem esforço. Mas aí eu não pensaria em vinho nenhum.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "E sobre o quê?";
			link.l1 = "Pensar em ficar a sós com você bem ali... E essa ideia não sai da minha cabeça agora.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "É mesmo? E onde você pretende se esconder dos olhares curiosos?";
			link.l1 = "Na cabine do capitão. Acho que devemos testar a resistência da cama dele.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ha-ha. E se o capitão nos pegar?\nEmbora... só de pensar nisso meu coração já bate mais rápido.";
			link.l1 = "Então não vamos perder tempo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "Foi maravilhoso, meu capitão...\nTenho uma novidade para você.";
			link.l1 = "Notícia? Estou todo ouvidos.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... Nós vamos ter um filho. Eu estou grávida, né.";
			link.l1 = "Querida... É verdade?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Você vai ser pai, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... Isso é incrível!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Você está feliz, meu amor?";
			link.l1 = "Feliz? Você está brincando? Poxa, eu sou a pessoa mais feliz do mundo! Mas... por que você não me contou antes?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Para impedir a partida? Eu quero muito conhecer seu pai, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... Eu te amo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Você foi incrível, como sempre, querido. Tenho uma novidade pra você.";
			link.l1 = "Notícia? Estou todo ouvidos.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", chevalier de Monpe - você vai ser pai.";
			link.l1 = "Isso... isso é verdade?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "Tão verdade quanto o fato de que meu nome é "+npchar.name+". Dentro de no máximo meio ano teremos um filho – um pequeno monsieur de Mor... ou, talvez, uma mademoiselle.";
			link.l1 = "Helena... Isso é inacreditável!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "Então é por isso que você não quis beber com a gente para comemorar a partida! Mas... por que não me contou antes?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Eu tinha medo que você decidisse não se arriscar e ficasse no arquipélago. Eu queria que você atendesse ao pedido do seu pai. E também... eu mesma quero muito conhecê-lo.";
			link.l1 = ""+npchar.name+"… Eu te amo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Então… O que estamos fazendo aqui? Pequenos gascões?";
				link.l1 = "Ha-ha-ha! Eu vou ter um filho, "+npchar.name+"! Eu vou ser pai!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Você não acha que usar a cabine do capitão sem avisar o próprio capitão é um pouco demais, até mesmo para alguém do seu nível?";
				link.l1 = "Me desculpe, capitão. Mas eu tenho um bom motivo! Eu vou ser pai!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Ou filha!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "E você escondeu isso de mim, seu canalha? E eu achando que você era meu amigo!";
			link.l1 = "Acabei de descobrir! Você acredita? Eu! Vou! Ser! Pai!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ha-ha-ha! Você está mesmo feliz, meu amigo! Nunca te vi assim antes\nBom, continuem aí com o papo de vocês, vou preparar os canhões para a salva de comemoração. Me avise quando estiver pronto para dar a ordem.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ha... Acredite, eu já imaginava o motivo da sua visita.";
			link.l1 = "Claro que não! "+sld.name+" estou grávida! Vou ter um filho!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Ou filha!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Hum... Bem, meus parabéns de coração!\nVou mandar preparar uma salva de canhões em sua homenagem. Avise quando estiver pronto para dar a ordem.\nEnquanto isso... a cabine está à sua disposição.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ahã... Então, papai... Vejo que o senhor já quer providenciar outro herdeiro, é isso?";
				link.l1 = "Ha-ha! Se dependesse de mim, eu faria logo uma dúzia de uma vez! Então, camarada, vamos disparar com todos os canhões?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Receio que não funciona assim, meu amigo. Mas nós tentamos.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "E aí, capitão, vamos disparar todos os canhões?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Agora não.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "A tripulação está só esperando por isso! Dê a ordem, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "A tripulação está pronta. Dê as ordens.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Canhoneiros! Fogo de todos os canhões! Atirem!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Como estou feliz em te ver, filho!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Papai... Mal posso acreditar que estou em casa de novo... Já até tinha esquecido como é a neve. Parece que aqui não mudou nada...";
			}
			else
			{
				link.l1 = "Papai... Não acredito que estou em casa de novo... Parece até que a neve resolveu cair em minha homenagem. "+month+". Aqui não mudou absolutamente nada...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "Mas o mesmo não se pode dizer de você! Sua postura, seu jeito de andar, as cicatrizes\n"+"Não, diante de mim já não está mais aquele garoto mimado que eu despedi para terras distantes.";
			link.l1 = "Nas Caraíbas a gente amadurece rápido, pai. Mas ainda teremos tempo pra falar disso. Conte, como está sua saúde? Espero que a doença tenha recuado, já que o senhor está aqui diante de mim todo equipado pra batalha?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Infelizmente, "+pchar.name+", ela só apertou ainda mais meu pescoço. Mas como eu poderia encontrar meu filho querido vestindo algo comum? Para mim, hoje é um grande dia, "+pchar.name+"\n"+"Parece que você tem alguém para me apresentar.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Infelizmente, "+pchar.name+", o seu aperto só fica mais forte com o passar dos anos. Mas será que eu poderia encontrar meu amado filho vestindo roupas comuns? Para mim, hoje é um grande dia, "+pchar.name+"\n"+"Vejo que você não veio sozinho\n"+"Você deve estar com fome depois da viagem? Suzanne preparou fígado de ganso do seu jeito favorito!\n"+"Venha à mesa – no caminho você pode nos apresentar!";
				link.l1 = "Confesso, senti esse aroma já quando estava chegando à propriedade!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Papai, permita-me apresentar minha esposa - "+sld.name+" "+pchar.lastname+". "+sld.name+", este é meu pai - o chevalier "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", estou encantado! Sua escolhida não se parece em nada com as damas mimadas da alta sociedade às quais estamos acostumados aqui. Ouso supor que ela conduz um navio com a mesma confiança com que conduz o coração do meu filho.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "É uma grande felicidade para mim conhecê-la, madame. Posso lhe assegurar, meu filho tem um gosto excelente!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "Estou lisonjeada, chevalier! O senhor tem razão, eu realmente sou capaz de segurar o leme até mesmo na pior tempestade. Mas quanto ao coração do seu filho — não há necessidade de comandá-lo. Estamos unidos nos nossos objetivos e desejos.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "O abade Benoît descreveu você como uma moça sábia e corajosa — e parece que ele não exagerou. Estou feliz que "+pchar.name+" encontrei em você não só uma esposa, mas uma companheira de alma igual à minha\n"+"Você deve estar com fome depois da viagem? Suzanne preparou fígado de ganso do seu jeito favorito!\n"+"Pois bem, convido todos à mesa! E espero que, no caminho, possamos nos conhecer melhor.";
			link.l1 = "Confesso, senti esse aroma já quando estava chegando na propriedade!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "É um prazer conhecê-lo, chevalier! "+pchar.name+" falaram muito sobre você, e eu imaginava você exatamente assim, viu!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", estou encantado! Sua escolhida não lembra nem um pouco aquelas damas da alta sociedade cheias de pó — e é nisso que está seu verdadeiro valor\n"+"Me parece que você escolheu uma bela rosa em vez de lírios mimados e caprichosos.";
			link.l1 = "A rosa selvagem, pai... "+sld.name+"  - um verdadeiro tesouro. Tenho certeza de que você vai concordar comigo quando conhecê-la melhor.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "Então não vamos adiar esse momento! Você deve estar com fome depois da viagem, não é? A Suzana preparou fígado de ganso do seu jeito favorito!\n"+"Convido todos à mesa! E no caminho, espero que "+sStr+"";
			link.l1 = "Confesso, senti esse aroma já quando estava chegando na propriedade!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Querida, você simplesmente precisa experimentar isso – nada se compara ao fígado de ganso preparado com a nossa receita de família! Ela veio do vovô – e ele ganhou como presente de um país do Mediterrâneo.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Não gostaria de começar a festa com tristeza, mas nós, como família, devemos lembrar daqueles que partiram antes de nós. Peço que levantem seus copos por Michel. Que Deus conceda paz à sua alma.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Eu tenho tanta coisa pra te perguntar, "+pchar.name+"... Mas antes, permita que sua esposa fale e "+sStr+". Por favor, conte-me como conheceu Charles.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Eu tenho tanta coisa pra te perguntar, "+pchar.name+"... Mas antes, deixe-me ouvir "+sStr+". Por favor, conte-me como conheceu Charles.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "Estou tão ansioso quanto você para ouvir isso!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Eu estive em perigo de morte... "+pchar.name+", como um verdadeiro cavalheiro, não deixou que nada de ruim acontecesse! Ele me defendeu e acabou com aqueles canalhas, né!";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" me tirou das mãos de um canalha inglês que teve a ousadia de... me sequestrar. Se tivesse chegado só uma hora depois, nunca teríamos nos conhecido.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Eu não duvidei que ele agiria como um verdadeiro nobre. Honra não é só uma palavra para a nossa família. Tenho orgulho de você, filho.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" invadir a casa do cara pálida para achar comida. O cara pálida pegou "+sld.name+" - e mandar para a prisão. Capitão "+pchar.name+" vir, resgatar "+sld.name+" da prisão. Desde então "+sld.name+" servir o capitão "+pchar.name+" e ser fiel até o último suspiro.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "É reconfortante saber que meu filho não é apenas um nobre de sangue, mas também um homem de bom coração. Fico feliz que ele tenha ao seu lado amigos tão leais como vocês, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "O capitão apareceu um dia na minha casa — procurando trabalho. Dei uma tarefa pra ele, e ele cumpriu direitinho. O chefe gostou dele, foi envolvendo cada vez mais o capitão nos seus assuntos, e me mandou pro navio dele — pra ficar de olho... E aí esse... sujeito simplesmente levantou âncora, que o diabo o carregue, e deixou o arquipélago sem dizer uma palavra ao capitão. Largou ele sozinho na confusão que ele mesmo criou. Ofereci minha ajuda ao capitão e, mesmo que Richard tenha sido um canalha com ele, que o diabo leve esse infeliz, o capitão não me mandou embora.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longwei e o senhor capitão trabalhavam para a mesma pessoa. Mas essa pessoa traiu Longwei. Então Longwei decidiu: não vai mais servir essa pessoa. O senhor capitão me levou para o navio dele, como oficial, e fez muito por Longwei.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Foi na taverna de Bridgetown que nos encontramos pela primeira vez: "+pchar.name+" estava procurando um trabalho, e eu - alguém de confiança para executá-lo. Esse encontro foi só o começo - depois vieram acontecimentos que entrelaçaram nossos caminhos. Tornei-me seu oficial, e agora posso chamá-lo de amigo sem hesitar - um homem por quem eu arriscaria a vida.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Enxergar a pessoa por trás das circunstâncias é uma habilidade rara. Isso, talvez, mostre que meu filho não é desprovido de bom senso.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Fico feliz que meu filho não seja um militar insensível, mas sim um verdadeiro comandante, que sabe cuidar dos seus companheiros.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Não é todo dia que se ouvem palavras assim. Acho que isso é a melhor prova de que meu filho não é só um marinheiro habilidoso, mas também um bom amigo.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Nos conhecemos em Bordeaux. O capitão embarcou no nosso navio como passageiro e nós o levamos até Martinica. Desde então – até a partida para cá – continuei sendo a voz da sua tripulação e observei como "+GetFullName(pchar)+" passo a passo, foi se tornando quem é agora.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Então, você conheceu o Charles ainda como aquele garoto insuportável que, por minha insistência, deixou a casa da família? Creio, monsieur, que teremos muito sobre o que conversar.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Meu querido "+pchar.name+", você percorreu um caminho longo e glorioso... Partiu para a savana selvagem atrás de uma simples pele de coelho, mas enfrentou um leão e voltou triunfante, trazendo sua pele sobre os ombros. Agora, mais do que nunca, estou tranquilo quanto ao destino de nossa propriedade e de todas as nossas terras.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "Mal posso esperar para te passar o comando de todos os assuntos da nossa família. Teremos muito trabalho pela frente, mas acredito que o próprio Senhor olha para você com bênçãos, e que você não só vai preservar o legado que te confio, mas também aumentar a honra e a prosperidade da família de Monpe.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "É uma grande honra para mim ser seu filho e herdeiro. Com alegria, assumo todas as responsabilidades pela nossa família. Tenho certeza de que minha esposa será meu apoio fiel nisso. Prometo fazer tudo ao meu alcance para engrandecer ainda mais nosso nome... E a primeira contribuição para o nosso futuro será o nascimento de uma criança!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "É uma grande honra para mim ser seu filho e herdeiro. Com alegria assumo todas as responsabilidades pela nossa família e prometo fazer tudo ao meu alcance para engrandecer ainda mais o nosso nome.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Papai, os anos no Novo Mundo me mudaram. Receio que não vou mais conseguir me adaptar ao ritmo tranquilo da vida aqui na Europa.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", não é possível...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Sim, pai. "+sld.name+" grávida.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "São realmente grandes notícias, meu querido filho! Deus ouviu minhas preces! Que todos aqui presentes sejam testemunhas: em homenagem ao recém-nascido, darei o baile mais grandioso que nossa propriedade já viu! Vamos erguer nossos copos — ao herdeiro!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Ou uma herdeira!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "Por um novo capítulo na história da nossa família!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "Pelo futuro guerreiro ou pela boa filha!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Pela saúde forte do bebê!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Por esse acaso que uniu vocês!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Pelo futuro brilhante da sua família!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "Pelo futuro de Alonso de Mor ou da Alonsita de Mor!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ah-haha!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ha-ha-ha!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "Para mim é uma grande honra ser seu filho e herdeiro. Com alegria assumo todas as responsabilidades pela nossa família e prometo fazer tudo ao meu alcance para engrandecer ainda mais o nome da nossa casa.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Me diga, "+pchar.name+", você pensou sobre a minha proposta de se casar com Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Eu confesso, pai... Yvonne nunca foi próxima do meu coração. Mas no Novo Mundo há muitas moças encantadoras. Prometo ao senhor – quando encontrar uma digna, não vou hesitar.";
			}
			else
			{
				link.l1 = "Eu confesso, pai... Yvonne nunca foi próxima do meu coração. Mas há muitas moças encantadoras na França. Prometo ao senhor – quando encontrar uma digna, não vou hesitar.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Gosto do seu espírito, meu querido filho. Vamos erguer nossos copos – por você, por suas conquistas e por um retorno digno ao lar!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Aos verdadeiros amigos, sem os quais não se sobrevive no Novo Mundo!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "Pelo grande coração do capitão Charles!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Pela vontade de ferro do capitão!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Pela sabedoria do senhor capitão!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Pela dedicação à causa!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "Pela habilidade de sair ileso de qualquer situação!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "Ouvi dizer que você insistiu bastante para conseguir uma audiência. Então, o que deseja do governador da Martinica?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Quero falar sobre trabalhar para o bem da coroa da França.";
			link.l1 = "Sim, eu tenho uma missão para você, que vai exigir toda a sua agilidade e habilidade em combate naval. Está pronto para se mostrar?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Sua Alteza, poderia explicar com mais detalhes a essência da missão que está por vir?";
			link.l1 = "Claro. Você precisa encontrar o navio-correio espanhol chamado 'Santa Esperanza', abordá-lo e trazer para mim os documentos que encontrar na cabine do capitão. O navio que mencionei deve passar por Trinidad em cerca de doze dias.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "Tá bom, eu aceito essa tarefa. Mas que documentos eu devo procurar?";
			link.l1 = "A correspondência postal. Lá, entre outras coisas, vão estar documentos muito importantes para mim. Mas você não precisa mexer nos papéis, é só me entregar o pacote inteiro. Por esse serviço, vou lhe pagar quinze mil pesos... Então, estarei esperando você na minha residência com o resultado do trabalho.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Acredito que não vou fazê-lo esperar muito, Sua Alteza.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Vossa Excelência... Permita-me fazer um relatório?";
			link.l1 = "Relate, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Hum-hum...";
			link.l1 = "Pode falar à vontade. Não tenho segredos da minha esposa.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "A inteligência informa: uma esquadra partiu de Willemstad. À frente está o navio de linha de segunda classe ‘Gouden Leeuw’, um verdadeiro monstro do mar. O poder total da esquadra é de mais de duzentos e cinquenta canhões e mais de mil e quinhentos soldados. O alvo deles é Saint-Pierre.";
			link.l1 = "Hum... Então, praticamente não temos tempo nenhum para nos prepararmos.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Como vamos proceder, senhor governador?";
			link.l1 = "Temos alguns navios na nossa ancoragem que podem atacar o inimigo por trás...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Você pretende atacar eles pelos dois lados?";
			link.l1 = "Exato. O forte vai atrair o fogo para si. E quando anoitecer, a esquadra sob meu comando vai atacar pelo mar. Vamos dispersar a atenção deles, e então do porto sairão brulotes carregados de piche e tábuas. Da frota deles não vai sobrar nem lasca.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Excelente plano, Sua Alteza! Permite-me dar a ordem para iniciar os preparativos?";
			link.l1 = "Comecem. E que o Senhor esteja conosco.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Guarda, chame o Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Senhor governador...";
				link.l1 = ""+npchar.name+", uma esquadra holandesa vai chegar aqui a qualquer momento e começar o cerco. Ouça a ordem: leve Philippe e "+sld.name+", e leve-os imediatamente ao abade. Que ele reúna todas as mulheres, crianças e idosos e cuide da segurança deles.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Senhor governador...";
			link.l1 = ""+npchar.name+", uma esquadra holandesa deve chegar a qualquer momento e cercar a cidade. Avise o abade para reunir todas as mulheres, crianças e idosos, e garantir a segurança deles. Quanto a você, pretendo te confiar o comando de um brulote. Os detalhes depois. O mais importante agora é proteger os civis.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Não acho que "+sld.name+" vai concordar em se juntar às outras mulheres. Ela está morrendo de tédio.";
			link.l1 = "Hum... Então diga a ela: que se prepare para a luta. Você também não vai ficar de braços cruzados – vai comandar o brulote. Os detalhes depois. Agora — cuide do meu filho.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "Será uma honra! Permite-me cumprir?";
			link.l1 = "Eu permito. Vá em frente. Cada segundo conta para nós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Bem... Admito que já esperava que você dissesse isso – mas ainda assim tinha esperança de ouvir outra resposta. Mas respeito sua escolha e não vou insistir.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Eu entendo que decepcionei você. Mas tenho uma novidade que, espero, vai superar tudo o que foi dito antes.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Estou todo ouvidos.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Vou ficar aqui por pelo menos um ano. "+sld.name+" na situação dela, o balanço do navio é totalmente contraindicado.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", não é possível...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Bem... Admito que já esperava que você dissesse isso – mas ainda assim tinha esperança de ouvir outra resposta. Respeito sua decisão e não vou insistir. Mas me diga, "+pchar.name+", você pensou sobre a minha proposta de se casar com Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Não conseguiu se segurar, né?";
			link.l1 = "Você?! Isso é um sonho?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "Sede de lucro fácil, poder, ilusão de invulnerabilidade... O que foi que te perdeu, irmão? O que ofuscou tua razão, como ofusca a mente de todos os rostos-pálidos?";
			link.l1 = "Vai embora! Você é só um fantasma! Você não está aqui!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Então você ainda não entendeu? Spectra sunt memoria peccatorum. É você quem é o fantasma... A lenda caribenha de um homem devorado pela ganância e pela vaidade cega. Quantos você matou por ouro, "+pchar.name+"?";
			link.l1 = "Pois bem, meu caro irmão, não me importo de te matar pela segunda vez! Você mesmo pediu por isso!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}