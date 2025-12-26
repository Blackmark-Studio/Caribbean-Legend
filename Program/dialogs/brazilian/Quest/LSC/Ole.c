// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Ops... Oi, tio. Você tem uma conta branca? Me dá a conta branca...";
			link.l1 = "Hm. Bom dia. Você é... o Garoto Branco?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Conta! Conta branca pro menino branco! Você tem uma conta branca, tio?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hum, não tenho contas, mas posso te dar esta pérola. Ela é branca e parece uma conta. Tudo bem pra você?";
				link.l1.go = "store_2";
			}
			link.l2 = "Não, não tenho contas, nem brancas nem vermelhas. Não sou menina nem índio pra usar contas. Diga...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Miçanga! Miçanga branca! Sem miçanga, sem conversa. Tio ruim... Me dá uma miçanga!";
			link.l1 = "Droga! Que sujeito maluco! Olho de Cobra e Chimiset estavam certos – ele não bate bem da cabeça... Que tipo de miçanga ele quer?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Me dá uma conta, tio. Bom tio... Uma conta branca!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Aqui, pegue sua conta. Era isso que você queria?";
				link.l1.go = "store_2";
			}
			link.l2 = "Ah, droga...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Sim, sim! É isso mesmo! O tio me deu uma conta! Obrigado, moço bom! Agora Ole tem mais uma conta. Logo vou ver a mamãe...";
			link.l1 = "Fico feliz por você. Bem, podemos conversar agora?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Claro, bom homem. Você é um bom homem, tio? Vamos ser amigos. Ole vai gostar de conversar. Qual é o seu nome?";
			link.l1 = "Meu nome é "+pchar.name+". Ole, um homem uma vez me falou sobre você, mas ele não está mais aqui. Ele disse que você o ajudou, e que poderia me ajudar também.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "O tio deu uma conta para o Ole - ele é um bom tio. Ole gosta de ajudar gente boa. Não há muita gente boa - tios ruins estão por toda parte. Eu vou te ajudar, com certeza. Eu gosto de ajudar.";
			link.l1 = "Legal! Então, agora somos amigos. Ole, me diga, você se lembra de um homem de pele avermelhada e um chapéu de penas magnífico? Ele me contou que você salvou a vida dele há muito tempo.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "Eu me lembro desse tio. Ele é um homem bom. Eu o salvei. Levei ele até a estátua. E recentemente salvei outro homem bom do porão de carga, junto com comida. Salvei ele dos tios do almirante malvado. Eles teriam matado ele. Eu queria levar ele até a estátua também, mas ele recusou. Completamente.";
			link.l1 = "Do porão de carga? Heh, acho que sei de quem você está falando... E conheço esse tio. Diga-me, Ole, quem é o homem que você salvou?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "O nome dele é Tio Nathan. Ele está doente, muito, muito doente. Mal conseguia andar quando Ole o encontrou.";
			link.l1 = "É mesmo... É estranho que ele tenha conseguido fazer isso.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "Não, não é estranho. Eu o encontrei e dei um pouco de rum de fogo pra ele. Eu nadei pelo buraco porque tem comida naquele navio. Os homens maus trancam a porta, mas eu sempre abro. He-he-he... Homens maus bobos. Eles atraem caranguejos, eu sei disso. Homens maus, eu fui lá e encontrei o Nathan. Ele não estava bem. Eu tinha rum de fogo — dei pra ele beber, aí ele melhorou. Depois dei a tintura, sempre carrego uma dessas, caso um caranguejo assustador morda o Ole. O tio bom Chimiset me disse pra fazer isso...";
			link.l1 = "Você deu o antídoto e o rum pra ele? Heh, você não é tão tolo quanto todo mundo pensa. Muito bem, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Tios maldosos acham que Ole é um bobo e zombam dele: Ole, o bobo... Ole não é bobo, só precisa juntar todas as contas brancas ou a mãe dele vai mandá-lo embora. Você vai me dar outra conta depois?";
			link.l1 = "Hm... Claro, Ole, somos amigos. Me diga, como você ia mandar o Hawk... o tio Nathan para a estátua? O tio Chimiset me disse que ela afundou junto com o navio...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "A estátua está no fundo. Ole sabe. Mas não é fundo, e o bom tio Henrik pode mandar o tio Nathan lá. O tio Henrik sabe andar debaixo d'água. Mas tem muitos caranguejos assustadores. Ole tem medo deles. Eles mordem e dói muito.";
			link.l1 = "Tio Henrik? Quem é ele?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Uncle Henrik lives among the wicked Narwhal uncles. Everybody knows him. He can walk underwater, and he teaches the Narwhal uncles how to dive there. Uncle Henrik is kind; he gave a white bead to Ole.";
			link.l1 = "E como os Narvais deixam você entrar? Ou o território deles está aberto para você?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Hi-hi... Tios malvados não deixam Ole entrar, mas Ole consegue entrar em qualquer cabine dos navios deles à noite. Eles são grandes e barulhentos, mas Ole é silencioso e cuidadoso. E eu conheci o tio Henrik nadando ao redor do navio de onde ele mergulha. O tio Henrik deu uma conta branca para Ole e agora somos amigos.";
			link.l1 = "Interessante... Eu também quero ser amigo do tio Henrik.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Você quer mergulhar até a estátua? Ela está lá, no casco do navio velho. Tem muitos caranguejos grandes e assustadores. Você não tem medo deles? Eles podem morder.";
			link.l1 = "Não, eu não tenho medo deles. Já matei um, então é melhor que eles tenham medo de mim.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Oh, "+pchar.name+" é muito corajoso! Então você deve ir até o Tio Henrik, ele vai te ensinar a andar no fundo do mar e você vai acabar com todos os caranguejos de lá. Você também vai encontrar mais uma conta grande para o Ole lá. Certo?";
			link.l1 = "Claro, eu vou. Mas preciso encontrar o tio Henrik primeiro.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "E por que você quer encontrá-lo? Ele mora no navio chamado 'San Gabriel', na oficina. Mas os malditos tios Narval talvez não te recebam bem.";
			link.l1 = "Eu mesmo vou lidar com os tios malvados. E só mais uma pergunta, onde está o tio Nathan agora? Estou procurando por ele, e ele é o motivo de eu estar aqui.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Eu escondi o Tio Nathan no meu refúgio no 'Fernanda'. Fica bem longe e ninguém mora lá. Todo mundo acha que o navio vai afundar logo, mas o Ole sabe que não é bem assim. Eu salvei o Tio Nathan e levei ele pra lá\nEle ainda está muito doente e bebe rum de fogo o tempo todo. Mal consegue andar e não tem força pra levantar nada mais pesado que uns dois quilos. Fico com pena dele, então levo rum de fogo dos baús e comida do porão dos homens ruins do almirante. Também cozinho uns ratos que eu pego pra ele. Ratos bem gostosos!";
			link.l1 = "Ratos saborosos? Entendi. Então o Nathan está no navio chamado... como você disse - 'Fernanda'? Não conheço esse navio...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Tio "+pchar.name+",   acabei de te dizer que não fica longe daqui. Você vai ter que nadar até lá. Tem uma porta na parte de trás dela, mas o tio Nathan não abre. O Ole pediu pra ele não abrir. Mas se você for amigo do tio Nathan, eu te conto como abrir. Bata na porta assim: toc-toc... toc-toc. Aí ele abre.";
			link.l1 = "Vou me lembrar disso. Obrigado, Ole! Você realmente me ajudou! Não sei como te agradecer de verdade.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Traga-me mais uma conta branca. Se encontrar, é claro.";
			link.l1 = "Ah, sim! Contas brancas! Ótimo. Até mais, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, tio "+pchar.name+"! Que bom te ver! Como você está?";
			link.l1 = "Obrigado, Ole, estou bem. Fico feliz em te ver também.";
			link.l1.go = "exit";
			link.l2 = "Escuta, Ole, você disse que os piratas do almirante trancam a porta do porão de carga e você sempre abre... Todos os baús lá estão trancados, e você disse que pega rum pra Tio Nathan deles. Como é que você faz isso?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole tem um conjunto de chaves muito boas. Elas abrem qualquer porta ou baú. Bem, nem todas. Algumas não podem ser abertas, mas a maioria pode. Ole as encontrou na cabine do tio Jurgen malvado. Ele trabalha com seu martelo todo dia perto do forno. Ele faz fechaduras e chaves. E também fabrica mosquetes grandes e assustadores para os Narvais malvados.";
			link.l1 = "Entendi. Ole, você pode me vender essas chaves? Eu posso pagar por elas...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Tudo bem, tio "+pchar.name+", eu vou te vender as chaves. Só vou ficar com uma para mim. Ela abre o quarto do almirante. Tem bastante comida e rum para o Tio Nathan. De qualquer forma, já não sobrou mais nenhuma conta ou rum nos baús.";
			link.l1 = "Quanto você quer por eles?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Primeiro, me conte, tio "+pchar.name+", você tem um navio grande?";
			link.l1 = "Sim, já estive. Mas ela não está aqui, está no anel externo. Mas vou deixar a ilha em breve e voltarei aqui no meu grande navio por causa do Tio Nathan.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "Para o tio Nathan? Ah, que maravilha! Olha, me promete que vai me tirar daqui no seu navio grande e me deixar viajar com você o tempo que eu quiser. Eu posso ser útil. Sei caçar e cozinhar ratos... Ah, e me dá cinco contas brancas. Aí eu te dou as chaves.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Claro! Aqui estão suas contas. Pegue-as.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Caçar e cozinhar ratos? Heh! Uma habilidade interessante. Tudo bem, Ole, temos um acordo. Vou trazer cinco contas e minha palavra.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, tio "+pchar.name+"! Que bom te ver! Como você está?";
			link.l1 = "Obrigado, Ole, estou bem. Fico feliz em te ver também.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Trouxe cinco contas brancas para as suas chaves.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Contas! Contas brancas! Tio "+pchar.name+"  deu contas para o Ole! Logo vou te ver, mamãe!... Tio "+pchar.name+", você promete que vai me tirar daqui quando voltar?";
			link.l1 = "Eu sim, Ole. Ainda não comi ratos. Vou te levar comigo.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Obrigado, obrigado, querido tio "+pchar.name+"   Tome suas chaves. Elas são fáceis de usar, é só ir testando uma por uma. Uma delas vai acabar abrindo a fechadura que você precisa. Se não funcionar, então a fechadura é complicada demais e você vai precisar de uma chave especial.";
			link.l1 = "Entendi. Acho que vou cuidar disso.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Espere, tio "+pchar.name+"! Eu consegui outra chave. Ela é bem bonita e engenhosa. O tio malvado Jurgen não faz chaves como essa. Não sei o que ela abre, mas talvez você descubra. Olha, é uma chave muito bonita, aposto que você nunca viu nada igual.";
			link.l1 = "Mostre-me... Sim, a chave é bem interessante. Mas de que adianta se você não sabe o que ela abre?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Tio "+pchar.name+", , você é muito estranho. De que adianta? Se existe uma chave, então em algum lugar há uma fechadura. Se há uma fechadura, então em algum lugar há uma moeda. Eu encontrei a chave na ilha. Isso significa que a fechadura também está aqui. Não tenho dúvidas. É uma chave engenhosa, e só coisas muito valiosas são trancadas com uma chave dessas. Ole sabe.";
			link.l1 = "Pra ser sincero, você é engraçado, Ole. Tá bom, eu compro. Quer miçangas em troca?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Sim, Ole quer cinco contas. Você vai dar pra ele, tio? "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Aqui, pegue suas contas.";
				link.l1.go = "key";
			}
			link.l2 = "Eu não tenho agora, mas vou trazer contas para você, com certeza.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Contas! Contas brancas para o menino branco! Para a mamãe dele! Aqui, tio "+pchar.name+", pegue a chave. E você vai encontrar a fechadura, Ole sabe. Você é corajoso, nem mesmo teme os caranguejos ferozes.";
			link.l1 = "Ah, não me faça rir, Ole! Valeu pela chave. Até mais!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, tio "+pchar.name+"! Que bom te ver! Como você está?";
			link.l1 = "Obrigado, Ole, estou bem. Fico feliz em te ver também.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Eu trouxe cinco contas brancas para a sua chave.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, tio "+pchar.name+"! Que bom te ver! Como você está?";
			link.l1 = "Obrigado, Ole, estou bem. Fico feliz em te ver também.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Oh, tio "+pchar.name+", você voltou! Você voltou para o navio grande! Vai me levar daqui? Tio "+pchar.name+", você me prometeu, lembra?";
			link.l1 = "Claro que sim, Ole. Seja bem-vindo a bordo! Acho que os ratos estão em apuros, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Sério? E quando foi que eu te prometi isso? Não me lembro de ter feito nenhuma promessa desse tipo...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Obrigado, tio! O Ole vai ser útil, você vai ver! Ah, será que vou ver a mamãe? Já estou indo!";
			link.l1 = "Não se apresse assim, Ole. Você pode arrumar suas coisas. Não vou zarpar imediatamente.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Você prometeu pra mim, prometeu sim! Disse que ia levar o Ole embora daqui! Tio malvado! Você enganou o Ole! Tio ruim!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Tio, tio... Eu preciso de mais uma conta branca. Por favor, dá uma conta branca pro Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Eu sabia que você ia pedir. Aqui, pegue sua conta. Satisfeito?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Ah, e que dor de cabeça... Não tenho mais contas, Ole, não tenho mesmo!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Obrigado! Bom, bom tio "+pchar.name+"! Ole tem mais uma conta e não restam muitas contas! E eu vou pra mamãe...";
			link.l1 = "Ah, e por que você é tão estranho...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Obrigado pelo amuleto, bom tio "+pchar.name+"!";
			link.l1 = "Seja bem-vindo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Sem conta? Mas como isso é possível, tio "+pchar.name+"?! Só faltam mais algumas contas... Preciso pegá-las. Nesse caso, vou para a terra firme. Vou procurar pelas contas...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "E para onde você vai? O que vai fazer sozinho? Não, não quero ser responsável pelo seu destino. Espere, vou verificar meus bolsos... Aqui! Pegue sua conta e fique comigo. Satisfeito?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "É seu direito, Ole. Se está cansado de navegar comigo, não vou te impedir. Tínhamos um acordo. Mas você tem conseguido pegar aquelas taxas direitinho...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Adeus, tio "+pchar.name+". Ole precisa de contas brancas ou nunca vai voltar para a mãe dele...";
			link.l1 = "Ah, sinto muito por você, mas o que posso fazer? Vá, Ole. Boa sorte.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Tio "+pchar.name+"! Eu preciso de mais uma conta branca. A última. Por favor, dê ela para Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Eu sabia que você ia pedir isso. Aqui, pegue sua conta. Satisfeito?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Ah, e que dor de cabeça... Não tenho mais contas, Ole, não tenho mesmo!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Obrigado, obrigado, querido tio "+pchar.name+"! Agora Ole tem todas as contas. Sim, cada uma delas! Agora Ole pode levá-las para a mamãe e ela não vai mandar Ole embora...";
			link.l1 = "Escuta, quem é essa mãe de quem você vive falando? E, afinal, me explica pra que você precisa dessas pérolas... dessas contas brancas? E o que quer dizer – você já tem todas elas?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Tio querido "+pchar.name+" ajudou Ole a juntar contas para a mãe dele... Ole era pequeno quando arrebentou o colar de contas brancas da mãe. Todas caíram na água. A mãe ficou furiosa com Ole, e ele não pode voltar para casa até juntar todas as contas perdidas\nEu lembro quantas eram. Cinco vezes dez contas. Agora Ole já tem todas. Tio "+pchar.name+", por favor, me leve para casa! Quero fazer mamãe feliz, devolver as contas. Me leve para casa!";
			link.l1 = "Meu Deus, que história incrível... Você chegou à Ilha ainda criança. Foi expulso de casa porque quebrou o colar de pérolas da sua mãe? Que estranho...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Leve-me até minha mãe, bom tio "+pchar.name+". Quero vê-la. Ela vai ficar feliz ao ver as contas.";
			link.l1 = "Eu gostaria, mas você sabe onde é sua casa? Onde sua mãe mora?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "Ela mora na ilha, na casa com o telhado vermelho.";
			link.l1 = "Sério! Você faz ideia de quantas ilhas existem aqui e quantas casas têm telhado vermelho? Qual é o nome dessa ilha? Me dê detalhes...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Eu não sei o nome dela. Eu sei que era uma ilha, mamãe estava dizendo pro papai que a gente estava na ilha! E a gente morava numa casa de telhado vermelho. Uma casa bonita, bem grande. Me leva pra mamãe, tio "+pchar.name+". Por favor...";
			link.l1 = "Ah, tudo bem. Vamos procurar por uma casa assim em cada ilha e perguntar pela sua mãe. Qual é o nome dela?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "O nome dela? Você é tão estranho, tio "+pchar.name+". O nome da mãe é Mãe. O nome da sua mãe é diferente?";
			link.l1 = "Ah, meu Deus, por favor, me dê um pouco de paciência... Tudo bem, Ole. Vamos tentar encontrar sua casa. Agora vá para o navio.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Obrigado, tio "+pchar.name+" . Você é muito, muito bondoso e gentil! Logo Ole vai ver a mamãe!";
			link.l1 = "Oh...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Mãe... Mãe, mamãe! Eu voltei!";
			link.l1 = "Filho...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mamãe, eu trouxe contas brancas para você! Consegui juntar todas! Você vai ter um colar de novo. Ainda está brava comigo?";
			link.l1 = "Deus... (chorando) Ole! Filho, por quê? Por que você foi embora? Eu não me importo com aquelas pérolas!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mamãe, aqui... pega. Eu venho juntando isso faz tempo. Tios bondosos me ajudaram, principalmente o tio "+sld.name+". Ele me levou no navio grande dele, me ajudou a juntar contas e me trouxe de volta pra casa...";
			link.l1 = "Ole... Você realmente cresceu, mas ainda é uma criança... Deixa eu te abraçar, meu filho! Me perdoa, por favor, por aquele maldito colar! Eu nunca mais vou te deixar sozinho, nunca! Vamos viver juntos e eu vou cuidar de você... Eu vou me redimir, eu prometo!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mãe, senti sua falta... Quero ficar com você. Ainda está brava comigo? Por que está chorando?";
			link.l1 = "(chorando) Não, não... Me desculpe, por favor me perdoe, filho!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Tio "+pchar.name+"! Estou tão feliz que você veio! Obrigada por me trazer até minha mãe. É maravilhoso estar aqui com ela... Não é ótimo estar em casa, tio? "+pchar.name+"?";
			link.l1 = "Sim. É. É isso mesmo. Fico feliz que você esteja contente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Olha, é melhor você guardar sua arma. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina na mão não é permitido aqui. Guarde isso.","Escuta, não fique bancando um cavaleiro medieval por aí com essa espada. Guarda isso, não combina com você...");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou um cidadão desta cidade e gostaria que você baixasse sua espada.","Olha, eu sou cidadão desta cidade e gostaria que você baixasse sua espada.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, amigo, andando por aí com uma arma. Posso ficar nervoso...","Não gosto quando homens passam na minha frente com as armas em punho. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso embora.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
