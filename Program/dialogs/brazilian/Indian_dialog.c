// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Não temos nada para conversar!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","Índia branca")+" quer conversar?","Você de novo, "+GetSexPhrase("Rostinho Pálido","Índia branca")+".",""+GetSexPhrase("O Paleface gosta de falar. Ele parece uma índia.","Índia branca gosta de conversar.")+"","Os espíritos trouxeram meu rosto pálido "+GetSexPhrase("irmão","irmã")+" para mim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim.","Sim, sou eu de novo.","Muito poético.","Também fico feliz em te ver.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Me diga, por que você veio, cara pálida?";
			link.l1 = "Ah, nada em especial, só queria ouvir o que você tinha a dizer...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("Homem branco quer conversar?","Você de novo, cara pálida?","O Cara-Pálida gosta de falar.","Os espíritos trouxeram meu irmão de rosto pálido até mim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim.","Sim, sou eu de novo.","Muito poético.","Também estou feliz em te ver.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" ouvir você, filho do mar.","O que você quer de "+npchar.name+", cara-pálida?","Estou ouvindo o que você tem a dizer, estranho.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Tenho algo para você. Quer dar uma olhada?","Quer dar uma olhada em algo realmente interessante? Tenho certeza de que vai gostar...","Tenho algo que vai te agradar, filho da selva. Quer dar uma olhada?");
				link.l1.go = "gift";
			}
			link.l9 = "Ah, nada em especial, só queria ouvir o que você tinha a dizer...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" quer olhar. Mostre.",""+npchar.name+" está interessado. Mostre-me.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Me dê um espelho.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Agora "+npchar.name+" agora pode se olhar não só nas águas do rio! Muito obrigada, bondoso estranho!";
			link.l1 = "Pronto, agora você pode admirar seu rosto o quanto quiser...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Que lindo! Esta pulseira é para "+npchar.name+"? Obrigado, gentil estranho!";
			link.l1 = "Coloque isso na sua mão morena, beleza, você vai ficar deslumbrante...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Que anel lindo! É para "+npchar.name+", sim? Obrigado, bondoso estranho!";
			link.l1 = "Coloque no seu dedo, e todos os seus amigos vão ficar morrendo de inveja...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Essas contas verdes maravilhosas são para "+npchar.name+"? Que lindo! Obrigada, gentil estranho!";
			link.l1 = "Adorne seu pescoço com elas, filha da selva. Todos vão te admirar...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh, que anel verde lindo! Isso é um presente para "+npchar.name+"? Obrigado, bondoso estranho!";
			link.l1 = "Vai ficar lindo na sua mão, bela...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Queria perguntar "+npchar.name+" Alguma coisa, filho do mar? ";
				link.l1 = "Você tem razão, bela. Meus guerreiros destemidos e eu vamos para a selva, até o assentamento espanhol nas montanhas, e estamos procurando um guia. Serei generoso tanto com o homem quanto com sua esposa. Tenho muitas riquezas: armas bonitas, óculos mágicos, espelhos, colares, pulseiras e anéis. Talvez seu marido possa ser o guia que procuramos?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Saudações, filho do mar. Sou Kumwana, chefe do clã da Tartaruga do povo Locono. O que traz você à minha aldeia?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Trouxe um presente para você, chefe. Dá uma olhada, vai gostar.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Chefe, vim pedir a sua ajuda. Quero chegar a um assentamento espanhol chamado Merida. Fica nas montanhas da sua selva, mas o problema é que não sei como chegar lá.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "Isso é muito bom pra você, filho do mar, não saber o caminho até lá. Ele passa por uma floresta, terra da destemida tribo Capong. Verdadeiros jaguares, eles são, oh-ey! Eu nunca vou praquele lugar dos espanhóis. Meu povo é um povo pacífico, não vamos pra terra dos Capong. Kumwana não pode te aconselhar. O caminho é perigoso demais.";
			link.l1 = "Mas os espanhóis acharam um jeito de chegar lá! E eu não tenho medo desses espanhóis...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Mas você deveria. Eles são pessoas cruéis. Mataram muitos do meu povo na floresta. Kumwana contou tudo.";
			link.l1 = "Merda...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Você de novo, filho do mar. O que quer dizer a Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Trouxe um presente para você, chefe. Dá uma olhada, você vai gostar.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "A esperança de encontrar Merida ainda está comigo...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Os Locono sempre ficam felizes em ver bons amigos.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Presentear uma pistola."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Dar uma bússola de presente.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Presenteie com uma luneta barata.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Presenteie com uma luneta comum."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Me dê um bom telescópio."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Que arma de rosto-pálido impressionante! Kumwana aceita seu presente! Você também, filho do mar, aceite um presente de Kumwana e do povo Locono.";
			link.l1 = "Obrigado, chefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Amuleto mágico dos rostos-pálidos! Kumwana aceita seu presente! Você também, filho do mar, aceite um presente de Kumwana e do povo Locono.";
			link.l1 = "Obrigado, chefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Tubo mágico dos rostos-pálidos! Kumwana aceita seu presente! Você também, filho do mar, aceite um presente de Kumwana e do povo Locono.";
			link.l1 = "Obrigado, chefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Tubo mágico dos rostos-pálidos! Kumwana aceita seu presente! Você também, filho do mar, aceite um presente de Kumwana e do povo Locono.";
			link.l1 = "Obrigado, chefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Tubo mágico dos rostos-pálidos! Kumwana aceita seu presente! Você também, filho do mar, aceite um presente de Kumwana e do povo Locono.";
			link.l1 = "Obrigado, chefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "O que traz você à nossa vila, filho do mar?";
			link.l1 = "Chief, I've come to ask for your assistance. I want to reach a Spanish settlement called Merida; it's located among the mountains in your selva. The problem is, I don't know how to get there. Perhaps you could provide me with a brave warrior who could show us the way?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Estrada perigosa, perigosa. O caminho passa por uma floresta, terra da destemida tribo Capong. Verdadeiros jaguares, eles são, oh-ey! Eu nunca vou naquele lugar dos espanhóis. Meu povo é um povo pacífico, não vamos para a terra dos Capong.";
			link.l1 = "Eu realmente preciso chegar a Mérida. Kumwana, por favor, pergunte aos seus homens, talvez alguém aceite se juntar à minha unidade? Meus guerreiros são experientes, bem armados e não temem nada, nem mesmo o Diabo. Vamos proteger o guia e recompensá-lo generosamente quando tudo terminar.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Muito bem, filho do mar. Vou reunir um círculo de guerreiros e contar a eles sobre seus desejos. Venha me ver amanhã, depois do amanhecer.";
			link.l1 = "Obrigado, chefe!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! Você de novo, filho do mar. O que quer dizer a Kumwana?";
			link.l1 = "Ainda nada, chefe.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Escuta, Kumwana. Meu povo e eu realmente precisamos atravessar o rio e chegar àquela maldita cidadezinha. Deixa eu te explicar o quanto isso é crucial pra gente.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Meus caçadores já lhe informaram que...";
			link.l1 = "Não precisa se repetir, Kumwana. Mas olhe lá fora – e não superestime suas habilidades. Meus homens valentes, que vieram aqui atrás das pedras espanholas, estão espalhados pela sua aldeia. E a paciência deles está se esgotando. E o que vai acontecer quando ela acabar de vez, é melhor você nem saber – acredite em mim.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Cale a boca e escute, macaco de pele vermelha. Meu povo pode ser muito mais temido do que esses malditos Kapongs. Não se deixe enganar pela nossa gentileza agora. Dou a você uma escolha simples: ou encontra um guia em vinte e quatro horas, ou vamos amarrar todos vocês e mandar pela selva na frente do nosso grupo. Se nos levar para o lado errado, você mesmo vai morrer nos pântanos ou será levado amarrado para lutar contra os Kapongs. Entendeu?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, eu preciso desse guia. Viemos de muito longe, e eu realmente não quero dizer aos meus homens que foi tudo em vão.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana já disse, nenhum dos Lokono quer ir com o cara pálido.";
			link.l1 = "E você não pode fazer nada a respeito? Fale com alguém pessoalmente. Dê uma ordem, afinal de contas. Você é o chefe ou não?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "O chefe não força o índio. O chefe governa e quer paz para seu povo. Os índios sabem – os Kapong vão ver que os Lokono trazem os rostos-pálidos. Suas cabeças serão levadas por Kanaima. Eles vêm para se vingar dos Lokono. Kapong – para matar. Capturar os Lokono, fazer escravos.";
			link.l1 = "E quem arrancou suas cabeças? Que espírito ou demônio faz dos índios vermes tão covardes? Bem, talvez eu realmente tenha que abandonar a campanha contra Mérida. Mas lembre-se de uma coisa, cacique. Sempre que me perguntarem o que sei sobre os Lokono, responderei sem hesitar – que são uma tribo de covardes inúteis. Liderados por um chefe tão covarde e míope quanto eles, cujo rosto se contorce numa careta de horror só de lembrar dos Kapongs. Você não vai conquistar glória entre os índios, nem respeito entre nós, os rostos-pálidos.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "O cara-pálida não conhece os costumes dos índios...";
			link.l1 = "Eu sei o suficiente para saber a quem os índios chamam de covarde e a quem chamam de bravo guerreiro. Adeus, Kumwana. E lembre-se das minhas palavras. Você é um governante covarde e de visão curta.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Por que me ameaçar assim? Achamos que você é uma boa pessoa...";
			link.l1 = "Estou bem, desde que você colabore, entendeu? Você tem um dia. E pode acreditar, meus homens fazem tudo o que eu mando. Somos mais fortes. E se duvidar... Eu vi sua esposa. E suas filhas. Acho que agora você entendeu o recado.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Por que me ameaçar assim? Achamos que você é uma boa pessoa...";
			link.l1 = "Estou bem, desde que você colabore, entendeu? Você tem um dia. E pode acreditar, meus homens fazem tudo o que eu mando. Somos mais fortes. E se duvidar... Eu vi sua esposa. E suas filhas. Acho que agora você entendeu o recado.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana entende, cara pálida. Na aldeia, há um caçador chamado Tagofa. Talvez ele possa te guiar até o assentamento...";
			link.l1 = "Voltarei em vinte e quatro horas. Charlie Prince não tem mais nada a dizer, selvagem.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Filho do mar, é você. Kumwana falou com os guerreiros dos Locono.";
			link.l1 = "E aí? Já tem um voluntário?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Temos alguns caçadores por aqui que já estiveram lá. Mas eles têm medo dos Capongs, dizem que as onças estão furiosas. Eles não vão, dizem que o Capong vai matar seu grupo. Eles não têm medo de brancos.";
			link.l1 = "Meus guerreiros são muito superiores a qualquer um deles! Parte da minha tropa passou a vida inteira na selva! Não somos simples amadores!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Me desculpe, filho do mar. Meus caçadores estão com medo, os Capongs são muito, muito perigosos.";
			link.l1 = "Então talvez eles possam explicar como chegar lá? Com detalhes.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Para chegar lá, você deve navegar pelo rio e depois desembarcar em um ponto específico. Se escolher o lugar errado, vai acabar no pântano e morrer. Nossa selva é cheia de perigos. Você não vai encontrar esse lugar sozinho, filho do mar.";
			link.l1 = RandSwear()+"E o que devo fazer então? Como posso convencer seus caçadores?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana, não precisa dizer mais nada, filho do mar.";
			link.l1 = "Tudo bem...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Meu marido Tagofa é o melhor caçador da tribo. Oh-ey! "+npchar.name+" tem orgulho do marido. "+npchar.name+" costuma ir com Tagofa na Selva. Vai para longe. Tagofa sabe onde fica o assentamento espanhol.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Tagofa sabe o caminho para a cidade espanhola que os rostos-pálidos chamam de Mérida?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Então, então... Tagofa sabe como chegar à cidade espanhola?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Meu marido não vai pra selva, filho do mar. Ele pesca peixes. Bom pescador, oh-ey! ","Meu marido é um bom caçador, oh-ey, mas ele não vai fundo na selva."),RandPhraseSimple("Um jaguar feriu meu marido durante a caça. Agora ele fica na aldeia fazendo flechas, oh-ey!","Seis luas atrás, três Capongs atacaram meu marido. Agora ele não sai mais para caçar longe da aldeia. Nunca! Oh-ey!"));
				link.l1 = LinkRandPhrase("Pena...","Que pena...","Que pena..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa cresceu nesta selva. Ele conhece cada árvore e cada pedra daqui!";
			link.l1 = "Eu vou dar muitos presentes para você e para o Tagofa se ele nos levar até lá. Joias, armas, o que quiser. Qualquer coisa que pedir. Dentro do razoável, é claro, he-he. Como posso falar com seu marido?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa não vai com o cara-pálida. Tagofa vai ficar na aldeia. Vai caçar. Não lute com os Kapong.";
			link.l1 = "Ele não vai precisar lutar contra os Kapong. Assim que vê-los, pode se esconder. Só o meu povo vai lutar.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Não, yalanaui. O cara-pálida nunca cumpre sua palavra. O cara-pálida fala – e a palavra logo voa para o vazio. Os Kapong vão matar Tagofa e depois virão para nossa aldeia, matar os Lokono.";
			link.l1 = "Você acha que esses Kapongs são tudo com o que você precisa se preocupar? Você está muito enganado...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu vai entrar no rosto-pálido! Hayami não vai mais falar com yalanaui.";
			link.l1 = "Ora, ora...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa went hunting a day ago. Promised to come back tomorrow when the sun sleeps. Come tomorrow, son of the sea, I will be with Tagofa in that hut; as you walk into the village, walk to the right. I will ask him if he will go or not go with you.";
			link.l1 = "Diga ao Tagofa que vou lhe dar a pistola mais bonita. E para você, vou presentear com muitas joias.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Os Lokono não confiam nos Yalanaui. Os Yalanaui enganam os índios, fazem deles escravos. Mas os Lokono ouviram falar de você, cara-pálida. Minha confiança é sua. Venha amanhã depois do pôr do sol, filho do mar. Estarei com Tagofa naquela cabana. Vou perguntar a ele se vai com você ou não.";
			link.l1 = "Diga ao Tagofa que vou dar a ele minha melhor pistola. E para você, tenho muitas joias.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			Notification_Perk(true, "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" está feliz em ver um filho do mar. Tagofa voltou. Mas ele bebeu kasheeri demais e está dormindo. Não o acorde, Tagofa está descansando. Eu vou falar.";
			link.l1 = "Muito bem, "+npchar.name+". O seu marido vai nos guiar até Mérida?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa concordou em guiar seus guerreiros pela selva até a vila espanhola. Mas há condições...";
			link.l1 = "Quais?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Você protege Tagofa dos guerreiros Capong. Tagofa não luta contra espanhóis nem Capong. Se ele enfrentar perigo, vai fugir e ninguém vai encontrá-lo, ele é o melhor caçador Locono.";
			link.l1 = "Entendo. Você se preocupa com seu homem, isso é compreensível. Prometo que vamos cuidar de todos esses Capongs nós mesmos.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa quer presentes do filho do mar: um pequeno para atirar muitas pedras e um grande para atirar uma pedra só, os bonitos. E também quer balas para cada arma: tantas quanto os dedos das duas mãos, três vezes.";
			link.l1 = "Opa! Seu homem entende mesmo de armas, hein? Muito bem. O que mais?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "E Tagofa quer um belo olho mágico dos rostos-pálidos.";
			link.l1 = "Uma luneta? Tudo bem. Mais alguma coisa?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Chega para Tagofa. "+npchar.name+" quer coisas bonitas. Um anel de ouro com uma pedra vermelha grande, e colares feitos de muitas, muitas pedras verdes. "+npchar.name+"Eu vi isso no White Mary em Maracaibo.";
			link.l1 = "Um anel de ouro com contas de rubi e jade?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Não é jade. É brilhante e os homens brancos dão valor a isso.";
			link.l1 = "Esmeralda? Miçangas de esmeralda?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+"sabe alguma coisa sobre joias! Muito bem, você vai conseguir.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Traga tudo para "+npchar.name+" juntos, filho do mar. Então Tagofa vai guiar você e seus guerreiros. Não perca tempo, em meia lua Tagofa e eu iremos para a aldeia vizinha. Para um grande dia. Agora vá, "+npchar.name+" quer dormir.";
			link.l1 = "Não vou te fazer esperar muito. Até logo.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Você trouxe o quê "+npchar.name+" e Tagofa perguntou?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Sim. Está tudo conforme a sua lista.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Não, ainda estou trabalhando nisso.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" está feliz, filho do mar. Agora te chamo de marido. Ele vai com você. Mas lembre-se do que prometeu a "+npchar.name+"!";
			link.l1 = "Sim, sim, eu me lembro de tudo. Vou mantê-lo seguro, não se preocupe.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Guarde sua arma, cara-pálida, ou vamos fazer isso por você!";
			link.l1 = LinkRandPhrase("Certo.","Certo.","Não se preocupe, estou guardando isso...");
			link.l1.go = "exit";
		break;  

	}
}
