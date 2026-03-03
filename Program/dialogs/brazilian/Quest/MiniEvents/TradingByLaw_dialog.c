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

		case "Kristian":
			dialog.text = "Bem-vindo ao meu humilde lar! Sou Christian. Christian Deluce, ao seu dispor. O que traz você até minha porta?";
			link.l1 = "O nome é Capitão "+GetFullName(pchar)+". Estou procurando adquirir uma boa quantidade de bebidas alcoólicas. Creio que fui claro?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "O quê??? Quem espalharia tais mentiras? É um grande mal-entendido, eu lhe garanto! Não negocio com bebidas alcoólicas de espécie alguma!";
			link.l1 = "Ora, ora... Parece que encontrei exatamente quem eu procurava.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Ó céus, não-não-não! Que acusações são essas! Contrabando de bebidas? Eu? Eu... eu apenas, hã, quero dizer... Muito bem, admito que tenho algumas bebidas, mas tudo perfeitamente legal! Só forneço refrescos para cidadãos particulares, ah... para festas e pequenas reuniões sociais!";
			link.l1 = "Por que esse tremor todo, bom homem? Não venho como seu carcereiro, mas como seu benfeitor. Sua sorte pode mudar, e minha bolsa ficar um pouco mais pesada com alguns dobrões nesse acordo.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Eu? N-nervoso? Que absurdo! Por que eu ficaria nervoso? Sou um homem de caráter impecável – minha casa fica à sombra da residência do governador! Não quebro nenhuma lei, juro pela minha honra!";
			link.l1 = "Então você não está envolvido no comércio de bebidas? Que pena, de verdade. Vim aqui com uma oportunidade de lucro considerável. Daquelas quantias em dobrões que um simples comerciante clandestino mal consegue imaginar. Mas já que você não é a pessoa que procuro, não vou incomodar mais e vou seguir meu caminho. A menos que...?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Ah... espere um instante... "+GetAddress_Form(NPChar)+"... me perdoe, minha cabeça voa como gaivotas na tempestade, acabei esquecendo seu nome distinto.";
			link.l1 = "Capitão "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", para ser sincero, eu... quer dizer... talvez eu saiba onde está a pessoa que você procura. Eu poderia transmitir a essa pessoa... sua proposta generosa.";
			link.l1 = "Revezar? Só pode estar brincando. Você realmente acha que assuntos tão delicados assim deveriam passar por mãos desnecessárias?";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "Você fala a verdade. Mas... que Deus me ajude... o dado está lançado... sim, sou mesmo o seu homem.";
			link.l1 = "Agora nos entendemos, Christian. A taverna está enfrentando uma séria falta de bebidas, e acredito que ambos podemos lucrar bastante com essa situação.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Capitão, estou bem ciente das aflições do estalajadeiro. O povo tem batido à minha porta, e isso me assusta a continuar com meu modesto ofício – agora há olhos demais me vigiando. Eu tinha esperança de que talvez você... bem, uma pessoa da sua posição pudesse...";
			link.l1 = "Por que você mesmo não procura o estalajadeiro para oferecer suas mercadorias?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "Ele... ele preferiria abraçar um leproso do que fazer negócios comigo. Aquele tolo pomposo só sente desprezo pelos humildes comerciantes como eu.";
			link.l1 = "De fato, a reputação dele o precede. Ele pode desprezar suas ofertas diretamente. Mas apresentadas por mim – aí já é outra história.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Você se oferece para ser o intermediário? Acho esse acordo bem conveniente... Recentemente conseguimos uma carga de tamanho impressionante – nunca lidamos com tanta quantidade antes! Teria mantido minhas adegas abastecidas por pelo menos meio ano. Mas, pela graça de Deus Todo-Poderoso, escapamos por pouco de sermos descobertos\nAinda não entendo como conseguimos passar pela rede do governador. Arriscar a sorte desse jeito uma segunda vez seria pura autodestruição.";
			link.l1 = "Então talvez seja hora de você sair um pouco das sombras. Não totalmente, veja bem, mas o suficiente para cuidar dos seus assuntos com menos perigo.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "D-dar um passo à frente? Mas... por quê, isso exige amigos influentes! E uma boa quantia de dinheiro! Pra quê tudo isso? Certamente você, um capitão com seu próprio navio, não pretende ancorar de vez e virar simples fornecedor de taverna, não é?";
			link.l1 = "Quanto a contatos, meu alcance vai onde o seu não chega. Sobre o dinheiro... o investimento deve ser modesto. E quanto à sua última preocupação – não tema. Você vai agir como meu agente nesses assuntos. Serei seu escudo, e você minha fonte constante. Nosso acordo será duradouro e vantajoso para ambos. Você ganha um cliente fiel, eu garanto mercadoria confiável. O que acha desse negócio?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Eu tinha certeza de que era uma armadilha elaborada. Mas, na verdade, sua proposta soa... realmente tentadora. Estabilidade, confiança... Jamais imaginei que a sorte sorriria para mim desse jeito. "+GetSexPhrase("Monsieur","Mademoiselle")+", você tem todo o meu apoio! Qual quantidade deseja comprar?";
			link.l1 = "Primeiro vamos estabelecer seu comércio de forma adequada, depois discutiremos os detalhes. Que quantidades de rum e vinho atualmente enfeitam seu estoque?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "Neste exato momento? Ah... Talvez devêssemos inspecionar minha adega, onde posso lhe dar um inventário preciso do que tenho.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Vamos ver... Que tesouros se escondem aqui embaixo? Ah, sim\nMeu estoque atual consiste exatamente em cem garrafas de rum de primeira e cem garrafas de vinho excelente.";
			link.l1 = "Um começo justo, eu diria. Assim que resolvermos suas dificuldades com importação, você conseguiria manter essas entregas todo mês, sem falhar?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Com toda certeza, Capitão! Não, eu conseguiria lidar com o triplo, não-não... quatro vezes essa quantidade! Não haverá atrasos – sempre manterei reservas de sobra, garantindo que qualquer contratempo seja rapidamente resolvido sem afetar seu suprimento.";
			link.l1 = "Diga seu preço por esta carga.";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "Eu consideraria um pagamento justo assim: dez dobrões por cada dez garrafas de vinho e três dobrões para cada dez garrafas de rum. No total, cento e trinta dobrões pela carga completa.";
			link.l1 = "Muito bem. Vou conversar com o estalajadeiro e volto já.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Capitão, quais são as novidades? Como foi sua conversa com o estalajadeiro?";
			link.l1 = "Ainda não falei com ele. Esse é meu próximo destino.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "Como foi, Capitão? Conseguiu chegar a um acordo com o estalajadeiro?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Fiz um excelente trabalho, Christian. Ele vai comprar esta e todas as próximas remessas por duzentos e quarenta dobrões. Pela primeira carga, vou te pagar os cento e trinta que pediu e ficar com o resto como minha recompensa. Mas os lucros futuros serão todos seus.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Fiz um bom negócio, Christian. Ele vai comprar esta e as próximas remessas por duzentos dobrões. Pela primeira, vou te pagar os cento e trinta que você pediu e ficar com a diferença como compensação justa. Todos os lucros futuros serão só seus.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "Isso é uma notícia incrível, Capitão! Nunca imaginei conseguir um acordo desses – muito obrigado! Mas... será que você não foi rápido demais? O governador... eu... quer dizer...";
			link.l1 = "O governador está bem ciente. De agora em diante, você vai pagar uma taxa mensal de cem dobrões e apresentar relatórios comerciais adequados.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "Inacreditável! Como você conseguiu isso, Capitão? O governador é um homem rígido, e um inimigo feroz dos contrabandistas...";
			link.l1 = "É isso mesmo, Christian – ele é contra o comércio ilegal, não contra negócios honestos. Ele me ouviu e deixou bem claras as condições para vender bebida na ilha. Agora você vai trabalhar sob o meu nome. Se fizer besteira, a culpa cai tanto sobre mim quanto sobre você. Então não me decepcione, ou eu vou atrás de você até no além.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "Eu juro, Capitão, você não vai se arrepender disso!";
			link.l1 = "Agora precisamos resolver as coisas com o estalajadeiro, e depois acertaremos os detalhes do nosso acordo.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Claro, Capitão. Está pronto para levar a carga agora? Vai custar cento e trinta doblões.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Sim, aqui estão seus dobrões.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "No momento, estou sem o dinheiro necessário. Espere aqui — voltarei com o pagamento.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Capitão! Voltou para buscar as mercadorias? O preço continua cento e trinta dobrões.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "De fato, consegui! Aqui está o seu pagamento.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Infelizmente, ainda não tenho o dinheiro. Voltarei mais tarde.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Muito obrigado! Pegue-os! Cem garrafas de vinho e cem garrafas de rum, como prometido.";
			link.l1 = "Minha tripulação vai cuidar da carga. Enquanto isso, preciso conversar com o estalajadeiro.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Você voltou tão rápido! Diga-me, nosso acordo correu bem?";
			link.l1 = "Tudo correu de forma admirável, Christian. O dono da taverna vai precisar de remessas idênticas duas vezes por mês. Mantenha um fluxo constante de bebidas para o estabelecimento dele, e logo você vai se despedir até da ideia de necessidade.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Capitão... você... é como se a própria Providência tivesse guiado você até a minha porta! Um verdadeiro milagre se desenrolou diante de mim – mal posso acreditar na minha sorte! Que fiz eu para merecer tamanha bondade? Palavras não bastam para expressar minha gratidão!";
			link.l1 = "Eu, porém, posso lhe esclarecer, Christian. Todo mês, você vai reservar uma parte selecionada das suas melhores mercadorias exclusivamente para que eu as compre, sem oferecer a nenhum outro comprador. Vou adquiri-las pelos preços que você indicar – dez dobrões por cada dez garrafas de vinho e três dobrões por cada dez de rum.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "Seria um enorme prazer para mim, "+pchar.name+", para reservar mercadorias só para você! Dou minha palavra de honra, nunca vou te decepcionar! De quantas garrafas precisa? Cinquenta? Cem talvez? Diga quanto quiser!";
			link.l1 = "Essas quantidades excedem minhas necessidades atuais. Vinte garrafas de cada serão mais que suficientes. Caso eu precise de mais, avisarei imediatamente.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Certamente, certamente! Então está combinado – vinte garrafas de vinho e vinte de rum por vinte e seis dobrões. No décimo quinto dia de cada mês, sua mercadoria estará à sua espera. Ficarei honrado com sua presença sempre que desejar aparecer, mesmo que seja apenas para trocar algumas palavras!";
			link.l1 = "Excelente! Resta apenas um último ponto importante, Christian. Apostei minha reputação na sua integridade. Não me decepcione, ou vai arcar com as consequências.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "Eu... que sugestão você faz, capitão... certamente você... não-não, jamais vou decepcionar! Tudo será conduzido com a mais absoluta correção, juro pela minha alma!";
			link.l1 = "Então até que nossos caminhos se cruzem novamente!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Seu intrometido "+GetSexPhrase("cur","vagabunda")+"! Nunca te ensinaram que se meter em assuntos que não são seus só traz desgraça?";
			link.l1 = "Foi você quem atacou meu navio sem ser convidado, e agora ainda tem a ousadia de me acusar de intromissão? Será que a loucura tomou conta da sua cabeça de vez?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Maldição, que raio caia no meu mastro de vante! Então é você, "+GetSexPhrase("moleque miserável","vadia inútil")+", não faz a menor ideia dos problemas em que se meteu? Achou mesmo que os suprimentos da taverna sumiram por acaso?";
			link.l1 = "Você assume a responsabilidade por ter reduzido aquela destilaria a cinzas?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ha-ha, finalmente a verdade atravessa esse seu crânio duro, que uma bala de corrente me rasgue por dentro! Fui eu mesmo, sim! Aquele fornecedor já estava enraizado demais no negócio. Mas como você pode ver, nunca deixo de derrotar meus rivais. E você vai ter o mesmo destino, que a metralha faça tiras das minhas velas!";
			link.l1 = "Muito divertido. Então vamos ver do que você é capaz, que as feras de Netuno devorem seu cadáver! Ha-ha!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "Saudações, "+pchar.name+"! Que ventos favoráveis trouxeram você até a minha porta?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Bom dia, Christian. Minha mercadoria está pronta?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Bom dia, Christian. Só queria me certificar de que tudo está correndo bem com você. Não vou incomodá-lo mais por agora.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Com certeza, Capitão! O senhor duvida, nem que seja um pouco, da minha dedicação?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Nem por um instante, Christian. Aqui está o seu pagamento, conforme combinado. Agora vou pegar minhas bebidas.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Nem um pouco. Infelizmente, minha bolsa está lamentavelmente vazia no momento. Voltarei quando estiver melhor preparado.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Com certeza, Capitão! O senhor duvida, nem que seja por um instante, do meu empenho?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Nem por um instante, Christian. Aqui estão seus dobrões, conforme combinado. Agora vou tomar posse dos meus barris.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Nem um pouco. Infelizmente, estou sem dinheiro no momento. Voltarei quando minha bolsa estiver devidamente cheia.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, quero aumentar meu pedido regular. Cem garrafas de rum e vinho por mês, para ser exato.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, gostaria de reconsiderar expandir nosso acordo.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Excelente. Como sempre, novos estoques estarão à sua disposição no dia quinze. Aguardo ansiosamente sua próxima visita.";
			link.l1 = "Pode contar com o meu retorno. Até que nossos caminhos se cruzem novamente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Capitão, embora tal expansão fosse muito bem-vinda para os negócios, não deixa de envolver um custo considerável! Maiores quantidades exigem mais trabalhadores, armazéns maiores, fretamento de navios mais espaçosos... Sem o investimento adequado, jamais conseguiria garantir a entrega pontual de pedidos tão grandes.";
			link.l1 = "E quanto custariam tais arranjos? Que investimento garantiria o bom funcionamento desse empreendimento ampliado?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Cinquenta mil pesos seriam suficientes. Quaisquer custos adicionais eu cubro do meu próprio bolso.";
			link.l1 = "Cinquenta mil? Por Deus... isso não é pouca coisa. Tem certeza de que não consegue se virar com um valor mais modesto?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "Com profundo pesar, Capitão, devo insistir que esta quantia representa o mínimo absoluto. Se tentarmos economizar, nossa empreitada pode... digamos, sair desastrosamente do rumo. Tais calamidades não serviriam nem aos seus interesses, nem aos meus, ouso dizer.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Aqui está o seu pagamento completo. Espero que mostre ser digno de tanta confiança, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Pensando melhor, Christian, talvez essa expansão seja um pouco precipitada. Vamos voltar a esse assunto quando as circunstâncias forem mais favoráveis.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Como desejar, Capitão. Se mudar de ideia, continuo à sua disposição.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Capitão, notícias esplêndidas! Trouxe as cinquenta mil em prata para prosseguirmos imediatamente?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Aqui está o seu pagamento completo. Veja se mostra ser digno de tanta confiança, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "No momento, meus cofres não têm os fundos necessários. Voltarei quando minhas finanças permitirem tal investimento.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Por minha honra, "+pchar.name+", você não vai se arrepender dessa decisão! Vou começar os preparativos sem demora. A partir da sua próxima coleta, você poderá receber cem garrafas do melhor rum e a mesma quantidade de vinho excelente, tudo pela soma de cento e trinta doblões por remessa completa.";
			link.l1 = "Muito satisfatório. Mas lembre-se – aja com a máxima discrição em tudo. Sua conduta reflete diretamente sobre minha reputação nestas águas.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}