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
		
		case "Sailor_1":
			dialog.text = "O que você quer, "+GetSexPhrase("amigo","moça")+"? Se você está me oferecendo um pouco de rum, não vou recusar. Já dei tantas voltas nessa cidade maldita que minhas pernas estão quase se enrolando. E qual é o seu nome, então?";
			link.l1 = "Capitão "+GetFullName(pchar)+". Você não é do 'Eagle', é?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "E eu - "+GetFullName(npchar)+". E sim, eu sou do 'Eagle'. Gosta do nosso navio, capitão?";
			}
			else
			{
				dialog.text = "Capitão? Ora, ora... Hum... Eu sou Antonio Velenta. E sim, sou do 'Eagle'. Nosso navio chamou sua atenção, Capitão?";
			}
			link.l1 = "Navio é navio. É melhor você embarcar logo em vez de ficar vagando pela cidade—seu capitão já está soltando fumaça. Ele quer zarpar antes da maré baixar, e algo me diz, rapaz, que ele não vai esperar por você.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Droga... Eu sei, eu sei... Mas ainda tenho uns assuntos pendentes nesta cidade. Que tal ganhar uns dobrões, hein, Capitão?";
			link.l1 = "Doublões nunca são mal-vindos. Mas ganhar dinheiro é uma coisa, se meter em encrenca é outra. Qual é o trabalho? Fala logo.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Veja, enquanto eu descarregava o porão, acabei encontrando uma carta. Não parecia que ela tinha sido escondida de propósito, só estava ali entre uns barris velhos. Nosso fluyt já passou por mais de uma abordagem, então é impossível saber de onde ela veio.";
			link.l1 = "Então você encontrou a carta, mas e daí?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "É endereçada a uma tal de Marisa Caldera, de Porto Bello. Selada com cera... Sinto aqui dentro – não é coisa pouca. Pode ser de um capitão, talvez de um comerciante... mas com certeza não é de um marinheiro comum como eu! Só que não vou ter tempo de encontrar a destinatária – nosso capitão não gosta nem um pouco de brincadeiras.  Não quer comprar de mim? Te passo por mil pesos. Você é capitão, não vai ser difícil encontrar essa senhorita. E vai saber, talvez ela te recompense com ouro, ou com outra coisa... se é que me entende?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Então, talvez eu encontre sua Marisa.  De qualquer forma, não tenho nada a perder. Exceto mil pesos. Entregue a carta.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "Desculpe, mas você vai ter que procurar outra pessoa. Tenho coisas mais importantes pra fazer do que entregar cartas.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Aqui está. Bom, se cuida, "+GetSexPhrase("companheiro","moça")+", eu devo ir – não quero que meus pertences zarparem junto com o 'Eagle'.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Quem é você? O que você quer?";
			link.l1 = "Meu nome é Capitão "+GetFullName(pchar)+". Estou procurando por Marisa Caldera.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Eu não conheço nenhuma Marisa. Você bateu na porta errada. Saia agora antes que eu chame os guardas – eles vão te expulsar rapidinho.";
			link.l1 = "Pai "+sld.name+" me disse que você é amiga dela. Tenho uma carta endereçada a ela. Pelo estado dela, está muito atrasada. Quero entregá-la pessoalmente.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ah, pai... Ele é bondoso com todos, mas raramente se engana sobre as pessoas. Pode deixar a carta comigo. Vou garantir que ela chegue até ela.";
			link.l1 = "Me perdoe, señorita, mas eu prefiro entregar pessoalmente. Ela pode querer saber como consegui isso e por que demorou tanto para chegar.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "E você espera que eu simplesmente acredite nas suas boas intenções? Já vi muitos canalhas com cara de santo. Deixe a carta ou siga seu caminho.";
			link.l1 = "Dou-lhe minha palavra de capitão de que não farei mal nem a você nem à Marisa. Além disso, pode chamar o guarda ou qualquer outra pessoa habilidosa com armas para a nossa reunião. Meu único objetivo é entregar esta carta pessoalmente à Marisa.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "Certo. Passe aqui amanhã depois das onze da noite. Não posso prometer que ela vai querer te encontrar, mas vou contar tudo o que você disse.";
			link.l1 = "Eu estarei lá. Até logo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Olá, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Você estava me procurando, e aqui estou. A Dolores disse que você tem uma carta para mim?";
			link.l1 = "Bom dia, dona Caldera. Isso mesmo, aqui está. Infelizmente, parece que demorou bastante para chegar até você.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... Esta é a letra dele... A letra do Ramiro!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Mas como isso é possível? Já se passaram dois anos!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitão... Como você conseguiu isso? Onde encontrou? Eu preciso saber de tudo! Por favor, me conte tudo o que souber.";
			link.l1 = "Esta carta chegou até mim por um marinheiro. Ele a encontrou em um canto escuro do porão do navio e queria entregá-la pessoalmente a você, mas foi obrigado a voltar às pressas para sua embarcação. Então ele me pediu para encontrá-lo, e aqui estou. Isso é tudo que eu sei...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Obrigado, "+GetAddress_Form(NPChar)+"! Muito obrigado! Por favor, não vá. Quero conversar mais com você, mas antes... preciso ler esta carta.";
			link.l1 = "Claro, Lady Caldera. Estarei aqui.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Twenty minutes passed, Marisa read the letter...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Ele escreveu esta carta antes da última viagem. Queria me contar que teve a chance de comprar uma grande carga de ébano de um comerciante em Belize, mas não tinha dinheiro suficiente. Foi aí que ele pegou esse empréstimo... Duzentos dobrões... Por causa disso, agora não consigo ter paz.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Isso explica tudo... Mas, infelizmente, isso não vai aliviar seu fardo. Seja forte, Marisa. A escuridão não é eterna, e essa dívida não vai te assombrar para sempre.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Não, Dolores, não vai ter! Ramiro escreveu que tem um dinheiro guardado... no nosso lugar. Se ainda estiver lá, talvez eu consiga pagar a dívida e finalmente fugir desse pesadelo.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "O Senhor teve misericórdia de você! Ele ouviu nossas preces...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Capitão, mais uma vez, obrigada por me trazer esta carta. Significa tudo para mim... Mas preciso lhe pedir mais um favor. Veja, meu marido Ramiro era tudo para mim, e nunca busquei proteção em outro homem. Agora que ele se foi, não tenho mais ninguém, nenhuma família minha\nPreciso chegar ao esconderijo dele – fica fora da cidade. Mas tenho muito medo de ir sozinha, os credores do meu falecido marido estão atrás de mim. Você agiu com honra ao me encontrar para entregar a carta... Por favor, me ajude mais uma vez.";
			link.l1 = "Claro, Marisa, eu te acompanho. Quando você gostaria de partir?";
			link.l1.go = "Marisa_16";
			link.l2 = "Me desculpe, senhora, mas minha estadia na sua cidade já se prolongou demais. Passeios pelo campo não fazem parte dos meus planos.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Eu entendo... Você já fez mais por mim do que eu poderia esperar. Obrigado, Capitão, e adeus.";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Obrigado, Capitão. Venha amanhã ao amanhecer, por volta das sete horas. Estarei pronto.";
			link.l1 = "Então até a próxima, senhora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, aí está você... É realmente um homem de honra! Vamos partir. Nosso caminho segue pela selva até a gruta, não muito longe da Baía dos Mosquitos.";
				}
				else
				{
					dialog.text = "Capitã, aí está você... Eu sabia que viria. Sabe, é a primeira vez que conheço uma mulher que comanda seu próprio navio. E já posso ver que você não fica atrás de nenhum homem—nem em honra, nem em nobreza!";
				}
				link.l1 = "Excelente, senhora. Então não vamos perder tempo. Fique perto e não se afaste nem por um instante.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Obrigada, Marisa. Meu pai foi capitão e um homem de honra – desde criança ele me ensinou esses mesmos valores.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Venha ao amanhecer, por volta das sete horas. Estarei pronto.";
				link.l1 = "Até logo, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Foi mesmo? Ele teve o mesmo destino que o meu Ramiro?";
			link.l1 = "Com certeza ele teria preferido encontrar seu fim com uma espada na mão ou no meio de uma tempestade. Mas o destino quis diferente – foi levado por uma doença sobre a qual nunca falou com ninguém.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Sinto muito pela sua perda, "+pchar.name+" O Senhor leva os melhores entre nós... E mesmo que nem sempre entendamos o motivo, é a vontade Dele. Só nos resta rezar pelo descanso de suas almas imortais.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Vamos seguir em frente. Nosso caminho passa pela selva até a gruta, não muito longe da Baía dos Mosquitos.";
			link.l1 = "Claro. Fique perto e não se afaste nem por um instante.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Aqui estamos... Ramiro e eu já nos abrigamos da chuva aqui, quando éramos jovens, antes de ele se tornar meu marido. Foi então que ele me disse que conquistaria meu coração, custasse o que custasse.";
			link.l1 = "Sinto muito que a senhora tenha vindo aqui sozinha, sem seu marido. Lugares assim guardam muitas lembranças. Vamos dar uma olhada – talvez, além das memórias, a gente encontre o que Ramiro guardou para os momentos mais difíceis.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Senhor "+pchar.lastname+"",""+pchar.name+"")+"... Você encontrou alguma coisa? É o que o Ramiro deixou para trás? Nem sei o que me assusta mais – se está vazio, ou se não vai ser suficiente para pagar a dívida...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(mostra) Aqui, isso é tudo o que estava no baú. Espero que seja o bastante para mudar seu destino para melhor.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Ainda estou procurando no baú.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Capitão! Claro! Isso deve ser o suficiente! Mas não posso deixar sua ajuda sem recompensa. Pegue cem dobrões. Se não fosse por você, eu nunca teria descoberto esse esconderijo e ainda estaria me escondendo dos homens enviados pelo credor do Ramiro...";
			link.l1 = "Você é muito generosa, senhora, obrigada. No nosso ramo, ouro nunca é desperdiçado.";
			link.l1.go = "Marisa_34";
			link.l2 = "Não, senhora. Você precisa desse dinheiro muito mais do que eu. O que importa é que agora pode deixar seus problemas para trás e viver em paz. Isso já é mais do que suficiente para mim.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Given: Amulet 'Cimaruta'", "None");
			notification("Given: Amulet 'Fisherman'", "None");
			notification("Given: Matchlock Musket", "None");
			notification("Given: Diamond (10)", "None");
			notification("Given: Ruby (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Então, "+GetSexPhrase("senhor",""+pchar.name+"")+", é melhor a gente ir andando. Se me viram na cidade, pode ter alguém nos seguindo. Melhor não ficar aqui por muito tempo.";
			link.l1 = "Você tem razão, Marisa. Vamos.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Capitão, por favor... meu marido guardava essa arma para proteger nossa família, e tenho certeza de que—em suas mãos—ela servirá a uma causa justa. Ramiro ficaria feliz em saber que ela foi para a pessoa que me salvou quando toda esperança havia se perdido.";
			link.l1 = "Certo, Marisa, obrigado. Você é uma mulher bondosa e honrada, e lamento de verdade que o destino tenha sido tão cruel com você.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Às vezes o Senhor nos envia dias difíceis, ou até anos, para testar nossa fé, mas Ele nunca abandona quem segue o caminho certo. Ele mandou você para me ajudar e agora, espero, meu maior problema logo ficará para trás.\nMas por enquanto, está na hora de voltarmos. Já ficamos aqui tempo demais, e pode ser perigoso, já que ainda estão me procurando.";
			link.l1 = "Claro, senhora, vamos.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha! Então aqui está o nosso desaparecido! Você realmente achou que podia se esconder aqui, nesse buraco feito um rato, e que eu não ia te encontrar? Já revirei a cidade inteira mais de uma vez, e você estava aqui o tempo todo"+GetSexPhrase(", e além disso, você saiu com algum moleque. Cadê o meu dinheiro, sua vadiazinha? É melhor entregar agora, ou essa caverna vai ser sua sepultura.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Você...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Então é você quem ganha a vida extorquindo mulheres por dívidas? Pelo tipo de trabalho que escolheu, inteligência nunca foi o seu ponto forte. É até espantoso que tenha conseguido chegar aqui sozinho, em vez de só seguir alguém mais esperto... como a sua própria bota, por exemplo.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Cale a boca, herói. Sua hora vai chegar, mas primeiro eu resolvo com ela. Ela deve quinhentos e vinte e cinco dobrões – é a dívida dela com juros. Ou paga tudo, ou fica aqui pra sempre – pra virar comida de verme. Mas já que você é tão certinho, pode pagar por ela, e eu vou embora.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Você acha que pode simplesmente entrar, insultar uma dama, me ignorar e sair daqui inteiro, ainda por cima com os dobrões? Parece que você não é dos mais espertos. Mas não vou arrumar confusão na frente de uma mulher. Então aqui está minha proposta: peça desculpas à Madame Caldera, pegue seus dobrões e caia fora daqui. Ou vou ter que te ensinar boas maneiras, afinal.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "Cale a boca e espere a sua vez. Vou cuidar de você depois, quando terminar com essa desgraçada. Ela deve quinhentos e vinte e cinco dobrões – essa é a dívida dela com os juros. Já que você é tão justo, pode pagar por ela, e eu vou embora.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Olha, estou disposto a relevar seu jeito grosseiro e até sua falta de educação comigo. Mas se quiser pegar seus dobrões e sair daqui inteiro, vai ter que pedir desculpas à Lady Caldera. Caso contrário, vamos ver quem sabe usar uma arma melhor. E pode acreditar, eu não carrego a minha só pra enfeite.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "Está claro que você não é lá muito esperto se achou que eu ia esperar minha vez. E menos ainda se pensou que eu ia fingir que não vi toda a confusão que você e os seus causaram à Lady Caldera.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Muito bem, faça do seu jeito. Se conseguirmos o dinheiro sem correr riscos desnecessários, não vejo motivo para me arriscar à toa. Entregue os dobrões – e suma daqui.";
			link.l1 = "Primeiro, peça desculpas à dama.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Me perdoe, senhora. O diabo falou mais alto do que eu.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Feliz"+GetSexPhrase("","")+"? Entregue o ouro e eu vou embora. Tenho muito o que fazer, não tenho tempo pra ficar aqui trocando gentilezas com você.";
			link.l1 = "Pegue seus dobrões e saia daqui.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Capitão, sinceramente, eu não entendo... O que isso significa?";
			link.l1 = "Isso significa que você não deve mais nada. Você está livre.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Mas... eu não tenho todo o dinheiro para te pagar agora. Se você puder esperar um pouco...";
			link.l1 = "Você não entende, Marisa. Você não me deve nada. Você não deve mais nada a ninguém. E o dinheiro que você encontrou vai ser muito útil pra você. Volte pra sua antiga vida – a igreja está te esperando.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Eu... Eu simplesmente não consigo acreditar. Coisas assim não acontecem, "+GetSexPhrase("caballero","senhorita")+"! Você pagou uma fortuna por mim... assim, do nada? E agora acabou tudo? Sem dívida, sem perseguição? Me diga, é verdade?";
			link.l1 = "É verdade, senhora. Acabou tudo. Você não deve mais nada a ninguém.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Oh, Capitão, você é tão nobre! Sinto como se tivesse sido enviado por Deus! Mas eu nem sei como agradecer. Você... mudou minha vida completamente, e eu... o que eu poderia fazer por você?";
			link.l1 = "Você não precisa fazer nada, Marisa. Apenas viva. Sem medo, sem as correntes do passado. Volte para a sua antiga vida e encontre felicidade nela – esse será o melhor jeito de me agradecer. Venha, eu te acompanho até a cidade.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "O que você fez, Capitão, você o matou!";
			link.l1 = "É isso mesmo, senhora. Eu precisava proteger você e sua honra...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Oh, Capitão, tirar uma vida, mesmo a de alguém como ele, é um pecado terrível e pesado! Você vai ter que rezar dia e noite para tentar lavar ao menos um pouco disso da sua alma imortal. Deus é minha testemunha, eu poderia simplesmente ter dado tudo o que tinha e ele teria ido embora... Mas agora... agora o sangue dele está nas suas mãos, e só os céus vão decidir se você será perdoado!";
			link.l1 = "Talvez tenha sido a vontade do Senhor. Mas vamos deixar isso pra lá. Vamos sair desta caverna.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Capitão, permita-me agradecer mais uma vez! Vou rezar pela sua saúde e bem-estar, "+pchar.name+". Por favor, venha à nossa igreja – que o Senhor lhe conceda o perdão por todos os seus pecados e a Sua bênção.";
			link.l1 = "Talvez eu apareça por lá qualquer hora. E lembre-se, Marisa, se eu não vir seu rostinho feliz lá, vou ficar muito decepcionado.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Você é tão gentil comigo. Vou ficar realmente feliz em te ver de novo na nossa cidade. Mas, por agora, me perdoe, mal posso esperar para colocar minha vida em ordem e compartilhar as boas notícias com a Dolores.";
			link.l1 = "Claro, Marisa. Adeus. Cuide-se.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Capitão, permita-me mais uma vez expressar minha eterna gratidão! Você fez o impossível por mim! Pela sua bondade e nobreza, quero lhe contar como consegui escapar dos mercenários nesses últimos dois anos. Talvez esse conhecimento um dia também lhe seja útil.";
			link.l1 = "Obrigada, senhora. Em casos assim, conhecimento vale tanto quanto ouro. Estou ouvindo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "Foi assim que passei esses dois anos. Num mundo onde a força vale tanto, saber se manter nas sombras abre oportunidades com as quais outros só podem sonhar.";
			link.l1 = "Obrigada por compartilhar sua história, Marisa. Você passou por muita coisa, e sua experiência realmente não tem preço.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Ficarei realmente feliz em vê-lo novamente em nossa cidade. Por favor, venha à nossa igreja—que o Senhor lhe conceda o perdão por todos os seus pecados e a Sua bênção.";
			link.l1 = "Talvez eu apareça por lá algum dia. E lembre-se, Marisa, se eu não vir seu rosto sorridente lá, vou ficar muito decepcionado.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Capitão... Você é tão gentil comigo. Mas agora, me perdoe, mal posso esperar para colocar minha vida em ordem e compartilhar as boas notícias com a Dolores.";
			link.l1 = "Claro, Marisa. Adeus. Cuide-se.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Did you hear? Captain "+GetFullName(pchar)+" paid off Calder's widow’s debt from his own pocket! Not many would part with that kind of money for a stranger. Seems Spain still has true caballeros left!","It warms the heart to see that Spain is home not only to worthy caballeros, but also to women whose honor and courage rival any man’s.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("They say a certain captain paid his own money to free Calder’s widow from her late husband’s debts! Not everyone would act so nobly. A true person of honor, don’t you think?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitão, é um prazer revê-lo! Eu estava esperando que passasse por aqui. Quem sabe hoje você tenha tempo para ficar um pouco e rezar?";
						link.l1 = "Feliz"+GetSexPhrase("","")+"  Prazer em conhecê-la, Marisa. Mas receio que não posso ficar muito tempo agora. Lembro do meu dever com o Senhor, mas a oração vai ter que esperar.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Capitão, você de novo! Sempre um prazer. Parece que o Senhor não quer que você esqueça o caminho da igreja... Quem sabe você encontre um momento para rezar, afinal?";
						link.l1 = "Marisa, é bom te ver. Mas não posso ficar – meus assuntos não podem esperar. Acredito que o Senhor conhece meus pensamentos mesmo sem oração.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitão, que alegria vê-lo novamente! Todos os dias agradeço a Deus pela sua bondade. O mundo ficou mais bonito quando você me ajudou.";
						link.l1 = "Feliz"+GetSexPhrase("","")+"   Que bom ver você com saúde, Marisa. Espero que a vida não tenha te trazido mais surpresas desagradáveis. Você parece bem mais feliz.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Capitão, que alegria vê-lo! Sempre que você vem à nossa igreja, sinto uma paz imensa. Você traz consigo a luz das boas ações.";
						link.l1 = "E eu fico feliz"+GetSexPhrase("","")+" Bom te ver, Marisa. Já se acostumou com a vida tranquila, ou ainda sente saudade de vez em quando?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", se todos continuassem adiando a oração, o mundo já teria mergulhado nas trevas há muito tempo. Deixe suas preocupações de lado por um momento – o arrependimento te dá forças para seguir em frente.";
			link.l1 = "Eu entendo, Marisa, mas realmente não posso agora. Acredito que o Senhor vai me ouvir mesmo sem palavras.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", mudou de ideia? Os pecados não desaparecem sozinhos, e quanto mais você espera, mais pesados eles ficam.";
			link.l1 = "Infelizmente, preciso ir. Mas da próxima vez, prometo que vou rezar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Mas a fé não é só saber, é agir! Você não pode adiar para sempre o caminho da redenção. Não quer sentir o alívio de se livrar do peso do pecado?";
			link.l1 = "Talvez, mas não agora. Que o Senhor me ouça, mesmo que a oração tenha que esperar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Capitão, você não acha que adiar o arrependimento já é um pecado por si só? Um dia pode ser tarde demais.";
			link.l1 = "Talvez, mas receio que hoje não tenho tempo. A fé está comigo, e o Senhor vê meu arrependimento mesmo sem oração.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Sim, graças a você posso respirar em paz novamente. Que o Senhor proteja você e sua jornada. Talvez queira rezar comigo?";
			link.l1 = "Acredito que suas orações já são fortes o bastante. O que mais importa é que agora você está cercado apenas de bondade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", mudou de ideia afinal? Vamos rezar para o nosso Criador?";
			link.l1 = "Infelizmente, Marisa, eu preciso ir agora, tenho coisas para fazer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Eu tento olhar só para frente. Agora eu tenho um futuro, e tudo isso é graças a você. Talvez devêssemos agradecer ao Senhor juntos por isso?";
			link.l1 = "Acho que você vai se sair melhor do que eu. O mais importante é que suas orações te tragam paz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", talvez eu consiga convencer você a fazer pelo menos uma oração?";
			link.l1 = "Me perdoe, Marisa, mas infelizmente não tenho tempo agora. Reze por mim também.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Capitão, aqui não é o lugar. A caverna que precisamos fica perto da Baía dos Mosquitos.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}