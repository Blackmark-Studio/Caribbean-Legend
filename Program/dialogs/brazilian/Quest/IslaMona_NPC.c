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
			dialog.text = "O que você precisa?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Mais alguma coisa, Capitão?";
			link.l1 = "Nada por agora...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha! Señor Jesucristo! Glória a Santiago, o Protetor! Glória à Virgem Maria! Estamos salvos! Ha-ha-ha!";
			link.l1 = "Espanhóis! Às armas!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Olá. Fiquei sabendo que você está com algum problema? Quem é você?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Tá bom, tudo bem, calma. É só um hábito.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha! Señor, meu nome é Rodrigo Jimenez. Sou agrimensor e, pela vontade do destino, el jefe deste povo infeliz.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Nós... fomos deixados aqui. Mas, señor, nós não somos criminosos! Ha-ha-ha-ha!";
			link.l1 = "O que é engraçado?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... Me desculpe, señor! É um problema meu, desde criança eu rio quando fico muito nervoso. Ha.";
			link.l1 = "E você foi escolhido como líder?.. Tudo bem. As pessoas não chegam em ilhas desabitadas à toa, señor. Quer se explicar? Só vou te dar uma chance.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Desculpe, receio que não tenha entendido seu nome, senhor. O senhor é inglês?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+". Isso é tão importante assim? Vamos deixar meu nome de lado por enquanto.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "De fato, sendo reconhecidos como hereges pela Igreja Católica Espanhola, precisamos comparecer diante do tribunal justo da Santa Inquisição. Por isso sua nacionalidade é tão importante para nós. Um capitão espanhol seria obrigado a nos entregar às autoridades locais. Não sobreviveríamos a isso de novo! Ha-ha!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha! É assim que a sorte nos trata, bem, não temos nada a perder mesmo. "+dialog.text;
			link.l1 = "Bem, felizmente para você, os assuntos da Inquisição não me dizem respeito. E daí? Vocês são pagãos?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Não, eu juro pra você! Nossa comunidade se dedicou à arte e ao comércio na gloriosa cidade de Cádiz por cinquenta anos. Tudo ia bem, até conseguimos um navio e uma licença pra negociar com as colônias do nosso Império. Agora vejo que, naquela época, cruzamos um certo limite e estávamos totalmente despreparados para os novos concorrentes... e os métodos deles.";
			link.l1 = "Você não negociou com alguém na Europa e, por causa disso, toda a comunidade ficou presa numa ilha deserta no Caribe? E eu achando que tinha problemas...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Infelizmente, é isso mesmo. Nossa comunidade foi fundada por judeus que se converteram à nova fé e receberam a chance de voltar para casa, na Espanha. Só essa história antiga já bastou para surgirem acusações e investigações oficiais.";
			link.l1 = "E então você fugiu...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Sim! Ha-ha-ha! Em nosso próprio navio! Estávamos indo para Curaçao para construir uma nova vida e um novo negócio. Mas subestimamos a persistência da Inquisição e pagamos caro por isso. O mensageiro deles nos interceptou não muito longe daqui e ordenou ao capitão que nos levasse de volta para casa...";
			link.l1 = "Droga!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "Tem mais! Ha! Nosso capitão não quis se dar ao trabalho de nos levar de volta pelo Atlântico nem de nos liberar da responsabilidade no porto mais próximo. E, tomando uma decisão digna do rei Salomão, nos deu comida, nos deixou aqui, e pronto.";
			link.l1 = "Uma história realmente trágica, não há dúvida. Vamos resumir: você não pode voltar para casa, as colônias amigas vão te denunciar, e os portos estrangeiros também não vão te receber – a guerra nessa região parece não ter fim. Quais são seus planos?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "O senhor pintou um quadro tão sombrio que até me faltam palavras. Parece até que não existe lugar melhor pra nós do que esta ilha.";
			link.l1 = "Acho que não, tem uma ilha melhor.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Sério? É espanhol?";
			link.l1 = "É meu. Por obra do destino, herdei um antigo esconderijo de piratas numa ilha desabitada. Agora é minha base, e quero expandi-la, explorar a ilha e, se possível, construir uma fábrica lá.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Você é um pirata?";
			link.l1 = "Sim.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Não.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Novo Mundo! De fato, estamos aqui. Lá em casa dizem que piratas são verdadeiros demônios, nem sequer humanos. Comem crianças, violentam mulheres e esfolam bons católicos vivos. Isso é verdade?";
			link.l1 = "Depende do dia da semana. Vamos conversar sobre isso outra hora. Estou procurando pessoas. Gente trabalhadora e capaz, disposta a viver longe da civilização por vários anos. Você teria interesse em algo assim?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Que pena, já que sou considerado um criminoso, gostaria de ver pelo menos um pirata.";
			link.l1 = "Talvez você tenha outra oportunidade dessas. Vamos conversar sobre isso em outro momento. Estou procurando pessoas trabalhadoras e capazes, dispostas a viver longe da civilização por alguns anos. Você se interessaria por algo assim?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Não temos outra saída. Mas, na verdade, essa nem é uma opção ruim. Aceitaremos, se você nos deixar viver e trabalhar em paz. E prometa que um dia vai nos mandar de volta pra casa! Dê sua palavra, senhor, e diga seu nome...";
			link.l1 = "Eu, Capitão "+GetFullName(pchar)+", eu te dou minha palavra. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha! Estamos salvos! Que assim seja! Somos várias famílias, cerca de 30 pessoas. Todos sabem ler e escrever, e têm habilidades em ofícios e comércio.";
			link.l1 = "O destino decidiu... Por favor, suba a bordo!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Prazer em conhecê-lo, Señor Rodgar. Parece que vamos ter que viver e trabalhar juntos por um bom tempo... Meu Deus, como você aguenta esse calor?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Se não se importar, vou me adiantar: Capitão, nos dê um dia para nos instalarmos e fazer uma inspeção rápida no estoque e no terreno. Tenho certeza de que o Señor Rodgar tem muitas ideias sobre o que fazer com esse pedaço de terra. Acho que vamos formar uma boa equipe.";
			link.l1 = "Você realmente não tem escolha, Hymenese. Ha-ha!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Sim, Capitão?";
			link.l1 = "Hymenese, alguma novidade boa pra mim?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Capitão, isso aqui é um pesadelo. Sua casa até que não é ruim, claro. Mas o resto... É impossível viver nessas cabanas, cercados de mato, e o Señor Rodgar nem sabe o que está acontecendo do outro lado da ilha!! Inacreditável! Ha-ha!";
			link.l1 = "Você está nervoso ou está realmente achando graça disso agora?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Claro, é engraçado! O que eles têm feito todos esses anos? Primeiro de tudo, precisamos terminar de construir algumas casas e reformar essas cabanas até ficarem em condições decentes. As pessoas precisam viver dignamente para poder trabalhar direito. Também vou pedir aos piratas que façam um reconhecimento completo da ilha. Talvez esse lugar seja rico não só em pedras e areia. Quando tudo estiver pronto, poderei te dizer exatamente o que fazer com essa terra.";
			link.l1 = "Parece ótimo! O que eu preciso fazer?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Materiais para casas, móveis e abrigos temporários. Calculei tudo. Aqui, pegue a lista.";
			link.l1 = "Impressionante...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Sério? Senhor, nós já construímos catedrais! Agora isso sim é impressionante...";
			link.l1 = "Estou inclinado a acreditar em você! Só não vá construir uma catedral aqui por engano. Vou ter que trazer um monte de material toda vez?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Não, esses materiais vão nos sustentar por um tempo, mas ainda vamos precisar trazer mais coisas depois. Se quiser evitar esse tipo de problema no futuro, traga o dobro de materiais.";
			link.l1 = "Tá bom, você me convenceu. Vou ver o que posso fazer. Tem algum prazo?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Não, senhor. Mas peço, por favor, que não demore – esse trabalho precisa ser feito para que tudo avance. E as pessoas também precisam de um lugar para morar. Carregue os materiais no armazém e não se esqueça de me avisar quando tudo estiver pronto. Ah, quase me esqueci! Fale com o senhor Rodgar sobre a exploração da ilha.";
			link.l1 = "Combinado!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Sim, Capitão?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Olá, Jiménez. Verifique o armazém.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Olá, Jiménez. Meus homens vasculharam toda a ilha. O que me diz?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Você lidou com essa responsabilidade de maneira exemplar! Se algum dia passar por Cádis, venha trabalhar comigo como almoxarife!";
			link.l1 = "Estou a caminho! Me diga, compadre, o que vai fazer agora?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Senhor Capitão, vamos primeiro cuidar do alojamento e dos suprimentos. Depois faremos os planos. Aguardo as mercadorias da sua lista no armazém.";
			link.l1 = "Certo, entendi. Primeiro, precisamos construir casas e organizar este lugar. As mercadorias vão chegar em breve.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Capitão, vamos primeiro resolver a questão da moradia e dos suprimentos. Podemos fazer planos depois. Estou aguardando as mercadorias da sua lista no armazém. E seu amigo pirata também está esperando provisões e remédios.";
			link.l1 = "Certo, entendi. Primeiro, precisamos construir casas e arrumar este lugar. As mercadorias vão chegar em breve. E também para o meu amigo pirata.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Nos dê seis meses, Capitão, e você não vai reconhecer este lugar.";
			link.l1 = "Você está dizendo que em seis meses não vai ter nem você, nem o povoado, nem os materiais aqui? Até mais!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Vamos começar a trabalhar assim que você resolver seus assuntos com esse bandido. Ele pediu mantimentos e remédios, e eu concordo com ele – é um pedido justo.";
			link.l1 = "Vou transmitir suas palavras a ele.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "E então, Capitão? Fez tudo o que seu pirata pediu?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Resolvi todos os problemas com o Rodgar. O reconhecimento da ilha já começou, mantimentos e remédios estão no depósito. Agora é a sua vez.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Não se preocupe, a gente vai dar um jeito. Eu cuido disso.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Señor Capitão! O que acha? Ha-ha-ha?";
			link.l1 = "Está bem melhor. Relate, Jiménez!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Agora você pode realmente morar aqui! Limpamos e reconstruímos todas as casas, menos a sua, é claro. Não é nada luxuoso, mas não fica atrás do que temos lá em Belize.";
			link.l1 = "Belize já pertence à Inglaterra há muito tempo, Jiménez.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Não sei se as casas sabem disso, Capitão, ha ha!";
			link.l1 = "Agora você tem um lugar para morar, e o povoado parece civilizado. O que vem agora?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Dê uma olhada ao redor, converse com o Señor Janssen e depois volte para mim. Vamos discutir os resultados do reconhecimento da ilha e nossos planos.";
			link.l1 = "Desde quando você começou a chamar o Rodgar assim? Vocês não viviam às turras?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "E ainda temos eles. Mas precisamos encontrar uma forma de construir relações de trabalho.";
			link.l1 = "Obrigado, Rodrigo. Eu volto logo.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Capitão. Señor Janssen.";
			link.l1 = "Vamos, me conte os resultados do reconhecimento da ilha.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Sim, Capitão. Eu mesmo inspecionei alguns lugares com o nosso prospector. Bem, o que posso dizer... Isla Mona é uma ilha pobre, pequena e bastante sem graça. Tem pouquíssimo espaço para construção, o terreno é difícil, íngreme, e quase não há terra fértil. Três praias, uma caverna alagada, mato fechado, uns papagaios, um bando de cabras e nós...";
			link.l1 = "Você está falando sério? Está dizendo que o bem mais valioso desta ilha é um rebanho de cabras?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha! Eu ia perguntar, señor! Ha-ha! Você não me deixou terminar!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Tudo bem, tudo certo, se acalme e continue. Sabe, investi muito neste lugar.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "E não foi em vão! Há água doce suficiente na caverna, terra bastante para cultivar árvores frutíferas, e dá para criar cabras. Com a pesca e o esforço dos seus companheiros, a questão da comida será resolvida bem rápido.";
			link.l1 = "Então, você não vai precisar trazer mais comida aqui? Nada mal. Eu esperava que este lugar pudesse sobreviver sem o meu cuidado constante. Vamos continuar.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Você está certo sobre tudo, Señor. Mas isso não é toda a novidade! Primeiro, o Señor Rodgar teve a ideia de construir uma taverna. Não sei o que isso vai te trazer, mas esse malandro está aprontando alguma coisa.";
			link.l1 = "Ele só quer encher a cara, é isso!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Além disso, a Baía do Governador acabou sendo muito mais profunda do que pensávamos. Podemos construir um cais de verdade.";
			link.l1 = "Eu não entendo muito bem como isso vai me beneficiar, mas já é uma boa notícia. Só espero que não seja só isso, certo?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Encontramos um bosque de árvores de bocote. Um lugar perfeito para uma fábrica.";
			link.l1 = "Você está me deixando feliz, Rodrigo! De fato, excelentes notícias!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Por enquanto é só, señor. Talvez surjam mais ideias no futuro. Você sabe como é, as melhores ideias aparecem enquanto estamos trabalhando! Sobre o que gostaria de perguntar?";
			link.l1 = "Me fale sobre bacote. Parece promissor.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "Na minha opinião, uma pequena fábrica conseguirá extrair essa madeira valiosa por alguns anos. As reservas são modestas, mas o recurso é estratégico. Podemos limpar um terreno no centro da ilha e construir uma casa com um armazém lá. É um começo. Além dos materiais de construção, também vamos precisar de cerca de 15 pares de algemas e mosquetes.";
			link.l1 = "E por que precisamos de algemas? E por que exatamente quinze?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "É trabalho duro, señor. Eu diria até que é trabalho de escravo.";
			link.l1 = "Entendi. Heh-heh...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Você ficou louco? Eu nunca vou me tornar um dono de escravos!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "E por que precisamos de um mosquete? E por que só um?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Eu concordo com o pirata, señor. Não entendo você, capitão. Toda a economia desta região é baseada no trabalho escravo, e vai continuar assim por muitos anos. Em que somos melhores?";
			link.l1 = "Eu vou tomar uma decisão. Enquanto isso, me diga por que você precisa de um mosquete? E por que exatamente um só?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "É claro, a fábrica vai precisar de manutenção. Com a construção dela, esta ilha vai ter uma economia, e você será o principal parceiro comercial. Nós mesmos vamos alimentar os escravos, mas você vai ter que pagar pela segurança e pela produção do seu próprio bolso. Os colonos vão cobrar 20 dobrões e cinco garrafas de vinho por cada remessa. Para questões de segurança, negocie com o Señor Janssen.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "quarenta medidas todo mês. E o ouro é para o futuro. Um dia você vai nos tirar daqui, lembra da sua promessa? Todo trabalho deve ser pago, e com seus dobrões, vamos pagar caçadores e artesãos pelo serviço na colônia. Assim, teremos comércio, e com ele – civilização!";
			link.l1 = "Isso aí! Muito bem! Por enquanto, tudo parece convincente o bastante...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "O que mais te interessa?";
			link.l1 = "Então, qual é a história da taverna? Por que não construir um teatro?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Capitão, eu avisei a ele que você não ia gostar da ideia da casa. Mas é a única opção. Você tem a maior casa da... aham, da cidade, vamos reformar o térreo para virar um salão, montar as mesas e a cozinha. Vamos guardar bebidas e comida nas adegas embaixo da casa. Temos gente para cozinhar e tocar música. O segundo andar continua sendo seu, não vamos mexer em nada lá. Nós mesmos vamos levar todas as suas coisas do térreo para cima.";
			link.l1 = "Certo. Então o que exatamente a taverna vai nos oferecer?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Vamos dar vida à cultura, e você terá a chance de manter cerca de trezentas pessoas em reserva bem no coração do Caribe.";
			link.l1 = "Interessante... Vou pensar nisso.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "O que mais te interessa?";
			link.l1 = "Bem, e quanto ao cais?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "É simples. Vamos limpar a Baía do Governador dos recifes, instalar luzes de sinalização e construir um cais. O senhor Janssen garante que você poderá abrigar três navios na baía, ou um navio de primeira classe. E vai ser bem mais agradável para você voltar aqui, sem ter que arrastar o bote pela praia toda vez.";
			link.l1 = "Seria bom.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "O que você gostaria de saber?";
			link.l1 = "Por enquanto é só. Eu volto quando decidir o que construir.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Senhor Capitão, pegue este documento. Tomei a liberdade de anotar todos os detalhes para não ter que repeti-los uma dúzia de vezes. Estude-o, traga os materiais e defina a tarefa.";
			link.l1 = "Obrigado, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно ещё 10 рабов
			{
				dialog.text = "Senhor Capitão, precisamos de 10 escravos para trabalhar na fábrica – eu já te disse, não esqueceu, né?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Já foi entregue. Descarregue-os e comece a produção.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "Minha memória está intacta. Vou trazê-los em breve.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Então, Señor Capitão, o que me diz?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Quero uma baía limpa e um cais seguro. Vai ser a base da minha frota.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Pode ir em frente e construir a taverna. Todo mundo vai gostar, e eu vou poder manter uma reserva aqui.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Comece a construir a plantação. Está na hora de recuperar o investimento.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, os especialistas mais valiosos e os equipamentos já foram entregues à fábrica. Você pode começar a trabalhar.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, vim buscar meu pau-ferro.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, já terminamos nossa grande construção?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, vamos construir sua igreja.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, trouxe os itens da sua igreja.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Nada por agora...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Os materiais estão disponíveis, tudo está pronto. A construção vai levar 4 meses.";
				link.l1 = "Você não está com pressa, está! Pois bem, boa sorte, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Receio que não haja materiais suficientes no armazém. Por favor, confira a lista novamente.";
				link.l1 = "Eu cuido disso.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Os materiais estão disponíveis, tudo está pronto. A construção vai levar 3 meses.";
				link.l1 = "Você não está com pressa, né! Então, boa sorte, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Receio que não haja materiais suficientes no armazém. Por favor, confira a lista novamente.";
				link.l1 = "Eu cuido disso.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Os materiais estão disponíveis, tudo está pronto. A construção vai levar 6 meses.";
				link.l1 = "Você não está com pressa, está! Boa sorte, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Receio que não haja materiais suficientes no armazém. Por favor, confira a lista novamente.";
				link.l1 = "Eu cuido disso.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Bem-vindo, Capitão. O que acha do seu novo porto?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "Está escuro, Rodrigo! Quase batemos no seu tão elogiado cais! Pelo menos você teve o bom senso de iluminá-lo!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Nada mal, Rodrigo! Pode parecer pouca coisa, mas é bom caminhar por essas tábuas até a praia. E a baía ficou mais fácil de navegar. Então, acho que agora posso acomodar mais navios nessa pequena baía?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Sim, Capitão. Tenho que admitir, sinto um certo orgulho nisso. Fique à vontade para me dizer como gostaria de prosseguir com o nosso grande projeto de construção.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Falando em construção. Minha fábrica já devia estar pronta também. Não é, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hic! Cap! Estamos comemorando aqui!";
			link.l1 = "Rodgar. Rodrigo. Ah, droga!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "O que foi, c-c-capitão? Não gostou da cor das paredes?";
			link.l1 = "Só agora percebo que vocês dois têm o mesmo nome! Ha-ha-ha! Um espanhol e um pirata, com o mesmo nome, construíram uma taverna numa ilha deserta e estão bebendo juntos como se os deuses índios fossem devorar todo mundo e acabar com o mundo ao amanhecer! Ha-ha! Tô com vocês!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! É isso mesmo! Mandou bem!";
			link.l1 = "Consegui!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Está tudo pronto. Vamos? Deixe-me te mostrar a sua fábrica.";
			link.l1 = "Mostre o caminho.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Capitão, quase tudo está pronto para começarmos as operações. Moradia para os trabalhadores, um armazém para matérias-primas, uma área de processamento – uma fábrica de respeito foi construída. Já marcamos as árvores mais promissoras para corte na selva. Traga quinze trabalhadores e o estoque combinado – 15 algemas e mosquetes – e começaremos a trabalhar.";
			link.l1 = "Nós? Você quer dizer os escravizados?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha! Os escravos vão cortar, os colonos vão processar, e os piratas vão proteger. Todo mundo vai ter trabalho – você embarcou numa empreitada séria, Capitão.";
			link.l1 = "Quase como a terra prometida, hein. Espere pela mercadoria, está na hora de eu sair para caçar.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Um destino triste... Eles nunca vão sair daqui.";
			link.l1 = "Rodgar... Quer dizer, Rodrigo! Primeiro, eles podem ir embora. E segundo, se você tivesse encontrado outra pessoa em Turks, seu destino não seria melhor.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Eu sei disso muito bem, Capitão. E não me esqueci. Deixe-me explicar como funciona esta fábrica. A partir do mês que vem, no dia quinze, vamos entregar quarenta toras de bacout processado. Claro, você não precisa vir buscar cada entrega todo mês – todos os lotes ficarão armazenados e esperando por você bem aqui, na fábrica.";
			link.l1 = "Então, eu posso pegar vários lotes de uma vez?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Dentro do razoável, é claro – não fique ausente por muito tempo. As pessoas não vão trabalhar anos sem receber, sem saber se o único cliente ainda está vivo ou não. Acho que vamos entregar seis carregamentos antes de suspender as operações.";
			link.l1 = "Eu preciso pegar todas as mercadorias de uma vez? E quanto ao preço, me lembra?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Sim, tudo de uma vez. O preço de um tronco padrão de bacout é dez dobrões. Além disso, para cada lote, você vai ter que entregar cinco garrafas de rum de qualidade e o mesmo número de garrafas de vinho. Rodgar garante que você não vai encontrar preços assim em nenhum outro lugar do mundo.";
			link.l1 = "De fato, concordo! Obrigado, Rodrigo. Vamos ao trabalho!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Excelente! Agora vamos voltar ao trabalho!";
			link.l1 = "Bom.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Claro, capitão, pode pegar. Temos os seguintes lotes prontos para o próximo embarque: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", isso é "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" toras. Portanto, você nos deve "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" doblões, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" garrafas de rum, e "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" garrafas de vinho, você tem tudo isso?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Claro. Aqui está o seu pagamento.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Parece que não tenho tudo. Vou trazer agora mesmo.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Excelente. Vamos transportar o bacout da fábrica para o seu armazém, de onde você pode retirá-lo quando quiser.";
				link.l1 = "Ótimo. Prepare o próximo lote.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Espere aí, capitão! Seu armazém está cheio – não vamos conseguir carregar todo o bacout colhido. Liberte um pouco de espaço no armazém e depois volte para falar comigo.";
				link.l1 = "Tudo bem, eu cuido disso.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Claro, capitão!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha! Capitão, receio que construir qualquer outra coisa seria uma tolice e um desperdício desnecessário. A menos que...";
			link.l1 = "A não ser o quê?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Capitão, é constrangedor para mim perguntar sobre isso... Você já investiu uma quantia considerável neste lugar!";
			link.l1 = "Um bordel?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Uma igreja?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Juro por São Tiago, isso até que não seria ruim! Mas na primeira noite, nossas mulheres iam botar fogo nisso. E na gente também. Não, capitão, estou falando de uma igreja. Sim, temos moradia decente e salário, o mar e diversão, famílias e amigos. Mas ainda assim, falta alguma coisa, entende?";
			link.l1 = "Posso imaginar.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Você me entende perfeitamente, capitão. Sim, temos moradia e salário decentes, o mar e diversão, família e amigos. Mas ainda assim, falta alguma coisa, entende?";
			link.l1 = "Posso imaginar.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Exatamente. Não podemos construir a Casa de Deus sem a sua ajuda. Um lugar assim precisa ser especial, precisa ser algo fora deste mundo. E, por isso, vai ser caro. Vamos precisar de velas, lingotes de ouro, âmbar e, claro, materiais de construção — e não dos mais baratos. Isso não vai te trazer nenhum lucro, então nem ouso pedir.";
			link.l1 = "Então, você precisa trazer um padre aqui?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Não.";
			link.l1 = "Já tem um padre entre vocês?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Não, capitão. E acho que você já entendeu tudo.";
			link.l1 = "Então, os santos padres da Inquisição tinham algum motivo para te perseguir? Vocês são hereges?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Pela lei canônica, somos os piores hereges. Não acreditamos que para se comunicar com Deus seja necessariamente preciso um intermediário deste mundo.";
			link.l1 = "Desse mundo?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Capitão, nós não somos satanistas, e nossa comunidade não é uma seita. Somos cristãos, como você, mas enxergamos as coisas de uma perspectiva muito ampla. Ampla demais, segundo algumas pessoas muito instruídas e respeitáveis. Se algum dia você se sentir aberto e disposto a entender, então eu lhe conto mais. Mas, por enquanto, apenas fique com essa lista. Só por precaução.";
			link.l1 = "Você devia ter me contado sobre isso antes, Rodrigo. Não quero voltar um belo dia e encontrar um sabá de bruxas ou o nascimento de uma nova fé nas minhas terras! Enquanto espera – tomarei uma decisão.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Lista impressionante. Estou começando a entender por que os padres precisam de tanto dinheiro! Vou pensar na sua proposta, Rodrigo, e tomar uma decisão.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Se for positivo, vou trazer todas as mercadorias da sua lista para o armazém, e vou espalhar os tesouros para você na mesa.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Se for positivo, vou trazer todas as mercadorias da sua lista para o armazém, e vou colocar os tesouros para você na mesa.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "Em nome de toda a nossa comunidade, eu te agradeço, capitão. Você não vai se arrepender disso, eu juro!";
			link.l1 = "Só vou me arrepender se você fizer algo completamente malfeito.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Capitão, todos os materiais de construção estão em estoque! Começaremos a obra assim que trouxer os itens de luxo da lista. Eles serão usados para joias e instrumentos rituais. Mais uma vez, muito obrigado, Capitão! Muchas gracias!";
			link.l1 = "De nada!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Muitíssimo obrigado, capitão! Está tudo pronto, vamos começar a construção. Volte daqui a alguns meses para o primeiro serviço. Ah, e mais uma coisa, as uvas estão maduras! Vamos fazer vinho caseiro, celebrar e festejar em sua homenagem!";
				link.l1 = "Acho que todos nós merecemos uma comemoração. Estarei de volta em dois meses.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Capitão, ainda há "+sAdd+" saiu.";
				link.l1 = "Claro, só me dê mais um tempinho, por favor. Sinceramente, se não fossem as velas, eu acharia que você vai enterrar um tesouro.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "E eu achando que você já tinha se livrado desse hábito idiota.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ha-ha-ha-ha-ha... ha. Eu também achei isso, capitão! Rodgar está certo, sua presença já significa, "+sTemp+"";
			link.l1 = "Já sei o que aconteceu. Houve alguma vítima?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Não se preocupe tanto, Rodgar. Não foi culpa sua, os fuzileiros chegaram rápido demais. De qualquer forma, não conseguiríamos mantê-los atrás das nossas linhas, e não houve tempo para acabar com todos eles à espada.";
			link.l1 = "E os espanhóis?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = " Só três deles conseguiram chegar até nós, e só um sobreviveu. O próprio capitão! Pelo visto, um oficial naval de alta patente. Mas ele ainda não pode nos ajudar – vai ter que ficar de cama por pelo menos mais alguns dias. Aliás, capitão, ouvimos tiros e, pelo seu estado, parece que você também.";
				link.l1 = "Pode-se dizer que sim. Os convidados indesejados claramente não esperavam uma visita tão inesperada e foram jogados de volta ao mar.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Somente três deles conseguiram chegar até nós, e só um sobreviveu. O próprio capitão! Pelo visto, um oficial naval muito respeitável. Mas ele ainda não pode nos ajudar – vai ter que ficar de cama por pelo menos mais alguns dias.";
				if (i >= 50) 
				{
					link.l1 = "Da última vez, deixei vários dos meus homens aqui de guarda, então vocês deviam ser bem mais numerosos que os fuzileiros. Por que não jogaram todos eles de volta ao mar de uma vez?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Certo, vamos resolver esse problema. O plano é o seguinte: vou atraí-los para um ataque aberto, e vamos fazer isso agora mesmo. Não faz sentido adiar. Preparem chumbo grosso e mosquetes, piratas nos portões, o resto fica em casa – e ninguém sai do lugar.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Capitão, eles são todos soldados profissionais, com um comandante. E nós nem temos armas de verdade. Sim, claro, poderíamos ter vencido pela quantidade, mas teríamos perdido pelo menos o dobro de gente, e cada pessoa aqui é valiosa e faz falta.";
			link.l1 = "Certo, vamos resolver esse problema. O plano é o seguinte: vou atraí-los para um ataque aberto, e vai ser agora. Não faz sentido esperar. Preparem chumbo grosso e mosquetes, piratas nos portões, o resto fica em casa – e ninguém sai do lugar.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Capitão, estamos prontos para lutar!";
			link.l1 = "Eu sei, Rodrigo. Mas você não me deixou terminar: se ao menos um inimigo conseguir passar pelos portões, todos vocês devem avançar sobre ele de todos os lados. E, na batalha, as chances de levar um tiro ou estilhaço diminuem. Mais alguma dúvida?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Muito bem! É uma pena, é claro, que um destino desses tenha recaído sobre seus compatriotas. Mas sou grato por você ter ficado do nosso lado mais uma vez.";
			link.l1 = "Não foi fácil, Rodrigo. As pessoas comuns chamariam isso de traição, e estariam certas.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Esta é a minha terra, Rodrigo. Ela deve ser sempre defendida, não importa de quem.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Sim, o velho Rodrigo não imaginava, quando deixou Cádiz, que tais aventuras o aguardavam no Novo Mundo.";
			link.l1 = "Nem me fale. Às vezes eu ainda tenho exatamente os mesmos pensamentos.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "É uma pena, é claro, que um destino desses tenha recaído sobre seus compatriotas. Mas sou grato por você ter ficado do nosso lado mais uma vez.";
			link.l1 = "Não foi fácil, Rodrigo. Qualquer pessoa comum chamaria isso de traição, e estaria certa.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Esta é a minha terra, Rodrigo. Ela deve ser sempre defendida, não importa de quem.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Entendo, capitão. Permita-me, então, lhe dar um breve panorama da situação em nosso assentamento durante a sua ausência.";
			link.l1 = "Sério? Espere... Capitão?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Entendo, capitão. Permita-me, então, lhe dar um breve panorama da situação em nosso assentamento durante a sua ausência.";
			link.l1 = "Sério? Espere... Capitão?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Não quis ofender. É que o Rodgar fala essa palavra de um jeito tão gostoso que eu quis experimentar também. Bem... coisa de pirata.";
			link.l1 = "Sem problema, só fiquei surpreso. Então, o que aconteceu aqui?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Primeiro, construímos a igreja. Vai levar um tempo, entre. Tem algo que quero lhe mostrar. Você fez uma grande coisa, capitão. Pode não parecer para você, mas poder se comunicar com Deus é algo muito, muito importante para nós. A partir de hoje, chamamos Isla Mona de nosso hogar.";
			link.l1 = "Lar, doce lar? Com certeza vou dar uma olhada. Será que carreguei todas aquelas velas à toa?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Não foi à toa! Em segundo lugar, a fábrica foi destruída – perdemos toda a mão de obra. Você vai ter que trazer um novo lote de escravos. Felizmente, depois de reavaliar a eficiência do trabalho, concluímos que dez escravos serão mais do que suficientes. Então, menos dor de cabeça pra você.";
			link.l1 = "Certo. Mais alguma coisa?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Está tudo pronto para a celebração. Bem, quase: precisamos dar uma arrumada aqui, enterrar os corpos desses pobres coitados... Então venha à igreja amanhã e começaremos.";
			link.l1 = "Na igreja? Lugar estranho pra começar a festa. Vai pedir alguém em casamento, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha! Não, capitão, embora algumas das nossas moças não se importassem. Não nos importamos se você quiser.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Combinado, vamos à igreja amanhã. Para rezar, é claro.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "E mais uma coisa, capitão. Antes da comemoração, vá lidar com o prisioneiro primeiro. A decisão precisa ser tomada, e eu entendo que vai ser desagradável de qualquer forma.";
			link.l1 = "Certo. Vou agora mesmo.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Todos estão aqui! Señor, não sabemos o que o senhor queria deste lugar no começo, nem como o vê agora. Para nós, primeiro foi um refúgio forçado, e agora se tornou um verdadeiro lar. Aqui vivem seus marinheiros, piratas e hereges espanhóis fugitivos. Em qualquer outro lugar do mundo, já teríamos cortado a garganta uns dos outros. Mas aqui, somos amigos, trabalhamos e aproveitamos a vida. Isla Mona não é o destino final no mapa deste mundo para nenhum de nós, mas talvez aqui passemos os anos mais felizes e produtivos de nossas vidas. E isso é mérito seu, é sua terra, é seu povo. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Certo, certo. Capitão, reunimos presentes para você – uma porção de coisas úteis e outras simplesmente agradáveis. Algumas trouxemos conosco, outras fizemos nós mesmos. Aceite este presente de coração aberto, e o resto lhe daremos com nosso trabalho.";
			link.l1 = "Obrigado... Eu não esperava por isso. São tão raros os momentos de luz e os gestos simples de humanidade na minha odisseia... Isso significa muito pra mim, acredite.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "E agora - de volta ao trabalho!";
			link.l1 = "Não, agora é—para a taverna! Rodrigo, vamos!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Sim, vamos aproveitar mais um pouco este momento maravilhoso.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hic!";
			link.l1 = "Aliás, percebi que você quase parou de rir feito louco de tudo e de nada. O ar fresco do Caribe?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Mais por causa da influência corrupta do Rodgar. Observando ele, aprendi a mandar tudo pro inferno.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Conheço muitas pessoas respeitáveis de lá.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Não, prefiro continuar bebendo rum e te encarando.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Capitão! Hic!";
			link.l1 = "Olá pra você também, Rodrigo. Vejo que sua noite foi agitada, hein?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Melhor... nem pergunte. Um mês... não vou beber. Ah. Tenho novidades! O capitão... voltou a si.";
			link.l1 = "O único espanhol sobrevivente?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hic! Ai! Sim, colocaram ele na factoría, numa casa sob guarda.";
			link.l1 = "Certo. Vou falar com ele. Tome cuidado para não exagerar.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Dei um mergulho, e agora está tudo como novo! Vamos viver e trabalhar. Vou tentar manter a factoría funcionando pelo máximo de tempo possível. Bom, e também fazer consertos, pequenas obras. Quem sabe até pensar em ter filhos com a minha.";
			link.l1 = "Feliz por todos vocês! Foi uma aventura muito tensa, cara... e maravilhosa, e fico feliz que tenha dado certo para nós. Boa sorte a todos, e para quem vai zarpar, ainda mais sorte!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Pare! Cabo "+GetFullName(npchar)+". Você entrou em uma zona de combate! Identifique-se imediatamente e diga o motivo da sua presença aqui!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Cabo, fique à vontade! "+GetFullName(pchar)+", capitão da Marinha Francesa. Ordeno que me escolte até seu oficial comandante. Cumpra a ordem!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", capitão do navio chamado '"+pchar.ship.name+"Cheguei nesta ilha totalmente por acaso – para possíveis reparos e para reabastecer o suprimento de água doce.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Sim, senhor, Capitão! Por favor, me siga. Só peço que tome cuidado! Esta ilha está cheia de bandidos.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Me desculpe, Capitão. O senhor não está de uniforme, então preciso verificar sua patente de oficial.";
				link.l1 = "Viu? Satisfeito? Agora - apresse-se e cumpra a ordem, cabo!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Você terá que vir comigo, Capitão. Nosso oficial superior vai falar com você. A partir deste momento, seu navio está temporariamente requisitado para as necessidades da Marinha Francesa. Avise imediatamente a guarda de plantão e me acompanhe.";
			link.l1 = "Requisitar o navio Charles Prince? Acho que não!";
			link.l1.go = "Capral_5";
			link.l2 = "Parece que não tenho escolha. Vou fazer como você disse.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Capitão, o caminho para o acampamento inimigo fica à nossa direita. Eu vou te acompanhar.";
				link.l1 = "Fique tranquilo, Cabo. Prefiro ir sozinho.";
			}
			else
			{
				dialog.text = "Capitão, o caminho para o acampamento inimigo fica à nossa direita. Você não vai se perder.";
				link.l1 = "Obrigado pela sua preocupação.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Capitão "+GetFullName(pchar)+"! Graças a Deus! Permita-me apresentar-me - Tenente "+GetFullName(npchar)+". Um grande admirador seu! Não sei o que está fazendo neste pedaço miserável de terra, mas chegou na hora certa!\nDevo dizer, Capitão, que você se tornou muito popular entre nossos oficiais. Embora muitos fiquem incomodados com seu... 'jeito especial' de servir, todos concordam que sua presença fortalece muito nossa frota. Estamos num impasse total no momento, então a ajuda de alguém como você não pode ser subestimada!";
				link.l1 = "O que eu posso fazer? E o que está acontecendo aqui?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Capitão "+GetFullName(pchar)+". Seu nome foi mencionado várias vezes nos relatórios da frota. E sempre de uma forma um tanto duvidosa. No entanto, agora você tem a chance de mudar essa reputação menos honrosa e servir à pátria.";
				link.l1 = "O que eu posso fazer? E o que está acontecendo aqui?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Estávamos no 'Warrior', uma missão rotineira – caçando saqueadores espanhóis especialmente ousados. O caso em si é bem simples: o espião indica a área e passa as informações sobre o alvo, e você pega eles além do horizonte. Não tem nada de especial pra contar, e acabou tudo muito mal: os espanhóis acharam a gente primeiro e atacaram, mesmo estando só num corveta. Se tivéssemos algo mais pesado, não teríamos ido pro fundo junto com eles... mas pelo menos conseguimos explodir todo o casco deles. Só meu grupo sobreviveu. Os castelhanos também tiveram alguns sobreviventes. Mas não por muito tempo, haha!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "A fragata 'Warrior'? O capitão Shocke está morto?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "I am not surprised that you asked about him, Captain. I heard about your involvement in intercepting the 'Alcantara'. A great feat; even then, you laid the foundation for your patent! Commander Shocke didn't die—quite the opposite! He was promoted and, at his request, sent to serve in the Mediterranean. We can only envy him, given our situation now. So, actually, about our situation...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Encontramos um assentamento na ilha – uma verdadeira toca de bandidos lotada de – escute só – piratas e espanhóis. Inacreditável! Sabe, normalmente esses desgraçados só sabem se matar e enforcar uns aos outros, mas aqui – veja só: bem no centro do arquipélago, eles trabalham juntos como uma família para extrair madeira de bucaneiro. Já viu o cais que construíram para eles mesmos? Não é de barquinho que chegam os visitantes desse lugar. Nossa missão é simples: com sua ajuda, tomamos o assentamento, pegamos a madeira de bucaneiro e os prisioneiros, e você leva todo mundo para Capsterburg. Enquanto isso, as autoridades que se virem... E enquanto elas se viram, a gente resolve a questão da madeira de bucaneiro e comemora direito com os outros oficiais do meu esquadrão!";
			link.l1 = "O que te impediu de tomar o assentamento para si até agora?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "O que nos impediu?! Temos apenas doze fuzileiros e sete marinheiros. Todos estão cansados e exaustos. Salvamos só cinco mosquetes, cada um com, no máximo, uma única carga! "+sTemp+"";
			link.l1 = "Mas você tem um plano?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Olha, não perdemos tempo. Primeiro de tudo, tomamos conta desta fábrica, pegando alguns mantimentos de comida e água, e o mais importante – um depósito cheio de madeira de bucaneiro e mais de uma dúzia de escravos! De qualquer forma, não conseguiríamos vigiar os escravos, então imediatamente fizemos um reconhecimento à força, mandando eles atacarem seus antigos donos sob a cobertura dos nossos mosquetes. Foi assim que descobrimos que os bandidos têm armas guardadas.";
			link.l1 = "Entendi direito que agora você quer mandar eu e meus homens lidar com essa arma em vez dos escravos?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Não, mas você pode ir até os bandidos sob uma bandeira de trégua. Sua chegada significa que o esconderijo deles foi descoberto, e agora os soldados do rei têm um navio e reforços. Bem, enquanto eles estiverem atentos e tentando entender a situação, chegue o mais perto possível do canhão, jogue uma granada de mão embaixo dele e não deixe que te matem até que nossos homens e os seus cheguem. Se não tiver certeza de que consegue, tente mandar um dos seus homens no seu lugar.";
			link.l1 = "Deixe-me ir até eles primeiro, sem a bomba, e oferecer uma chance de se renderem. Vou observar, avaliar o humor e a força deles, e plantar a dúvida em seus corações. Se não se renderem, aí sim volto até eles, mas com a bomba.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... e até lá, eles já vão estar acostumados com você, então vai ser mais fácil fazer a sabotagem! Esperto! Bem, não esperava menos de você, Capitão. Siga quando estiver pronto. Mas ainda assim, aqui... Pode ser útil.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... e até lá, eles já vão estar acostumados com você, então vai ser mais fácil fazer o sabotagem. É isso que vamos fazer. Continue!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Houve uma longa batalha com os espanhóis nesta região. Ambos os navios afundaram, e os sobreviventes vieram parar aqui. A maioria são franceses, mas alguns dos nossos inimigos também conseguiram sobreviver. E você não precisa saber mais do que isso, desculpe, Capitão. Informação confidencial, espero que entenda.";
			link.l1 = "Entendido.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Encontramos um assentamento na ilha – uma verdadeira toca de bandidos, e veja só: piratas e espanhóis juntos. Inacreditável! Normalmente esses desgraçados só sabem se matar e enforcar uns aos outros, mas aqui – veja você: bem no coração do arquipélago, trabalham juntos como uma família para extrair madeira de bucaneiro. Já viu o cais que construíram para eles mesmos? Não é de barquinho que os visitantes chegam ali. Nossa missão é bem simples: com a sua ajuda, tomamos o assentamento, pegamos a madeira de bucaneiro e os prisioneiros, e você leva todo mundo para Capsterburg. Enquanto isso, as autoridades vão se virar... E enquanto eles se resolvem, talvez eu até deixe você pegar um pouco de madeira valiosa para o que precisar.";
			link.l1 = "O que te impediu de tomar o assentamento sozinho até agora?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Aí está você! Alguma novidade?";
			link.l1 = "Isso é uma guarda de honra?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Obviamente, uma decisão será tomada em breve sobre nossos próximos passos. Eu não gostaria de ter que procurar meu pessoal pela ilha inteira para dar novas ordens.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Excelente iniciativa! Você receberá suas ordens. Fiz o reconhecimento: o inimigo está fraco e o canhão sem munição. Ordeno que ataque imediatamente o covil dos bandidos, tenente. Pare de ficar se lamentando. Só mais um dia na frota. Execute!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "Na minha opinião, você poderia tê-los pegado logo depois daquele reconhecimento dos 'escravos', à força mesmo. A defesa deles é ridícula, só uns poucos que sabem lutar de verdade. Não tem por que complicar – já podíamos estar bebendo vinho de saque sentados em cima de um monte de pau-ferro.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Afirmativo, Capitão!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "E esses são os resultados do seu reconhecimento? Eu entendo que pode ser estranho esperar demais de alguém que não é militar, mas eu preciso de fatos! Fatos, Capitão, não a sua opinião!";
			link.l1 = "Você me ofende, tenente. Reportando!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Neste momento, há um capitão sobrevivente de um navio espanhol que você afundou conosco. Um comandante experiente que logo vai se recuperar. Se você demorar, ele vai se reerguer e organizar a defesa conforme a ciência militar, e aí teremos problemas. Precisamos agir rápido – repito, eles estão fracos e desmoralizados.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Os reforços estão chegando em breve – para tomar a madeira do bucaneiro. Não acho que seja blefe: você mesmo viu os cais e a pilha de mercadorias prontas para entrega no armazém da fábrica. Precisamos nos apressar – repito, eles estão fracos e desmoralizados. Se você demorar, vai acabar esperando a chegada de um navio pirata.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Quase metade dos habitantes desse buraco são mulheres. Você nem chegou a lutar com a milícia: durante todo esse tempo, não houve mais do que uma dúzia de combatentes contra você. Eles estão fracos e desmoralizados.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Pense nos troféus e na glória, Tenente! Uma vitória solo sobre um corsário espanhol, capturar o covil de bandidos e uma fonte única de madeira de bucaneiro – tudo isso pede que você comande seu próprio navio! Repito, eles estão fracos e desmoralizados, é hora de esmagá-los!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Essas informações são valiosas, e você estava certo, não há motivo para demorarmos aqui. Meus homens estão todos aqui, somos fortes, treinados e estamos prontos. Tudo estará resolvido em meia hora. Capitão, por favor, prepare-se para receber pessoas, prisioneiros e carga em seu navio. Não vamos ficar aqui por muito tempo.";
				link.l1 = "Está tudo pronto, Tenente. Só estávamos esperando por você. Até mais!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Isso é uma informação valiosa. Nesse caso, vá até o cais e prepare sua equipe de abordagem. Vamos invadir o covil dos bandidos juntos, e imediatamente. Os melhores dos meus homens e dos seus vão liderar a vanguarda – serão eles que tomarão os portões. O restante discutiremos depois que inspecionarmos nossas forças juntos. Não me decepcione, nem ao seu país, "+GetFullName(pchar)+".";
				link.l1 = "...Então tá. Até mais, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Isso é uma informação valiosa, e você estava certo, não há motivo para demorarmos aqui. Meus homens estão todos aqui, somos fortes, treinados e estamos prontos. Tudo estará resolvido em meia hora. Capitão, por favor, prepare-se para receber pessoas, prisioneiros e carga em seu navio. Não vamos ficar aqui por muito tempo.";
				link.l1 = "Está tudo pronto, Tenente. Só estávamos esperando por você. Até mais!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Isso é uma informação valiosa. Nesse caso, vá até o cais e prepare sua equipe de abordagem. Vamos atacar o covil dos bandidos juntos, e imediatamente. Os melhores dos meus homens e dos seus vão liderar a vanguarda – serão eles que tomarão os portões. O resto discutiremos depois de inspecionarmos nossas forças juntos. Não decepcione a mim nem ao seu país, "+GetFullName(pchar)+".";
				link.l1 = "...Então está bem. Até mais tarde, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 70, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Essas informações são valiosas, e você estava certo, não há motivo para demorarmos aqui. Meus homens estão todos aqui, somos fortes, bem treinados e estamos prontos. Tudo estará resolvido em meia hora. Capitão, por favor, prepare-se para receber pessoas, prisioneiros e carga no seu navio. Não vamos ficar aqui por muito tempo.";
				link.l1 = "Está tudo pronto, Tenente. Só estávamos esperando por você. Até mais!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 70, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Isso é uma informação valiosa. Nesse caso, vá até o cais e prepare sua equipe de abordagem. Vamos atacar o covil dos bandidos juntos, e imediatamente. Os melhores dos meus homens e dos seus vão liderar a vanguarda – serão eles que tomarão os portões. O resto discutiremos depois que inspecionarmos nossas forças juntos. Não me decepcione, nem ao seu país, "+GetFullName(pchar)+".";
				link.l1 = "...Então tá. Até mais, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Essas informações são valiosas, e você estava certo, não há motivo para demorarmos aqui. Meus homens estão todos presentes, somos fortes, bem treinados e estamos prontos. Tudo estará resolvido em meia hora. Capitão, por favor, prepare-se para receber pessoas, prisioneiros e carga em seu navio. Não vamos ficar aqui por muito tempo.";
				link.l1 = "Está tudo pronto, tenente. Só estávamos esperando por você. Até mais!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Esta informação é valiosa. Nesse caso, vá até o cais e prepare sua equipe de abordagem. Vamos atacar o covil dos bandidos juntos, e imediatamente. Os melhores dos meus homens e dos seus vão liderar a vanguarda – serão eles que tomarão os portões. O restante discutiremos depois de inspecionarmos nossas forças juntos. Não decepcione a mim nem ao seu país, "+GetFullName(pchar)+".";
				link.l1 = "...Então está bem. Até logo, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				Notification_Skill(true, 90, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Isso é uma informação valiosa, e você estava certo, não há motivo para demorarmos aqui. Meus homens estão todos aqui, somos fortes, treinados e prontos. Tudo estará resolvido em meia hora. Capitão, por favor, prepare-se para receber pessoas, prisioneiros e carga no seu navio. Não vamos ficar aqui por muito tempo.";
				link.l1 = "Está tudo pronto, tenente. Só estávamos esperando você. Até mais!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 90, SKILL_LEADERSHIP);
				dialog.text = "Obrigado, Capitão. Isso é uma informação valiosa. Nesse caso, vá até o cais e prepare sua equipe de abordagem. Vamos invadir o covil dos bandidos juntos, imediatamente. Os melhores dos meus homens e dos seus vão liderar a vanguarda – serão eles que tomarão os portões. O resto discutiremos depois que inspecionarmos nossas forças juntos. Não decepcione a mim nem ao seu país, "+GetFullName(pchar)+".";
				link.l1 = "...Então tá. Até mais, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "E eu, tolo que sou, admirei você! A-agh! O orgulho da França, Capitão "+GetFullName(pchar)+"!! Você não é digno da sua patente!!!";
			else dialog.text = ""+GetFullName(pchar)+", canalha, traidor e maldito pirata! Eu devia ter imaginado que esse covil miserável era o seu domínio fedorento! A França não esquece nem perdoa homens como você!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Está pronto, Capitão? Sua tripulação parece à altura!";
			link.l1 = "Obrigado, tenente. Vamos começar?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Sim, vamos prosseguir imediatamente!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha! "+GetFullName(pchar)+"! Que encontro. Ei, peguem ele! Esse desgraçado é dono de tudo aqui! Essa ilha é dele!";
			link.l1 = "Que dia é esse...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Capitão, quais são as ordens? Recebemos um sinal para aguardar e preparar o grupo de abordagem.";
			link.l1 = "A ordem está dada. Rapazes, venham comigo, precisamos limpar nossa casa desses intrusos. O prêmio é meu, todos os troféus são de vocês!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Viva!";
			link.l1 = "À batalha!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Saudações, senhor. É o dono destas terras? Permita-me apresentar: sou o grande Francisco de Alba, ex-capitão da corveta 'Perro Marino'.";
			link.l1 = "Sim, esta é a minha terra. Eu sou "+GetFullName(pchar)+", capitão do navio '"+pchar.ship.name+"'. Grandioso? Nunca tivemos convidados tão distintos aqui antes.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Oh, Monsieur "+GetFullName(pchar)+"! Seu nome é bem conhecido. Veja, ultimamente o seu nome tem aparecido com tanta frequência nos relatórios da Casa de Contratação que eu realmente esperava receber ordens para lidar com você.";
			link.l1 = "Vai negociar comigo?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Acho que não faz sentido fingir. Meu trabalho é caçar e destruir os inimigos da Espanha e do rei Filipe em todos os mares do mundo.";
			link.l1 = "É uma sorte que tais ordens ainda não tenham chegado. Você é claramente um oficial naval muito habilidoso.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "O fato de eu estar agora meio morto, prisioneiro numa ilhota cheia de piratas, com meus compatriotas fugindo, só confirma sua conclusão, ha-ha! Foi uma missão muito perigosa, mas ordens são ordens. Quase conseguimos! Sinto muito pelos meus homens – conhecia todos pelo nome, servimos juntos por muitos anos. Mas meu país vai ter que derramar ainda mais sangue de seus filhos para manter seu status imperial. Nossa família entende isso melhor do que a maioria.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Vamos voltar a assuntos mais urgentes por agora. O que eu faço com você, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Aliás, Monsieur de Mor, o 'Warrior' — aquele barquinho era conhecido seu, não era? Sua operação ousada em Porto Bello não passou despercebida. Corajosa, até suicida. Você estava mesmo precisando de dinheiro, não é? Ha!";
			link.l1 = "Você sabe muito sobre mim, Grand. Mas vamos falar do seu destino.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "O que há para pensar? Como em qualquer boa história, você tem três opções: me matar, me deixar aqui ou me libertar. Se me libertar, dou a palavra da família de Alba de que nunca contarei a ninguém sobre este lugar ou seu envolvimento nas minhas desventuras. Além disso, ficarei em dívida com você, e até que essa dívida seja paga, nunca lutarei contra você.";
			link.l1 = "Não posso arriscar, vovô.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Você vai passar um tempo aqui. Vai viver e trabalhar em igualdade com seus compatriotas.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Bem-vindo a bordo do meu navio, Grand. Vou deixá-lo em terra no farol de Santiago quando chegar a hora. Espero que cumpra sua palavra.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Eu entendo, señor. Bem, de qualquer forma, já estou morto naquela batalha junto com meus homens. É um bom desfecho.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Eu admito, não gosto de fazer nada pela metade. Mas não há desonra em ser prisioneiro, então aceito seu presente de vida e vou viver em paz com esse povo gentil e aparentemente muito feliz. No entanto, se um dia eu sair daqui, não lhe devo nada.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Dou-lhe minha palavra, e a palavra da família de Alba! Nos vemos no navio!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Capitão "+GetFullName(pchar)+"! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "Um pedaço de um mapa?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Isso era tudo de valor que eu tinha comigo. Não tenho dúvidas de que você vai encontrar a outra parte facilmente. Adeus! E boa sorte para você, meu amigo.";
			link.l1 = "Até logo, Grand. Lembre-se da sua palavra, e boa sorte pra você!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Saudações! Como vai, Capitão? As coisas estão indo bem para nós.","Trabalhar para a comunidade é a maior alegria!","Sua ilha é maravilhosa, Capitão, e faremos tudo o que pudermos para que ela prospere.");
			link.l1 = LinkRandPhrase("Que bom ouvir isso.","Fico feliz em saber que está tudo bem.","Admiro seu entusiasmo, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Não leve a mal, señor, mas viver aqui é impossível.","Qualquer coisa é melhor do que ficar preso nas celas da Inquisição..."),RandPhraseSimple("Obrigado por nos salvar, Capitão.","Esses... piratas são seus amigos?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Não é ruim aqui! Só é meio sem graça.","Capitão, bom te ver. Passe aqui quando puder!"),RandPhraseSimple("Alguém encontrou caveiras na praia e trouxe para a reunião da manhã. Isso aqui é sempre assim?","Vou te contar um segredo, Senhor Jiménez claramente se beneficia do ar fresco e da segurança deste lugar."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Aqui não é ruim! Só um pouco sem graça.","Capitão, bom te ver. Apareça quando puder!"),RandPhraseSimple("Alguém encontrou caveiras na praia e trouxe para a reunião da manhã. Isso aqui é sempre assim?","Vou te contar um segredo, Señor Jimenez claramente se beneficia do ar fresco e da segurança deste lugar."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Deus te abençoe, Capitão!","Uma vez por semana, fazemos apresentações na praia e na taverna. Passe por lá qualquer hora."),RandPhraseSimple("Seus marinheiros estão sempre trazendo todo tipo de bugiganga em troca de comida fresca. Obrigada por incentivar isso.","É incrível como este lugar ainda não foi descoberto. Espero que continue assim."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Obrigado, señor. Graças a você, conhecemos o verdadeiro Novo Mundo. Que Deus te abençoe!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Segurança e tranquilidade – é isso que eu gosto deste lugar!","Um paraíso maravilhoso! Bem, quase...","Estamos felizes por termos encontrado um novo lar aqui, depois de tantas dificuldades.");
			link.l1 = LinkRandPhrase("Fico feliz por você e pela sua comunidade.","Sim, eu também gosto desta ilhazinha.","É bom saber que você está satisfeito.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Olá.","Senhor, quem são aqueles... homens rudes armados?","Obrigado por nos salvar, Capitão.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Nossos homens fizeram um ótimo trabalho – as casas ficaram excelentes. Mas nós também nos esforçamos muito!","Senhor Capitão, não se preocupe: as mulheres do nosso pequeno clã não têm medo de dificuldades nem de desconfortos temporários.","Que ar puro aqui! E o mar! Dá até pra sentir Deus mais perto!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Nossos homens fizeram um ótimo trabalho - as casas ficaram excelentes. Mas nós também nos esforçamos muito!","Senhor Capitão, não se preocupe: as mulheres do nosso pequeno clã não têm medo de dificuldades nem de desconfortos temporários.","Que ar maravilhoso aqui! E o mar! Dá até pra sentir Deus mais perto!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Volte mais vezes, Señor Capitão. Fico sempre feliz em te ver.","Senhor Rodgar é um contador de histórias incrível. Eu poderia ouvi-lo falar para sempre!","Hehe. Dizem que alguém do nosso grupo já está esperando um novo membro na família. A vida segue até mesmo na Isla Mona!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Você... Muchas gracias, senhor! Apareça mais vezes...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Está tudo certo, capitão!","Os escravos estão sob controle, não se preocupe."),RandPhraseSimple("Você não precisa se preocupar, motim está fora de questão.","Obrigado pelo rum! Vamos começar a trabalhar!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Espanhóis? Não esperávamos isso de você.","Agora temos que andar até a praia só para conseguir dormir em paz!"),RandPhraseSimple("Por que você decidiu por tudo isso, hein, Capitão?","O chefe confiou em você naquela época - e ele não estava errado. Vamos acreditar em você de novo."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Depois de um trabalho exaustivo, não é pecado tomar um ou dois drinques...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("Aproveite sua bebida, compadre, ha-ha!","Relaxa, camarada, só não exagera, senão a esposa vai te dar uma bronca, ha-ha!","Calma, amigo, a vida não é só trabalho!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitão, belo lugar que você tem aqui!","Imagine se de repente ficássemos sem rum. Você com certeza arranjaria mais, não é?"),RandPhraseSimple("Eu sonhei com umas férias assim por muito tempo. Mas queria mesmo era um bordel... só uma ideia maluca, Capitão.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Obrigado pelo tempo livre, Capitão.","Belo lugar que você construiu aqui – você realmente tem talento para manter tudo em ordem, Capitão."),RandPhraseSimple("Comida fresca, bebida, chão firme sob os pés. Isso é um sonho.","Eu gostaria de ficar aqui um pouco mais."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Estou tão cansado - mal consigo ficar de pé.","Não tenho mais forças para viver assim!"),RandPhraseSimple("Esse trabalho é pesado demais pra mim.","Os capatazes não deixaram uma célula viva na minha pele!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Posso ajudar em alguma coisa, capitão?","Entra, prova uma paella local. Só, pelo amor de Deus, não pergunta do que ela é feita!","Bem-vindo, capitão. O que achou daqui?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Senhor, seja bem-vindo!","Olá, capitão. Vai ficar?","Você veio por mim? Por favor, entre, não repare na bagunça, señor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}