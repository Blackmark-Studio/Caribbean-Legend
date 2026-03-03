// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug óbvio. Avise os desenvolvedores sobre isso.";
			link.l1 = "Ah, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "O que diabos está acontecendo aqui, senhores? Ouvi barulho de briga.";
			link.l1 = "Olá, oficial, ouvi uma mulher gritando e...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Capitão "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "You are free to go for now, captain. I can see what happened here; we will summon you if we have any questions.";
			link.l1 = "Muito bem...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "O que diabos está acontecendo aqui, senhores? Ouvi barulho de briga.";
			link.l1 = "Ufa... Oficial, estou aqui a pedido da moça da taverna — ela disse que alguém estava sendo morto aqui, e era verdade — aqueles dois canalhas atacaram esse nobre cavalheiro. Infelizmente, não consegui salvá-lo. Os desgraçados acabaram com ele.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Maldição... Ele é espanhol! O que ele estaria fazendo aqui? Hm. E você, quem é, então, "+GetAddress_Form(NPChar)+"?";
			link.l1 = ""+GetFullName(pchar)+". Capitão "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Capitão, você está livre para ir por enquanto. Seu depoimento bate com o da testemunha. Chamaremos você se for necessário.";
			link.l1 = "Muito bem...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Deixe-me explicar tudo, oficial! Eu, Don Domingo Ortiz Albalate de Santo Domingo, vim a Port-au-Prince a convite de uma jovem dama. Enquanto esperava por nosso encontro, fiquei hospedado na taverna. Mas não se passaram nem duas horas antes que dois canalhas malditos invadissem meu quarto, e se não fosse pela ajuda providencial de "+GetSexPhrase("esse bom senhor que apareceu","essa bela señorita que apareceu")+", eu teria me metido em uma encrenca daquelas.";
			link.l1 = "Don Domingo Ortiz Albalate? Você é espanhol?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Tão espanhol quanto o próprio Rei Felipe, ha! Gostaria também de ressaltar que meus documentos estão em perfeito orden. Sou um nobre da Espanha, não algum pirata imundo!";
			link.l1 = "Don Domingo, nossas mais sinceras desculpas por este incidente lamentável! Por favor, venha conosco para responder a algumas perguntas e tomar uma garrafa de vinho na guarnição. Vamos cuidar de tudo. Quanto a você...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitão! "+UpperFirst(GetAddress_Form(NPChar))+" Capitão! Juro por Santiago e pela Santíssima Virgem, você é um homem nobre, e um verdadeiro filho de Castela sempre recompensa tal nobreza! Gostaria de vê-lo recompensado mais tarde, quando eu terminar meus assuntos aqui. Por favor, me honre com uma visita à minha humilde casa em Santo Domingo! Fica perto dos portões da cidade. Vou preparar um banquete para você, "+GetSexPhrase("meu buen amigo","minha salvadora")+"! Lembre-se do meu nome, é Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Capitão "+pchar.lastname+"?! Oh Madre de Dios! Que desastre! Isso é um massacre! O que aconteceu aqui, "+GetSexPhrase("meu bom amigo","minha salvadora")+"? Quem são esses homens?";
			link.l1 = "Que bom ver você, Don Domingo. Estes são... Eu vim aqui para lhe fazer uma visita. Está vendo aquele sujeito ali? É o Ugo, seu criado, e ele...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Ah não, você foi enganado, capitão!";
			link.l1 = "Entendi, parece que isso acontece comigo o tempo todo. Três canalhas invadiram sua casa, mataram seu fiel Ugo – já encontrei o corpo dele lá em cima – e armaram uma emboscada pra você. Minha chegada não fazia parte dos planos deles. Eles não sobreviveram ao nosso encontro.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! Você maneja a espada como os mestres de esgrima de Toledo! Ainda bem que está do meu lado! Ai, meu pobre Ugo! Ele me criou desde criança e agora... ser assassinado por essas malditas canalhas!";
			link.l1 = "Don Domingo, parece que o senhor ainda não está fora de perigo. Seu homem, Ugo, sabia de algo. Leia este bilhete. Encontrei-o em cima de uma mesa.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Me dá isso... (lendo) Não pode ser... ah, não! Isso é inacreditável! Tio Luis... Mas...";
			link.l1 = "Alguma pista de quem fez isso?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Apenas suspeitas... suspeitas terríveis, "+GetSexPhrase("meu bom amigo","minha salvadora")+"! Como o irmão da minha mãe pôde fazer uma coisa dessas?";
			link.l1 = "Você se importaria de me contar o que está acontecendo? Me desculpe, Don Domingo, mas pela minha experiência, parentes costumam ser os piores inimigos que um homem pode ter...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Sim, você está certo, "+GetAddress_Form(NPChar)+"! Eu vou te contar tudo! Você já me salvou duas vezes e parece que é o único em quem posso confiar agora! Mas vamos sair desse lugar horrível, estou ficando enjoado aqui. Preciso avisar o alcalde sobre essa confusão, eles vão cuidar do pobre Ugo. Que tal tomarmos um vinho na taberna local para acalmar os nervos?";
			link.l1 = "Seus nervos certamente precisam mais do que os meus, mostre o caminho, señor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "Então, meu amigo, permita-me contar uma versão... resumida da história da minha família. Minha mãe, Dona Isabella Ortiz, casou-se com meu pai, o Marquês Ricardo Albalate, e adotou o sobrenome dele, como manda a tradição. O irmão dela, Luis Ortiz, era comandante de uma guarnição nas colônias, mas depois do casamento da minha mãe, foi nomeado por meu pai para administrar uma plantação de açúcar não muito longe de Portobello\nEra uma plantação enorme e muito rica, realmente lucrativa. Após a trágica morte dos meus pais no mar, há alguns anos, eu, como filho único, herdei tudo, inclusive a plantação. Meu tio manteve o cargo e eu estava satisfeito com o aluguel que ele me pagava. Ele sempre foi pontual com os pagamentos.";
			link.l1 = "Então você acha que seu tio...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Sim. No momento, ele não passa de um arrendatário. A fazenda é minha, não dele. Mas! Se algo me acontecer – ela passará a ser dele.";
			link.l1 = "Sabe, Domingo, já conheci homens que matariam toda a própria família a sangue frio por uma recompensa bem menos tentadora que essa.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Você claramente precisa escolher melhor suas companhias, Carlos. Meu querido Ugo mencionou os papéis do meu tio na última carta... Isso é uma pista direta. Ah, eu não quero acreditar nisso! Mas... minha prima, Margarita Ortiz, que mora na Espanha, ficou noiva há pouco tempo. Será que é por isso, "+GetAddress_Form(NPChar)+" capitão?";
			link.l1 = "Seu tio querido pode de repente precisar de um pouco de dinheiro...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Dinheiro?! Mas é claro... mas não se esqueça do título de marquês! Isso faria da minha prima uma esposa à altura para seu futuro marido! Jesus Cristo! Como fui tola!";
			link.l1 = "Esse título de nobreza vale mais do que a plantação de açúcar.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Wait a minute! I just remembered that this wasn't the first attempt on my life! I had an encounter with a beggar in the street a few weeks ago! The drunken canalla offended me in a manner I couldn't ignore. He turned out to be a damn good fencer; he drew steel and even managed to wound me with a rapier before I killed him.";
			link.l1 = "E como diabos você foi parar numa taverna em Port-au-Prince? Você mencionou uma jovem señorita?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(ficando vermelho) Senhor... Sim, capitão, havia uma señorita jovem e bonita lá... agora vejo que ela era só isca pra armadilha. Malditos, malditos por toda parte, não dá pra confiar em ninguém! Coitado do Ugo... agora ele está morto.";
			link.l1 = "Você devia fazer alguma coisa sobre isso, Domingo. Que tal fugir para a Espanha?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "Para a Espanha? E deixar minha plantação para aquele canalha? Capitão, eu sou o Marquês Domingo Ortiz Albalate!";
			link.l1 = "Mas...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", posso pedir sua ajuda? Com Ugo morto, não tenho mais ninguém em quem confiar ao meu lado. Você já me salvou duas vezes! Duas vezes! Eu lhe devo muito, estou para sempre em dívida com você, e mesmo assim ouso pedir mais um favor. Juro pela Santa Mãe que vou recompensá-lo por isso!";
			if (startHeroType == 2)  
			{
				link.l1 = "Como posso ajudá-lo, "+npchar.name+"?";
				link.l1.go = "noble_20";
			}
			else
			{
				link.l1 = "Muito bem, você é um bom homem para um espanhol. O que posso fazer por você, Domingo?";
				link.l1.go = "noble_20";
			}
			
		break;
		
		case "noble_20":
			dialog.text = "Vamos até a minha plantação em Portobello! Sei que meu tio está em Cartagena neste momento. Ugo mencionou alguns papéis, então vamos conferir os livros e documentos de Don Luis Ortiz! Talvez a gente encontre algo que ajude a desmascarar essa conspiração nojenta. É uma boa distância até Portobello, mas vou te pagar direitinho pela viagem!";
			link.l1 = "Seria absurdo recusar você agora, Don Domingo. Já estou envolvido demais para desistir.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Graças a Deus, eu sabia que você ia me ajudar, amigo! Aqui, pegue estes vinte mil pesos como pagamento pela viagem até Portobello. Quando partimos? Precisamos nos apressar antes que meu tio volte de Cartagena!";
			link.l1 = "Então não vamos perder tempo.";
			if (startHeroType != 2 && CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20 && GetNationRelation2MainCharacter(SPAIN) == RELATION_NEUTRAL) {link.l1.go = "noble_22";}
			else {link.l1.go = "noble_22x";}
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Aqui está uma licença da Companhia Holandesa das Índias Ocidentais. Ela vale por vinte dias, vamos só colocar seu nome aqui. Pronto. Isso deve nos ajudar a evitar qualquer problema com a Costa Garda.";
			link.l1 = "Excelente!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Agora posso subir a bordo do seu navio, capitão?";
			link.l1 = "Considere-se um hóspede de honra. Assim que o vento estiver a nosso favor, partimos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "Então, Capitão Carlos, aqui estamos nós. Agora precisamos encontrar a casa do meu tio e ver o que tem lá dentro.";
			link.l1 = "Dom Domingo, devemos esperar algum problema com a guarda?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Não. Embora... hm. Existe a chance de que o Luis tenha feito eles se voltarem contra mim. De qualquer forma, a discrição é sempre a melhor parte da coragem. Vamos encontrar a casa que precisamos.";
			link.l1 = "Você ainda não sabe? É a sua plantação.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm... Para ser totalmente honesto, da última vez que estive aqui, eu tinha só oito anos. Mas pretendo mudar isso o quanto antes!";
			link.l1 = "Entendi. Então vamos começar a procurar. A casa do seu tio deve ser a maior daqui.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "O que você tem aí, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Dá uma olhada, Don Domingo. Parece registros de contabilidade. Isso pode ser interessante.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(lendo) Hm... Sim. Olha só isso... Ay caramba! Cem mil pesos! E mais cento e cinquenta mil! E aqui... (virando as páginas) Tio Luis!";
			link.l1 = "Algo interessante?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Alguma coisa interessante! Meu querido tio tinha uma renda cinco vezes maior do que me contou! Ladrão! Trapaceiro!";
			link.l1 = "Não posso dizer que estou surpreso. Não dá pra confiar totalmente em ninguém sem conferir como as coisas realmente estão de vez em quando. Isso é só bom senso.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Bom senso é para homens comuns, talvez. Minha criação me deixou cego para esse tipo de traição em cavalheiros que eu julgava honrados! Você está certo, como sempre, Carlos! Meu próprio tio está me roubando! Mierda! Isso é culpa minha, mas eu vou consertar. Esta plantação é minha e meu tio foi afastado do cargo a partir de hoje! Ele não é ninguém! Vou fazer questão de vê-lo castigado!";
			link.l1 = "Don Domingo... Você não acha que seu tio pode não gostar dessa decisão?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Eu não dou a mínima se ele concorda ou não! Eu sou o Marquês Domingo Ortiz Albalate e Luis Ortiz não passa de um inquilino, e ainda por cima ex-inquilino! E ele...";
			link.l1 = "Se acalme, señor. Você é um rosto desconhecido por aqui e eu sou um francês navegando sob licença holandesa, com um... passado complicado com as patrulhas espanholas contra piratas. Quanto ao seu tio, ele praticamente manda nesta cidade. Pense nos guardas e no governador local. Você realmente acha que eles vão ficar do seu lado?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Você acertou em cheio... Talvez... Não. Soldados espanhóis jamais ousariam tocar em um nobre! Meu tio pode me desafiar, se tiver coragem!";
			link.l1 = "Ainda assim, sugiro seguir outro caminho. Que tal recorrer ao tribunal?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! Você está certo, Carlos. Vamos falar com as autoridades competentes. Meu tio cometeu um erro ao anotar detalhes exatos sobre seus negócios com contrabandistas. Ele comprou escravos deles por preços muito baixos. Esses livros vão nos ajudar muito. Duvido que aquele desgraçado consiga me prejudicar de alguma forma enquanto estiver apodrecendo nas masmorras. Vamos! Para Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "Isso não passa de uma mentira suja e insolente! Como ele ousa manchar o bom nome dos meus pais com essa língua desprezível! Maldito seja, eu vou fazê-lo pagar por isso! Saque sua espada, seu assassino!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Tio Luis está no lugar certo reservado para sua alma – no inferno... "+pchar.name+", você foi enviado a mim pelo meu anjo da guarda! Ainda bem que não confiou na palavra desse canalha. Para ser sincero, temi que você fosse me deixar aqui sozinho para enfrentar esse miserável\nSim "+GetAddress_Form(NPChar)+", eu também não sou perfeito, mas isso... essa mentira imunda sobre eu contratar piratas para matar meus próprios pais! Me culpar por isso... isso! Bah! Um destino mais do que merecido.";
			link.l1 = "Que bom que conseguimos, Don Domingo. E agora? Espero que não tenhamos problemas com a lei espanhola.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Com a lei? Ha-ha! Não, "+pchar.name+", I will show this fine accounting book with all my uncle's smuggling operations in it. Do not forget about the several attempts on my life; we've got a great number of witnesses after his last try just now. Don't worry about it, "+GetAddress_Form(NPChar)+". This is my town, it's time to show them all!";
			link.l1 = "Por favor, vá com cautela, señor. Deixe que pensem melhor de você do que pensavam do seu falecido tio.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "Esse é o plano, capitão. Mas não terei piedade de quem ousar me desafiar. Deixe-me expressar minha sincera gratidão a você, "+pchar.name+"! Por favor, vá até a taberna, descanse um pouco, tome uma ou duas canecas. Eu até iria com você, mas você estava certo. Chegou a hora de eu criar juízo e assumir o controle da plantação sozinho. Venha me ver aqui amanhã, capitão!";
			link.l1 = "Muito bem, Don Domingo. Até amanhã.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, aqui está você, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Como vai, dom Domingo? Como está a sua plantação?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "A fazenda é ótima, não posso dizer o mesmo do dinheiro – descobri que meu querido tio transferiu todo o dinheiro para o banco em Cartagena. Vai levar muito tempo dos advogados para eu recuperar meu ouro. Mas tudo bem, eu dou um jeito nisso. Não fique triste, capitão, vou cumprir minha promessa de recompensar você pela sua nobreza, honestidade e amizade!";
			link.l1 = "Jamais pensei em recompensa quando lutei ao seu lado, señor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Eu sei disso, capitão, e isso já diz muito sobre o seu caráter! Toda boa ação merece ser recompensada. Então, embora eu não tenha dinheiro no momento, vou mandar carregar seu navio com mercadorias da minha plantação. Quero dizer café, um ótimo lote. Tenho certeza de que você vai conseguir um bom lucro vendendo tudo.";
			link.l1 = "Oh! Isso é bom...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Além disso, tenho alguns itens que não têm muito valor para mim, mas que seriam de grande valor para qualquer marinheiro como você. Um bom telescópio e três amuletos. Por favor, aceite-os, agora são todos seus.";
			link.l1 = "Gratidão!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Finally, I present you with my rapier as a token of my immeasurable gratitude. She served me well; now let her serve you even better. Look at her and remember your good Spanish friend - marquis Domingo Albalate!";
			link.l1 = "Muito obrigado, señor! Eu não esperava...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "E agora, infelizmente, preciso me despedir. Devo ir a Portobelo ver o governador e depois a Cartagena... Resumindo, minha vida despreocupada acabou, chegou a hora de viver como um homem adulto.";
			link.l1 = "Bem, agora você está bem mais esperto...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "É verdade. Foi um prazer, "+GetAddress_Form(NPChar)+"! Venha me visitar algum dia. Boa sorte no mar!";
			link.l1 = "O mesmo para você nos seus negócios de plantação, dom Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, estamos atrasados, señor! Que pena, meu velho tio já fez um belo trabalho limpando seus papéis. Parece que alguém contou pra ele sobre Santo Domingo e ele se precaveu... Mas não vou deixar por isso mesmo! Preciso procurar o governador de Portobello pra abrir um processo contra meu tio. Já cansei dele mexendo na minha fortuna.";
			link.l1 = "Boa decisão.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "I want to thank you, captain! It was a pleasure! I present you my rapier as a token of my gratitude. She served me well; now let her serve you even better. Look at her and remember your good Spanish friend – marquis Domingo Albalate!";
			link.l1 = "Muito obrigado, señor! Eu não esperava...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "E agora, infelizmente, preciso me despedir. Devo ir para Portobelo. Meus dias despreocupados acabaram, é hora de viver como um homem adulto. Boa sorte no mar!";
			link.l1 = "Boa sorte com seu tio, dom Domingo! Tenho certeza de que você vai se sair bem!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			if (pchar.sex == "woman") { dialog.text = "Parece que cheguei bem na hora. Meu sobrinho rebelde e sua nova paixão, Capitão "+GetFullName(pchar)+"... Sim, sim, "+GetSexPhrase("rapaz","senhorita")+", não se surpreenda — já fiz algumas perguntas sobre você."; }
			else { dialog.text = "Parece que cheguei bem na hora. Meu sobrinho rebelde e seu anjo da guarda, Capitão "+GetFullName(pchar)+"... Sim, sim, "+GetSexPhrase("rapaz","senhorita")+", não se assuste — já fiz algumas perguntas sobre você."; }
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Você está certo, capitão, mas o resto você entendeu tudo errado. Não devia se meter nos assuntos de família dos outros. Você não faz ideia de quem está protegendo. Meu sobrinho perdido, Domingo, é um vagabundo inútil, o maior frequentador de todas as tavernas e bordéis, que dorme ou pelo menos tenta dormir com toda garota que vê pela frente. Eu pago o aluguel dele todo mês e ele torra tudo em poucos dias, sempre pedindo mais e mais. Sempre a mesma coisa. O comportamento vergonhoso dele enlouqueceu a mãe dele, minha irmã.  Ouvi boatos de que esse rapaz sem vergonha chegou a contratar e guiar alguns corsários ingleses até um certo navio do Marquês Ricardo Albalate, que eles afundaram junto com aquele homem honrado e minha querida irmã. Domingo queria tanto o dinheiro da família que seria capaz de matar por isso... Infelizmente, não consegui reunir provas suficientes para mandar esse canalha para a forca.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			if (pchar.sex == "woman") { dialog.text = "Meu querido sobrinho, como sempre, no seu próprio mundo. Tanta algazarra, espadas tilintando e copos batendo, mas pouca coisa de valor. Não sei o que você vê nele, señorita, ele é..."; }
			else { dialog.text = "Meu querido sobrinho, como sempre, no seu próprio mundo. Tanta algazarra, espadas tilintando e copos batendo, mas pouca coisa de valor. Não entendo o que foi nele que te fez querer ajudar um moleque tão sem mérito..."; }
			link.l1 = "Pelo que entendi, depois que não conseguiu encontrar nenhuma prova contra seu sobrinho, você começou a mandar assassinos atrás dele. Parece que um simples processo judicial teria bastado.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Você só fala mentiras. O Domingo aqui já fez inimigos demais pra contar. Por onde passa, deixa um rastro de amantes desprezadas e maridos traídos. Eu até me pergunto como ele ainda está vivo! Pergunte pra ele, quantos casamentos ele já arruinou? Quantos noivos ofendidos ele já feriu ou matou?";
			link.l1 = "O servo dele, Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah, Ugo! O pior canalha de todos! Ugo adorava seu mestre devasso. Todos os crimes do seu mestre não passavam de travessuras de criança para ele. Lembre-se, "+GetSexPhrase("rapaz","senhorita")+", negócios de família são só para a família. Quem se mete onde não deve acaba se dando mal.";
			link.l1 = "Agora você está me ameaçando.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Atenção. Escute, Capitão: "+GetSexPhrase("você foi longe demais, mas ","")+"já que não te vejo como inimigo—apenas alguém mal orientado—vou te fazer uma proposta: dê meia-volta e vá embora. Não quero derramamento de sangue. Vamos resolver nossos assuntos de família sem você. "+GetSexPhrase("Estou pronto para compensar qualquer gasto que você tenha tido com meu sobrinho:","Para facilitar as coisas pra você, estou disposto a te pagar:")+" "+FindRussianMoneyString(iTotalTemp)+" em dinheiro. Pegue e esqueça este lugar. Caso contrário, meus guardas simplesmente vão te matar.";
			link.l1 = "'Família em primeiro lugar', é o que eu sempre digo. Então não é da minha conta, entregue o dinheiro e 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "A sua história fede mais do que o adubo da sua plantação. Don Domingo pode não ser santo, mas você, senhor, é um diabo!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Eu sabia que você era um homem sensato. Pegue seu dinheiro e adios, capitão. Tente não fuçar na vida dos outros da próxima vez – ninguém gosta disso.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			if (pchar.sex == "woman") {dialog.text = "Agora entendi. Você é igualzinha ao meu sobrinho — uma garota tola e imprudente. Feita sob medida pra ele. Hora de dar uma lição nos dois!";}
			else {dialog.text = "Agora entendi. Você não é diferente do meu sobrinho — um garoto tolo e arrogante! Está na hora de dar uma lição em vocês dois!";}
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" "+GetAddress_Form(NPChar)+". Como posso ajudar?";
			link.l1 = "Saudações. Com licença, esta é a residência do senhor Domingo Albalate?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Sim, esta é a casa dos Albalate. É modesta, mas confortável. Meu nome é Ugo, sirvo ao jovem mestre. Veio procurá-lo?";
			link.l1 = "Sim, senhor. Don Domingo me convidou para a casa dele há pouco tempo. Ele foi muito convincente. Posso vê-lo?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Ai de mim, meu bom "+GetSexPhrase("caballero","senhorita")+", Don Domingo não está em casa no momento. Olha, eu mesma queria saber onde encontrar esse rapaz travesso... ah, perdão, jovem senhor. Posso perguntar o que deseja com ele?";
			link.l1 = "Bem... Eu ajudei Dom Domingo por acaso. Ele foi atacado por dois canalhas numa taverna em Port-au-Prince. Ajudei seu patrão a se defender daqueles... como ele os chamou mesmo... maldita canalha. Dom Domingo me convidou para visitá-lo aqui depois que terminasse a investigação. Achei que tudo já estaria resolvido, então esperava encontrá-lo em casa.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Deus! Que histórias terríveis você está contando aqui! Preciso ver o comandante imediatamente – avisá-lo sobre os perigos que Don Domingo está enfrentando neste momento! "+UpperFirst(GetAddress_Form(NPChar))+", você precisa ir e eu devo me apressar!";
			link.l1 = "Calma, Ugo. Seu jovem patrão está seguro. Ele disse que os documentos dele estão em ordem, já era pra terem liberado ele, por isso estou aqui. Acredito que logo vamos vê-lo.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! Como você pôde? Aquele garoto ingênuo – e nas mãos daqueles franceses comedores de rãs?! Sem falar nos ladrões ameaçando a vida dele? Não, eu preciso ver o comandante! "+UpperFirst(GetAddress_Form(NPChar))+", por favor, vá!";
			link.l1 = "Tá bom, tá bom, não precisa insistir tanto. Eu já estou indo.";
			link.l1.go = "ugo_exit";
			link.l2 = "Senhor, por que tanta ansiedade? Já lhe disse que não há perigo para o seu patrão. Deixe-me ficar aqui e esperar pela chegada do Senhor Domingo, estou muito cansado da longa viagem e agradeceria sua hospitalidade. Gostaria de um pouco de água fresca e um banho quente para tirar o sal da garganta. Depois, pode ir até a guarnição local e fazer o que quiser.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", saia desta casa agora mesmo!";
			link.l1 = "Ugo, duvido muito que um criado tenha permissão para falar com um cavalheiro dessa maneira. Também duvido que Dom Domingo aprovaria esse tipo de tratamento com um homem que salvou a vida dele!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Ah é? (chamando para cima) Rapazes, desçam aqui, temos um problema!";
			link.l1 = "Mas que diabos?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
